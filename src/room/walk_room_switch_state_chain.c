#include "types.h"
#include "room_script.h"

// Room-script VM entry (see docs/formats/room_scripts.md). Walks chain `chain`
// record by record until it ends or a handler yields (run state 2). A handler that
// queues a jump through g_bRoomScriptPendingChain starts that chain next; unless the
// opcode is 0x40 the caller is saved and the walk returns to it once the callee ends.
// resumeFromSaved instead continues the caller saved on top of the call stack.
void WalkRoomSwitchStateChain_candidate(u32 chain, s32 resumeFromSaved)
{
    RoomScriptRecord *pRecord;
    RoomScriptRecord *pNext;
    s32 pushedFrames;
    u32 step;
    RoomScriptTable *pTable;
    u32 slotOffset;
    u16 *pChainOffsets;

    if (g_dwRoomScriptRunState == 4)
        return;

    pushedFrames = 0;
    g_bRoomScriptPendingChain = chain;
    if (g_dwRoomScriptRunState == 2)
        g_dwRoomScriptRunState = 3;
    else
        g_dwRoomScriptRunState = 0;

    while (1)
    {
        g_bRoomScriptCurrentRow = g_bRoomScriptPendingChain;
        g_bRoomScriptPendingChain = 0xff;
        // First record of the chain, or where the saved caller left off.
        if (resumeFromSaved != 0)
        {
            resumeFromSaved = 0;
            pNext = g_aRoomScriptCallStack[g_bRoomScriptCallStackDepth + 1].pReturn;
        }
        else
        {
            pTable = g_pRoomSwitchStateObjectTable;
            slotOffset = g_bRoomScriptCurrentRow * 2;
            pChainOffsets = pTable->awChainOffsets;
            pNext = (RoomScriptRecord *)((u8 *)pTable + *(u16 *)((u8 *)pChainOffsets + slotOffset));
        }

        // Dispatch records through the opcode handler table.
        do
        {
            pRecord = pNext;
            if (pRecord->dwOpcode == 0)
                step = g_abRoomScriptOpcodeLengths[0];
            else
            {
                g_pRoomScriptNextRecord = (RoomScriptRecord *)((u8 *)pRecord + g_abRoomScriptOpcodeLengths[pRecord->dwOpcode]);
                if (g_dwRoomScriptRunState == 1)
                    g_bRoomScriptYieldOpcode = pRecord->dwOpcode;
                g_apRoomScriptOpcodeHandlers[pRecord->dwOpcode](pRecord);
                step = g_abRoomScriptOpcodeLengths[pRecord->dwOpcode];
            }
            pNext = (RoomScriptRecord *)((u8 *)pNext + step);

            // A handler queued a jump to another chain.
            if (g_bRoomScriptPendingChain != 0xff)
            {
                if (pRecord->dwOpcode != 0x40)
                {
                    g_bRoomScriptCallStackDepth++;
                    g_aRoomScriptCallStack[g_bRoomScriptCallStackDepth].bRow = chain;
                    g_aRoomScriptCallStack[g_bRoomScriptCallStackDepth].pReturn = pNext;
                    pushedFrames++;
                }
                if (g_bRoomScriptPendingChain != 0xff)
                    break;
            }
        } while (pRecord->dwOpcode != 0 && g_dwRoomScriptRunState != 2);

        if (g_bRoomScriptPendingChain == 0xff)
            break;
    }

    // Remember where a yielded walk stops.
    if (g_dwRoomScriptRunState == 2 && g_pRoomScriptYieldContinuation == NULL)
        g_pRoomScriptYieldContinuation = pNext;

    if (pRecord->dwOpcode != 0)
        return;

    // Chain ended: return to the innermost caller this walk saved.
    if (g_bRoomScriptCallStackDepth != 0 && pushedFrames != 0)
    {
        g_bRoomScriptCallStackDepth -= pushedFrames;
        WalkRoomSwitchStateChain_candidate(g_aRoomScriptCallStack[g_bRoomScriptCallStackDepth + 1].bRow, 1);
    }

    if (pRecord->dwOpcode != 0)
        return;

    if (g_dwRoomScriptRunState == 3)
        g_dwRoomScriptRunState = 2;
}

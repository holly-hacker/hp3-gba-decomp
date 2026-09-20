#include "types.h"
#include "room_script.h"

// Room-script VM entry that continues the walk stopped at g_pRoomScriptYieldContinuation.
// Otherwise identical to WalkRoomSwitchStateChain_candidate, except that jumps save the
// chain being walked (g_bRoomScriptCurrentRow) as the caller.
void ResumeRoomSwitchStateChain_candidate(void)
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

    g_dwRoomScriptRunState = 1;
    pushedFrames = 0;
    pNext = g_pRoomScriptYieldContinuation;

    while (1)
    {
        if (pNext != g_pRoomScriptYieldContinuation)
        {
            g_bRoomScriptCurrentRow = g_bRoomScriptPendingChain;
            g_bRoomScriptPendingChain = 0xff;
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
                    g_aRoomScriptCallStack[g_bRoomScriptCallStackDepth].bRow = g_bRoomScriptCurrentRow;
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
    if (g_dwRoomScriptRunState == 2)
        g_pRoomScriptYieldContinuation = pNext;
    else
        g_pRoomScriptYieldContinuation = NULL;

    if (pRecord->dwOpcode != 0)
        return;

    // Chain ended: return to the innermost caller this walk saved.
    if (g_bRoomScriptCallStackDepth != 0 && pushedFrames != 0)
    {
        g_bRoomScriptCallStackDepth -= pushedFrames;
        WalkRoomSwitchStateChain_candidate(g_aRoomScriptCallStack[g_bRoomScriptCallStackDepth + 1].bRow, 1);
    }
}

#pragma once

#include "types.h"
#include "room_script.h"

// The room-script conditional branch shared by the Goto* opcodes. Handlers that
// test a fixed condition inline it; src/room/compare_and_branch_room_script.c
// defines ROOM_SCRIPT_BRANCH_LINKAGE as empty to emit the out-of-line copy that
// the compare opcodes call.
#ifndef ROOM_SCRIPT_BRANCH_LINKAGE
#define ROOM_SCRIPT_BRANCH_LINKAGE extern inline
#endif

// Compares lhs against rhs with cmpOp and queues the taken side's chain in
// g_bRoomScriptPendingChain (a zero falseChain means no jump), then respawns the
// taken side's object row if ShouldRunRoomScriptRow_candidate allows it.
ROOM_SCRIPT_BRANCH_LINKAGE void CompareAndBranchRoomScript(u8 lhs, u32 cmpOp, u8 rhs, u8 trueChain, u8 falseChain,
                                                           u8 trueRow, u8 falseRow)
{
    u32 result;

    g_bRoomScriptPendingChain = 0xff;
    if (falseChain == 0)
        falseChain = 0xff;

    switch (cmpOp)
    {
    case RoomScriptCompareEqual:
        result = lhs == rhs;
        break;
    case RoomScriptCompareNotEqual:
        result = lhs != rhs;
        break;
    case RoomScriptCompareGreater:
        result = lhs > rhs;
        break;
    case RoomScriptCompareGreaterEqual:
        result = lhs >= rhs;
        break;
    case RoomScriptCompareLess:
        result = lhs < rhs;
        break;
    case RoomScriptCompareLessEqual:
        result = lhs <= rhs;
        break;
    default:
        result = 0;
        break;
    }

    if (result)
    {
        g_bRoomScriptPendingChain = trueChain;
        if (ShouldRunRoomScriptRow_candidate(trueRow))
            RespawnRoomObjectsInRow_candidate(trueRow);
    }
    else
    {
        g_bRoomScriptPendingChain = falseChain;
        if (ShouldRunRoomScriptRow_candidate(falseRow))
            RespawnRoomObjectsInRow_candidate(falseRow);
    }
}

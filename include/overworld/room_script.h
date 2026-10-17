#pragma once

#include "types.h"
#include "actor.h"

// Room-script VM; see docs/formats/room_scripts.md. A chain is a sequence of
// records, each starting with a u32 opcode (0 ends the chain).

// Chain index -> chain offset table, reached through g_pRoomScriptChainTable.
typedef struct RoomScriptTable {
    u16 wHeader;
    u16 awChainOffsets[0];
} RoomScriptTable;

// A record: the opcode word followed by operand bytes; the length table gives
// the total size per opcode.
typedef union RoomScriptOperands {
    u8 ab[16];
    s8 asb[16];
    u16 aw[8];
    s16 asw[8];
    u32 adw[4];
} RoomScriptOperands;

typedef struct RoomScriptRecord {
    u32 dwOpcode;
    RoomScriptOperands operand;
} RoomScriptRecord;

// One saved caller of a nested chain call.
typedef struct RoomScriptCallFrame {
    RoomScriptRecord *pReturn;
    u8 bRow;
    u8 pad[3];
} RoomScriptCallFrame;

typedef void (*RoomScriptOpcodeHandler)(RoomScriptRecord *pRecord);

// 0 = idle, 1 = resuming a yielded chain, 2 = yielded (the walk stops after
// the current record), 3 = walking while a yielded chain is pending, 4 = disabled.
extern u32 g_dwRoomScriptRunState;
extern RoomScriptTable *g_pRoomScriptChainTable;
// Chain the VM is walking; 0xFF in g_bRoomScriptPendingChain means no jump pending.
extern u8 g_bRoomScriptCurrentChain;
extern u8 g_bRoomScriptPendingChain;
// Record after the one being dispatched.
extern RoomScriptRecord *g_pRoomScriptNextRecord;
// Opcode the walk yielded on, latched while resuming.
extern u8 g_bRoomScriptYieldOpcode;
extern RoomScriptRecord *g_pRoomScriptYieldContinuation;
extern u8 g_bRoomScriptCallStackDepth;
extern RoomScriptCallFrame g_aRoomScriptCallStack[];

extern u32 GetPartyMasterStatsSlot_candidate(u32 characterId);
extern u8 g_abRoomScriptExitParams_candidate[2];
extern void SyncFollowerLevelToLeader_candidate(u32 characterId);
extern void GrantPartyExperience_candidate(u32 xp);
extern void CyclePartyLeaderSelection_candidate(Actor *pLeader, u32 direction);
// Allocates a RoomActorType_ScriptEffect actor of the given kind (Actor+0x8C),
// ticked by the kind's entry in the script-effect tick table. Kind 1 (the delayed respawn timer,
// tick at 0x080200FC) counts dwStateTimer down, then runs the row/chain, or resumes the yielded
// chain if the walk yielded on a delayed-respawn opcode.
extern Actor *SpawnScriptEffectActor(u32 kind);
extern void sub_080236DC(u32 characterId);
extern void sub_080237D0(u32 arg0);

// Chain and actor row queued by PlayCutscene for the transition back.
extern u8 g_bPendingRoomScriptChain;
extern u8 g_bPendingRoomScriptRow;

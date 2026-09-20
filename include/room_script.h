#pragma once

#include "types.h"
#include "object.h"

// Room-script VM; see docs/formats/room_scripts.md. A chain is a sequence of
// records, each starting with a u32 opcode (0 ends the chain).

// Chain index -> chain offset table, reached through g_pRoomSwitchStateObjectTable.
typedef struct RoomScriptTable {
    u16 wHeader;
    u16 awChainOffsets[1];
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

extern const RoomScriptOpcodeHandler g_apRoomScriptOpcodeHandlers[93];  // ROM 0x0805BA8C
// Total record length in bytes, opcode word included, per opcode.
extern const u8 g_abRoomScriptOpcodeLengths[93];  // ROM 0x0805EB34

// 0 = idle, 1 = resuming a yielded chain, 2 = yielded (the walk stops after
// the current record), 3 = walking while a yielded chain is pending, 4 = disabled.
extern u32 g_dwRoomScriptRunState;
extern RoomScriptTable *g_pRoomSwitchStateObjectTable;
// Chain the VM is walking; 0xFF in g_bRoomScriptPendingChain means no jump pending.
extern u8 g_bRoomScriptCurrentRow;
extern u8 g_bRoomScriptPendingChain;
// Record after the one being dispatched.
extern RoomScriptRecord *g_pRoomScriptNextRecord;
// Opcode the walk yielded on, latched while resuming.
extern u8 g_bRoomScriptYieldOpcode;
extern RoomScriptRecord *g_pRoomScriptYieldContinuation;
extern u8 g_bRoomScriptCallStackDepth;
extern RoomScriptCallFrame g_aRoomScriptCallStack[];

// Starts chain `chain`; with resumeFromSaved it continues the saved caller
// frame on top of the call stack instead.
extern void WalkRoomSwitchStateChain_candidate(u32 chain, s32 resumeFromSaved);
extern void ResumeRoomSwitchStateChain_candidate(void);
extern void RespawnRoomObjectsInRow_candidate(u32 row);

// Live object at tile (x, y); every script targets (0, 0xFF), the player slot.
extern Object *GetRoomObjectField_candidate(u32 x, u32 y);

extern void CompareAndBranchRoomScript_candidate(u32 lhs, u32 cmpOp, u32 rhs, u32 trueChain, u32 falseChain,
                                                 u32 trueRow, u32 falseRow);
// Whether chain row `row` may run; false for 0, true from 2 up, and for 1 only
// while g_wRoomResourceFlags_candidate bit 0 is set.
extern u32 ShouldRunRoomScriptRow_candidate(u32 row);
extern u16 GetRoomRowColumnCount_candidate(u32 row);
extern u32 GetPartyMasterStatsSlot_candidate(u32 characterId);
extern u8 IsFolioPageGroupUnlocked_candidate(u32 pageGroupId);
extern void LevelUpPartyMember_candidate(u32 fighterType);
extern u8 g_abRoomScriptExitParams_candidate[2];
extern void SyncFollowerLevelToLeader_candidate(u32 characterId);
extern void sub_08024980(u32 characterId);  // fills follower slot 0
extern void sub_080249A4(u32 characterId);  // fills follower slot 1
extern Object *sub_0802F6C0(u32 characterId);
extern void sub_08024A30(u32 rewardId);
extern void sub_08024A88(u32 rewardId);
extern void RestorePendingCameraFocus_candidate(void *pFocus);
extern void *g_pPendingCameraFocus_candidate;
extern void GrantPartyExperience_candidate(u32 xp);
extern void CyclePartyLeaderSelection_candidate(Object *pLeader, u32 direction);
extern void RespawnRowAndRunChain_candidate(u32 respawnRow, u32 chainRow);
extern void WriteRoomBgTile_candidate(u32 x, u32 y, u32 tileId, u32 layer);
extern void ConsumeBattleItemSlot(u32 itemId, u32 count);
extern void sub_080236DC(u32 characterId);
extern void sub_080237D0(u32 arg0);

// Chain and object row queued by PlayCutscene for the transition back.
extern u8 g_bPendingRoomScriptChain;
extern u8 g_bPendingRoomScriptRow;

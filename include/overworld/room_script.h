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

extern u32 GetPartyMasterStatsSlot_candidate(u32 characterId);
// Levels a recruited Hermione or Ron up to around Harry's level.
extern void CatchUpToHarryLevel(u8 characterId);
extern void CycleSelectedFieldSpell(Actor *pLeader, u8 direction);
// Allocates a RoomActorType_ScriptEffect actor of the given kind (ScriptEffectKind_*),
// ticked by g_apfnScriptEffectActorTicks[kind].
extern Actor *SpawnScriptEffectActor(u32 kind);
// Removes a character from the party; removing the leader promotes the followers.
extern void RemovePartyMember(u8 characterId);
// Changes the leader's character and sprite, keeping the actor.
extern void SetPartyLeaderCharacter(u8 characterId);

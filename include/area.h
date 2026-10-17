#pragma once

#include "types.h"
#include "actor.h"
#include "overworld/room_actor.h"
#include "overworld/room_blob.h"

// Area loading: builds the current room's runtime tables from its resource blob
// and runs its room-script chains; see docs/formats/rooms.md.

// Room tile actorType -> constructor table.
extern const RoomActorConstructor g_apRoomActorConstructors[ROOM_ACTOR_TYPE_COUNT];  // ROM 0x0804C054 (US)

// A player spawn point: a room blob header record, or a default record. FindRoomEntryPoint
// matches bEntryId and bIndex against its two arguments.
typedef struct RoomEntryPoint {
    s16 nX;
    s16 nY;
    u8 bEntryId;
    u8 bIndex;   // also indexes g_aDefaultRoomEntryPoints; both callers pass 0
    u8 bFacing;
    u8 pad_07;
} RoomEntryPoint;

// Used by FindRoomEntryPoint when the room has no record for the entry id.
extern const RoomEntryPoint g_aDefaultRoomEntryPoints[2];  // ROM 0x0804C08C (US)

extern void SpawnMissingRoomGroupActors(u32 row);
// Starts chain `chain`; with resumeFromSaved it continues the saved caller
// frame on top of the call stack instead.
extern void RunRoomScriptChain(u32 chain, s32 resumeFromSaved);
extern void ResumeRoomScriptChain(void);

extern u8 *BuildRoomActorTable(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut);
extern u8 *BuildRoomActorGroup(const RoomBlobTable *pTable, u8 *pOut, u8 index);
extern u8 *BuildRoomRouteTable(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut);
extern u8 *BuildRoomScriptChainTable(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut);
extern void InitRoomScriptState(void);
extern void ParseRoomResourceBlob(const RoomBlobHeader *pBlob);

extern void RespawnGroupAndRunChain(u32 respawnRow, u32 chainRow);
// Whether chain row `row` may run; false for 0, true from 2 up, and for 1 only
// while g_wRoomResourceFlags_candidate bit 0 is set.
extern u32 ShouldRunRoomIndex(u32 row);
extern u16 GetRoomGroupMemberCount(u32 row);
extern void *GetRoomActorStaticRecord(u8 bColumn, u8 bRow);
// Live actor at tile (x, y); every script targets (0, 0xFF), the player slot.
// x == 0 with y >= 0xFE selects a slot of the array at 0x03003358 instead of a tile; every
// script uses (0, 255).
extern Actor *GetRoomActorPtr(u32 x, u32 y);
extern void SetRoomActorPtr(Actor *actor, u8 col, u8 row);

// Waypoint routes in g_pRoomRouteTable; see docs/formats/rooms.md.
extern u8 GetRoomRouteWaypointCount(u8 route);  // waypoint count
extern IntPoint GetRoomRouteWaypointPos(u8 route, u8 waypoint);
extern void RunRoomRouteWaypointChain(u8 route, u8 waypoint);  // runs the waypoint's chain

extern void StopRoomScriptChains(void);
extern u8 GetRoomBlobStageVariant(u32 questState, const void *pRoomResourceBlob);

extern u8 *CopyRoomBlobHeaderRecords(const RoomBlobHeader *pBlob, const RoomBlobSubBlock *pVariant);
// Copies `size` bytes of static tile data to `pDst + 8`.
extern void CopyRoomActorStaticBytes(const u8 *pSrc, u8 *pDst, u8 size);
// Copies a warp trigger list ({u32 count, 8-byte records}); returns the end.
extern u8 *CopyRoomRouteWaypoints(const RoomBlobTable *pTable, u8 *pDst, u8 index);
// Copies a room-script chain up to and including its terminator; returns the end.
extern u8 *CopyRoomScriptChain(const RoomBlobTable *pTable, u8 *pDst, u8 index);
// Byte size of an offset array of `count` u16 entries, padded to a multiple of 4.
extern u16 GetRoomOffsetTableSize(u16 count);
// `size` rounded up to a multiple of 4.
extern u16 AlignRoomSizeTo4(u16 size);

// Three words zeroed whenever a type 10 or 12 actor is constructed.
extern u32 g_adwRoomActorUnkACState[3];
extern u16 g_wRoomResourceFlags_candidate;
// Chain the VM is walking; 0xFF in g_bRoomScriptPendingChain means no jump pending.
extern u8 g_bRoomScriptCurrentChain;
extern RoomScriptRecord *g_pRoomScriptYieldContinuation;
// Record after the one being dispatched.
extern RoomScriptRecord *g_pRoomScriptNextRecord;
extern u8 g_bRoomScriptCallStackDepth;
// Opcode the walk yielded on, latched while resuming.
extern u8 g_bRoomScriptYieldOpcode;
// Runtime buffer (0x2200 bytes) and the tables built inside it.
extern RoomBlobHeader *g_pRoomTableBuffer;
// Set by the room chain runner while it processes a chain; consumed (cleared)
// once per frame by HandleOverworldPauseMenuInput.
extern u32 g_dwRoomChainRanThisFrame_candidate;
extern RoomBlobTable *g_pRoomActorTable;
extern RoomBlobTable *g_pRoomRouteTable;
extern RoomScriptTable *g_pRoomScriptChainTable;
extern RoomScriptCallFrame g_aRoomScriptCallStack[];

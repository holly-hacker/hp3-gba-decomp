#pragma once

#include "types.h"

// Per-room resource blob. ParseRoomResourceBlob builds the room's runtime tables
// from it in one buffer, in the order header records, actor table, route table, script
// chain table.

// A player spawn point: a room blob header record, or a default record. FindRoomEntryPoint
// matches bEntryId and bIndex against its two arguments.
typedef struct RoomEntryPoint {
    s16 nX;
    s16 nY;
    u8 bEntryId;
    u8 bIndex;   // also indexes g_aDefaultRoomEntryPoints; both callers pass 0
    u8 bFacing;
    u8 bUnused;  // always 0xFF
} RoomEntryPoint;

// Blob start. wSize is the byte offset of the RoomBlobStageIndex that follows
// (4 + 8 * wRecordCount). The runtime buffer starts with a copy of this header.
typedef struct RoomBlobHeader {
    u16 wSize;
    u16 wRecordCount;
    RoomEntryPoint aRecords[0];
} RoomBlobHeader;

typedef struct RoomBlobVariantEntry {
    u16 wSubBlockOffset;  // from the blob start
    u8 abUnused[6];       // always 0
} RoomBlobVariantEntry;

// Selects the sub-block to use per story stage.
typedef struct RoomBlobStageIndex {
    u8 bVariantCount;
    u8 abStageToVariant[33];  // indexed by g_abQuestEventState[0]
    u16 wUnused;              // always 0xFFFF
    RoomBlobVariantEntry aEntries[0];
} RoomBlobStageIndex;

// Offset table: wCount, then wCount u16 offsets from the table start. The
// blob stores the count in a byte followed by a zero pad byte.
typedef struct RoomBlobTable {
    u16 wCount;
    u16 awOffsets[0];
} RoomBlobTable;

// Blob-side column of the actor table: the row count, then one static record size per row
// (the records follow, starting on a 4-byte boundary).
typedef struct RoomBlobColumn {
    u8 bCount;
    u8 bUnused;  // always 0
    u8 abRowSizes[0];
} RoomBlobColumn;

// One sub-block per variant; entry 0 is the default one.
typedef struct RoomBlobSubBlock {
    u16 wRouteTableOffset;
    u16 wScriptChainTableOffset;
    u16 wFlags;  // copied to g_wRoomVariantFlags; bit 0 puts the default sub-block's
                 // tables first
    u16 wEndOffset;  // unused; to the sub-block's end marker
    RoomBlobTable actorTable;  // inline at +8
} RoomBlobSubBlock;

// Each room's resource blob, in room table order.
extern const u8 Room00Blob[];
extern const u8 Room01Blob[];
extern const u8 Room02Blob[];
extern const u8 Room03Blob[];
extern const u8 Room04Blob[];
extern const u8 Room05Blob[];
extern const u8 Room06Blob[];
extern const u8 Room07Blob[];
extern const u8 Room08Blob[];
extern const u8 Room09Blob[];
extern const u8 Room10Blob[];
extern const u8 Room11Blob[];
extern const u8 Room12Blob[];
extern const u8 Room13Blob[];
extern const u8 Room14Blob[];
extern const u8 Room15Blob[];
extern const u8 Room16Blob[];
extern const u8 Room17Blob[];
extern const u8 Room18Blob[];
extern const u8 Room19Blob[];
extern const u8 Room20Blob[];
extern const u8 Room21Blob[];
extern const u8 Room22Blob[];
extern const u8 Room23Blob[];
extern const u8 Room24Blob[];
extern const u8 Room25Blob[];
extern const u8 Room26Blob[];
extern const u8 Room27Blob[];
extern const u8 Room28Blob[];
extern const u8 Room29Blob[];
extern const u8 Room30Blob[];
extern const u8 Room31Blob[];
extern const u8 Room32Blob[];
extern const u8 Room33Blob[];
extern const u8 Room34Blob[];
extern const u8 Room35Blob[];
extern const u8 Room36Blob[];
extern const u8 Room37Blob[];
extern const u8 Room38Blob[];
extern const u8 Room39Blob[];
extern const u8 Room40Blob[];
extern const u8 Room41Blob[];
extern const u8 Room42Blob[];
extern const u8 Room43Blob[];
extern const u8 Room44Blob[];
extern const u8 Room45Blob[];
extern const u8 Room46Blob[];
extern const u8 Room47Blob[];
extern const u8 Room48Blob[];
extern const u8 Room49Blob[];
extern const u8 Room50Blob[];
extern const u8 Room51Blob[];
extern const u8 Room52Blob[];
extern const u8 Room53Blob[];
extern const u8 Room54Blob[];

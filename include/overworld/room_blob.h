#pragma once

#include "types.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

// Per-room resource blob, see docs/formats/rooms.md. ParseRoomResourceBlob_candidate
// builds the room's runtime tables from it in one buffer, in the order
// header records, object table, warp trigger table, switch-state table.

typedef struct RoomBlobRecord {
    u32 dwWord0;
    u32 dwWord4;
} RoomBlobRecord;

// Blob start. wSize is the byte offset of the RoomBlobStageIndex that follows
// (4 + 8 * wRecordCount). The runtime buffer starts with a copy of this header.
typedef struct RoomBlobHeader {
    u16 wSize;
    u16 wRecordCount;
    RoomBlobRecord aRecords[0];
} RoomBlobHeader;

typedef struct RoomBlobVariantEntry {
    u16 wSubBlockOffset;  // from the blob start
    u8 abUnknown[6];
} RoomBlobVariantEntry;

// Selects the sub-block to use per story stage.
typedef struct RoomBlobStageIndex {
    u8 bVariantCount;
    u8 abStageToVariant[33];  // indexed by g_abQuestEventState[0]
    u16 wPad;
    RoomBlobVariantEntry aEntries[0];
} RoomBlobStageIndex;

// Offset table: wCount, then wCount u16 offsets from the table start. The
// blob stores the count in a byte followed by a zero pad byte.
typedef struct RoomBlobTable {
    u16 wCount;
    u16 awOffsets[0];
} RoomBlobTable;

// Blob-side column of the object table: the row count, then one static record size per row
// (the records follow, starting on a 4-byte boundary).
typedef struct RoomBlobColumn {
    u8 bCount;
    u8 bPad;
    u8 abRowSizes[0];
} RoomBlobColumn;

// One sub-block per variant; entry 0 is the default one.
typedef struct RoomBlobSubBlock {
    u16 wWarpTableOffset;
    u16 wSwitchTableOffset;
    u16 wFlags;  // bit 0 mirrored into g_wRoomResourceFlags_candidate
    u16 wUnknown6;
    RoomBlobTable objectTable;  // inline at +8
} RoomBlobSubBlock;

// Runtime buffer (0x2200 bytes) and the tables built inside it.
extern RoomBlobHeader *g_pRoomTableBuffer;
extern RoomBlobTable *g_pRoomObjectTable;
extern RoomBlobTable *g_pRoomWarpTriggerTable;

// Byte size of an offset array of `count` u16 entries, padded to a multiple of 4.
extern u16 sub_08005EC8(u16 count);
// `size` rounded up to a multiple of 4.
extern u16 sub_08005EE8(u16 size);
// Copies `size` bytes of static tile data to `pDst + 8`.
extern void sub_08005E18(const u8 *pSrc, u8 *pDst, u8 size);
// Copies a warp trigger list ({u32 count, 8-byte records}); returns the end.
extern u8 *sub_08005E40(const RoomBlobTable *pTable, u8 *pDst, u8 index);
// Copies a room-script chain up to and including its terminator; returns the end.
extern u8 *sub_08005E84(const RoomBlobTable *pTable, u8 *pDst, u8 index);

extern u8 *CopyRoomBlobHeaderRecords_candidate(const RoomBlobHeader *pBlob, const RoomBlobSubBlock *pVariant);
extern u8 *BuildRoomObjectTable_candidate(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut);
extern u8 *BuildRoomObjectColumn_candidate(const RoomBlobTable *pTable, u8 *pOut, u8 index);
extern u8 *BuildRoomWarpTriggerTable_candidate(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut);
extern u8 *BuildRoomSwitchStateObjectTable_candidate(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut);

extern void ParseRoomResourceBlob_candidate(const RoomBlobHeader *pBlob);

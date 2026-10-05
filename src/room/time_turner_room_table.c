#include "types.h"
#include "gen/graphics/rooms.h"
#include "overworld/room_blob.h"
#include "overworld/room.h"

// The room table entries of the two backgrounds of the Harry and Hermione Time-Turner
// cutscene. They reuse the resources of rooms 33 (hospital_wing) and 14 (path_to_hagrids_hut).
const RoomTableEntry g_aTimeTurnerCutsceneRoomTable[2] = {
    {
        .pBgTilemap0 = gRoom33BgMap0,
        .pBgLayer0Extra = gRoom33BgBlocks0,
        .pBgTilemap1 = gRoom33BgMap1,
        .pBgLayer1Extra = gRoom33BgBlocks1,
        .pBgTilemap2 = gRoom33BgMap2,
        .pBgLayer2Extra = gRoom33BgBlocks2,
        .pBgTilemap3 = gRoom33BgMap3,
        .pBgLayer3Extra = gRoom33BgBlocks3,
        .pCollisionBehaviorTable = gRoom33CollisionBehavior,
        .pCollisionTilemap = gRoom33CollisionMap,
        .pRoomResourceBlob = Room33Blob,
        .aBgResources = {{gRoom33TilesetA, gRoom33PaletteA}, {gRoom33TilesetB, gRoom33PaletteB}},
        .bDefaultMusicModule = 11,
    },
    {
        .pBgTilemap0 = gRoom14BgMap0,
        .pBgLayer0Extra = gRoom14BgBlocks0,
        .pBgTilemap1 = gRoom14BgMap1,
        .pBgLayer1Extra = gRoom14BgBlocks1,
        .pBgTilemap2 = gRoom14BgMap2,
        .pBgLayer2Extra = gRoom14BgBlocks2,
        .pBgTilemap3 = gRoom14BgMap3,
        .pBgLayer3Extra = gRoom14BgBlocks3,
        .pCollisionBehaviorTable = gRoom14CollisionBehavior,
        .pCollisionTilemap = gRoom14CollisionMap,
        .pRoomResourceBlob = Room14Blob,
        .aBgResources = {{gRoom14TilesetA, gRoom14PaletteA}, {gRoom14TilesetB, gRoom14PaletteB}},
        .bEncounterCountA = 12,
        .bEncounterCountB = 12,
        .bEncounterCountC = 12,
        .bDefaultMusicModule = 16,
    },
};

#include "types.h"
#include "gen/RoomGraphics.h"
#include "overworld/room.h"

// The room table entries of the two backgrounds of the Harry and Hermione Time-Turner
// cutscene. They reuse the resources of rooms 33 (hospital_wing) and 14 (path_to_hagrids_hut).
const RoomTableEntry g_aTimeTurnerCutsceneRoomTable[2] = {
    {
        .pBgTilemap0 = Room33BgMap0,
        .pBgLayer0Extra = Room33BgBlocks0,
        .pBgTilemap1 = Room33BgMap1,
        .pBgLayer1Extra = Room33BgBlocks1,
        .pBgTilemap2 = Room33BgMap2,
        .pBgLayer2Extra = Room33BgBlocks2,
        .pBgTilemap3 = Room33BgMap3,
        .pBgLayer3Extra = Room33BgBlocks3,
        .pCollisionBehaviorTable = Room33CollisionBehavior,
        .pCollisionTilemap = Room33CollisionMap,
        .pRoomResourceBlob = Room33Blob,
        .aBgResources = {{Room33TilesetA, Room33PaletteA}, {Room33TilesetB, Room33PaletteB}},
        .bDefaultMusicModule = 11,
    },
    {
        .pBgTilemap0 = Room14BgMap0,
        .pBgLayer0Extra = Room14BgBlocks0,
        .pBgTilemap1 = Room14BgMap1,
        .pBgLayer1Extra = Room14BgBlocks1,
        .pBgTilemap2 = Room14BgMap2,
        .pBgLayer2Extra = Room14BgBlocks2,
        .pBgTilemap3 = Room14BgMap3,
        .pBgLayer3Extra = Room14BgBlocks3,
        .pCollisionBehaviorTable = Room14CollisionBehavior,
        .pCollisionTilemap = Room14CollisionMap,
        .pRoomResourceBlob = Room14Blob,
        .aBgResources = {{Room14TilesetA, Room14PaletteA}, {Room14TilesetB, Room14PaletteB}},
        .bEncounterCountA = 12,
        .bEncounterCountB = 12,
        .bEncounterCountC = 12,
        .bDefaultMusicModule = 16,
    },
};

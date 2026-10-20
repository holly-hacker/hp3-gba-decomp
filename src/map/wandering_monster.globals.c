#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "gen/graphics/overworld.h"
#include "map.h"

// Spawn-terrain collision type per encounter kind; see GetEncounterKindTerrainType.
const u32 g_adwEncounterKindTerrainTypes[3] = { 0x1A, 0x20, 0x21 };

// The "?" silhouette shown for a wandering monster whose roster has an
// unanalyzed monster.
const ActorAssetRecord g_UnknownWanderingMonsterAsset = {
    (void *)gActorSprite2_020Tiles, (void *)gActorSprite2_020Frames, (void *)gActorSprite2_020Palette, 0,
};

// No reference found.
const ActorGfxRecord g_UnusedWanderingMonsterGfx = {
    (void *)gOverworldPlayer019Tiles,
    (void *)gOverworldPlayer019Frames,
};

const u8 g_WanderingMonsterAnimData[] = {
    ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
    ANIM_FRAME(4, 4), ANIM_FRAME(5, 4),
    ANIM_JUMP(0),
};

const u8 g_UnknownWanderingMonsterAnimData[] = {
    ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
    ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
    ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2),
    ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2),
    ANIM_FRAME(16, 2), ANIM_FRAME(17, 2), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2),
    ANIM_FRAME(20, 2), ANIM_FRAME(21, 2), ANIM_FRAME(22, 2), ANIM_FRAME(23, 2),
    ANIM_FRAME(24, 2), ANIM_FRAME(25, 2), ANIM_FRAME(26, 2), ANIM_FRAME(27, 2),
    ANIM_FRAME(28, 2), ANIM_FRAME(29, 2), ANIM_FRAME(30, 2),
    ANIM_JUMP(0),
};

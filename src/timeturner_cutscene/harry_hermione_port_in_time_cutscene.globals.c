#include "types.h"
#include "actor_anim.h"
#include "gen/graphics/overworld.h"
#include "timeturner_cutscene.h"

// Pixels; the camera focus start in each room of g_aTimeTurnerCutsceneRoomTable.
const IntPoint g_aHarryHermionePortInTimeCameraStart[2] = {
    { 313, 310 },
    { 810, 240 },
};

const HarryHermionePortInTimePosition g_aHarryHermionePortInTimeActorPos[2] = {
    { 303, 342, 323, 342 },
    { 800, 240, 820, 240 },
};

// Harry, then Hermione taking out and using the Time-Turner.
const ActorAssetRecord g_aHarryHermionePortInTimeActorAssets[2] = {
    { (void *)gHarryWalkTiles, (void *)gHarryWalkFrames, (void *)gHarryWalkPalette, 0 },
    { (void *)gHermioneTimeTurnerTiles, (void *)gHermioneTimeTurnerFrames, (void *)gHermioneTimeTurnerPalette, 0 },
};

// One animation per actor: Harry holds his first walk frame; Hermione plays the Time-Turner
// sequence once, with a sound midway.
const u8 g_aHarryHermionePortInTimeAnims[2][32] = {
    {
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {
        ANIM_FRAME(0, 10), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_SOUND(47), ANIM_FRAME(6, 3),
        ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3),
        ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(0, 3), ANIM_END,
    },
};

// Type unknown; no reference found.
const u8 g_abHarryHermionePortInTimeUnused[4] = { 4, 2, 0, 2 };

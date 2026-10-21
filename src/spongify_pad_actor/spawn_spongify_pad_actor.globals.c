#include "types.h"
#include "actor_anim.h"
#include "spongify_pad_actor.h"
#include "gen/graphics/overworld.h"

const ActorGfxRecord g_aRoomSpongifyPadSprites[4] = {
    { (void *)gSpongifyPadRug001Tiles, (void *)gSpongifyPadRug001Frames },
    { (void *)gSpongifyPadRug002Tiles, (void *)gSpongifyPadRug002Frames },
    { (void *)gSpongifyPadLeavesTiles, (void *)gSpongifyPadLeavesFrames },
    { (void *)gSpongifyEffectTiles, (void *)gSpongifyEffectFrames },
};

// Indexed by the actor's character id.
const ActorGfxRecord *const g_apRoomSpongifyPadAnimFrames[3] = {
    &g_aRoomSpongifyPadSprites[0],
    &g_aRoomSpongifyPadSprites[1],
    &g_aRoomSpongifyPadSprites[2],
};

const void *const g_apRoomSpongifyPadEffectData[3] = {
    gSpongifyPadLeavesPalette,
    gSpongifyPadLeavesPalette,
    gActorSprite2_115Palette,
};

// Command 5 is the animation of SpawnSpongifyPadEffect.
const u8 g_abRoomSpongifyPadAnimData[30] = {
    // 0
    ANIM_FRAME(0, 9), ANIM_FRAME(1, 9), ANIM_JUMP(0),
    0, 0, 0, 0,  // unused
    // 5
    ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
    ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_FRAME(24, 3), ANIM_FRAME(25, 3),
    ANIM_FRAME(42, 3), ANIM_END,
};

// The same sprites as g_SpongifyParticleGfx0/1, loaded into particle pool 2 entries 2 and 3.
const ActorGfxRecord g_RoomSpongifyPadParticleGfx0 = { (void *)gSpongifyParticle1Tiles, (void *)gSpongifyParticle1Frames };
const ActorGfxRecord g_RoomSpongifyPadParticleGfx1 = { (void *)gSpongifyParticle2Tiles, (void *)gSpongifyParticle2Frames };

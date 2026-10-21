#include "gen/graphics/overworld.h"
#include "actor_anim.h"
#include "pressure_pad_actor.h"

const ActorGfxRecord g_PushResetButtonSprite = {
    (void *)gButtonTiles, (void *)gButtonFrames,
};

// Indexed by the actor's character id.
const ActorGfxRecord *const g_apPushResetButtonSprites[2] = {
    &g_PushResetButtonSprite,
    &g_PushResetButtonSprite,
};

const void *const g_apPushResetButtonPalettes[2] = {
    gButtonPalette,
    gButtonPalette,
};

// Press animations, indexed by the actor's character id. The ANIM_EVENT at the
// fully pressed frame makes TickPushResetButtonActor respawn the targets.
const u8 g_aabPushResetButtonPressAnims[2][20] = {
    {
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_EVENT(0),
        ANIM_FRAME(2, 3), ANIM_FRAME(1, 3), ANIM_FRAME(0, 3), ANIM_END,
    },
    {
        ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_EVENT(0),
        ANIM_FRAME(6, 1), ANIM_FRAME(5, 1), ANIM_FRAME(4, 1), ANIM_END,
    },
};

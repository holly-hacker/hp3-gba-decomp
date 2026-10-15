#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "cursor.h"
#include "gen/graphics/menus.h"

const ActorAssetRecord g_MenuCursor8bppAsset = {
    (void *)gMenuSprite005Tiles, (void *)gMenuSprite005Frames, NULL, 0,
};

const ActorAssetRecord g_MenuCursorAsset = {
    (void *)gMenuSprite003Tiles, (void *)gMenuSprite003Frames, NULL, 0,
};

const ActorAssetRecord g_MenuCursorKind5Asset = {
    (void *)gMenuSprite006Tiles, (void *)gMenuSprite006Frames, (void *)gMenuSprite006Palette, 0,
};

const ActorAssetRecord g_MenuCursorSparkleAnimAsset = {
    (void *)gMenuSprite007Tiles, (void *)gMenuSprite007Frames, NULL, 1,
};

const u8 g_MenuCursorSparkleAnimData[] = {
    ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
    ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1),
    ANIM_JUMP(0),
};

const ActorAssetRecord g_MenuCursorParticleAsset = {
    (void *)gMenuSprite008Tiles, (void *)gMenuSprite008Frames, NULL, 1,
};

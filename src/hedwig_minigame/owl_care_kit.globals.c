#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "hedwig_minigame.h"
#include "gen/graphics/battle.h"
#include "gen/graphics/minigames/owl_care.h"

const ActorGfxRecord g_aOwlCareSprites[16] = {
    { (void *)gOwlCare001Tiles, (void *)gOwlCare001Frames },
    { (void *)gOwlCareCageDoorSpriteTiles, (void *)gOwlCareCageDoorSpriteFrames },
    { (void *)gOwlCareDroppingSpriteTiles, (void *)gOwlCareDroppingSpriteFrames },
    { (void *)gOwlCare004Tiles, (void *)gOwlCare004Frames },
    { (void *)gOwlCare005Tiles, (void *)gOwlCare005Frames },
    { (void *)gOwlCare006Tiles, (void *)gOwlCare006Frames },
    { (void *)gOwlCare007Tiles, (void *)gOwlCare007Frames },
    { (void *)gOwlCare008Tiles, (void *)gOwlCare008Frames },
    { (void *)gOwlCare009Tiles, (void *)gOwlCare009Frames },
    { (void *)gOwlCare010Tiles, (void *)gOwlCare010Frames },
    { (void *)gOwlCareExerciseBubbleSpriteTiles, (void *)gOwlCareExerciseBubbleSpriteFrames },
    { (void *)gOwlCareFeedBubbleSpriteTiles, (void *)gOwlCareFeedBubbleSpriteFrames },
    { (void *)gOwlCareGroomBubbleSpriteTiles, (void *)gOwlCareGroomBubbleSpriteFrames },
    { (void *)gOwlCarePetBubbleSpriteTiles, (void *)gOwlCarePetBubbleSpriteFrames },
    { (void *)gOwlCareCleanBubbleSpriteTiles, (void *)gOwlCareCleanBubbleSpriteFrames },
    { (void *)gOwlCareTeachBubbleSpriteTiles, (void *)gOwlCareTeachBubbleSpriteFrames },
};

const u32 g_dwOwlCareBg3Control = 0x2F83;
const u32 g_dwOwlCareBg2Control = 0x3083;
const u32 g_dwOwlCareBg1Control = 0x3E0A;
const u32 g_dwOwlCareBg0Control = 0x3F09;

const OwlCareBgFrame g_aOwlCareBgFrames[4] = {
    { 0, 0 },
    { 30, 0 },
    { 0, 20 },
    { 30, 20 },
};

const OwlCareActionStates g_aOwlCareActionStates[6] = {
    { OwlStateFed,     OwlStateRefuse,      OwlStateNeedFeed },
    { OwlStateCleaned, OwlStateIdleAnim2,   OwlStateNeedClean },
    { OwlStatePetted,  OwlStateRefusePet,   OwlStateNeedPet },
    { OwlStateGroomed, OwlStateRefuseGroom, OwlStateNeedGroom },
    { OwlStateTakeOff, OwlStateIdleAnim3,   OwlStateNeedExercise },
    { OwlStateTaught,  OwlStateRefuse,      OwlStateNeedTeach },
};

const OwlAnim g_aOwlAnims[OWL_STATE_COUNT] = {
    { &g_aOwlCareSprites[0], g_abOwlCareAnim00 },  // OwlStateIdle
    { &g_aOwlCareSprites[0], g_abOwlCareAnim01 },  // OwlStateIdleAnim1
    { &g_aOwlCareSprites[0], g_abOwlCareAnim02 },  // OwlStateIdleAnim2
    { &g_aOwlCareSprites[0], g_abOwlCareAnim03 },  // OwlStateIdleAnim3
    { &g_aOwlCareSprites[0], g_abOwlCareAnim04 },  // OwlStateIdleAnim4
    { &g_aOwlCareSprites[0], g_abOwlCareAnim05 },  // OwlStateIdleAnim5
    { &g_aOwlCareSprites[5], g_abOwlCareAnim06 },  // OwlStateFed
    { &g_aOwlCareSprites[9], g_abOwlCareAnim07 },  // OwlStateCleaned
    { &g_aOwlCareSprites[0], g_abOwlCareAnim08 },  // OwlStatePetted
    { &g_aOwlCareSprites[7], g_abOwlCareAnim09 },  // OwlStateGroomed
    { &g_aOwlCareSprites[4], g_abOwlCareAnim10 },  // OwlStateFlap
    { &g_aOwlCareSprites[8], g_abOwlCareAnim11 },  // OwlStateTaught
    { &g_aOwlCareSprites[0], g_abOwlCareAnim12 },  // OwlStateRefusePet
    { &g_aOwlCareSprites[3], g_abOwlCareAnim13 },  // OwlStateRefuseGroom
    { &g_aOwlCareSprites[0], g_abOwlCareAnim14 },  // OwlStateRefuse
    { &g_aOwlCareSprites[0], g_abOwlCareAnim03 },  // OwlStateNeedFeed
    { &g_aOwlCareSprites[0], g_abOwlCareAnim03 },  // OwlStateNeedClean
    { &g_aOwlCareSprites[0], g_abOwlCareAnim03 },  // OwlStateNeedPet
    { &g_aOwlCareSprites[0], g_abOwlCareAnim03 },  // OwlStateNeedGroom
    { &g_aOwlCareSprites[0], g_abOwlCareAnim03 },  // OwlStateNeedExercise
    { &g_aOwlCareSprites[0], g_abOwlCareAnim03 },  // OwlStateNeedTeach
    { &g_aOwlCareSprites[0], g_abOwlCareAnim21 },  // OwlStateUnusedA
    { &g_aOwlCareSprites[0], g_abOwlCareAnim22 },  // OwlStateUnusedB
    { &g_aOwlCareSprites[0], g_abOwlCareAnim23 },  // OwlStateUnusedC
    { &g_aOwlCareSprites[6], g_abOwlCareAnim24 },  // OwlStateMailDepart
    { &g_aOwlCareSprites[6], g_abOwlCareAnim25 },  // OwlStateMailReturn
    { &g_aOwlCareSprites[4], g_abOwlCareAnim26 },  // OwlStateLand
    { &g_aOwlCareSprites[4], g_abOwlCareAnim27 },  // OwlStateGlide
    { &g_aOwlCareSprites[4], g_abOwlCareAnim28 },  // OwlStateTakeOff
    { &g_aOwlCareSprites[6], g_abOwlCareAnim24 },  // OwlStateAway
    { &g_aOwlCareSprites[0], g_abOwlCareAnim00 },  // OwlStateMailDelivered
};

// By care action, Feed to Teach.
const ActorAssetRecord g_aOwlThoughtBubbleSprites[OwlStateNeedTeach - OwlStateNeedFeed + 1] = {
    { (void *)gOwlCareFeedBubbleSpriteTiles, (void *)gOwlCareFeedBubbleSpriteFrames, (void *)gOwlCareFeedBubblePalette, 0 },
    { (void *)gOwlCareCleanBubbleSpriteTiles, (void *)gOwlCareCleanBubbleSpriteFrames, (void *)gOwlCareCleanBubblePalette, 0 },
    { (void *)gOwlCarePetBubbleSpriteTiles, (void *)gOwlCarePetBubbleSpriteFrames, (void *)gOwlCarePetBubblePalette, 0 },
    { (void *)gOwlCareGroomBubbleSpriteTiles, (void *)gOwlCareGroomBubbleSpriteFrames, (void *)gOwlCareGroomBubblePalette, 0 },
    { (void *)gOwlCareExerciseBubbleSpriteTiles, (void *)gOwlCareExerciseBubbleSpriteFrames, (void *)gOwlCareExerciseBubblePalette, 0 },
    { (void *)gOwlCareTeachBubbleSpriteTiles, (void *)gOwlCareTeachBubbleSpriteFrames, (void *)gOwlCareTeachBubblePalette, 0 },
};

const ActorAssetRecord g_OwlCareCleanerSparkles = {
    (void *)gBattleEffect013Tiles, (void *)gBattleEffect013Frames, (void *)gBattleEffect013Palette, 3,
};

const u8 g_abOwlThoughtBubbleAnim[28] = {
    ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4), ANIM_FRAME(4, 4),
    ANIM_FRAME(5, 4), ANIM_FRAME(6, 30), ANIM_FRAME(5, 4), ANIM_FRAME(4, 4), ANIM_FRAME(3, 4),
    ANIM_FRAME(2, 4), ANIM_FRAME(1, 4), ANIM_FRAME(0, 4), ANIM_END,
};

const ActorAssetRecord g_OwlCageDoorSprite = {
    (void *)gOwlCareCageDoorSpriteTiles, (void *)gOwlCareCageDoorSpriteFrames, (void *)gOwlCareCageDoorPalette, 0,
};

const u8 *const g_apOwlCageDoorAnims[4] = {
    g_abOwlCageDoorAnim0,
    g_abOwlCageDoorAnim1,
    g_abOwlCageDoorAnim2,
    g_abOwlCageDoorAnim3,
};

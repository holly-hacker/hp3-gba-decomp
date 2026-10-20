#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "move.h"
#include "gen/graphics/overworld.h"

// Indexed by FieldSpell: the effect actor's sprite while g_aaFieldSpellCastAnims plays.
const ActorAssetRecord g_aFieldSpellCastAssets[8] = {
    { (void *)gFlipendoEffectTiles, (void *)gFlipendoEffectFrames, (const ObjPalette *)gFlipendoEffectPalette, 0 },  // Flipendo
    { (void *)gLumosCastTiles, (void *)gLumosCastFrames, (const ObjPalette *)gLumosCastPalette, 0 },  // Lumos
    { (void *)gReparoEffectTiles, (void *)gReparoEffectFrames, (const ObjPalette *)gReparoEffectPalette, 0 },  // Reparo
    { (void *)gAlohomoraEffectTiles, (void *)gAlohomoraEffectFrames, (const ObjPalette *)gAlohomoraEffectPalette, 0 },  // Alohomora
    { (void *)gGlaciusEffectTiles, (void *)gGlaciusEffectFrames, (const ObjPalette *)gGlaciusEffectPalette, 0 },  // Glacius
    { (void *)gSpongifyEffectTiles, (void *)gSpongifyEffectFrames, (const ObjPalette *)gSpongifyEffectPalette, 0 },  // Spongify
    { (void *)gDiffindoEffectTiles, (void *)gDiffindoEffectFrames, (const ObjPalette *)gDiffindoEffectPalette, 0 },  // Diffindo
    { (void *)gWingardiumLeviosaCastTiles, (void *)gWingardiumLeviosaCastFrames, (const ObjPalette *)gWingardiumLeviosaCastPalette, 0 },  // Wingardium Leviosa
};

// Indexed by FieldSpell: the effect actor's sprite once the cast animation ends.
const ActorAssetRecord g_aFieldSpellAssets[8] = {
    { (void *)gFlipendoEffectTiles, (void *)gFlipendoEffectFrames, (const ObjPalette *)gFlipendoEffectPalette, 0 },  // Flipendo
    { (void *)gLumosLightTiles, (void *)gLumosLightFrames, NULL, 0 },  // Lumos
    { (void *)gReparoEffectTiles, (void *)gReparoEffectFrames, (const ObjPalette *)gReparoEffectPalette, 0 },  // Reparo
    { (void *)gAlohomoraEffectTiles, (void *)gAlohomoraEffectFrames, (const ObjPalette *)gAlohomoraEffectPalette, 0 },  // Alohomora
    { (void *)gGlaciusEffectTiles, (void *)gGlaciusEffectFrames, (const ObjPalette *)gGlaciusEffectPalette, 0 },  // Glacius
    { (void *)gSpongifyEffectTiles, (void *)gSpongifyEffectFrames, (const ObjPalette *)gSpongifyEffectPalette, 0 },  // Spongify
    { (void *)gDiffindoEffectTiles, (void *)gDiffindoEffectFrames, (const ObjPalette *)gDiffindoEffectPalette, 0 },  // Diffindo
    { (void *)gWingardiumLeviosaEffectTiles, (void *)gWingardiumLeviosaEffectFrames, (const ObjPalette *)gWingardiumLeviosaEffectPalette, 0 },  // Wingardium Leviosa
};

// Indexed by FieldSpell: the sprite of g_pFieldSpellCompanionActor (only Lumos spawns one).
const ActorAssetRecord g_aFieldSpellCompanionAssets[8] = {
    { (void *)gFlipendoEffectTiles, (void *)gFlipendoEffectFrames, NULL, 0 },  // Flipendo
    { (void *)gLumosGlowTiles, (void *)gLumosGlowFrames, (const ObjPalette *)gLumosCastPalette, 0 },  // Lumos
    { (void *)gReparoEffectTiles, (void *)gReparoEffectFrames, NULL, 0 },  // Reparo
    { (void *)gAlohomoraEffectTiles, (void *)gAlohomoraEffectFrames, (const ObjPalette *)gAlohomoraEffectPalette, 0 },  // Alohomora
    { (void *)gGlaciusEffectTiles, (void *)gGlaciusEffectFrames, (const ObjPalette *)gGlaciusEffectPalette, 0 },  // Glacius
    { (void *)gSpongifyEffectTiles, (void *)gSpongifyEffectFrames, (const ObjPalette *)gSpongifyEffectPalette, 0 },  // Spongify
    { (void *)gDiffindoEffectTiles, (void *)gDiffindoEffectFrames, (const ObjPalette *)gDiffindoEffectPalette, 0 },  // Diffindo
    { (void *)gWingardiumLeviosaCastTiles, (void *)gWingardiumLeviosaCastFrames, (const ObjPalette *)gWingardiumLeviosaCastPalette, 0 },  // Wingardium Leviosa
};

// Lumos's particles, loaded as particle pool 2 entry 0.
const ActorGfxRecord g_LumosParticleGfx = { (void *)gLumosParticleTiles, (void *)gLumosParticleFrames };

// Reparo's particles, loaded as particle pool 2 entries 0-2.
const ActorGfxRecord g_ReparoParticleGfx0 = { (void *)gReparoParticle1Tiles, (void *)gReparoParticle1Frames };
const ActorGfxRecord g_ReparoParticleGfx1 = { (void *)gReparoParticle2Tiles, (void *)gReparoParticle2Frames };
const ActorGfxRecord g_ReparoParticleGfx2 = { (void *)gReparoParticle3Tiles, (void *)gReparoParticle3Frames };

// Glacius's particles, loaded as particle pool 2 entry 4.
const ActorGfxRecord g_GlaciusParticleGfx = { (void *)gGlaciusParticleTiles, (void *)gGlaciusParticleFrames };

// Spongify's particles, loaded as particle pool 2 entries 0-1.
const ActorGfxRecord g_SpongifyParticleGfx0 = { (void *)gSpongifyParticle1Tiles, (void *)gSpongifyParticle1Frames };
const ActorGfxRecord g_SpongifyParticleGfx1 = { (void *)gSpongifyParticle2Tiles, (void *)gSpongifyParticle2Frames };

// The player's sprite while Lumos is lit, and the one it gets back.
const ActorGfxRecord g_LumosPlayerGfx = { (void *)gHarryLumosTiles, (void *)gHarryLumosFrames };
const ActorGfxRecord g_LumosEndPlayerGfx = { (void *)gOverworldPlayer008Tiles, (void *)gOverworldPlayer008Frames };

// The player's standing frame for each facing, for g_LumosPlayerGfx and g_LumosEndPlayerGfx.
const u8 g_abLumosPlayerStandFrames[8] = { 4, 3, 2, 1, 0, 1, 2, 3 };

// The four-way direction of each facing: up, right, down, left.
const u8 g_abFacingDirection4[8] = { 0, 0, 1, 1, 2, 2, 3, 3 };

// Indexed by FieldSpell, with g_aFieldSpellCastAssets.
const u8 g_aaFieldSpellCastAnims[8][66] = {
    {  // Flipendo
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Lumos
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 3), ANIM_FRAME(2, 1), ANIM_FRAME(3, 2), ANIM_END,
    },
    {  // Reparo
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Alohomora
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Glacius
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Spongify
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1), ANIM_FRAME(4, 1),
        ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_JUMP(0),
    },
    {  // Diffindo
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_JUMP(0),
    },
    {  // Wingardium Leviosa
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_END,
    },
};

// Indexed by FieldSpell, with g_aFieldSpellCompanionAssets.
const u8 g_aaFieldSpellCompanionAnims[8][66] = {
    {  // Flipendo
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Lumos
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1), ANIM_FRAME(4, 1),
        ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_FRAME(8, 1), ANIM_FRAME(9, 1),
        ANIM_FRAME(10, 1), ANIM_FRAME(11, 1), ANIM_JUMP(0), ANIM_FRAME(12, 1), ANIM_FRAME(13, 3),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_END,
    },
    {  // Reparo
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Alohomora
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Glacius
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Spongify
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Diffindo
        ANIM_FRAME(0, 1), ANIM_JUMP(0),
    },
    {  // Wingardium Leviosa
        ANIM_FRAME(0, 1), ANIM_END,
    },
};

// Indexed by FieldSpell, with g_aFieldSpellAssets.
const u8 g_aaFieldSpellAnims[8][66] = {
    {  // Flipendo
        ANIM_FRAME(34, 2), ANIM_FRAME(35, 2), ANIM_FRAME(36, 2), ANIM_FRAME(37, 2),
        ANIM_FRAME(38, 2), ANIM_FRAME(39, 2), ANIM_FRAME(40, 2), ANIM_FRAME(41, 3),
        ANIM_FRAME(42, 3), ANIM_END,
    },
    {  // Lumos
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_JUMP(0),
    },
    {  // Reparo
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 2), ANIM_END,
    },
    {  // Alohomora
        ANIM_FRAME(94, 2), ANIM_FRAME(95, 2), ANIM_FRAME(96, 2), ANIM_FRAME(97, 2),
        ANIM_FRAME(98, 2), ANIM_FRAME(99, 2), ANIM_FRAME(100, 2), ANIM_FRAME(101, 2),
        ANIM_FRAME(102, 2), ANIM_FRAME(103, 2), ANIM_FRAME(104, 2), ANIM_FRAME(105, 2),
        ANIM_FRAME(106, 2), ANIM_FRAME(107, 2), ANIM_FRAME(108, 2), ANIM_FRAME(109, 2),
        ANIM_FRAME(110, 2), ANIM_FRAME(111, 2), ANIM_FRAME(112, 2), ANIM_END,
    },
    {  // Glacius
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Spongify
        ANIM_FRAME(0, 1), ANIM_END,
    },
    {  // Diffindo
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_END,
    },
    {  // Wingardium Leviosa
        ANIM_FRAME(0, 1), ANIM_END,
    },
};

// Indexed by the caster's facing; facings 5-7 use the frames of 3-1, horizontally flipped.
const u8 g_aaFieldSpellFlightAnims[8][66] = {
    {  // 0
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_JUMP(0),
    },
    {  // 1
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 2), ANIM_JUMP(0),
    },
    {  // 2
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_JUMP(0),
    },
    {  // 3
        ANIM_FRAME(2, 2), ANIM_FRAME(3, 2), ANIM_JUMP(0),
    },
    {  // 4
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_JUMP(0),
    },
    {  // 5
        ANIM_FRAME(2, 2), ANIM_FRAME(3, 2), ANIM_JUMP(0),
    },
    {  // 6
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_JUMP(0),
    },
    {  // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 2), ANIM_JUMP(0),
    },
};

// Indexed by the caster's g_abFacingDirection4; left uses the frames of right, flipped.
const u8 g_aaFieldSpellImpactAnims[4][66] = {
    {  // 0
        ANIM_FRAME(26, 2), ANIM_FRAME(27, 1), ANIM_FRAME(28, 1), ANIM_FRAME(29, 1),
        ANIM_FRAME(30, 1), ANIM_FRAME(31, 2), ANIM_FRAME(32, 3), ANIM_FRAME(33, 3), ANIM_END,
    },
    {  // 1
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 1), ANIM_FRAME(20, 1), ANIM_FRAME(21, 1),
        ANIM_FRAME(22, 1), ANIM_FRAME(23, 2), ANIM_FRAME(24, 3), ANIM_FRAME(25, 3), ANIM_END,
    },
    {  // 2
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 1), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_END,
    },
    {  // 3
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 1), ANIM_FRAME(20, 1), ANIM_FRAME(21, 1),
        ANIM_FRAME(22, 1), ANIM_FRAME(23, 2), ANIM_FRAME(24, 3), ANIM_FRAME(25, 3), ANIM_END,
    },
};

// Alohomora unlocking, indexed like g_aaFieldSpellImpactAnims.
const u8 g_aaAlohomoraUnlockAnims[4][66] = {
    {  // 0
        ANIM_FRAME(66, 2), ANIM_FRAME(67, 2), ANIM_FRAME(68, 2), ANIM_FRAME(69, 2),
        ANIM_FRAME(70, 2), ANIM_FRAME(71, 2), ANIM_FRAME(72, 2), ANIM_FRAME(73, 2),
        ANIM_FRAME(74, 2), ANIM_FRAME(75, 2), ANIM_FRAME(76, 2), ANIM_FRAME(77, 2),
        ANIM_FRAME(78, 2), ANIM_FRAME(79, 2), ANIM_FRAME(80, 2), ANIM_FRAME(81, 2),
        ANIM_FRAME(82, 2), ANIM_FRAME(83, 2), ANIM_FRAME(84, 2), ANIM_FRAME(85, 2),
        ANIM_FRAME(86, 2), ANIM_FRAME(87, 2), ANIM_FRAME(88, 2), ANIM_FRAME(89, 2),
        ANIM_FRAME(90, 2), ANIM_FRAME(91, 2), ANIM_FRAME(92, 2), ANIM_FRAME(93, 2), ANIM_END,
    },
    {  // 1
        ANIM_FRAME(38, 2), ANIM_FRAME(39, 2), ANIM_FRAME(40, 2), ANIM_FRAME(41, 2),
        ANIM_FRAME(42, 2), ANIM_FRAME(43, 2), ANIM_FRAME(44, 2), ANIM_FRAME(45, 2),
        ANIM_FRAME(46, 2), ANIM_FRAME(47, 2), ANIM_FRAME(48, 2), ANIM_FRAME(49, 2),
        ANIM_FRAME(50, 2), ANIM_FRAME(51, 2), ANIM_FRAME(52, 2), ANIM_FRAME(53, 2),
        ANIM_FRAME(54, 2), ANIM_FRAME(55, 2), ANIM_FRAME(56, 2), ANIM_FRAME(57, 2),
        ANIM_FRAME(58, 2), ANIM_FRAME(59, 2), ANIM_FRAME(60, 2), ANIM_FRAME(61, 2),
        ANIM_FRAME(62, 2), ANIM_FRAME(63, 2), ANIM_FRAME(64, 2), ANIM_FRAME(65, 2), ANIM_END,
    },
    {  // 2
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 2),
        ANIM_FRAME(22, 2), ANIM_FRAME(23, 2), ANIM_FRAME(24, 2), ANIM_FRAME(25, 2),
        ANIM_FRAME(26, 2), ANIM_FRAME(27, 2), ANIM_FRAME(28, 2), ANIM_FRAME(29, 2),
        ANIM_FRAME(30, 2), ANIM_FRAME(31, 2), ANIM_FRAME(32, 2), ANIM_FRAME(33, 2),
        ANIM_FRAME(34, 2), ANIM_FRAME(35, 2), ANIM_FRAME(36, 2), ANIM_FRAME(37, 2), ANIM_END,
    },
    {  // 3
        ANIM_FRAME(38, 2), ANIM_FRAME(39, 2), ANIM_FRAME(40, 2), ANIM_FRAME(41, 2),
        ANIM_FRAME(42, 2), ANIM_FRAME(43, 2), ANIM_FRAME(44, 2), ANIM_FRAME(45, 2),
        ANIM_FRAME(46, 2), ANIM_FRAME(47, 2), ANIM_FRAME(48, 2), ANIM_FRAME(49, 2),
        ANIM_FRAME(50, 2), ANIM_FRAME(51, 2), ANIM_FRAME(52, 2), ANIM_FRAME(53, 2),
        ANIM_FRAME(54, 2), ANIM_FRAME(55, 2), ANIM_FRAME(56, 2), ANIM_FRAME(57, 2),
        ANIM_FRAME(58, 2), ANIM_FRAME(59, 2), ANIM_FRAME(60, 2), ANIM_FRAME(61, 2),
        ANIM_FRAME(62, 2), ANIM_FRAME(63, 2), ANIM_FRAME(64, 2), ANIM_FRAME(65, 2), ANIM_END,
    },
};

const u8 g_abDiffindoEndAnim[66] = {
    ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 2), ANIM_END,
};

const u8 g_abDiffindoHitAnim[66] = {
    ANIM_FRAME(3, 2), ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
    ANIM_END,
};

const u8 g_abSpongifyHitAnim[66] = {
    ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 1),
    ANIM_FRAME(13, 1), ANIM_FRAME(14, 1), ANIM_FRAME(15, 1), ANIM_FRAME(16, 1), ANIM_FRAME(17, 1),
    ANIM_END,
};

const u8 g_abSpongifyEndAnim[66] = {
    ANIM_FRAME(26, 2), ANIM_FRAME(27, 2), ANIM_FRAME(28, 2), ANIM_FRAME(29, 2), ANIM_FRAME(30, 2),
    ANIM_FRAME(31, 2), ANIM_FRAME(32, 2), ANIM_FRAME(33, 2), ANIM_FRAME(34, 2), ANIM_FRAME(35, 2),
    ANIM_FRAME(36, 2), ANIM_FRAME(37, 2), ANIM_FRAME(38, 2), ANIM_FRAME(39, 2), ANIM_FRAME(40, 2),
    ANIM_FRAME(41, 2), ANIM_FRAME(42, 2), ANIM_END,
};

// Flight velocity for each facing, pixels per tick.
const PixelVector g_aFieldSpellVelocities[8] = {
    { 0, -4 },
    { 3, -3 },
    { 4, 0 },
    { 3, 3 },
    { 0, 4 },
    { -3, 3 },
    { -4, 0 },
    { -3, -3 },
};

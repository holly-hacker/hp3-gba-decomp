#include "types.h"
#include "actor_anim.h"
#include "world_actors.h"
#include "gen/graphics/overworld.h"

const ActorGfxRecord g_aWorldActorSprites[80] = {
    { (void *)gActorSprite2_126Tiles, (void *)gActorSprite2_126Frames },  // 0
    { (void *)gPushableBlockTiles, (void *)gPushableBlockFrames },  // 1
    { (void *)gActorSprite2_128Tiles, (void *)gActorSprite2_128Frames },  // 2
    { (void *)gChestTiles, (void *)gChestFrames },  // 3
    { (void *)gActorSprite2_129Tiles, (void *)gActorSprite2_129Frames },  // 4
    { (void *)gActorShadowTiles, (void *)gActorShadowFrames },  // 5
    { (void *)gLockedDoorTiles, (void *)gLockedDoorFrames },  // 6
    { (void *)gActorSprite2_131Tiles, (void *)gActorSprite2_131Frames },  // 7
    { (void *)gActorSprite2_132Tiles, (void *)gActorSprite2_132Frames },  // 8
    { (void *)gActorSprite2_133Tiles, (void *)gActorSprite2_133Frames },  // 9
    { (void *)gActorSprite2_134Tiles, (void *)gActorSprite2_134Frames },  // 10
    { (void *)gActorSprite2_135Tiles, (void *)gActorSprite2_135Frames },  // 11
    { (void *)gActorSprite2_136Tiles, (void *)gActorSprite2_136Frames },  // 12
    { (void *)gActorSprite2_137Tiles, (void *)gActorSprite2_137Frames },  // 13
    { (void *)gActorSprite2_138Tiles, (void *)gActorSprite2_138Frames },  // 14
    { (void *)gActorSprite2_139Tiles, (void *)gActorSprite2_139Frames },  // 15
    { (void *)gActorSprite2_140Tiles, (void *)gActorSprite2_140Frames },  // 16
    { (void *)gActorSprite2_141Tiles, (void *)gActorSprite2_141Frames },  // 17
    { (void *)gActorSprite2_142Tiles, (void *)gActorSprite2_142Frames },  // 18
    { (void *)gActorSprite2_143Tiles, (void *)gActorSprite2_143Frames },  // 19
    { (void *)gActorSprite2_144Tiles, (void *)gActorSprite2_144Frames },  // 20
    { (void *)gActorSprite2_145Tiles, (void *)gActorSprite2_145Frames },  // 21
    { (void *)gActorSprite2_146Tiles, (void *)gActorSprite2_146Frames },  // 22
    { (void *)gActorSprite2_147Tiles, (void *)gActorSprite2_147Frames },  // 23
    { (void *)gActorSprite2_148Tiles, (void *)gActorSprite2_148Frames },  // 24
    { (void *)gActorSprite2_149Tiles, (void *)gActorSprite2_149Frames },  // 25
    { (void *)gActorSprite2_150Tiles, (void *)gActorSprite2_150Frames },  // 26
    { (void *)gActorSprite2_151Tiles, (void *)gActorSprite2_151Frames },  // 27
    { (void *)gActorSprite2_152Tiles, (void *)gActorSprite2_152Frames },  // 28
    { (void *)gActorSprite2_153Tiles, (void *)gActorSprite2_153Frames },  // 29
    { (void *)gActorSprite2_154Tiles, (void *)gActorSprite2_154Frames },  // 30
    { (void *)gActorSprite2_155Tiles, (void *)gActorSprite2_155Frames },  // 31
    { (void *)gActorSprite2_156Tiles, (void *)gActorSprite2_156Frames },  // 32
    { (void *)gActorSprite2_157Tiles, (void *)gActorSprite2_157Frames },  // 33
    { (void *)gActorSprite2_158Tiles, (void *)gActorSprite2_158Frames },  // 34
    { (void *)gActorSprite2_159Tiles, (void *)gActorSprite2_159Frames },  // 35
    { (void *)gActorSprite2_160Tiles, (void *)gActorSprite2_160Frames },  // 36
    { (void *)gActorSprite2_161Tiles, (void *)gActorSprite2_161Frames },  // 37
    { (void *)gActorSprite2_162Tiles, (void *)gActorSprite2_162Frames },  // 38
    { (void *)gActorSprite2_163Tiles, (void *)gActorSprite2_163Frames },  // 39
    { (void *)gActorSprite2_164Tiles, (void *)gActorSprite2_164Frames },  // 40
    { (void *)gActorSprite2_165Tiles, (void *)gActorSprite2_165Frames },  // 41
    { (void *)gActorSprite2_166Tiles, (void *)gActorSprite2_166Frames },  // 42
    { (void *)gActorSprite2_167Tiles, (void *)gActorSprite2_167Frames },  // 43
    { (void *)gActorSprite2_168Tiles, (void *)gActorSprite2_168Frames },  // 44
    { (void *)gActorSprite2_169Tiles, (void *)gActorSprite2_169Frames },  // 45
    { (void *)gActorSprite2_109Tiles, (void *)gActorSprite2_109Frames },  // 46
    { (void *)gActorSprite2_170Tiles, (void *)gActorSprite2_170Frames },  // 47
    { (void *)gActorSprite2_171Tiles, (void *)gActorSprite2_171Frames },  // 48
    { (void *)gActorSprite2_172Tiles, (void *)gActorSprite2_172Frames },  // 49
    { (void *)gActorSprite2_173Tiles, (void *)gActorSprite2_173Frames },  // 50
    { (void *)gActorSprite2_174Tiles, (void *)gActorSprite2_174Frames },  // 51
    { (void *)gLever001Tiles, (void *)gLever001Frames },  // 52
    { (void *)gActorSprite2_175Tiles, (void *)gActorSprite2_175Frames },  // 53
    { (void *)gActorSprite2_176Tiles, (void *)gActorSprite2_176Frames },  // 54
    { (void *)gActorSprite2_177Tiles, (void *)gActorSprite2_177Frames },  // 55
    { (void *)gActorSprite2_178Tiles, (void *)gActorSprite2_178Frames },  // 56
    { (void *)gActorSprite2_179Tiles, (void *)gActorSprite2_179Frames },  // 57
    { (void *)gActorSprite2_180Tiles, (void *)gActorSprite2_180Frames },  // 58
    { (void *)gActorSprite2_181Tiles, (void *)gActorSprite2_181Frames },  // 59
    { (void *)gActorSprite2_182Tiles, (void *)gActorSprite2_182Frames },  // 60
    { (void *)gActorSprite2_183Tiles, (void *)gActorSprite2_183Frames },  // 61
    { (void *)gFlamePillar003Tiles, (void *)gFlamePillar003Frames },  // 62
    { (void *)gFlamePillar002Tiles, (void *)gFlamePillar002Frames },  // 63
    { (void *)gFlamePillar001Tiles, (void *)gFlamePillar001Frames },  // 64
    { (void *)gLever003Tiles, (void *)gLever003Frames },  // 65
    { (void *)gActorSprite2_184Tiles, (void *)gActorSprite2_184Frames },  // 66
    { (void *)gActorSprite2_185Tiles, (void *)gActorSprite2_185Frames },  // 67
    { (void *)gActorSprite2_186Tiles, (void *)gActorSprite2_186Frames },  // 68
    { (void *)gRaisingPlatformTiles, (void *)gRaisingPlatformFrames },  // 69
    { (void *)gLever002Tiles, (void *)gLever002Frames },  // 70
    { (void *)gActorSprite2_187Tiles, (void *)gActorSprite2_187Frames },  // 71
    { (void *)gActorSprite2_188Tiles, (void *)gActorSprite2_188Frames },  // 72
    { (void *)gActorSprite2_189Tiles, (void *)gActorSprite2_189Frames },  // 73
    { (void *)gActorSprite2_190Tiles, (void *)gActorSprite2_190Frames },  // 74
    { (void *)gActorSprite2_191Tiles, (void *)gActorSprite2_191Frames },  // 75
    { (void *)gActorSprite2_192Tiles, (void *)gActorSprite2_192Frames },  // 76
    { (void *)gActorSprite2_193Tiles, (void *)gActorSprite2_193Frames },  // 77
    { (void *)gActorSprite2_194Tiles, (void *)gActorSprite2_194Frames },  // 78
    { (void *)gActorSprite2_195Tiles, (void *)gActorSprite2_195Frames },  // 79
};

// Indexed by the actor's kind.
const ActorGfxRecord *const g_apWorldActorAnimFrames[91] = {
    &g_aWorldActorSprites[0],
    &g_aWorldActorSprites[1],
    &g_aWorldActorSprites[2],
    &g_aWorldActorSprites[3],
    &g_aWorldActorSprites[3],
    &g_aWorldActorSprites[4],
    &g_aWorldActorSprites[6],
    &g_aWorldActorSprites[7],
    &g_aWorldActorSprites[8],
    &g_aWorldActorSprites[9],
    &g_aWorldActorSprites[10],
    &g_aWorldActorSprites[11],
    &g_aWorldActorSprites[12],
    &g_aWorldActorSprites[13],
    &g_aWorldActorSprites[14],
    &g_aWorldActorSprites[14],
    &g_aWorldActorSprites[15],
    &g_aWorldActorSprites[16],
    &g_aWorldActorSprites[17],
    &g_aWorldActorSprites[18],
    &g_aWorldActorSprites[19],
    &g_aWorldActorSprites[20],
    &g_aWorldActorSprites[21],
    &g_aWorldActorSprites[22],
    &g_aWorldActorSprites[23],
    &g_aWorldActorSprites[24],
    &g_aWorldActorSprites[25],
    &g_aWorldActorSprites[26],
    &g_aWorldActorSprites[27],
    &g_aWorldActorSprites[28],
    &g_aWorldActorSprites[27],
    &g_aWorldActorSprites[26],
    &g_aWorldActorSprites[27],
    &g_aWorldActorSprites[36],
    &g_aWorldActorSprites[36],
    &g_aWorldActorSprites[31],
    &g_aWorldActorSprites[32],
    &g_aWorldActorSprites[37],
    &g_aWorldActorSprites[38],
    &g_aWorldActorSprites[33],
    &g_aWorldActorSprites[33],
    &g_aWorldActorSprites[34],
    &g_aWorldActorSprites[29],
    &g_aWorldActorSprites[29],
    &g_aWorldActorSprites[30],
    &g_aWorldActorSprites[35],
    &g_aWorldActorSprites[39],
    &g_aWorldActorSprites[39],
    &g_aWorldActorSprites[39],
    &g_aWorldActorSprites[40],
    &g_aWorldActorSprites[40],
    &g_aWorldActorSprites[41],
    &g_aWorldActorSprites[42],
    &g_aWorldActorSprites[44],
    &g_aWorldActorSprites[45],
    &g_aWorldActorSprites[46],
    &g_aWorldActorSprites[47],
    &g_aWorldActorSprites[48],
    &g_aWorldActorSprites[49],
    &g_aWorldActorSprites[50],
    &g_aWorldActorSprites[51],
    &g_aWorldActorSprites[52],
    &g_aWorldActorSprites[53],
    &g_aWorldActorSprites[54],
    &g_aWorldActorSprites[55],
    &g_aWorldActorSprites[56],
    &g_aWorldActorSprites[57],
    &g_aWorldActorSprites[58],
    &g_aWorldActorSprites[59],
    &g_aWorldActorSprites[60],
    &g_aWorldActorSprites[61],
    &g_aWorldActorSprites[62],
    &g_aWorldActorSprites[63],
    &g_aWorldActorSprites[64],
    &g_aWorldActorSprites[65],
    &g_aWorldActorSprites[66],
    &g_aWorldActorSprites[67],
    &g_aWorldActorSprites[68],
    &g_aWorldActorSprites[69],
    &g_aWorldActorSprites[70],
    &g_aWorldActorSprites[71],
    &g_aWorldActorSprites[72],
    &g_aWorldActorSprites[73],
    &g_aWorldActorSprites[74],
    &g_aWorldActorSprites[75],
    &g_aWorldActorSprites[76],
    &g_aWorldActorSprites[67],
    &g_aWorldActorSprites[33],
    &g_aWorldActorSprites[77],
    &g_aWorldActorSprites[78],
    &g_aWorldActorSprites[79],
};

const void *const g_apWorldActorEffectData[91] = {
    gActorPalette001Palette,
    gActorPalette002Palette,
    gActorPalette002Palette,
    gChestPalette,
    gChestPalette,
    gActorPalette003Palette,
    gActorPalette004Palette,
    gActorPalette005Palette,
    gActorPalette006Palette,
    gActorPalette007Palette,
    gActorPalette008Palette,
    gActorPalette009Palette,
    gActorPalette010Palette,
    gActorPalette011Palette,
    gActorPalette012Palette,
    gActorPalette012Palette,
    gActorPalette013Palette,
    gActorPalette014Palette,
    gActorPalette015Palette,
    gActorPalette016Palette,
    gActorPalette017Palette,
    gActorPalette018Palette,
    gActorPalette019Palette,
    gActorPalette020Palette,
    gActorPalette021Palette,
    gActorPalette022Palette,
    gActorPalette023Palette,
    gActorPalette024Palette,
    gActorPalette024Palette,
    gActorPalette023Palette,
    gActorPalette024Palette,
    gActorPalette024Palette,
    gActorPalette024Palette,
    gDementorPalette,
    gDementorPalette,
    gActorPalette025Palette,
    gActorPalette025Palette,
    gActorPalette025Palette,
    gActorPalette025Palette,
    gActorPalette025Palette,
    gActorPalette025Palette,
    gActorPalette025Palette,
    gActorPalette026Palette,
    gActorPalette026Palette,
    gActorPalette027Palette,
    gActorPalette028Palette,
    gActorPalette029Palette,
    gActorPalette029Palette,
    gActorPalette029Palette,
    gActorPalette030Palette,
    gActorPalette030Palette,
    gActorPalette031Palette,
    gActorPalette032Palette,
    gActorPalette033Palette,
    gActorPalette034Palette,
    gActorSprite2_109Palette,
    gActorPalette035Palette,
    gActorPalette036Palette,
    gActorPalette037Palette,
    gActorPalette038Palette,
    gActorPalette039Palette,
    gActorSprite2_123Palette,
    gActorPalette040Palette,
    gActorPalette041Palette,
    gActorPalette042Palette,
    gActorPalette043Palette,
    gActorPalette044Palette,
    gActorPalette045Palette,
    gActorPalette046Palette,
    gActorPalette047Palette,
    gActorPalette048Palette,
    gActorPalette049Palette,
    gFlamePillar003Palette,
    gActorPalette050Palette,
    gActorSprite2_125Palette,
    gActorPalette051Palette,
    gActorPalette052Palette,
    gActorPalette053Palette,
    gRaisingPlatformPalette,
    gActorSprite2_124Palette,
    gActorPalette054Palette,
    gActorPalette055Palette,
    gActorPalette056Palette,
    gActorPalette057Palette,
    gActorPalette058Palette,
    gActorPalette059Palette,
    gActorPalette052Palette,
    gActorPalette025Palette,
    gActorPalette060Palette,
    gActorPalette061Palette,
    gActorPalette062Palette,
};

// Velocity (whole pixels per frame) and the facing a pushed actor takes from
// its pusher's Direction; diagonals push horizontally.
const s32 g_aWorldActorPushVelocity[8][2] = {
    { 0, -5 },  // Up
    { 5, 0 },  // UpRight
    { 5, 0 },  // Right
    { 5, 0 },  // DownRight
    { 0, 5 },  // Down
    { -5, 0 },  // DownLeft
    { -5, 0 },  // Left
    { -5, 0 },  // UpLeft
};

const u32 g_adwWorldActorPushFacing[8] = {
    DirectionUp, DirectionRight, DirectionRight, DirectionRight,
    DirectionDown, DirectionLeft, DirectionLeft, DirectionLeft,
};

// Particle sprites of BreakWorldActor: 0-2 for kind 0, 3-5 for the other kinds; 6 is unused.
const ActorGfxRecord g_WorldActorParticleGfx0 = { (void *)gOverworldSpellEffect021Tiles, (void *)gOverworldSpellEffect021Frames };
const ActorGfxRecord g_WorldActorParticleGfx1 = { (void *)gOverworldSpellEffect022Tiles, (void *)gOverworldSpellEffect022Frames };
const ActorGfxRecord g_WorldActorParticleGfx2 = { (void *)gOverworldSpellEffect023Tiles, (void *)gOverworldSpellEffect023Frames };
const ActorGfxRecord g_WorldActorParticleGfx3 = { (void *)gOverworldSpellEffect024Tiles, (void *)gOverworldSpellEffect024Frames };
const ActorGfxRecord g_WorldActorParticleGfx4 = { (void *)gOverworldSpellEffect025Tiles, (void *)gOverworldSpellEffect025Frames };
const ActorGfxRecord g_WorldActorParticleGfx5 = { (void *)gOverworldSpellEffect026Tiles, (void *)gOverworldSpellEffect026Frames };
const ActorGfxRecord g_WorldActorParticleGfx6 = { (void *)gOverworldSpellEffect027Tiles, (void *)gOverworldSpellEffect027Frames };

// One animation block per kind.
const u8 g_abWorldActorAnimData[91][90] = {
    {  // 0
        // 0
        ANIM_FRAME(0, 0), ANIM_END,
        // 2
        ANIM_FRAME(5, 6), ANIM_FRAME(10, 0), ANIM_END,
        // 5
        ANIM_FRAME(7, 6), ANIM_FRAME(10, 0), ANIM_END,
    },
    {  // 1
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 2
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 3
        // 0
        ANIM_FRAME(15, 3), ANIM_END,
        // 2
        ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3), ANIM_FRAME(19, 3),
        ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_END,
    },
    {  // 4
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
        ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
        ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3), ANIM_FRAME(19, 3),
        ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_END,
        // 23
        ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_FRAME(24, 3), ANIM_FRAME(25, 3),
        ANIM_FRAME(26, 3), ANIM_FRAME(27, 3), ANIM_FRAME(28, 3), ANIM_FRAME(29, 3),
        ANIM_FRAME(30, 3), ANIM_FRAME(31, 3), ANIM_END,
    },
    {  // 5
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_END,
    },
    {  // 6
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4), ANIM_FRAME(4, 4),
        ANIM_FRAME(5, 4), ANIM_FRAME(6, 4), ANIM_FRAME(7, 4), ANIM_FRAME(8, 4),
        ANIM_FRAME(9, 4), ANIM_END,
    },
    {  // 7
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 8
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 9
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 10
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 11
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 12
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 13
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 14
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_JUMP(0),
    },
    {  // 15
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
    },
    {  // 16
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
        ANIM_JUMP(0),
    },
    {  // 17
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2),
        ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2),
        ANIM_FRAME(16, 2), ANIM_FRAME(17, 2), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2),
        ANIM_FRAME(20, 2), ANIM_JUMP(0),
    },
    {  // 18
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2),
        ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2),
        ANIM_FRAME(16, 2), ANIM_FRAME(17, 2), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2),
        ANIM_FRAME(20, 2), ANIM_JUMP(0),
    },
    {  // 19
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2),
        ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2),
        ANIM_FRAME(16, 2), ANIM_FRAME(17, 2), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2),
        ANIM_FRAME(20, 2), ANIM_JUMP(0),
    },
    {  // 20
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2),
        ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2),
        ANIM_FRAME(16, 2), ANIM_FRAME(17, 2), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2),
        ANIM_FRAME(20, 2), ANIM_JUMP(0),
    },
    {  // 21
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 22
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 23
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 24
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 25
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 26
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(0, 3), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3),
        ANIM_END,
    },
    {  // 27
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(0, 3), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3),
        ANIM_END,
    },
    {  // 28
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(0, 3), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3),
        ANIM_END,
    },
    {  // 29
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(0, 2), ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2),
        ANIM_END,
    },
    {  // 30
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(0, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(6, 3),
        ANIM_END,
    },
    {  // 31
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(0, 3), ANIM_SOUND(13), ANIM_FRAME(1, 3), ANIM_FRAME(0, 3),
        ANIM_SOUND(13), ANIM_FRAME(2, 3), ANIM_FRAME(0, 3), ANIM_SOUND(13),
        ANIM_FRAME(3, 3), ANIM_FRAME(0, 3), ANIM_END,
    },
    {  // 32
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(0, 3), ANIM_SOUND(13), ANIM_FRAME(1, 3), ANIM_FRAME(0, 3),
        ANIM_SOUND(13), ANIM_FRAME(2, 3), ANIM_FRAME(0, 3), ANIM_SOUND(13),
        ANIM_FRAME(3, 3), ANIM_FRAME(0, 3), ANIM_END,
    },
    {  // 33
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2), ANIM_FRAME(4, 2),
        ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2), ANIM_FRAME(8, 2),
        ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 2),
        ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2),
        ANIM_FRAME(17, 2), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 2),
        ANIM_FRAME(21, 2), ANIM_FRAME(22, 2), ANIM_FRAME(23, 2), ANIM_FRAME(24, 2),
        ANIM_FRAME(25, 2), ANIM_FRAME(26, 2), ANIM_FRAME(27, 2), ANIM_FRAME(0, 2),
        ANIM_END,
    },
    {  // 34
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(28, 2), ANIM_FRAME(29, 2), ANIM_FRAME(30, 2), ANIM_FRAME(31, 2),
        ANIM_FRAME(32, 2), ANIM_FRAME(33, 2), ANIM_FRAME(34, 2), ANIM_FRAME(35, 2),
        ANIM_FRAME(36, 2), ANIM_FRAME(37, 2), ANIM_FRAME(38, 2), ANIM_FRAME(39, 2),
        ANIM_FRAME(40, 2), ANIM_FRAME(41, 2), ANIM_FRAME(42, 2), ANIM_FRAME(43, 2),
        ANIM_FRAME(44, 2), ANIM_FRAME(45, 2), ANIM_FRAME(46, 2), ANIM_FRAME(47, 2),
        ANIM_FRAME(48, 2), ANIM_FRAME(49, 2), ANIM_FRAME(50, 2), ANIM_FRAME(0, 2),
        ANIM_END,
    },
    {  // 35
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 4), ANIM_SOUND(12), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 3), ANIM_FRAME(6, 0), ANIM_FRAME(7, 0),
        ANIM_END,
    },
    {  // 36
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 4), ANIM_SOUND(12), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 3), ANIM_FRAME(6, 0), ANIM_FRAME(7, 0),
        ANIM_END,
    },
    {  // 37
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1), ANIM_END,
    },
    {  // 38
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1), ANIM_END,
    },
    {  // 39
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(12, 3), ANIM_JUMP(0),
        // 3
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2), ANIM_FRAME(4, 2),
        ANIM_FRAME(5, 2), ANIM_FRAME(6, 0), ANIM_END,
    },
    {  // 40
        // 0
        ANIM_FRAME(6, 0), ANIM_END,
        // 2
        ANIM_FRAME(7, 2), ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2),
        ANIM_FRAME(11, 2), ANIM_END,
    },
    {  // 41
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 42
        // 0
        ANIM_FRAME(0, 0), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_FRAME(4, 3),
        ANIM_END,
    },
    {  // 43
        // 0
        ANIM_FRAME(4, 0), ANIM_END,
        // 2
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
        ANIM_FRAME(8, 3), ANIM_FRAME(9, 0), ANIM_END,
    },
    {  // 44
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 0), ANIM_END,
    },
    {  // 45
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 46
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_END,
    },
    {  // 47
        // 0
        ANIM_FRAME(3, 3), ANIM_END,
        // 2
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 3), ANIM_END,
    },
    {  // 48
        // 0
        ANIM_FRAME(6, 3), ANIM_END,
        // 2
        ANIM_FRAME(7, 2), ANIM_FRAME(8, 3), ANIM_END,
    },
    {  // 49
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_END,
    },
    {  // 50
        // 0
        ANIM_FRAME(3, 3), ANIM_END,
        // 2
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 3), ANIM_END,
    },
    {  // 51
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1), ANIM_FRAME(4, 1),
        ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_FRAME(8, 1),
        ANIM_FRAME(9, 1), ANIM_FRAME(10, 1), ANIM_FRAME(11, 1), ANIM_FRAME(12, 1),
        ANIM_FRAME(13, 1), ANIM_FRAME(14, 1), ANIM_FRAME(15, 1), ANIM_FRAME(16, 3),
        ANIM_END,
        // 19
        ANIM_FRAME(17, 3), ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(0, 2),
        ANIM_END,
    },
    {  // 52
        // 0
        ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2),
        ANIM_FRAME(17, 2), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 2),
        ANIM_FRAME(21, 2), ANIM_FRAME(22, 2), ANIM_FRAME(23, 2), ANIM_JUMP(0),
        // 12
        ANIM_FRAME(24, 2), ANIM_FRAME(25, 2), ANIM_FRAME(26, 2), ANIM_FRAME(27, 2),
        ANIM_FRAME(28, 2), ANIM_FRAME(29, 2), ANIM_FRAME(30, 2), ANIM_FRAME(31, 2),
        ANIM_FRAME(32, 2), ANIM_FRAME(33, 2), ANIM_END,
        // 23
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2),
        ANIM_FRAME(12, 2), ANIM_END,
    },
    {  // 53
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_END,
    },
    {  // 54
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2), ANIM_FRAME(4, 2),
        ANIM_END,
    },
    {  // 55
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_END,
    },
    {  // 56
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_END,
    },
    {  // 57
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2), ANIM_FRAME(4, 2),
        ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2), ANIM_END,
    },
    {  // 58
        // 0
        ANIM_FRAME(0, 2), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2), ANIM_END,
    },
    {  // 59
        ANIM_FRAME(0, 2), ANIM_END,
    },
    {  // 60
        ANIM_FRAME(0, 2), ANIM_END,
    },
    {  // 61
        // 0
        ANIM_FRAME(0, 1), ANIM_END,
        // 2
        ANIM_FRAME(1, 1), ANIM_END,
    },
    {  // 62
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
    },
    {  // 63
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
    },
    {  // 64
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
    },
    {  // 65
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 12), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 3), ANIM_FRAME(6, 4), ANIM_FRAME(7, 4),
        ANIM_FRAME(8, 2), ANIM_END,
    },
    {  // 66
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
    },
    {  // 67
        ANIM_FRAME(0, 2), ANIM_END,
    },
    {  // 68
        ANIM_FRAME(0, 2), ANIM_END,
    },
    {  // 69
        // 0
        ANIM_FRAME(0, 1), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_END,
    },
    {  // 70
        // 0
        ANIM_FRAME(0, 1), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_END,
    },
    {  // 71
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_END,
    },
    {  // 72
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_END,
    },
    {  // 73
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_END,
    },
    {  // 74
        // 0
        ANIM_FRAME(0, 1), ANIM_END,
        // 2
        ANIM_FRAME(1, 1), ANIM_END,
    },
    {  // 75
        ANIM_FRAME(0, 2), ANIM_END,
    },
    {  // 76
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 2), ANIM_FRAME(8, 2), ANIM_FRAME(9, 2),
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_END,
    },
    {  // 77
        // 0
        ANIM_FRAME(0, 1), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_END,
    },
    {  // 78
        // 0
        ANIM_FRAME(0, 1), ANIM_END,
        // 2
        ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1), ANIM_FRAME(4, 1),
        ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_FRAME(8, 1),
        ANIM_FRAME(9, 1), ANIM_END,
    },
    {  // 79
        // 0
        ANIM_FRAME(0, 1), ANIM_END,
        // 2
        ANIM_FRAME(1, 1), ANIM_END,
    },
    {  // 80
        // 0
        ANIM_FRAME(0, 1), ANIM_END,
        // 2
        ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_END,
    },
    {  // 81
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 82
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_JUMP(0),
    },
    {  // 83
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 84
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 85
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 86
        ANIM_FRAME(11, 0), ANIM_END,
    },
    {  // 87
        // 0
        ANIM_FRAME(0, 3), ANIM_END,
        // 2
        ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2), ANIM_FRAME(4, 2),
        ANIM_FRAME(5, 2), ANIM_FRAME(6, 0), ANIM_END,
    },
    {  // 88
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 89
        ANIM_FRAME(0, 0), ANIM_END,
    },
    {  // 90
        // 0
        ANIM_FRAME(0, 0), ANIM_END,
        // 2
        ANIM_FRAME(1, 0), ANIM_END,
    },
};

// Frame and animation start command for each Direction.
const u8 g_abWorldActorFacingFrames[8] = { 4, 3, 2, 1, 0, 1, 2, 3 };
const u8 g_abWorldActorFacingAnimStart[8] = { 5, 5, 5, 2, 2, 2, 2, 5 };

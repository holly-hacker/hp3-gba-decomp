#include "types.h"
#include "graphics/object_anim.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_aRoomObjTriggerSprites[80] = {
    { (void *)gObjectSprite2_126Tiles, (void *)gObjectSprite2_126Frames },  // 0
    { (void *)gPushableBlockTiles, (void *)gPushableBlockFrames },  // 1
    { (void *)gObjectSprite2_128Tiles, (void *)gObjectSprite2_128Frames },  // 2
    { (void *)gChestTiles, (void *)gChestFrames },  // 3
    { (void *)gObjectSprite2_129Tiles, (void *)gObjectSprite2_129Frames },  // 4
    { (void *)gOverworldPlayer019Tiles, (void *)gOverworldPlayer019Frames },  // 5
    { (void *)gLockedDoorTiles, (void *)gLockedDoorFrames },  // 6
    { (void *)gObjectSprite2_131Tiles, (void *)gObjectSprite2_131Frames },  // 7
    { (void *)gObjectSprite2_132Tiles, (void *)gObjectSprite2_132Frames },  // 8
    { (void *)gObjectSprite2_133Tiles, (void *)gObjectSprite2_133Frames },  // 9
    { (void *)gObjectSprite2_134Tiles, (void *)gObjectSprite2_134Frames },  // 10
    { (void *)gObjectSprite2_135Tiles, (void *)gObjectSprite2_135Frames },  // 11
    { (void *)gObjectSprite2_136Tiles, (void *)gObjectSprite2_136Frames },  // 12
    { (void *)gObjectSprite2_137Tiles, (void *)gObjectSprite2_137Frames },  // 13
    { (void *)gObjectSprite2_138Tiles, (void *)gObjectSprite2_138Frames },  // 14
    { (void *)gObjectSprite2_139Tiles, (void *)gObjectSprite2_139Frames },  // 15
    { (void *)gObjectSprite2_140Tiles, (void *)gObjectSprite2_140Frames },  // 16
    { (void *)gObjectSprite2_141Tiles, (void *)gObjectSprite2_141Frames },  // 17
    { (void *)gObjectSprite2_142Tiles, (void *)gObjectSprite2_142Frames },  // 18
    { (void *)gObjectSprite2_143Tiles, (void *)gObjectSprite2_143Frames },  // 19
    { (void *)gObjectSprite2_144Tiles, (void *)gObjectSprite2_144Frames },  // 20
    { (void *)gObjectSprite2_145Tiles, (void *)gObjectSprite2_145Frames },  // 21
    { (void *)gObjectSprite2_146Tiles, (void *)gObjectSprite2_146Frames },  // 22
    { (void *)gObjectSprite2_147Tiles, (void *)gObjectSprite2_147Frames },  // 23
    { (void *)gObjectSprite2_148Tiles, (void *)gObjectSprite2_148Frames },  // 24
    { (void *)gObjectSprite2_149Tiles, (void *)gObjectSprite2_149Frames },  // 25
    { (void *)gObjectSprite2_150Tiles, (void *)gObjectSprite2_150Frames },  // 26
    { (void *)gObjectSprite2_151Tiles, (void *)gObjectSprite2_151Frames },  // 27
    { (void *)gObjectSprite2_152Tiles, (void *)gObjectSprite2_152Frames },  // 28
    { (void *)gObjectSprite2_153Tiles, (void *)gObjectSprite2_153Frames },  // 29
    { (void *)gObjectSprite2_154Tiles, (void *)gObjectSprite2_154Frames },  // 30
    { (void *)gObjectSprite2_155Tiles, (void *)gObjectSprite2_155Frames },  // 31
    { (void *)gObjectSprite2_156Tiles, (void *)gObjectSprite2_156Frames },  // 32
    { (void *)gObjectSprite2_157Tiles, (void *)gObjectSprite2_157Frames },  // 33
    { (void *)gObjectSprite2_158Tiles, (void *)gObjectSprite2_158Frames },  // 34
    { (void *)gObjectSprite2_159Tiles, (void *)gObjectSprite2_159Frames },  // 35
    { (void *)gObjectSprite2_160Tiles, (void *)gObjectSprite2_160Frames },  // 36
    { (void *)gObjectSprite2_161Tiles, (void *)gObjectSprite2_161Frames },  // 37
    { (void *)gObjectSprite2_162Tiles, (void *)gObjectSprite2_162Frames },  // 38
    { (void *)gObjectSprite2_163Tiles, (void *)gObjectSprite2_163Frames },  // 39
    { (void *)gObjectSprite2_164Tiles, (void *)gObjectSprite2_164Frames },  // 40
    { (void *)gObjectSprite2_165Tiles, (void *)gObjectSprite2_165Frames },  // 41
    { (void *)gObjectSprite2_166Tiles, (void *)gObjectSprite2_166Frames },  // 42
    { (void *)gObjectSprite2_167Tiles, (void *)gObjectSprite2_167Frames },  // 43
    { (void *)gObjectSprite2_168Tiles, (void *)gObjectSprite2_168Frames },  // 44
    { (void *)gObjectSprite2_169Tiles, (void *)gObjectSprite2_169Frames },  // 45
    { (void *)gObjectSprite2_109Tiles, (void *)gObjectSprite2_109Frames },  // 46
    { (void *)gObjectSprite2_170Tiles, (void *)gObjectSprite2_170Frames },  // 47
    { (void *)gObjectSprite2_171Tiles, (void *)gObjectSprite2_171Frames },  // 48
    { (void *)gObjectSprite2_172Tiles, (void *)gObjectSprite2_172Frames },  // 49
    { (void *)gObjectSprite2_173Tiles, (void *)gObjectSprite2_173Frames },  // 50
    { (void *)gObjectSprite2_174Tiles, (void *)gObjectSprite2_174Frames },  // 51
    { (void *)gLever001Tiles, (void *)gLever001Frames },  // 52
    { (void *)gObjectSprite2_175Tiles, (void *)gObjectSprite2_175Frames },  // 53
    { (void *)gObjectSprite2_176Tiles, (void *)gObjectSprite2_176Frames },  // 54
    { (void *)gObjectSprite2_177Tiles, (void *)gObjectSprite2_177Frames },  // 55
    { (void *)gObjectSprite2_178Tiles, (void *)gObjectSprite2_178Frames },  // 56
    { (void *)gObjectSprite2_179Tiles, (void *)gObjectSprite2_179Frames },  // 57
    { (void *)gObjectSprite2_180Tiles, (void *)gObjectSprite2_180Frames },  // 58
    { (void *)gObjectSprite2_181Tiles, (void *)gObjectSprite2_181Frames },  // 59
    { (void *)gObjectSprite2_182Tiles, (void *)gObjectSprite2_182Frames },  // 60
    { (void *)gObjectSprite2_183Tiles, (void *)gObjectSprite2_183Frames },  // 61
    { (void *)gFlamePillar003Tiles, (void *)gFlamePillar003Frames },  // 62
    { (void *)gFlamePillar002Tiles, (void *)gFlamePillar002Frames },  // 63
    { (void *)gFlamePillar001Tiles, (void *)gFlamePillar001Frames },  // 64
    { (void *)gLever003Tiles, (void *)gLever003Frames },  // 65
    { (void *)gObjectSprite2_184Tiles, (void *)gObjectSprite2_184Frames },  // 66
    { (void *)gObjectSprite2_185Tiles, (void *)gObjectSprite2_185Frames },  // 67
    { (void *)gObjectSprite2_186Tiles, (void *)gObjectSprite2_186Frames },  // 68
    { (void *)gRaisingPlatformTiles, (void *)gRaisingPlatformFrames },  // 69
    { (void *)gLever002Tiles, (void *)gLever002Frames },  // 70
    { (void *)gObjectSprite2_187Tiles, (void *)gObjectSprite2_187Frames },  // 71
    { (void *)gObjectSprite2_188Tiles, (void *)gObjectSprite2_188Frames },  // 72
    { (void *)gObjectSprite2_189Tiles, (void *)gObjectSprite2_189Frames },  // 73
    { (void *)gObjectSprite2_190Tiles, (void *)gObjectSprite2_190Frames },  // 74
    { (void *)gObjectSprite2_191Tiles, (void *)gObjectSprite2_191Frames },  // 75
    { (void *)gObjectSprite2_192Tiles, (void *)gObjectSprite2_192Frames },  // 76
    { (void *)gObjectSprite2_193Tiles, (void *)gObjectSprite2_193Frames },  // 77
    { (void *)gObjectSprite2_194Tiles, (void *)gObjectSprite2_194Frames },  // 78
    { (void *)gObjectSprite2_195Tiles, (void *)gObjectSprite2_195Frames },  // 79
};

// Indexed by the object's kind.
const ObjectGfxRecord *const g_apRoomObjTriggerAnimFrames[91] = {
    &g_aRoomObjTriggerSprites[0],
    &g_aRoomObjTriggerSprites[1],
    &g_aRoomObjTriggerSprites[2],
    &g_aRoomObjTriggerSprites[3],
    &g_aRoomObjTriggerSprites[3],
    &g_aRoomObjTriggerSprites[4],
    &g_aRoomObjTriggerSprites[6],
    &g_aRoomObjTriggerSprites[7],
    &g_aRoomObjTriggerSprites[8],
    &g_aRoomObjTriggerSprites[9],
    &g_aRoomObjTriggerSprites[10],
    &g_aRoomObjTriggerSprites[11],
    &g_aRoomObjTriggerSprites[12],
    &g_aRoomObjTriggerSprites[13],
    &g_aRoomObjTriggerSprites[14],
    &g_aRoomObjTriggerSprites[14],
    &g_aRoomObjTriggerSprites[15],
    &g_aRoomObjTriggerSprites[16],
    &g_aRoomObjTriggerSprites[17],
    &g_aRoomObjTriggerSprites[18],
    &g_aRoomObjTriggerSprites[19],
    &g_aRoomObjTriggerSprites[20],
    &g_aRoomObjTriggerSprites[21],
    &g_aRoomObjTriggerSprites[22],
    &g_aRoomObjTriggerSprites[23],
    &g_aRoomObjTriggerSprites[24],
    &g_aRoomObjTriggerSprites[25],
    &g_aRoomObjTriggerSprites[26],
    &g_aRoomObjTriggerSprites[27],
    &g_aRoomObjTriggerSprites[28],
    &g_aRoomObjTriggerSprites[27],
    &g_aRoomObjTriggerSprites[26],
    &g_aRoomObjTriggerSprites[27],
    &g_aRoomObjTriggerSprites[36],
    &g_aRoomObjTriggerSprites[36],
    &g_aRoomObjTriggerSprites[31],
    &g_aRoomObjTriggerSprites[32],
    &g_aRoomObjTriggerSprites[37],
    &g_aRoomObjTriggerSprites[38],
    &g_aRoomObjTriggerSprites[33],
    &g_aRoomObjTriggerSprites[33],
    &g_aRoomObjTriggerSprites[34],
    &g_aRoomObjTriggerSprites[29],
    &g_aRoomObjTriggerSprites[29],
    &g_aRoomObjTriggerSprites[30],
    &g_aRoomObjTriggerSprites[35],
    &g_aRoomObjTriggerSprites[39],
    &g_aRoomObjTriggerSprites[39],
    &g_aRoomObjTriggerSprites[39],
    &g_aRoomObjTriggerSprites[40],
    &g_aRoomObjTriggerSprites[40],
    &g_aRoomObjTriggerSprites[41],
    &g_aRoomObjTriggerSprites[42],
    &g_aRoomObjTriggerSprites[44],
    &g_aRoomObjTriggerSprites[45],
    &g_aRoomObjTriggerSprites[46],
    &g_aRoomObjTriggerSprites[47],
    &g_aRoomObjTriggerSprites[48],
    &g_aRoomObjTriggerSprites[49],
    &g_aRoomObjTriggerSprites[50],
    &g_aRoomObjTriggerSprites[51],
    &g_aRoomObjTriggerSprites[52],
    &g_aRoomObjTriggerSprites[53],
    &g_aRoomObjTriggerSprites[54],
    &g_aRoomObjTriggerSprites[55],
    &g_aRoomObjTriggerSprites[56],
    &g_aRoomObjTriggerSprites[57],
    &g_aRoomObjTriggerSprites[58],
    &g_aRoomObjTriggerSprites[59],
    &g_aRoomObjTriggerSprites[60],
    &g_aRoomObjTriggerSprites[61],
    &g_aRoomObjTriggerSprites[62],
    &g_aRoomObjTriggerSprites[63],
    &g_aRoomObjTriggerSprites[64],
    &g_aRoomObjTriggerSprites[65],
    &g_aRoomObjTriggerSprites[66],
    &g_aRoomObjTriggerSprites[67],
    &g_aRoomObjTriggerSprites[68],
    &g_aRoomObjTriggerSprites[69],
    &g_aRoomObjTriggerSprites[70],
    &g_aRoomObjTriggerSprites[71],
    &g_aRoomObjTriggerSprites[72],
    &g_aRoomObjTriggerSprites[73],
    &g_aRoomObjTriggerSprites[74],
    &g_aRoomObjTriggerSprites[75],
    &g_aRoomObjTriggerSprites[76],
    &g_aRoomObjTriggerSprites[67],
    &g_aRoomObjTriggerSprites[33],
    &g_aRoomObjTriggerSprites[77],
    &g_aRoomObjTriggerSprites[78],
    &g_aRoomObjTriggerSprites[79],
};

const void *const g_apRoomObjTriggerEffectData[91] = {
    gObjectPalette001Palette,
    gObjectPalette002Palette,
    gObjectPalette002Palette,
    gChestPalette,
    gChestPalette,
    gObjectPalette003Palette,
    gObjectPalette004Palette,
    gObjectPalette005Palette,
    gObjectPalette006Palette,
    gObjectPalette007Palette,
    gObjectPalette008Palette,
    gObjectPalette009Palette,
    gObjectPalette010Palette,
    gObjectPalette011Palette,
    gObjectPalette012Palette,
    gObjectPalette012Palette,
    gObjectPalette013Palette,
    gObjectPalette014Palette,
    gObjectPalette015Palette,
    gObjectPalette016Palette,
    gObjectPalette017Palette,
    gObjectPalette018Palette,
    gObjectPalette019Palette,
    gObjectPalette020Palette,
    gObjectPalette021Palette,
    gObjectPalette022Palette,
    gObjectPalette023Palette,
    gObjectPalette024Palette,
    gObjectPalette024Palette,
    gObjectPalette023Palette,
    gObjectPalette024Palette,
    gObjectPalette024Palette,
    gObjectPalette024Palette,
    gObjectSprite2_002Palette,
    gObjectSprite2_002Palette,
    gObjectPalette025Palette,
    gObjectPalette025Palette,
    gObjectPalette025Palette,
    gObjectPalette025Palette,
    gObjectPalette025Palette,
    gObjectPalette025Palette,
    gObjectPalette025Palette,
    gObjectPalette026Palette,
    gObjectPalette026Palette,
    gObjectPalette027Palette,
    gObjectPalette028Palette,
    gObjectPalette029Palette,
    gObjectPalette029Palette,
    gObjectPalette029Palette,
    gObjectPalette030Palette,
    gObjectPalette030Palette,
    gObjectPalette031Palette,
    gObjectPalette032Palette,
    gObjectPalette033Palette,
    gObjectPalette034Palette,
    gObjectSprite2_109Palette,
    gObjectPalette035Palette,
    gObjectPalette036Palette,
    gObjectPalette037Palette,
    gObjectPalette038Palette,
    gObjectPalette039Palette,
    gObjectSprite2_123Palette,
    gObjectPalette040Palette,
    gObjectPalette041Palette,
    gObjectPalette042Palette,
    gObjectPalette043Palette,
    gObjectPalette044Palette,
    gObjectPalette045Palette,
    gObjectPalette046Palette,
    gObjectPalette047Palette,
    gObjectPalette048Palette,
    gObjectPalette049Palette,
    gFlamePillar003Palette,
    gObjectPalette050Palette,
    gObjectSprite2_125Palette,
    gObjectPalette051Palette,
    gObjectPalette052Palette,
    gObjectPalette053Palette,
    gRaisingPlatformPalette,
    gObjectSprite2_124Palette,
    gObjectPalette054Palette,
    gObjectPalette055Palette,
    gObjectPalette056Palette,
    gObjectPalette057Palette,
    gObjectPalette058Palette,
    gObjectPalette059Palette,
    gObjectPalette052Palette,
    gObjectPalette025Palette,
    gObjectPalette060Palette,
    gObjectPalette061Palette,
    gObjectPalette062Palette,
};

// Velocity (whole pixels per frame) and the facing a pushed object takes from
// its pusher's Direction; diagonals push horizontally.
const s32 g_aRoomObjTriggerPushVelocity[8][2] = {
    { 0, -5 },  // Up
    { 5, 0 },  // UpRight
    { 5, 0 },  // Right
    { 5, 0 },  // DownRight
    { 0, 5 },  // Down
    { -5, 0 },  // DownLeft
    { -5, 0 },  // Left
    { -5, 0 },  // UpLeft
};

const u32 g_adwRoomObjTriggerPushFacing[8] = {
    DirectionUp, DirectionRight, DirectionRight, DirectionRight,
    DirectionDown, DirectionLeft, DirectionLeft, DirectionLeft,
};

const ObjectGfxRecord g_aRoomObjTriggerEffectSprites[7] = {
    { (void *)gOverworldSpellEffect021Tiles, (void *)gOverworldSpellEffect021Frames },
    { (void *)gOverworldSpellEffect022Tiles, (void *)gOverworldSpellEffect022Frames },
    { (void *)gOverworldSpellEffect023Tiles, (void *)gOverworldSpellEffect023Frames },
    { (void *)gOverworldSpellEffect024Tiles, (void *)gOverworldSpellEffect024Frames },
    { (void *)gOverworldSpellEffect025Tiles, (void *)gOverworldSpellEffect025Frames },
    { (void *)gOverworldSpellEffect026Tiles, (void *)gOverworldSpellEffect026Frames },
    { (void *)gOverworldSpellEffect027Tiles, (void *)gOverworldSpellEffect027Frames },
};

// One animation block per kind.
const u8 g_abRoomObjTriggerAnimData[91][90] = {
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
const u8 g_abRoomObjTriggerFacingFrames[8] = { 4, 3, 2, 1, 0, 1, 2, 3 };
const u8 g_abRoomObjTriggerFacingAnimStart[8] = { 5, 5, 5, 2, 2, 2, 2, 5 };

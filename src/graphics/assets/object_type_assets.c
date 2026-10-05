#include "types.h"
#include "graphics/object.h"
#include "overworld/room_object.h"
#include "gen/graphics/battle.h"
#include "gen/graphics/overworld.h"

// Sprites of spawned objects, indexed by object kind; see docs/formats/graphics.md.
const ObjectAssetRecord g_aObjectTypeAssets[137] = {
    { (void *)gUnnamed001Tiles, (void *)gUnnamed001Frames, (void *)gUnnamed001Palette, 0 },  // 0
    { (void *)gObjectSprite2_021Tiles, (void *)gObjectSprite2_021Frames, (void *)gObjectSprite2_021Palette, 0 },  // 1
    { (void *)gObjectSprite2_022Tiles, (void *)gObjectSprite2_022Frames, (void *)gOverworldPlayer006Palette, 0 },  // 2
    { (void *)gObjectSprite2_023Tiles, (void *)gObjectSprite2_023Frames, (void *)gObjectSprite2_023Palette, 0 },  // 3
    { (void *)gUnnamed001Tiles, (void *)gUnnamed001Frames, (void *)gObjectSprite2_024Palette, 0 },  // 4
    { (void *)gObjectSprite2_025Tiles, (void *)gObjectSprite2_025Frames, (void *)gObjectSprite2_025Palette, 0 },  // 5
    { (void *)gObjectSprite2_026Tiles, (void *)gObjectSprite2_026Frames, (void *)gOverworldPlayer005Palette, 0 },  // 6
    { (void *)gObjectSprite2_027Tiles, (void *)gObjectSprite2_027Frames, (void *)gOverworldPlayer006Palette, 0 },  // 7
    { (void *)gObjectSprite2_028Tiles, (void *)gObjectSprite2_028Frames, (void *)gObjectSprite2_028Palette, 0 },  // 8
    { (void *)gObjectSprite2_029Tiles, (void *)gObjectSprite2_029Frames, (void *)gObjectSprite2_029Palette, 0 },  // 9
    { (void *)gObjectSprite2_030Tiles, (void *)gObjectSprite2_030Frames, (void *)gObjectSprite2_030Palette, 0 },  // 10
    { (void *)gObjectSprite2_031Tiles, (void *)gObjectSprite2_031Frames, (void *)gObjectSprite2_031Palette, 0 },  // 11
    { (void *)gObjectSprite2_002Tiles, (void *)gObjectSprite2_002Frames, (void *)gObjectSprite2_002Palette, 0 },  // 12
    { (void *)gObjectSprite2_032Tiles, (void *)gObjectSprite2_032Frames, (void *)gObjectSprite2_032Palette, 0 },  // 13
    { (void *)gObjectSprite2_033Tiles, (void *)gObjectSprite2_033Frames, (void *)gObjectSprite2_033Palette, 0 },  // 14
    { (void *)gObjectSprite2_007Tiles, (void *)gObjectSprite2_007Frames, (void *)gObjectSprite2_007Palette, 0 },  // 15
    { (void *)gObjectSprite2_034Tiles, (void *)gObjectSprite2_034Frames, (void *)gOverworldPlayer004Palette, 0 },  // 16
    { (void *)gObjectSprite2_035Tiles, (void *)gObjectSprite2_035Frames, (void *)gObjectSprite2_035Palette, 0 },  // 17
    { (void *)gObjectSprite2_036Tiles, (void *)gObjectSprite2_036Frames, (void *)gObjectSprite2_036Palette, 0 },  // 18
    { (void *)gObjectSprite2_037Tiles, (void *)gObjectSprite2_037Frames, (void *)gObjectSprite2_037Palette, 0 },  // 19
    { (void *)gObjectSprite2_038Tiles, (void *)gObjectSprite2_038Frames, (void *)gObjectSprite2_038Palette, 0 },  // 20
    { (void *)gObjectSprite2_039Tiles, (void *)gObjectSprite2_039Frames, (void *)gObjectSprite2_039Palette, 0 },  // 21
    { (void *)gObjectSprite2_040Tiles, (void *)gObjectSprite2_040Frames, (void *)gObjectSprite2_040Palette, 0 },  // 22
    { (void *)gObjectSprite2_041Tiles, (void *)gObjectSprite2_041Frames, (void *)gObjectSprite2_041Palette, 0 },  // 23
    { (void *)gObjectSprite2_042Tiles, (void *)gObjectSprite2_042Frames, (void *)gObjectSprite2_042Palette, 0 },  // 24
    { (void *)gObjectSprite2_043Tiles, (void *)gObjectSprite2_043Frames, (void *)gObjectSprite2_043Palette, 0 },  // 25
    { (void *)gObjectSprite2_044Tiles, (void *)gObjectSprite2_044Frames, (void *)gObjectSprite2_044Palette, 0 },  // 26
    { (void *)gObjectSprite2_045Tiles, (void *)gObjectSprite2_045Frames, (void *)gObjectSprite2_045Palette, 0 },  // 27
    { (void *)gObjectSprite2_046Tiles, (void *)gObjectSprite2_046Frames, (void *)gObjectSprite2_046Palette, 0 },  // 28
    { (void *)gObjectSprite2_047Tiles, (void *)gObjectSprite2_047Frames, (void *)gObjectSprite2_047Palette, 0 },  // 29
    { (void *)gObjectSprite2_048Tiles, (void *)gObjectSprite2_048Frames, (void *)gObjectSprite2_048Palette, 0 },  // 30
    { (void *)gObjectSprite2_003Tiles, (void *)gObjectSprite2_003Frames, (void *)gOverworldPlayer004Palette, 0 },  // 31
    { (void *)gObjectSprite2_008Tiles, (void *)gObjectSprite2_008Frames, (void *)gOverworldPlayer006Palette, 0 },  // 32
    { (void *)gObjectSprite2_049Tiles, (void *)gObjectSprite2_049Frames, (void *)gObjectSprite2_049Palette, 0 },  // 33
    { (void *)gObjectSprite2_009Tiles, (void *)gObjectSprite2_009Frames, (void *)gOverworldPlayer005Palette, 0 },  // 34
    { (void *)gObjectSprite2_050Tiles, (void *)gObjectSprite2_050Frames, (void *)gObjectSprite2_050Palette, 0 },  // 35
    { (void *)gObjectSprite2_004Tiles, (void *)gObjectSprite2_004Frames, (void *)gObjectSprite2_004Palette, 0 },  // 36
    { (void *)gObjectSprite2_051Tiles, (void *)gObjectSprite2_051Frames, (void *)gObjectSprite2_051Palette, 0 },  // 37
    { (void *)gObjectSprite2_052Tiles, (void *)gObjectSprite2_052Frames, (void *)gObjectSprite2_052Palette, 0 },  // 38
    { (void *)gObjectSprite2_053Tiles, (void *)gObjectSprite2_053Frames, (void *)gObjectSprite2_053Palette, 0 },  // 39
    { (void *)gObjectSprite2_053Tiles, (void *)gObjectSprite2_053Frames, (void *)gObjectSprite2_054Palette, 0 },  // 40
    { (void *)gObjectSprite2_053Tiles, (void *)gObjectSprite2_053Frames, (void *)gObjectSprite2_055Palette, 0 },  // 41
    { (void *)gObjectSprite2_053Tiles, (void *)gObjectSprite2_053Frames, (void *)gObjectSprite2_056Palette, 0 },  // 42
    { (void *)gObjectSprite2_057Tiles, (void *)gObjectSprite2_057Frames, (void *)gObjectSprite2_057Palette, 0 },  // 43
    { (void *)gObjectSprite2_057Tiles, (void *)gObjectSprite2_057Frames, (void *)gObjectSprite2_058Palette, 0 },  // 44
    { (void *)gObjectSprite2_057Tiles, (void *)gObjectSprite2_057Frames, (void *)gObjectSprite2_059Palette, 0 },  // 45
    { (void *)gObjectSprite2_057Tiles, (void *)gObjectSprite2_057Frames, (void *)gObjectSprite2_060Palette, 0 },  // 46
    { (void *)gObjectSprite2_061Tiles, (void *)gObjectSprite2_061Frames, (void *)gObjectSprite2_061Palette, 0 },  // 47
    { (void *)gObjectSprite2_061Tiles, (void *)gObjectSprite2_061Frames, (void *)gObjectSprite2_062Palette, 0 },  // 48
    { (void *)gObjectSprite2_061Tiles, (void *)gObjectSprite2_061Frames, (void *)gObjectSprite2_063Palette, 0 },  // 49
    { (void *)gObjectSprite2_061Tiles, (void *)gObjectSprite2_061Frames, (void *)gObjectSprite2_064Palette, 0 },  // 50
    { (void *)gObjectSprite2_065Tiles, (void *)gObjectSprite2_065Frames, (void *)gObjectSprite2_065Palette, 0 },  // 51
    { (void *)gObjectSprite2_065Tiles, (void *)gObjectSprite2_065Frames, (void *)gObjectSprite2_066Palette, 0 },  // 52
    { (void *)gObjectSprite2_065Tiles, (void *)gObjectSprite2_065Frames, (void *)gObjectSprite2_067Palette, 0 },  // 53
    { (void *)gObjectSprite2_065Tiles, (void *)gObjectSprite2_065Frames, (void *)gObjectSprite2_068Palette, 0 },  // 54
    { (void *)gObjectSprite2_069Tiles, (void *)gObjectSprite2_069Frames, (void *)gObjectSprite2_069Palette, 0 },  // 55
    { (void *)gObjectSprite2_069Tiles, (void *)gObjectSprite2_069Frames, (void *)gObjectSprite2_070Palette, 0 },  // 56
    { (void *)gObjectSprite2_069Tiles, (void *)gObjectSprite2_069Frames, (void *)gObjectSprite2_071Palette, 0 },  // 57
    { (void *)gObjectSprite2_069Tiles, (void *)gObjectSprite2_069Frames, (void *)gObjectSprite2_072Palette, 0 },  // 58
    { (void *)gObjectSprite2_073Tiles, (void *)gObjectSprite2_073Frames, (void *)gObjectSprite2_073Palette, 0 },  // 59
    { (void *)gObjectSprite2_073Tiles, (void *)gObjectSprite2_073Frames, (void *)gObjectSprite2_074Palette, 0 },  // 60
    { (void *)gObjectSprite2_073Tiles, (void *)gObjectSprite2_073Frames, (void *)gObjectSprite2_075Palette, 0 },  // 61
    { (void *)gObjectSprite2_073Tiles, (void *)gObjectSprite2_073Frames, (void *)gObjectSprite2_076Palette, 0 },  // 62
    { (void *)gObjectSprite2_077Tiles, (void *)gObjectSprite2_077Frames, (void *)gObjectSprite2_077Palette, 0 },  // 63
    { (void *)gObjectSprite2_078Tiles, (void *)gObjectSprite2_078Frames, (void *)gOverworldPlayer006Palette, 0 },  // 64
    { (void *)gObjectSprite2_079Tiles, (void *)gObjectSprite2_079Frames, (void *)gObjectSprite2_079Palette, 0 },  // 65
    { (void *)gObjectSprite2_080Tiles, (void *)gObjectSprite2_080Frames, (void *)gObjectSprite2_080Palette, 0 },  // 66
    { (void *)gObjectSprite2_081Tiles, (void *)gObjectSprite2_081Frames, (void *)gObjectSprite2_081Palette, 0 },  // 67
    { (void *)gObjectSprite2_082Tiles, (void *)gObjectSprite2_082Frames, (void *)gOverworldPlayer005Palette, 0 },  // 68
    { (void *)gObjectSprite2_083Tiles, (void *)gObjectSprite2_083Frames, (void *)gOverworldPlayer004Palette, 0 },  // 69
    { (void *)gObjectSprite2_084Tiles, (void *)gObjectSprite2_084Frames, (void *)gObjectSprite2_084Palette, 0 },  // 70
    { (void *)gObjectSprite2_085Tiles, (void *)gObjectSprite2_085Frames, (void *)gObjectSprite2_085Palette, 0 },  // 71
    { (void *)gObjectSprite2_085Tiles, (void *)gObjectSprite2_085Frames, (void *)gObjectSprite2_054Palette, 0 },  // 72
    { (void *)gObjectSprite2_085Tiles, (void *)gObjectSprite2_085Frames, (void *)gObjectSprite2_055Palette, 0 },  // 73
    { (void *)gObjectSprite2_085Tiles, (void *)gObjectSprite2_085Frames, (void *)gObjectSprite2_056Palette, 0 },  // 74
    { (void *)gObjectSprite2_086Tiles, (void *)gObjectSprite2_086Frames, (void *)gObjectSprite2_086Palette, 0 },  // 75
    { (void *)gObjectSprite2_086Tiles, (void *)gObjectSprite2_086Frames, (void *)gObjectSprite2_058Palette, 0 },  // 76
    { (void *)gObjectSprite2_086Tiles, (void *)gObjectSprite2_086Frames, (void *)gObjectSprite2_059Palette, 0 },  // 77
    { (void *)gObjectSprite2_086Tiles, (void *)gObjectSprite2_086Frames, (void *)gObjectSprite2_060Palette, 0 },  // 78
    { (void *)gObjectSprite2_087Tiles, (void *)gObjectSprite2_087Frames, (void *)gObjectSprite2_087Palette, 0 },  // 79
    { (void *)gObjectSprite2_087Tiles, (void *)gObjectSprite2_087Frames, (void *)gObjectSprite2_062Palette, 0 },  // 80
    { (void *)gObjectSprite2_087Tiles, (void *)gObjectSprite2_087Frames, (void *)gObjectSprite2_063Palette, 0 },  // 81
    { (void *)gObjectSprite2_087Tiles, (void *)gObjectSprite2_087Frames, (void *)gObjectSprite2_064Palette, 0 },  // 82
    { (void *)gObjectSprite2_088Tiles, (void *)gObjectSprite2_088Frames, (void *)gObjectSprite2_088Palette, 0 },  // 83
    { (void *)gObjectSprite2_088Tiles, (void *)gObjectSprite2_088Frames, (void *)gObjectSprite2_066Palette, 0 },  // 84
    { (void *)gObjectSprite2_088Tiles, (void *)gObjectSprite2_088Frames, (void *)gObjectSprite2_067Palette, 0 },  // 85
    { (void *)gObjectSprite2_088Tiles, (void *)gObjectSprite2_088Frames, (void *)gObjectSprite2_068Palette, 0 },  // 86
    { (void *)gObjectSprite2_089Tiles, (void *)gObjectSprite2_089Frames, (void *)gObjectSprite2_089Palette, 0 },  // 87
    { (void *)gObjectSprite2_089Tiles, (void *)gObjectSprite2_089Frames, (void *)gObjectSprite2_070Palette, 0 },  // 88
    { (void *)gObjectSprite2_089Tiles, (void *)gObjectSprite2_089Frames, (void *)gObjectSprite2_071Palette, 0 },  // 89
    { (void *)gObjectSprite2_089Tiles, (void *)gObjectSprite2_089Frames, (void *)gObjectSprite2_072Palette, 0 },  // 90
    { (void *)gObjectSprite2_090Tiles, (void *)gObjectSprite2_090Frames, (void *)gObjectSprite2_090Palette, 0 },  // 91
    { (void *)gObjectSprite2_090Tiles, (void *)gObjectSprite2_090Frames, (void *)gObjectSprite2_074Palette, 0 },  // 92
    { (void *)gObjectSprite2_090Tiles, (void *)gObjectSprite2_090Frames, (void *)gObjectSprite2_075Palette, 0 },  // 93
    { (void *)gObjectSprite2_090Tiles, (void *)gObjectSprite2_090Frames, (void *)gObjectSprite2_076Palette, 0 },  // 94
    { (void *)gObjectSprite2_109Tiles, (void *)gObjectSprite2_109Frames, (void *)gObjectSprite2_109Palette, 0 },  // 95
    { (void *)gObjectSprite2_091Tiles, (void *)gObjectSprite2_091Frames, (void *)gObjectSprite2_091Palette, 0 },  // 96
    { (void *)gObjectSprite2_092Tiles, (void *)gObjectSprite2_092Frames, (void *)gObjectSprite2_092Palette, 0 },  // 97
    { (void *)gObjectSprite2_019Tiles, (void *)gObjectSprite2_019Frames, (void *)gObjectSprite2_019Palette, 0 },  // 98
    { (void *)gObjectSprite2_018Tiles, (void *)gObjectSprite2_018Frames, (void *)gObjectSprite2_018Palette, 0 },  // 99
    { (void *)gObjectSprite2_005Tiles, (void *)gObjectSprite2_005Frames, (void *)gObjectSprite2_005Palette, 0 },  // 100
    { (void *)gObjectSprite2_006Tiles, (void *)gObjectSprite2_006Frames, (void *)gObjectSprite2_006Palette, 0 },  // 101
    { (void *)gMonsterBattle024Tiles, (void *)gMonsterBattle024Frames, (void *)gMonsterPalette036Palette, 0 },  // 102
    { (void *)gMonsterBattle028Tiles, (void *)gMonsterBattle028Frames, (void *)gMonsterBattle028Palette, 0 },  // 103
    { (void *)gMonsterBattle029Tiles, (void *)gMonsterBattle029Frames, (void *)gMonsterBattle029Palette, 0 },  // 104
    { (void *)gMonsterOverworld014Tiles, (void *)gMonsterOverworld014Frames, (void *)gMonsterPalette024Palette, 0 },  // 105
    { (void *)gMonsterOverworld007Tiles, (void *)gMonsterOverworld007Frames, (void *)gMonsterPalette013Palette, 0 },  // 106
    { (void *)gMonsterOverworld025Tiles, (void *)gMonsterOverworld025Frames, (void *)gUnnamed002Palette, 0 },  // 107
    { (void *)gMonsterOverworld028Tiles, (void *)gMonsterOverworld028Frames, (void *)gMonsterOverworld028Palette, 0 },  // 108
    { (void *)gObjectSprite2_093Tiles, (void *)gObjectSprite2_093Frames, (void *)gObjectSprite2_093Palette, 0 },  // 109
    { (void *)gUnnamed003Tiles, (void *)gUnnamed003Frames, NULL, 0 },  // 110
    { (void *)gUnnamed003Tiles, (void *)gUnnamed003Frames, NULL, 0 },  // 111
    { (void *)gUnnamed001Tiles, (void *)gUnnamed001Frames, NULL, 0 },  // 112
    { (void *)gObjectSprite2_094Tiles, (void *)gObjectSprite2_094Frames, NULL, 0 },  // 113
    { (void *)gOverworldPlayer015Tiles, (void *)gOverworldPlayer015Frames, NULL, 0 },  // 114
    { (void *)gObjectSprite2_028Tiles, (void *)gObjectSprite2_028Frames, NULL, 0 },  // 115
    { (void *)gObjectSprite2_029Tiles, (void *)gObjectSprite2_029Frames, NULL, 0 },  // 116
    { (void *)gObjectSprite2_095Tiles, (void *)gObjectSprite2_095Frames, NULL, 0 },  // 117
    { (void *)gOverworldPlayer014Tiles, (void *)gOverworldPlayer014Frames, NULL, 0 },  // 118
    { (void *)gObjectSprite2_096Tiles, (void *)gObjectSprite2_096Frames, NULL, 0 },  // 119
    { (void *)gObjectSprite2_096Tiles, (void *)gObjectSprite2_096Frames, NULL, 0 },  // 120
    { (void *)gObjectSprite2_097Tiles, (void *)gObjectSprite2_097Frames, NULL, 0 },  // 121
    { (void *)gObjectSprite2_014Tiles, (void *)gObjectSprite2_014Frames, NULL, 0 },  // 122
    { (void *)gObjectSprite2_098Tiles, (void *)gObjectSprite2_098Frames, NULL, 0 },  // 123
    { (void *)gObjectSprite2_099Tiles, (void *)gObjectSprite2_099Frames, NULL, 0 },  // 124
    { (void *)gObjectSprite2_099Tiles, (void *)gObjectSprite2_099Frames, NULL, 0 },  // 125
    { (void *)gObjectSprite2_100Tiles, (void *)gObjectSprite2_100Frames, NULL, 0 },  // 126
    { (void *)gObjectSprite2_100Tiles, (void *)gObjectSprite2_100Frames, NULL, 0 },  // 127
    { (void *)gObjectSprite2_101Tiles, (void *)gObjectSprite2_101Frames, NULL, 0 },  // 128
    { (void *)gObjectSprite2_011Tiles, (void *)gObjectSprite2_011Frames, NULL, 0 },  // 129
    { (void *)gObjectSprite2_102Tiles, (void *)gObjectSprite2_102Frames, NULL, 0 },  // 130
    { (void *)gObjectSprite2_013Tiles, (void *)gObjectSprite2_013Frames, NULL, 0 },  // 131
    { (void *)gObjectSprite2_103Tiles, (void *)gObjectSprite2_103Frames, NULL, 0 },  // 132
    { (void *)gObjectSprite2_104Tiles, (void *)gObjectSprite2_104Frames, NULL, 0 },  // 133
    { (void *)gObjectSprite2_105Tiles, (void *)gObjectSprite2_105Frames, NULL, 0 },  // 134
    { (void *)gObjectSprite2_097Tiles, (void *)gObjectSprite2_097Frames, NULL, 0 },  // 135
    { (void *)gObjectSprite2_106Tiles, (void *)gObjectSprite2_106Frames, NULL, 0 },  // 136
};

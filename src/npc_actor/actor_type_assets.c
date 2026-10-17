#include "types.h"
#include "actor.h"
#include "gen/graphics/battle.h"
#include "gen/graphics/overworld.h"
#include "npc_actor.h"

// Sprites of spawned actors, indexed by actor kind; see docs/formats/graphics.md.
const ActorAssetRecord g_aActorTypeAssets[137] = {
    { (void *)gUnnamed001Tiles, (void *)gUnnamed001Frames, (void *)gUnnamed001Palette, 0 },  // 0
    { (void *)gActorSprite2_021Tiles, (void *)gActorSprite2_021Frames, (void *)gActorSprite2_021Palette, 0 },  // 1
    { (void *)gActorSprite2_022Tiles, (void *)gActorSprite2_022Frames, (void *)gOverworldPlayer006Palette, 0 },  // 2
    { (void *)gActorSprite2_023Tiles, (void *)gActorSprite2_023Frames, (void *)gActorSprite2_023Palette, 0 },  // 3
    { (void *)gUnnamed001Tiles, (void *)gUnnamed001Frames, (void *)gActorSprite2_024Palette, 0 },  // 4
    { (void *)gActorSprite2_025Tiles, (void *)gActorSprite2_025Frames, (void *)gActorSprite2_025Palette, 0 },  // 5
    { (void *)gActorSprite2_026Tiles, (void *)gActorSprite2_026Frames, (void *)gOverworldPlayer005Palette, 0 },  // 6
    { (void *)gActorSprite2_027Tiles, (void *)gActorSprite2_027Frames, (void *)gOverworldPlayer006Palette, 0 },  // 7
    { (void *)gActorSprite2_028Tiles, (void *)gActorSprite2_028Frames, (void *)gActorSprite2_028Palette, 0 },  // 8
    { (void *)gActorSprite2_029Tiles, (void *)gActorSprite2_029Frames, (void *)gActorSprite2_029Palette, 0 },  // 9
    { (void *)gActorSprite2_030Tiles, (void *)gActorSprite2_030Frames, (void *)gActorSprite2_030Palette, 0 },  // 10
    { (void *)gActorSprite2_031Tiles, (void *)gActorSprite2_031Frames, (void *)gActorSprite2_031Palette, 0 },  // 11
    { (void *)gDementorTiles, (void *)gDementorFrames, (void *)gDementorPalette, 0 },  // 12
    { (void *)gActorSprite2_032Tiles, (void *)gActorSprite2_032Frames, (void *)gActorSprite2_032Palette, 0 },  // 13
    { (void *)gActorSprite2_033Tiles, (void *)gActorSprite2_033Frames, (void *)gActorSprite2_033Palette, 0 },  // 14
    { (void *)gActorSprite2_007Tiles, (void *)gActorSprite2_007Frames, (void *)gActorSprite2_007Palette, 0 },  // 15
    { (void *)gActorSprite2_034Tiles, (void *)gActorSprite2_034Frames, (void *)gOverworldPlayer004Palette, 0 },  // 16
    { (void *)gActorSprite2_035Tiles, (void *)gActorSprite2_035Frames, (void *)gActorSprite2_035Palette, 0 },  // 17
    { (void *)gActorSprite2_036Tiles, (void *)gActorSprite2_036Frames, (void *)gActorSprite2_036Palette, 0 },  // 18
    { (void *)gActorSprite2_037Tiles, (void *)gActorSprite2_037Frames, (void *)gActorSprite2_037Palette, 0 },  // 19
    { (void *)gActorSprite2_038Tiles, (void *)gActorSprite2_038Frames, (void *)gActorSprite2_038Palette, 0 },  // 20
    { (void *)gActorSprite2_039Tiles, (void *)gActorSprite2_039Frames, (void *)gActorSprite2_039Palette, 0 },  // 21
    { (void *)gActorSprite2_040Tiles, (void *)gActorSprite2_040Frames, (void *)gActorSprite2_040Palette, 0 },  // 22
    { (void *)gActorSprite2_041Tiles, (void *)gActorSprite2_041Frames, (void *)gActorSprite2_041Palette, 0 },  // 23
    { (void *)gActorSprite2_042Tiles, (void *)gActorSprite2_042Frames, (void *)gActorSprite2_042Palette, 0 },  // 24
    { (void *)gActorSprite2_043Tiles, (void *)gActorSprite2_043Frames, (void *)gActorSprite2_043Palette, 0 },  // 25
    { (void *)gActorSprite2_044Tiles, (void *)gActorSprite2_044Frames, (void *)gActorSprite2_044Palette, 0 },  // 26
    { (void *)gActorSprite2_045Tiles, (void *)gActorSprite2_045Frames, (void *)gActorSprite2_045Palette, 0 },  // 27
    { (void *)gActorSprite2_046Tiles, (void *)gActorSprite2_046Frames, (void *)gActorSprite2_046Palette, 0 },  // 28
    { (void *)gActorSprite2_047Tiles, (void *)gActorSprite2_047Frames, (void *)gActorSprite2_047Palette, 0 },  // 29
    { (void *)gActorSprite2_048Tiles, (void *)gActorSprite2_048Frames, (void *)gActorSprite2_048Palette, 0 },  // 30
    { (void *)gHarryWalkTiles, (void *)gHarryWalkFrames, (void *)gOverworldPlayer004Palette, 0 },  // 31
    { (void *)gActorSprite2_008Tiles, (void *)gActorSprite2_008Frames, (void *)gOverworldPlayer006Palette, 0 },  // 32
    { (void *)gActorSprite2_049Tiles, (void *)gActorSprite2_049Frames, (void *)gActorSprite2_049Palette, 0 },  // 33
    { (void *)gActorSprite2_009Tiles, (void *)gActorSprite2_009Frames, (void *)gOverworldPlayer005Palette, 0 },  // 34
    { (void *)gActorSprite2_050Tiles, (void *)gActorSprite2_050Frames, (void *)gActorSprite2_050Palette, 0 },  // 35
    { (void *)gActorSprite2_004Tiles, (void *)gActorSprite2_004Frames, (void *)gActorSprite2_004Palette, 0 },  // 36
    { (void *)gActorSprite2_051Tiles, (void *)gActorSprite2_051Frames, (void *)gActorSprite2_051Palette, 0 },  // 37
    { (void *)gActorSprite2_052Tiles, (void *)gActorSprite2_052Frames, (void *)gActorSprite2_052Palette, 0 },  // 38
    { (void *)gActorSprite2_053Tiles, (void *)gActorSprite2_053Frames, (void *)gActorSprite2_053Palette, 0 },  // 39
    { (void *)gActorSprite2_053Tiles, (void *)gActorSprite2_053Frames, (void *)gActorSprite2_054Palette, 0 },  // 40
    { (void *)gActorSprite2_053Tiles, (void *)gActorSprite2_053Frames, (void *)gActorSprite2_055Palette, 0 },  // 41
    { (void *)gActorSprite2_053Tiles, (void *)gActorSprite2_053Frames, (void *)gActorSprite2_056Palette, 0 },  // 42
    { (void *)gActorSprite2_057Tiles, (void *)gActorSprite2_057Frames, (void *)gActorSprite2_057Palette, 0 },  // 43
    { (void *)gActorSprite2_057Tiles, (void *)gActorSprite2_057Frames, (void *)gActorSprite2_058Palette, 0 },  // 44
    { (void *)gActorSprite2_057Tiles, (void *)gActorSprite2_057Frames, (void *)gActorSprite2_059Palette, 0 },  // 45
    { (void *)gActorSprite2_057Tiles, (void *)gActorSprite2_057Frames, (void *)gActorSprite2_060Palette, 0 },  // 46
    { (void *)gActorSprite2_061Tiles, (void *)gActorSprite2_061Frames, (void *)gActorSprite2_061Palette, 0 },  // 47
    { (void *)gActorSprite2_061Tiles, (void *)gActorSprite2_061Frames, (void *)gActorSprite2_062Palette, 0 },  // 48
    { (void *)gActorSprite2_061Tiles, (void *)gActorSprite2_061Frames, (void *)gActorSprite2_063Palette, 0 },  // 49
    { (void *)gActorSprite2_061Tiles, (void *)gActorSprite2_061Frames, (void *)gActorSprite2_064Palette, 0 },  // 50
    { (void *)gActorSprite2_065Tiles, (void *)gActorSprite2_065Frames, (void *)gActorSprite2_065Palette, 0 },  // 51
    { (void *)gActorSprite2_065Tiles, (void *)gActorSprite2_065Frames, (void *)gActorSprite2_066Palette, 0 },  // 52
    { (void *)gActorSprite2_065Tiles, (void *)gActorSprite2_065Frames, (void *)gActorSprite2_067Palette, 0 },  // 53
    { (void *)gActorSprite2_065Tiles, (void *)gActorSprite2_065Frames, (void *)gActorSprite2_068Palette, 0 },  // 54
    { (void *)gActorSprite2_069Tiles, (void *)gActorSprite2_069Frames, (void *)gActorSprite2_069Palette, 0 },  // 55
    { (void *)gActorSprite2_069Tiles, (void *)gActorSprite2_069Frames, (void *)gActorSprite2_070Palette, 0 },  // 56
    { (void *)gActorSprite2_069Tiles, (void *)gActorSprite2_069Frames, (void *)gActorSprite2_071Palette, 0 },  // 57
    { (void *)gActorSprite2_069Tiles, (void *)gActorSprite2_069Frames, (void *)gActorSprite2_072Palette, 0 },  // 58
    { (void *)gActorSprite2_073Tiles, (void *)gActorSprite2_073Frames, (void *)gActorSprite2_073Palette, 0 },  // 59
    { (void *)gActorSprite2_073Tiles, (void *)gActorSprite2_073Frames, (void *)gActorSprite2_074Palette, 0 },  // 60
    { (void *)gActorSprite2_073Tiles, (void *)gActorSprite2_073Frames, (void *)gActorSprite2_075Palette, 0 },  // 61
    { (void *)gActorSprite2_073Tiles, (void *)gActorSprite2_073Frames, (void *)gActorSprite2_076Palette, 0 },  // 62
    { (void *)gActorSprite2_077Tiles, (void *)gActorSprite2_077Frames, (void *)gActorSprite2_077Palette, 0 },  // 63
    { (void *)gActorSprite2_078Tiles, (void *)gActorSprite2_078Frames, (void *)gOverworldPlayer006Palette, 0 },  // 64
    { (void *)gActorSprite2_079Tiles, (void *)gActorSprite2_079Frames, (void *)gActorSprite2_079Palette, 0 },  // 65
    { (void *)gActorSprite2_080Tiles, (void *)gActorSprite2_080Frames, (void *)gActorSprite2_080Palette, 0 },  // 66
    { (void *)gActorSprite2_081Tiles, (void *)gActorSprite2_081Frames, (void *)gActorSprite2_081Palette, 0 },  // 67
    { (void *)gActorSprite2_082Tiles, (void *)gActorSprite2_082Frames, (void *)gOverworldPlayer005Palette, 0 },  // 68
    { (void *)gActorSprite2_083Tiles, (void *)gActorSprite2_083Frames, (void *)gOverworldPlayer004Palette, 0 },  // 69
    { (void *)gActorSprite2_084Tiles, (void *)gActorSprite2_084Frames, (void *)gActorSprite2_084Palette, 0 },  // 70
    { (void *)gActorSprite2_085Tiles, (void *)gActorSprite2_085Frames, (void *)gActorSprite2_085Palette, 0 },  // 71
    { (void *)gActorSprite2_085Tiles, (void *)gActorSprite2_085Frames, (void *)gActorSprite2_054Palette, 0 },  // 72
    { (void *)gActorSprite2_085Tiles, (void *)gActorSprite2_085Frames, (void *)gActorSprite2_055Palette, 0 },  // 73
    { (void *)gActorSprite2_085Tiles, (void *)gActorSprite2_085Frames, (void *)gActorSprite2_056Palette, 0 },  // 74
    { (void *)gActorSprite2_086Tiles, (void *)gActorSprite2_086Frames, (void *)gActorSprite2_086Palette, 0 },  // 75
    { (void *)gActorSprite2_086Tiles, (void *)gActorSprite2_086Frames, (void *)gActorSprite2_058Palette, 0 },  // 76
    { (void *)gActorSprite2_086Tiles, (void *)gActorSprite2_086Frames, (void *)gActorSprite2_059Palette, 0 },  // 77
    { (void *)gActorSprite2_086Tiles, (void *)gActorSprite2_086Frames, (void *)gActorSprite2_060Palette, 0 },  // 78
    { (void *)gActorSprite2_087Tiles, (void *)gActorSprite2_087Frames, (void *)gActorSprite2_087Palette, 0 },  // 79
    { (void *)gActorSprite2_087Tiles, (void *)gActorSprite2_087Frames, (void *)gActorSprite2_062Palette, 0 },  // 80
    { (void *)gActorSprite2_087Tiles, (void *)gActorSprite2_087Frames, (void *)gActorSprite2_063Palette, 0 },  // 81
    { (void *)gActorSprite2_087Tiles, (void *)gActorSprite2_087Frames, (void *)gActorSprite2_064Palette, 0 },  // 82
    { (void *)gActorSprite2_088Tiles, (void *)gActorSprite2_088Frames, (void *)gActorSprite2_088Palette, 0 },  // 83
    { (void *)gActorSprite2_088Tiles, (void *)gActorSprite2_088Frames, (void *)gActorSprite2_066Palette, 0 },  // 84
    { (void *)gActorSprite2_088Tiles, (void *)gActorSprite2_088Frames, (void *)gActorSprite2_067Palette, 0 },  // 85
    { (void *)gActorSprite2_088Tiles, (void *)gActorSprite2_088Frames, (void *)gActorSprite2_068Palette, 0 },  // 86
    { (void *)gActorSprite2_089Tiles, (void *)gActorSprite2_089Frames, (void *)gActorSprite2_089Palette, 0 },  // 87
    { (void *)gActorSprite2_089Tiles, (void *)gActorSprite2_089Frames, (void *)gActorSprite2_070Palette, 0 },  // 88
    { (void *)gActorSprite2_089Tiles, (void *)gActorSprite2_089Frames, (void *)gActorSprite2_071Palette, 0 },  // 89
    { (void *)gActorSprite2_089Tiles, (void *)gActorSprite2_089Frames, (void *)gActorSprite2_072Palette, 0 },  // 90
    { (void *)gActorSprite2_090Tiles, (void *)gActorSprite2_090Frames, (void *)gActorSprite2_090Palette, 0 },  // 91
    { (void *)gActorSprite2_090Tiles, (void *)gActorSprite2_090Frames, (void *)gActorSprite2_074Palette, 0 },  // 92
    { (void *)gActorSprite2_090Tiles, (void *)gActorSprite2_090Frames, (void *)gActorSprite2_075Palette, 0 },  // 93
    { (void *)gActorSprite2_090Tiles, (void *)gActorSprite2_090Frames, (void *)gActorSprite2_076Palette, 0 },  // 94
    { (void *)gActorSprite2_109Tiles, (void *)gActorSprite2_109Frames, (void *)gActorSprite2_109Palette, 0 },  // 95
    { (void *)gActorSprite2_091Tiles, (void *)gActorSprite2_091Frames, (void *)gActorSprite2_091Palette, 0 },  // 96
    { (void *)gActorSprite2_092Tiles, (void *)gActorSprite2_092Frames, (void *)gActorSprite2_092Palette, 0 },  // 97
    { (void *)gActorSprite2_019Tiles, (void *)gActorSprite2_019Frames, (void *)gActorSprite2_019Palette, 0 },  // 98
    { (void *)gActorSprite2_018Tiles, (void *)gActorSprite2_018Frames, (void *)gActorSprite2_018Palette, 0 },  // 99
    { (void *)gActorSprite2_005Tiles, (void *)gActorSprite2_005Frames, (void *)gActorSprite2_005Palette, 0 },  // 100
    { (void *)gActorSprite2_006Tiles, (void *)gActorSprite2_006Frames, (void *)gActorSprite2_006Palette, 0 },  // 101
    { (void *)gMonsterBattle024Tiles, (void *)gMonsterBattle024Frames, (void *)gMonsterPalette036Palette, 0 },  // 102
    { (void *)gMonsterBattle028Tiles, (void *)gMonsterBattle028Frames, (void *)gMonsterBattle028Palette, 0 },  // 103
    { (void *)gMonsterBattle029Tiles, (void *)gMonsterBattle029Frames, (void *)gMonsterBattle029Palette, 0 },  // 104
    { (void *)gMonsterOverworld014Tiles, (void *)gMonsterOverworld014Frames, (void *)gMonsterPalette024Palette, 0 },  // 105
    { (void *)gMonsterOverworld007Tiles, (void *)gMonsterOverworld007Frames, (void *)gMonsterPalette013Palette, 0 },  // 106
    { (void *)gMonsterOverworld025Tiles, (void *)gMonsterOverworld025Frames, (void *)gUnnamed002Palette, 0 },  // 107
    { (void *)gMonsterOverworld028Tiles, (void *)gMonsterOverworld028Frames, (void *)gMonsterOverworld028Palette, 0 },  // 108
    { (void *)gActorSprite2_093Tiles, (void *)gActorSprite2_093Frames, (void *)gActorSprite2_093Palette, 0 },  // 109
    { (void *)gUnnamed003Tiles, (void *)gUnnamed003Frames, NULL, 0 },  // 110
    { (void *)gUnnamed003Tiles, (void *)gUnnamed003Frames, NULL, 0 },  // 111
    { (void *)gUnnamed001Tiles, (void *)gUnnamed001Frames, NULL, 0 },  // 112
    { (void *)gActorSprite2_094Tiles, (void *)gActorSprite2_094Frames, NULL, 0 },  // 113
    { (void *)gOverworldPlayer015Tiles, (void *)gOverworldPlayer015Frames, NULL, 0 },  // 114
    { (void *)gActorSprite2_028Tiles, (void *)gActorSprite2_028Frames, NULL, 0 },  // 115
    { (void *)gActorSprite2_029Tiles, (void *)gActorSprite2_029Frames, NULL, 0 },  // 116
    { (void *)gActorSprite2_095Tiles, (void *)gActorSprite2_095Frames, NULL, 0 },  // 117
    { (void *)gOverworldPlayer014Tiles, (void *)gOverworldPlayer014Frames, NULL, 0 },  // 118
    { (void *)gActorSprite2_096Tiles, (void *)gActorSprite2_096Frames, NULL, 0 },  // 119
    { (void *)gActorSprite2_096Tiles, (void *)gActorSprite2_096Frames, NULL, 0 },  // 120
    { (void *)gActorSprite2_097Tiles, (void *)gActorSprite2_097Frames, NULL, 0 },  // 121
    { (void *)gActorSprite2_014Tiles, (void *)gActorSprite2_014Frames, NULL, 0 },  // 122
    { (void *)gActorSprite2_098Tiles, (void *)gActorSprite2_098Frames, NULL, 0 },  // 123
    { (void *)gActorSprite2_099Tiles, (void *)gActorSprite2_099Frames, NULL, 0 },  // 124
    { (void *)gActorSprite2_099Tiles, (void *)gActorSprite2_099Frames, NULL, 0 },  // 125
    { (void *)gActorSprite2_100Tiles, (void *)gActorSprite2_100Frames, NULL, 0 },  // 126
    { (void *)gActorSprite2_100Tiles, (void *)gActorSprite2_100Frames, NULL, 0 },  // 127
    { (void *)gActorSprite2_101Tiles, (void *)gActorSprite2_101Frames, NULL, 0 },  // 128
    { (void *)gActorSprite2_011Tiles, (void *)gActorSprite2_011Frames, NULL, 0 },  // 129
    { (void *)gActorSprite2_102Tiles, (void *)gActorSprite2_102Frames, NULL, 0 },  // 130
    { (void *)gActorSprite2_013Tiles, (void *)gActorSprite2_013Frames, NULL, 0 },  // 131
    { (void *)gActorSprite2_103Tiles, (void *)gActorSprite2_103Frames, NULL, 0 },  // 132
    { (void *)gActorSprite2_104Tiles, (void *)gActorSprite2_104Frames, NULL, 0 },  // 133
    { (void *)gActorSprite2_105Tiles, (void *)gActorSprite2_105Frames, NULL, 0 },  // 134
    { (void *)gActorSprite2_097Tiles, (void *)gActorSprite2_097Frames, NULL, 0 },  // 135
    { (void *)gActorSprite2_106Tiles, (void *)gActorSprite2_106Frames, NULL, 0 },  // 136
};

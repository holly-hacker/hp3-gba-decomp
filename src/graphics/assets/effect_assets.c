#include "types.h"
#include "graphics/object.h"
#include "gen/BattleEffects.h"
#include "gen/BattleEffects2.h"

// Battle effect sprites used by object scripts (docs/formats/battle_scripts.md).
const ObjectAssetRecord g_aEffectObjectAssets[17] = {
    { (void *)gBattleEffect005Tiles, (void *)gBattleEffect005Frames, (void *)gBattleEffect005Palette, 3 }, // 0
    { (void *)gBattleEffect006Tiles, (void *)gBattleEffect006Frames, (void *)gBattleEffect005Palette, 3 }, // 1
    { (void *)gBattleEffect007Tiles, (void *)gBattleEffect007Frames, (void *)gBattleEffect005Palette, 3 }, // 2
    { (void *)gBattleEffect008Tiles, (void *)gBattleEffect008Frames, (void *)gBattleEffect005Palette, 3 }, // 3
    { (void *)gBattleEffect009Tiles, (void *)gBattleEffect009Frames, (void *)gBattleEffect009Palette, 3 }, // 4
    { (void *)gBattleEffect010Tiles, (void *)gBattleEffect010Frames, (void *)gBattleEffect009Palette, 3 }, // 5
    { (void *)gBattleEffect011Tiles, (void *)gBattleEffect011Frames, (void *)gBattleEffect009Palette, 3 }, // 6
    { (void *)gBattleEffect012Tiles, (void *)gBattleEffect012Frames, (void *)gBattleEffect009Palette, 3 }, // 7
    { (void *)gBattleEffect013Tiles, (void *)gBattleEffect013Frames, (void *)gBattleEffect013Palette, 3 }, // 8
    { (void *)gBattleEffect014Tiles, (void *)gBattleEffect014Frames, (void *)gBattleEffect014Palette, 3 }, // 9
    { (void *)gBattleEffect001Tiles, (void *)gBattleEffect001Frames, (void *)gBattleEffect001Palette, 3 }, // 10
    { (void *)gBattleEffect015Tiles, (void *)gBattleEffect015Frames, (void *)gBattleEffect015Palette, 3 }, // 11
    { (void *)gBattleEffect016Tiles, (void *)gBattleEffect016Frames, (void *)gBattleEffect015Palette, 3 }, // 12
    { (void *)gBattleEffect017Tiles, (void *)gBattleEffect017Frames, (void *)gBattleEffect015Palette, 3 }, // 13
    { (void *)gBattleEffect018Tiles, (void *)gBattleEffect018Frames, (void *)gBattleEffect018Palette, 3 }, // 14
    { (void *)gBattleEffect019Tiles, (void *)gBattleEffect019Frames, (void *)gBattleEffect018Palette, 3 }, // 15
    { (void *)gBattleEffect020Tiles, (void *)gBattleEffect020Frames, (void *)gBattleEffect018Palette, 3 }, // 16
};

void *const g_apEffectPalettes[5] = {
    (void *)gBattleEffect021Palette,
    (void *)gBattleEffect022Palette,
    (void *)gBattleEffect023Palette,
    (void *)gBattleEffect024Palette,
    (void *)gBattleEffect025Palette,
};

// SetObjectAnim's animation table.
const ObjectAssetRecord g_aEffectAnimAssets[103] = {
    { (void *)gBattleEffect026Tiles, (void *)gBattleEffect026Frames, (void *)gBattleEffect026Palette, 5 }, // 0
    { (void *)gBattleEffect027Tiles, (void *)gBattleEffect027Frames, (void *)gBattleEffect027Palette, 5 }, // 1
    { (void *)gBattleEffect028Tiles, (void *)gBattleEffect028Frames, (void *)gBattleEffect028Palette, 5 }, // 2
    { (void *)gBattleEffect029Tiles, (void *)gBattleEffect029Frames, (void *)gBattleEffect029Palette, 5 }, // 3
    { (void *)gBattleEffect026Tiles, (void *)gBattleEffect026Frames, (void *)gBattleEffect026Palette, 5 }, // 4
    { (void *)gBattleEffect030Tiles, (void *)gBattleEffect030Frames, (void *)gBattleEffect030Palette, 5 }, // 5
    { (void *)gBattleEffect030Tiles, (void *)gBattleEffect030Frames, (void *)gBattleEffect030Palette, 5 }, // 6
    { (void *)gBattleEffect031Tiles, (void *)gBattleEffect031Frames, (void *)gBattleEffect031Palette, 5 }, // 7
    { (void *)gBattleEffect032Tiles, (void *)gBattleEffect032Frames, (void *)gBattleEffect032Palette, 5 }, // 8
    { (void *)gBattleEffect033Tiles, (void *)gBattleEffect033Frames, (void *)gBattleEffect033Palette, 5 }, // 9
    { (void *)gBattleEffect034Tiles, (void *)gBattleEffect034Frames, (void *)gBattleEffect034Palette, 5 }, // 10
    { (void *)gBattleEffect035Tiles, (void *)gBattleEffect035Frames, (void *)gBattleEffect035Palette, 5 }, // 11
    { (void *)gBattleEffect036Tiles, (void *)gBattleEffect036Frames, (void *)gBattleEffect036Palette, 5 }, // 12
    { (void *)gBattleEffect037Tiles, (void *)gBattleEffect037Frames, (void *)gBattleEffect003Palette, 5 }, // 13
    { (void *)gBattleEffect038Tiles, (void *)gBattleEffect038Frames, (void *)gBattleEffect038Palette, 5 }, // 14
    { (void *)gBattleEffect039Tiles, (void *)gBattleEffect039Frames, (void *)gBattleEffect039Palette, 5 }, // 15
    { (void *)gBattleEffect040Tiles, (void *)gBattleEffect040Frames, (void *)gBattleEffect040Palette, 5 }, // 16
    { (void *)gBattleEffect034Tiles, (void *)gBattleEffect034Frames, (void *)gBattleEffect034Palette, 5 }, // 17
    { (void *)gBattleEffect041Tiles, (void *)gBattleEffect041Frames, (void *)gBattleEffect041Palette, 3 }, // 18
    { (void *)gBattleEffect042Tiles, (void *)gBattleEffect042Frames, (void *)gBattleEffect042Palette, 3 }, // 19
    { (void *)gBattleEffect043Tiles, (void *)gBattleEffect043Frames, (void *)gBattleEffect043Palette, 3 }, // 20
    { (void *)gBattleEffect044Tiles, (void *)gBattleEffect044Frames, (void *)gBattleEffect044Palette, 5 }, // 21
    { (void *)gBattleEffect045Tiles, (void *)gBattleEffect045Frames, (void *)gBattleEffect045Palette, 5 }, // 22
    { (void *)gBattleEffect046Tiles, (void *)gBattleEffect046Frames, (void *)gBattleEffect046Palette, 5 }, // 23
    { (void *)gBattleEffect047Tiles, (void *)gBattleEffect047Frames, (void *)gBattleEffect047Palette, 5 }, // 24
    { (void *)gBattleEffect048Tiles, (void *)gBattleEffect048Frames, (void *)gBattleEffect048Palette, 5 }, // 25
    { (void *)gBattleEffect049Tiles, (void *)gBattleEffect049Frames, (void *)gBattleEffect049Palette, 5 }, // 26
    { (void *)gBattleEffect026Tiles, (void *)gBattleEffect026Frames, (void *)gBattleEffect026Palette, 5 }, // 27
    { (void *)gBattleEffect050Tiles, (void *)gBattleEffect050Frames, (void *)gBattleEffect050Palette, 5 }, // 28
    { (void *)gBattleEffect051Tiles, (void *)gBattleEffect051Frames, (void *)gBattleEffect051Palette, 3 }, // 29
    { (void *)gBattleEffect052Tiles, (void *)gBattleEffect052Frames, (void *)gBattleEffect052Palette, 5 }, // 30
    { (void *)gBattleEffect053Tiles, (void *)gBattleEffect053Frames, (void *)gBattleEffect053Palette, 5 }, // 31
    { (void *)gBattleEffect035Tiles, (void *)gBattleEffect035Frames, (void *)gBattleEffect035Palette, 5 }, // 32
    { (void *)gBattleEffect054Tiles, (void *)gBattleEffect054Frames, (void *)gBattleEffect054Palette, 3 }, // 33
    { (void *)gBattleEffect054Tiles, (void *)gBattleEffect054Frames, (void *)gBattleEffect054Palette, 3 }, // 34
    { (void *)gBattleEffect055Tiles, (void *)gBattleEffect055Frames, (void *)gBattleEffect055Palette, 3 }, // 35
    { (void *)gBattleEffect026Tiles, (void *)gBattleEffect026Frames, (void *)gBattleEffect026Palette, 3 }, // 36
    { (void *)gBattleEffect056Tiles, (void *)gBattleEffect056Frames, (void *)gBattleEffect056Palette, 3 }, // 37
    { (void *)gBattleEffect057Tiles, (void *)gBattleEffect057Frames, (void *)gBattleEffect057Palette, 5 }, // 38
    { (void *)gBattleEffect058Tiles, (void *)gBattleEffect058Frames, (void *)gBattleEffect058Palette, 5 }, // 39
    { (void *)gBattleEffect059Tiles, (void *)gBattleEffect059Frames, (void *)gBattleEffect059Palette, 5 }, // 40
    { (void *)gBattleEffect060Tiles, (void *)gBattleEffect060Frames, (void *)gBattleEffect060Palette, 5 }, // 41
    { (void *)gBattleEffect061Tiles, (void *)gBattleEffect061Frames, (void *)gBattleEffect061Palette, 5 }, // 42
    { (void *)gBattleEffect026Tiles, (void *)gBattleEffect026Frames, (void *)gBattleEffect026Palette, 3 }, // 43
    { (void *)gBattleEffect062Tiles, (void *)gBattleEffect062Frames, (void *)gBattleEffect062Palette, 5 }, // 44
    { (void *)gBattleEffect062Tiles, (void *)gBattleEffect062Frames, (void *)gBattleEffect062Palette, 5 }, // 45
    { (void *)gBattleEffect2_001Tiles, (void *)gBattleEffect2_001Frames, (void *)gBattleEffect2_001Palette, 5 }, // 46
    { (void *)gBattleEffect063Tiles, (void *)gBattleEffect063Frames, (void *)gBattleEffect063Palette, 5 }, // 47
    { (void *)gBattleEffect013Tiles, (void *)gBattleEffect013Frames, (void *)gBattleEffect013Palette, 3 }, // 48
    { (void *)gBattleEffect064Tiles, (void *)gBattleEffect064Frames, (void *)gBattleEffect064Palette, 3 }, // 49
    { (void *)gBattleEffect065Tiles, (void *)gBattleEffect065Frames, (void *)gBattleEffect065Palette, 3 }, // 50
    { (void *)gBattleEffect066Tiles, (void *)gBattleEffect066Frames, (void *)gBattleEffect066Palette, 3 }, // 51
    { (void *)gBattleEffect067Tiles, (void *)gBattleEffect067Frames, (void *)gBattleEffect067Palette, 3 }, // 52
    { (void *)gBattleEffect068Tiles, (void *)gBattleEffect068Frames, (void *)gBattleEffect068Palette, 3 }, // 53
    { (void *)gBattleEffect069Tiles, (void *)gBattleEffect069Frames, (void *)gBattleEffect069Palette, 5 }, // 54
    { (void *)gBattleEffect070Tiles, (void *)gBattleEffect070Frames, (void *)gBattleEffect070Palette, 5 }, // 55
    { (void *)gBattleEffect071Tiles, (void *)gBattleEffect071Frames, (void *)gBattleEffect071Palette, 5 }, // 56
    { (void *)gBattleEffect072Tiles, (void *)gBattleEffect072Frames, (void *)gBattleEffect004Palette, 5 }, // 57
    { (void *)gBattleEffect073Tiles, (void *)gBattleEffect073Frames, (void *)gBattleEffect073Palette, 5 }, // 58
    { (void *)gBattleEffect074Tiles, (void *)gBattleEffect074Frames, (void *)gBattleEffect074Palette, 5 }, // 59
    { (void *)gBattleEffect070Tiles, (void *)gBattleEffect070Frames, (void *)gBattleEffect070Palette, 5 }, // 60
    { (void *)gBattleEffect075Tiles, (void *)gBattleEffect075Frames, (void *)gBattleEffect075Palette, 5 }, // 61
    { (void *)gBattleEffect032Tiles, (void *)gBattleEffect032Frames, (void *)gBattleEffect076Palette, 5 }, // 62
    { (void *)gBattleEffect032Tiles, (void *)gBattleEffect032Frames, (void *)gBattleEffect077Palette, 5 }, // 63
    { (void *)gBattleEffect032Tiles, (void *)gBattleEffect032Frames, (void *)gBattleEffect078Palette, 5 }, // 64
    { (void *)gBattleEffect079Tiles, (void *)gBattleEffect079Frames, (void *)gBattleEffect079Palette, 5 }, // 65
    { (void *)gBattleEffect080Tiles, (void *)gBattleEffect080Frames, (void *)gBattleEffect080Palette, 5 }, // 66
    { (void *)gBattleEffect081Tiles, (void *)gBattleEffect081Frames, (void *)gBattleEffect081Palette, 5 }, // 67
    { (void *)gBattleEffect082Tiles, (void *)gBattleEffect082Frames, (void *)gBattleEffect082Palette, 5 }, // 68
    { (void *)gBattleEffect083Tiles, (void *)gBattleEffect083Frames, (void *)gBattleEffect083Palette, 5 }, // 69
    { (void *)gBattleEffect035Tiles, (void *)gBattleEffect035Frames, (void *)gBattleEffect035Palette, 5 }, // 70
    { (void *)gBattleEffect084Tiles, (void *)gBattleEffect084Frames, (void *)gBattleEffect084Palette, 5 }, // 71
    { (void *)gBattleEffect085Tiles, (void *)gBattleEffect085Frames, (void *)gBattleEffect085Palette, 5 }, // 72
    { (void *)gBattleEffect086Tiles, (void *)gBattleEffect086Frames, (void *)gBattleEffect086Palette, 5 }, // 73
    { (void *)gBattleEffect087Tiles, (void *)gBattleEffect087Frames, (void *)gBattleEffect087Palette, 3 }, // 74
    { (void *)gBattleEffect088Tiles, (void *)gBattleEffect088Frames, (void *)gBattleEffect088Palette, 3 }, // 75
    { (void *)gBattleEffect089Tiles, (void *)gBattleEffect089Frames, (void *)gBattleEffect089Palette, 3 }, // 76
    { (void *)gBattleEffect090Tiles, (void *)gBattleEffect090Frames, (void *)gBattleEffect090Palette, 5 }, // 77
    { (void *)gBattleEffect091Tiles, (void *)gBattleEffect091Frames, (void *)gBattleEffect091Palette, 5 }, // 78
    { (void *)gBattleEffect092Tiles, (void *)gBattleEffect092Frames, (void *)gBattleEffect092Palette, 5 }, // 79
    { (void *)gBattleEffect093Tiles, (void *)gBattleEffect093Frames, (void *)gBattleEffect079Palette, 5 }, // 80
    { (void *)gBattleEffect094Tiles, (void *)gBattleEffect094Frames, (void *)gBattleEffect094Palette, 5 }, // 81
    { (void *)gBattleEffect095Tiles, (void *)gBattleEffect095Frames, (void *)gBattleEffect095Palette, 5 }, // 82
    { (void *)gBattleEffect096Tiles, (void *)gBattleEffect096Frames, (void *)gBattleEffect096Palette, 5 }, // 83
    { (void *)gBattleEffect097Tiles, (void *)gBattleEffect097Frames, (void *)gBattleEffect097Palette, 3 }, // 84
    { (void *)gBattleEffect098Tiles, (void *)gBattleEffect098Frames, (void *)gBattleEffect098Palette, 3 }, // 85
    { (void *)gBattleEffect099Tiles, (void *)gBattleEffect099Frames, (void *)gBattleEffect099Palette, 3 }, // 86
    { (void *)gBattleEffect100Tiles, (void *)gBattleEffect100Frames, (void *)gBattleEffect100Palette, 3 }, // 87
    { (void *)gBattleEffect101Tiles, (void *)gBattleEffect101Frames, (void *)gBattleEffect101Palette, 5 }, // 88
    { (void *)gBattleEffect013Tiles, (void *)gBattleEffect013Frames, (void *)gBattleEffect013Palette, 3 }, // 89
    { (void *)gBattleEffect102Tiles, (void *)gBattleEffect102Frames, (void *)gBattleEffect102Palette, 5 }, // 90
    { (void *)gBattleEffect103Tiles, (void *)gBattleEffect103Frames, (void *)gBattleEffect103Palette, 5 }, // 91
    { (void *)gBattleEffect104Tiles, (void *)gBattleEffect104Frames, (void *)gBattleEffect104Palette, 5 }, // 92
    { (void *)gBattleEffect105Tiles, (void *)gBattleEffect105Frames, (void *)gBattleEffect105Palette, 5 }, // 93
    { (void *)gBattleEffect106Tiles, (void *)gBattleEffect106Frames, (void *)gBattleEffect106Palette, 5 }, // 94
    { (void *)gBattleEffect107Tiles, (void *)gBattleEffect107Frames, (void *)gBattleEffect107Palette, 5 }, // 95
    { (void *)gBattleEffect108Tiles, (void *)gBattleEffect108Frames, (void *)gBattleEffect108Palette, 5 }, // 96
    { (void *)gBattleEffect109Tiles, (void *)gBattleEffect109Frames, (void *)gBattleEffect109Palette, 3 }, // 97
    { (void *)gBattleEffect110Tiles, (void *)gBattleEffect110Frames, (void *)gBattleEffect110Palette, 3 }, // 98
    { (void *)gBattleEffect111Tiles, (void *)gBattleEffect111Frames, (void *)gBattleEffect111Palette, 3 }, // 99
    { (void *)gBattleEffect112Tiles, (void *)gBattleEffect112Frames, (void *)gBattleEffect112Palette, 3 }, // 100
    { (void *)gBattleEffect113Tiles, (void *)gBattleEffect113Frames, (void *)gBattleEffect113Palette, 3 }, // 101
    { (void *)gBattleEffect114Tiles, (void *)gBattleEffect114Frames, (void *)gBattleEffect114Palette, 3 }, // 102
};

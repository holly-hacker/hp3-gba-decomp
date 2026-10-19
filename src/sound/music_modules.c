#include "sound.h"
#include "sound_modules.h"

// Indexed by module id: PlayMusicModule loops one, PlayJingle plays one over the music.
const Module *const g_apMusicModules[52] = {
    &MusLeakyCauldron,  // 0
    &MusLeakyCauldronCellar,  // 1
    &MusBattle,  // 2
    &MusPause,  // 3
    &MusHogwartsMiscRoom2,  // 4
    &MusHogwartsHall,  // 5
    &MusHogwartsHallways,  // 6
    &MusHogwartsGrounds,  // 7
    &Module30,  // 8
    &MusHogwartsExpressCreepy,  // 9
    &Module24,  // 10
    &MusHogwartsMiscRoom1,  // 11
    &Module3,  // 12
    &MusHogwartsClassroom,  // 13
    &Module4,  // 14
    &Module31,  // 15
    &Module44,  // 16
    &Module43,  // 17
    &Module10,  // 18
    &Module47,  // 19
    &Module36,  // 20
    &Module37,  // 21
    &Module46,  // 22
    &Module35,  // 23
    &Module20,  // 24
    &SfxTimeSkip,  // 25
    &SfxGetKeyItem,  // 26
    &SfxLevelUp,  // 27
    &Module16,  // 28
    &MusBattleVictory,  // 29
    &Module29,  // 30
    &Module42,  // 31
    &Module49,  // 32
    &MusTitle,  // 33
    &Module6,  // 34
    &Module7,  // 35
    &Module11,  // 36
    &Module13,  // 37
    &Module12,  // 38
    &Module21,  // 39
    &SfxShortcutUp,  // 40
    &SfxShortcutDown,  // 41
    &Module14,  // 42
    &Module27,  // 43
    &Module15,  // 44
    &Module17,  // 45
    &MusBattleBoss,  // 46
    &Module48,  // 47
    &Module5,  // 48
    &Module45,  // 49
    &Module32,  // 50
    &MusHogwartsExpress,  // 51
};

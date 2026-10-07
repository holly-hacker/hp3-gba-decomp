#include "types.h"
#include "menu/minigame_difficulty_select.h"

const u32 g_adwMinigameDifficultyTextIds[4] = {
    0x5A6,  // "Easy"
    0x5A7,  // "Medium"
    0x5A8,  // "Hard"
    0x5A9,  // "Erase High Scores"
};

const GameMode g_aeMinigameDifficultyModes[4] = {
    WizardCrackerPopItMinigame,
    HippogriffGlideMinigame,
    RiddikulusMinigame,
    DivinationTeaMinigame,
};

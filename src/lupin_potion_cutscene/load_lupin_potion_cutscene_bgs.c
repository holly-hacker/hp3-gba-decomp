#include "lupin_potion_cutscene.h"
#include "background.h"
#include "gen/graphics/minigames/hippogriff.h"

void LoadLupinPotionCutsceneBgs(void)
{
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwLupinPotionBg0Control);
    SetBgControl(1, g_dwLupinPotionBg1Control);
    SetBgControl(2, g_dwLupinPotionTextBgControl);
    SetBgControl(3, g_dwLupinPotionBg3Control);
    LoadBgGraphic(3, gHippogriffFliesIntoAirGraphic, 0, 0, 0, 0);
    LoadBgGraphic(1, gHippogriffLanguageMinigameBgs015, 0, 0, 0, 0);
    LoadBgGraphic(2, gHippogriffLanguageMinigameBgs016, 0, 0, 0, 0);
    LoadBgGraphic(0, gHippogriffLanguageMinigameBgs017, 0, 0, 0, 0);
    SetBgScrollFixed(0, -0x280000, 0);
    SetBgScrollFixed(1, 0x390000, 0x200000);
    SetBgScrollFixed(2, 0x90000, 0x200000);
    SetBgScrollFixed(3, 0, 0);
}

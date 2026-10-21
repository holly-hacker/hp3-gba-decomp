#include "types.h"
#include "background.h"
#include "input.h"
#include "sound.h"
#include "menu_icon.h"
#include "hedwig_minigame.h"
#include "owl_name_select.h"
#include "owl_name_select_inline.h"

void StepOwlNameSelectChoice(void)
{
    u32 choice;
    u32 max;

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
    {
        choice = g_saveStateBlock.owlCareKit.bNameIndex;
        max = 13;
    }
    else
    {
        choice = g_saveStateBlock.owlCareKit.bTypeIndex;
        max = 2;
    }
    StepCursorLeftRightHeld(&choice, 0, max, 1, 0);

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
        g_saveStateBlock.owlCareKit.bNameIndex = choice;
    else
    {
        g_saveStateBlock.owlCareKit.bTypeIndex = choice;
        SetOwlPaletteRow(g_apMenuIconActors[2]->oam.paletteNum);
    }

    ClearBgTilemapRect(2, 5, 18, 20, 2);
    DrawOwlNameSelectChoice();
    PlaySoundById(0);
}

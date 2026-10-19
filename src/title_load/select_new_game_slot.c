#include "types.h"
#include "background.h"
#include "modes.h"
#include "save.h"
#include "font.h"
#include "text.h"
#include "pause_menu.h"
#include "screen_transitions.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "title_load.h"
#include "title_new_inline.h"

// A slot holding a started game asks before it is overwritten.
void SelectNewGameSlot(void)
{
    if (g_saveManager.adwSlotValid[g_GameModeStackContext.dwModeScratchB]
        && (g_saveManager.aSlotPreview[g_GameModeStackContext.dwModeScratchB].bSaveFlags
            & PlaytimeCounterActive))
    {
        ExitSaveSlotScreen();
        ClearBgTilemap(2);
        ClearBgTilemap(1);
        g_GameModeStackContext.dwModeScratchB = 0;
        g_GameModeStackContext.dwModeState = 1;
        LoadBgGraphic(1, gSaveMenuBg1Graphic, 1, 0, 0, 0);
        BuildListMenu(&g_NewGameSlotConfirmationMenuDefinition);
        SelectTextFont(1, 0, -1);
        // "Do you want to overwrite this saved game?"
        PrintTextBox(0xC1, 0x78, 0x38, 0x90, GetDialogText(0x8E3), 1);
        SetBgScroll(0, 8, 0);
        PlayScreenTransitionInByIndex(0x3F, 2);
    }
    else
    {
        StartNewGame();
    }
}

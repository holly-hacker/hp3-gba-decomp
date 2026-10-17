#include "types.h"
#include "graphics/display.h"
#include "modes.h"
#include "pscreen_save.h"
#include "particles.h"
#include "game/save.h"
#include "default_menu.h"

void InitializeGameSave(void)
{
    u32 stringId;

    ClearObjPaletteSlots();
    InitializeMenuScreen(0x533, 9, 0, gSaveMenuBg1Graphic, 0, 0);  // "Save Game"

    if (g_saveManager.adwSlotValid[g_saveManager.dwActiveSlot] != 0
        && (g_saveManager.aSlotPreview[g_saveManager.dwActiveSlot].bSaveFlags & PlaytimeCounterActive))
    {
        // "Do you want to overwrite this saved game?" / "Do you want to save your current progress?"
        stringId = (g_PrevGameModeStackContext.dwCurrentGameMode == GameCompletedReplayCutscene) ? 0x8E4 : 0x8E3;
        ShowSaveConfirmationPrompt_candidate(stringId);
        g_GameModeStackContext.dwModeState = 8;
        g_GameModeStackContext.dwModeScratchB = 0;
    }
    else
    {
        ShowSavingMessage_candidate();
        g_GameModeStackContext.dwModeTimer = 1;
        g_GameModeStackContext.dwModeState = 2;
    }

    PlayScreenTransitionInByIndex(0x3F, 2);
}

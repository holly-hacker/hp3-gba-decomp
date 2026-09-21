#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "game_save.h"
#include "graphics.h"
#include "main_menu.h"
#include "save.h"

void InitializeGameSave(void)
{
    u32 stringId;

    ClearResourceCacheSlots();
    sub_0801DF6C(0x533, 9, 0, g_SaveMenuBg1Graphic, 0, 0);  // "Save Game"

    if (g_saveManager.adwSlotValid[g_saveManager.dwActiveSlot] != 0
        && (g_saveManager.aSlotPreview[g_saveManager.dwActiveSlot].bFlags & 1))
    {
        // "Do you want to overwrite this saved game?" / "Do you want to save your current progress?"
        stringId = (g_PrevGameModeCtx.dwCurrentGameMode == GameCompletedReplayCutscene) ? 0x8E4 : 0x8E3;
        ShowSaveConfirmationPrompt_candidate(stringId);
        g_GameModeStackContext.dwModeState_candidate = 8;
        g_GameModeStackContext.dwModeScratchB_candidate = 0;
    }
    else
    {
        ShowSavingMessage_candidate();
        g_GameModeStackContext.dwModeTimer_candidate = 1;
        g_GameModeStackContext.dwModeState_candidate = 2;
    }

    PlayScreenTransitionInByIndex_candidate(0x3F, 2);
}

#include "types.h"
#include "audio.h"
#include "battle.h"
#include "game_modes.h"
#include "main_menu.h"
#include "save.h"

void HandleSaveLoadContinuation(void)
{
    ExitSaveSlotScreen_candidate();

    if (g_bSaveSlotScreenResult != SaveSlotResultCancelled)
    {
        g_saveManager.dwActiveSlot = g_GameModeStackContext.dwModeScratchB_candidate;
        DisableKrawall();
        LoadSaveSlot(g_saveManager.dwActiveSlot);
        EnableKrawall();

        if (ValidateSaveSlot(g_saveManager.dwActiveSlot))
        {
            sub_0802B0F4();
            sub_0803BD48(g_saveManager.dwActiveSlot);

            if (g_saveStateBlock.bSaveFlags & ContinueRestartsIntro)
            {
                InitRoomState();
                g_saveStateBlock.bSaveFlags &= ~ContinueRestartsIntro;
                PushGameMode(Intro);
            }
            else
                PushGameMode_3(Overworld, 2, g_bCurrentRoomId, 0xFF);
        }
    }
}

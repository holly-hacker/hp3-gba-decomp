#include "types.h"
#include "sound.h"
#include "battle/battle.h"
#include "modes.h"
#include "menu/main_menu.h"
#include "overworld/room.h"
#include "save.h"
#include "map.h"

void HandleSaveLoadContinuation(void)
{
    ExitSaveSlotScreen_candidate();

    if (g_bSaveSlotScreenResult != SaveSlotResultCancelled)
    {
        g_saveManager.dwActiveSlot = g_GameModeStackContext.dwModeScratchB;
        DisableKrawall();
        LoadSaveSlot(g_saveManager.dwActiveSlot);
        EnableKrawall();

        if (ValidateSaveSlot(g_saveManager.dwActiveSlot))
        {
            ClearRoomActorStateBuffer();
            UnpackSaveSlot(g_saveManager.dwActiveSlot);

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

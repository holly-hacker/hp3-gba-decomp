#include "sound.h"
#include "modes.h"
#include "background.h"
#include "actor.h"
#include "cursor.h"
#include "particles.h"
#include "default_menu.h"
#include "pscreen_save_inline.h"

void ResolveSaveConfirmation(void)
{
    if (g_GameModeStackContext.dwModeScratchB == 0)
    {
        // "No": return to wherever the save was opened from.
        if (g_PrevGameModeStackContext.dwCurrentGameMode == InGameMenu
            || g_PrevGameModeStackContext.dwCurrentGameMode == InGameMenuFadeIn)
            PushGameMode(InGameMenu);
        else
            PushGameMode(MainMenu);

        PlaySoundById(2);
    }
    else
    {
        ClearBgTilemapRect(2, 3, 6, 0x18, 8);
        ReleaseMenuCursor(g_pMenuCursorActor);
        g_pMenuCursorActor = NULL;
        FreeAllParticleEmitters();
        FreeAllParticles();
        FreeAllActors(&g_ActiveActorListState.pHead);
        ShowSavingMessage();
        g_GameModeStackContext.dwModeState = 2;
        g_GameModeStackContext.dwModeTimer = 0x14;
        PlaySoundById(1);
    }
}

#include "types.h"
#include "background.h"
#include "sound.h"
#include "modes.h"
#include "save.h"
#include "actor.h"
#include "cursor.h"
#include "particles.h"
#include "default_menu.h"
#include "screen_transitions.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "title_load.h"
#include "title_new.h"

// The overwrite prompt's selection: No returns to the slot list, Yes starts the game.
void ResolveOverwriteConfirmation(void)
{
    u32 slot;

    switch (g_GameModeStackContext.dwModeScratchB)
    {
    case 0:
        PlaySoundById(2);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        ClearBgTilemap(2);
        ClearBgTilemap(1);
        ReleaseMenuCursor(g_pMenuCursorActor);
        FreeAllParticleEmitters();
        FreeAllParticles();
        FreeAllActors(&g_ActiveActorListState.pHead);
        g_GameModeStackContext.dwModeScratchB = g_saveManager.dwActiveSlot;
        InitializeMenuScreen(0x8CD, 9, 1, gMenuScreenGraphic, 0, 1);  // "New Game"
        g_GameModeStackContext.dwModeState = 0;
        SpawnSaveSlotActors();
        for (slot = 0; slot < SAVE_SLOT_COUNT; slot++)
            DrawSaveSlot(slot, g_GameModeStackContext.dwModeScratchB);
        PlayScreenTransitionInByIndex(0x3F, 2);
        break;

    case 1:
        PlaySoundById(1);
        g_GameModeStackContext.dwModeScratchB = g_saveManager.dwActiveSlot;
        StartNewGame();
        break;
    }
}

#pragma once

#include "types.h"
#include "background.h"
#include "modes.h"
#include "save.h"
#include "actor.h"
#include "default_menu.h"
#include "screen_transitions.h"
#include "title_new.h"

// The ROM compiles ExitSaveSlotScreen into SelectNewGameSlot and also keeps an
// out-of-line copy, as one translation unit with an inline definition would. The
// file that emits the out-of-line copy defines the linkage macro as empty.
#ifndef EXIT_SAVE_SLOT_SCREEN_LINKAGE
#define EXIT_SAVE_SLOT_SCREEN_LINKAGE extern inline
#endif

EXIT_SAVE_SLOT_SCREEN_LINKAGE void ExitSaveSlotScreen(void)
{
    g_saveManager.dwActiveSlot = (u8)g_GameModeStackContext.dwModeScratchB;
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ExitMenuScreen();
    ResetBgLayer(0);
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 0;
    FreeAllActors(&g_ActiveActorListState.pHead);
}

#include "types.h"
#include "area.h"
#include "background.h"
#include "battle/battle.h"
#include "char_block.h"
#include "color.h"
#include "interrupts.h"
#include "modes.h"
#include "mem.h"
#include "actor.h"
#include "minigame_menu.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_script.h"
#include "flipbook.h"
#include "hero.h"
#include "map.h"
#include "sound.h"
#include "move.h"
#include "screen_transitions.h"
#include "main.h"

// Overworld mode's pDestroyFn. Plays the outgoing screen transition, then
// tears down the overworld's actors, palettes and lists. The mode being
// pushed (pending) decides the transition and which state is kept for the
// mode that returns to the overworld.
void ExitOverworldScreen(void)
{
    if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == Battle)
    {
        PlayScreenTransitionOutByIndex(0x3F, 0xD);
    }
    else if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == InGameMenu)
    {
        SetScreenDarkenParams_candidate(0, 8);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        SetScreenDarkenParams_candidate(0, 8);
    }
    else
    {
        PlayScreenTransitionOutByIndex(0x3F, 2);
    }

    StopRoomScriptChains();
    FreeRoomSharedTileset();
    sub_0802B210();

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == Battle
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == InGameMenu
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == Options
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == BoggartMinigame
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == DementorMinigame
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == WizardCrackerPopItMinigame
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == HelpTopicScreen
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == ClockSkipCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == HogwartsUpNightCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == CoolTrainCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == UnusedChristmasArrivedCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == SiriusBlackCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == PeterPettigrewCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == RonSleepingCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == TimeTurnerPermissionCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == HippogriffFliesIntoAirCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == HarryArrivedAtHogwartsCutscene)
        sub_0802B08C();

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == HarryPatronusCutscene
        && g_dwPendingGameMode.dwCurrentGameModeArg1 == 1)
        sub_0802B08C();

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == BuckbeakMinigame
        && g_dwPendingGameMode.dwCurrentGameModeArg3 != 2)
        sub_0802B08C();

    if (g_dwPendingCameraFocusFlag != 0)
        RestorePendingCameraFocus_candidate(g_pPendingCameraFocus_candidate);

    sub_08024918();
    RestoreDefaultVBlankCallback();

    if (g_dwGameModeFlags & 0x80000)
        g_dwGameModeFlags |= 0x400000;

    sub_0803FF04();
    FreeAllParticleEmitters();
    FreeAllParticles();
    UnreserveObjPaletteSlot(1);
    UnreserveObjPaletteSlot(2);
    FreeAllActors(&g_ActiveActorListState.pHead);
    ResetPaletteAnimations();
    ResetBgLayer(0);
    sub_080203CC();
    FreeBgTileAnimations();

    g_dwGameModeFlags &= ~0x40000000;
}

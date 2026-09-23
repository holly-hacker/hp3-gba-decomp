#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "mem.h"
#include "minigame_menu.h"
#include "overworld.h"
#include "room.h"
#include "room_script.h"

// Overworld mode's pDestroyFn. Plays the outgoing screen transition, then
// tears down the overworld's objects, palettes and lists. The mode being
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
        sub_0803D420(0, 8);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        sub_0803D420(0, 8);
    }
    else
    {
        PlayScreenTransitionOutByIndex(0x3F, 2);
    }

    sub_08005D88();
    sub_0802DDAC();
    sub_0802B210();

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == Battle
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == InGameMenu
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == Options
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == RiddikulusMinigame
        || (g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == HarryVsDementorsMinigame
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

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == HippogriffGlideMinigame
        && g_dwPendingGameMode.dwCurrentGameModeArg3 != 2)
        sub_0802B08C();

    if (g_dwPendingCameraFocusFlag != 0)
        RestorePendingCameraFocus_candidate(g_pPendingCameraFocus_candidate);

    sub_08024918();
    sub_08026254();

    if (g_dwGameModeFlags & 0x80000)
        g_dwGameModeFlags |= 0x400000;

    sub_0803FF04();
    sub_080316D4();
    sub_0803171C();
    sub_08030960(1);
    sub_08030960(2);
    sub_080015D4(&g_ActiveObjectListState.pHead);
    sub_0800D2DC();
    sub_08007AA8(0);
    sub_080203CC();
    sub_0800A914();

    g_dwGameModeFlags &= ~0x40000000;
}

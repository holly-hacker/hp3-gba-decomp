#include "area.h"
#include "background.h"
#include "char_block.h"
#include "color.h"
#include "interrupts.h"
#include "modes.h"
#include "actor.h"
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
    if ((g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == Battle)
    {
        PlayScreenTransitionOutByIndex(0x3F, 0xD);
    }
    else if ((g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == InGameMenu)
    {
        SetPaletteFadeParams(0, 8);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        SetPaletteFadeParams(0, 8);
    }
    else
    {
        PlayScreenTransitionOutByIndex(0x3F, 2);
    }

    StopRoomScriptChains();
    FreeRoomCollision();
    FreeOverworldBgTileBitOffsets();

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == Battle
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == InGameMenu
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == Options
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == BoggartMinigame
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == DementorMinigame
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == WizardCrackerPopItMinigame
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == HelpTopicScreen
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == ClockSkipCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == HogwartsUpNightCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == CoolTrainCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == UnusedChristmasArrivedCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == SiriusBlackCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == PeterPettigrewCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == RonSleepingCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == TimeTurnerPermissionCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == HippogriffFliesIntoAirCutscene
        || (g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == HarryArrivedAtHogwartsCutscene)
        SaveRoomActorStateOnExit();

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == HarryPatronusCutscene
        && g_dwPendingGameMode.dwCurrentGameModeArg1 == 1)
        SaveRoomActorStateOnExit();

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~GameModeSwitchPending) == BuckbeakMinigame
        && g_dwPendingGameMode.dwCurrentGameModeArg3 != 2)
        SaveRoomActorStateOnExit();

    if (g_dwFieldSpellActive != 0)
        EndFieldSpellEffect(g_pFieldSpellEffectActor);

    FreePartyActors();
    RestoreDefaultVBlankCallback();

    if (g_dwGameModeFlags & GameModeFlagKeepCamera)
        g_dwGameModeFlags |= GameModeFlagFreezeViewOnExit;

    StopAllSoundEffects();
    FreeAllParticleEmitters();
    FreeAllParticles();
    UnreserveObjPaletteSlot(1);
    UnreserveObjPaletteSlot(2);
    FreeAllActors(&g_ActiveActorListState.pHead);
    ResetPaletteAnimations();
    ResetBgLayer(0);
    ClearRoomTileAnimations();
    FreeBgTileAnimations();

    g_dwGameModeFlags &= ~GameModeFlagUnk40000000;
}

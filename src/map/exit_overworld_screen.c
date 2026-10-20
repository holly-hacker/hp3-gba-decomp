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
    if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == Battle)
    {
        PlayScreenTransitionOutByIndex(0x3F, 0xD);
    }
    else if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == InGameMenu)
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
    FreeRoomSharedTileset();
    FreeOverworldBgTileBitOffsets();

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
        SaveRoomActorStateOnExit();

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == HarryPatronusCutscene
        && g_dwPendingGameMode.dwCurrentGameModeArg1 == 1)
        SaveRoomActorStateOnExit();

    if ((g_dwPendingGameMode.dwCurrentGameMode & ~0x80) == BuckbeakMinigame
        && g_dwPendingGameMode.dwCurrentGameModeArg3 != 2)
        SaveRoomActorStateOnExit();

    if (g_dwFieldSpellActive != 0)
        EndFieldSpellEffect(g_pFieldSpellEffectActor);

    FreePartyActors();
    RestoreDefaultVBlankCallback();

    if (g_dwGameModeFlags & GameModeFlagUnk80000)
        g_dwGameModeFlags |= GameModeFlagUnk400000;

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

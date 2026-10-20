#include "modes.h"
#include "input.h"
#include "sound.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "map.h"
#include "area.h"
#include "hero.h"
#include "main.h"
#include "trigger_actor.h"

void HandleOverworldPauseMenuInput(void)
{
    Actor *controlled;

    controlled = g_OverworldControlState.aSlots[g_OverworldControlState.bSlotIndex].pActor;
    HandleWanderingMonsterTouch();

    if (controlled->bActionSubState != 5
        && g_dwRoomChainRanThisFrame_candidate == 0
        && IsGameModeTransitionPending() == 0
        && g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bState != 1
        && (g_dwGameModeFlags & (GameModeFlagOverlayMode | GameModeFlagSwitchingMode
                                 | GameModeFlagScreenTransition | GameModeFlagModeChangeRequested)) == 0
        && (g_pPlayerActor->dwFlags & ActorFlagAnimPaused) == 0
        && g_pPlayerActor->bActionState == 0x21) {
        if (g_wKeysPressed & KeyStart) {
            if (g_dwPauseMenuLocked != 0) {
                PlaySoundById(3);
            }
            else if (g_dwPauseMenuCooldown == 0) {
                g_wKeysPressed = 0;
                SetActorVelocity(g_pPlayerActor, 0, 0);
                g_dwPauseMenuCooldown = 4;
                PlaySoundById(1);
                PushGameMode(InGameMenu);
                g_bRestoringRoomActors_candidate = 1;
            }
        }
        else if (g_wKeysPressed & KeySelect) {
            if (g_dwPauseMenuLocked != 0) {
                PlaySoundById(3);
            }
            else if (g_dwPauseMenuCooldown == 0) {
                g_wKeysPressed = 0;
                SetActorVelocity(g_pPlayerActor, 0, 0);
                g_dwPauseMenuCooldown = 4;
                PlaySoundById(1);
                PushGameMode(Options);
                g_bRestoringRoomActors_candidate = 1;
            }
        }
    }

    g_dwRoomChainRanThisFrame_candidate = 0;
}

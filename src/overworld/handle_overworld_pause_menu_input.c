#include "types.h"
#include "game_modes.h"
#include "input.h"
#include "audio.h"
#include "object.h"
#include "overworld.h"

void HandleOverworldPauseMenuInput(void)
{
    Object *controlled;

    controlled = g_OverworldControlState.aSlots[g_OverworldControlState.bSlotIndex].pObject;
    HandleWanderingMonsterTouch();

    if (controlled->bActionSubState != 5
        && g_dwRoomChainRanThisFrame_candidate == 0
        && IsGameModeTransitionPending() == 0
        && g_aQueuedObjectMoves[g_OverworldControlState.bSlotIndex].bState != 1
        && (g_dwGameModeFlags & 0x80000811) == 0
        && (g_pPlayerObject->dwFlags & ObjectFlagAnimPaused) == 0
        && g_pPlayerObject->bActionState == 0x21) {
        if (g_wKeysPressed & 8) {
            if (g_dwPauseMenuLocked != 0) {
                PlaySoundById(3);
            }
            else if (g_dwPauseMenuCooldown == 0) {
                g_wKeysPressed = 0;
                SetObjectVelocity(g_pPlayerObject, 0, 0);
                g_dwPauseMenuCooldown = 4;
                PlaySoundById(1);
                PushGameMode(InGameMenu);
                g_bUnk03005E18 = 1;
            }
        }
        else if (g_wKeysPressed & 4) {
            if (g_dwPauseMenuLocked != 0) {
                PlaySoundById(3);
            }
            else if (g_dwPauseMenuCooldown == 0) {
                g_wKeysPressed = 0;
                SetObjectVelocity(g_pPlayerObject, 0, 0);
                g_dwPauseMenuCooldown = 4;
                PlaySoundById(1);
                PushGameMode(Options);
                g_bUnk03005E18 = 1;
            }
        }
    }

    g_dwRoomChainRanThisFrame_candidate = 0;
}

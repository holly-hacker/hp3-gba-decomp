#include "types.h"
#include "actor.h"
#include "area.h"
#include "background.h"
#include "camera.h"
#include "event_actors.h"
#include "hero.h"
#include "main.h"
#include "modes.h"
#include "overworld/overworld.h"
#include "screen_transitions.h"

// Cuts the camera away to (wFocusX, wFocusY), runs the row/chain there, holds for
// dwStateTimer frames and cuts back to the player. Action states run 4, 6, 3, 5, 0, 1.
void TickCameraCutawayActor(Actor *actor)
{
    Actor *player = g_OverworldControlState.aSlots[g_OverworldControlState.bSlotIndex].pActor;

    switch (actor->bActionState)
    {
    case 0:
        if (--actor->wTimedMoveTicks == 0xFFFF)
        {
            g_apfnScreenTransitionsIn[actor->modeState.cutaway.bPlayerViewTransition](0x3F);
            SetActorActionState(actor, 1);
        }
        break;
    case 1:
        actor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    case 2:
        break;
    case 3:
        if (--actor->dwStateTimer == -1)
            SetActorActionState(actor, 5);
        break;
    case 4:
    {
        FixedPoint focus;

        if (g_dwGameModeFlags & (GameModeFlagUnk80 | GameModeFlagUnk4000 | GameModeFlagUnk800000))
            DisableBg(0);
        g_apfnScreenTransitionsOut[actor->modeState.cutaway.bPlayerViewTransition](0x3F);
        focus.x = actor->modeState.cutaway.wFocusX << 16;
        focus.y = actor->modeState.cutaway.wFocusY << 16;
        SetCameraFocusPinned(1, g_OverworldControlState.bSlotIndex);
        SnapCameraFocus(focus, g_OverworldControlState.bSlotIndex);
        RespawnGroupAndRunChain(actor->modeState.cutaway.bRespawnRow, actor->modeState.cutaway.bChainRow);
        SetActorActionState(actor, 6);
        actor->wTimedMoveTicks = 1;
        break;
    }
    case 5:
        g_apfnScreenTransitionsOut[actor->modeState.cutaway.bFocusViewTransition](0x3F);
        SetCameraFocusPinned(0, g_OverworldControlState.bSlotIndex);
        SnapCameraFocus(player->pos, g_OverworldControlState.bSlotIndex);
        SetCameraFollowTarget_candidate(player, g_PlayerCameraFocusOffset, g_OverworldControlState.bSlotIndex);
        SetActorActionState(actor, 0);
        actor->wTimedMoveTicks = 1;
        break;
    case 6:
        if (--actor->wTimedMoveTicks == 0xFFFF)
        {
            g_apfnScreenTransitionsIn[actor->modeState.cutaway.bFocusViewTransition](0x3F);
            SetActorActionState(actor, 3);
        }
        break;
    }

    actor->bActionFlags = 0;
}

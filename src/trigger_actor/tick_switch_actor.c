#include "types.h"
#include "area.h"
#include "trigger_actor.h"
#include "trigger_actor_inline.h"

// Variants: 0 flips on when a RoomActorType_WorldActor touches it; 1 is on while weighed
// down; 2 and 5 spring back nRearmTicks after turning on; 3 flips on when the
// player comes within bPauseRange; 4 re-arms nRearmTicks after each flip; 6-8
// flip on an A press; 9 and 10 only hold a frame; 11 has no sprite and
// follows bKeepOff. Action state 4 steps the animation to the far end, then
// runs the record's on or off chain; action state 1 destroys the switch.
void TickSwitchActor(Actor *pActor)
{
    if (pActor->wSubtype == 1 && SWITCH_STATE(pActor)->nPlateFlipping == 0)
    {
        if (SWITCH_STATE(pActor)->bStep == 1)
        {
            if (SWITCH_STATE(pActor)->nPlatePressed != 0)
            {
                pActor->bActionState = 4;
                SWITCH_STATE(pActor)->nPlateFlipping = 1;
                PlaySwitchSound(pActor);
            }
        }
        else
        {
            if (SWITCH_STATE(pActor)->nPlatePressed == 0)
            {
                pActor->bActionState = 4;
                SWITCH_STATE(pActor)->nPlateFlipping = 1;
                PlaySwitchSound(pActor);
            }
        }
    }

    switch (pActor->bActionState)
    {
    case 0:
        if (pActor->wSubtype == 11)
        {
            if ((SWITCH_STATE(pActor)->bStep == 1 && SWITCH_STATE(pActor)->bKeepOff == 0)
                || (SWITCH_STATE(pActor)->bStep == -1 && SWITCH_STATE(pActor)->bKeepOff != 0))
                pActor->bActionState = 4;
        }
        break;
    case 1:
        pActor->dwFlags = (pActor->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy
                          | ActorFlagAnimFrameLoaded;
        break;
    case 3:
        if (--pActor->dwStateTimer == -1)
        {
            if (pActor->wSubtype == 4)
            {
                pActor->dwFlags |= ActorFlagWantsCollisionCheck;
                pActor->bActionState = 0;
            }
            else
            {
                pActor->bActionState = 4;
            }
        }
        break;
    case 4:
        if (pActor->wSubtype == 9 || pActor->wSubtype == 10)
        {
            pActor->bActionState = 0;
        }
        else if (pActor->anim.bAnimFrameCounter-- == 0 || pActor->wSubtype > 10)
        {
            u8 step = SWITCH_STATE(pActor)->bStep;
            u8 variant = pActor->wSubtype;
            s8 frame;
            u8 endFrame;
            RoomActorRecordSwitch *pRecord;

            if (variant <= 10)
                frame = step + SWITCH_STATE(pActor)->bFrame;
            else
                frame = 0;

            if (variant <= 10 && step == 1)
                endFrame = pActor->anim.pAnimTable->pFrameData->wFrameCount - 1;
            else
                endFrame = 0;

            if (endFrame == frame)
            {
                if ((step == 1 && (variant == 2 || variant == 5)) || variant == 4)
                {
                    pActor->dwStateTimer = SWITCH_STATE(pActor)->nRearmTicks;
                    pActor->bActionState = 3;
                }
                else
                {
                    pActor->bActionState = 0;
                }

                if (step == 1)
                {
                    pRecord = GetRoomActorStaticRecord(pActor->bRoomRecordCol,
                                                       pActor->bRoomRecordRow);
                    RespawnGroupAndRunChain(pRecord->bOnRespawnGroup, pRecord->bOnChain);
                    SWITCH_STATE(pActor)->bStep = -1;
                }
                else
                {
                    pRecord = GetRoomActorStaticRecord(pActor->bRoomRecordCol,
                                                       pActor->bRoomRecordRow);
                    RespawnGroupAndRunChain(pRecord->bOffRespawnGroup, pRecord->bOffChain);
                    SWITCH_STATE(pActor)->bStep = 1;
                    if (variant == 2 || variant == 5)
                        pActor->dwFlags |= ActorFlagWantsCollisionCheck;
                }

                SWITCH_STATE(pActor)->nPlateFlipping = 0;
            }

            if (variant <= 10)
                SetActorAnimFrame(pActor, frame);
            SWITCH_STATE(pActor)->bFrame = frame;
        }
        break;
    }

    SWITCH_STATE(pActor)->nPlatePressed = 0;
}

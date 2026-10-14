#include "camera.h"
#include "graphics/audio.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

// Per-frame update of one camera focus slot: pan toward the target, shake, or follow.
void TickCameraFocus_candidate(u8 slot)
{
    u8 index = slot;
    Actor *pControlled = g_OverworldControlState.aSlots[index].pActor;
    u8 state = g_aCameraEffects_candidate[index].bState;
    u32 framesLeft;
    u16 counter;
    FixedPoint pos;

    if (state == 1)
    {
        if (g_aCameraEffects_candidate[index].pTarget != pControlled || g_aCameraEffects_candidate[index].wCounter == 0)
        {
            if (MoveCameraFocusToward_candidate(g_aCameraEffects_candidate[index].pTarget->pos.x, g_aCameraEffects_candidate[index].pTarget->pos.y,
                                                g_aCameraEffects_candidate[index].nStep, index) == CAMERA_FOCUS_ARRIVED)
            {
                if (g_aCameraEffects_candidate[index].wCounter == 0)
                {
                    if (g_aCameraEffects_candidate[index].pTarget == pControlled)
                    {
                        g_aCameraEffects_candidate[index].bState = 0;
                        pControlled->vel = g_aCameraEffects_candidate[index].savedVel;
                        SetActorActionSubState(pControlled, g_aCameraEffects_candidate[index].bSavedActionSubState);
                    }

                    if (g_aCameraEffects_candidate[index].bChainRan == 0)
                    {
                        g_aCameraEffects_candidate[index].bChainRan = 1;
                        RespawnGroupAndRunChain(g_aCameraEffects_candidate[index].bRespawnRow, g_aCameraEffects_candidate[index].bChainRow);
                    }

                    if (g_aCameraEffects_candidate[index].dwResumeScript != 0)
                    {
                        g_aCameraEffects_candidate[index].dwResumeScript = 0;
                        ResumeRoomScriptChain();
                    }
                }
                else
                {
                    g_aCameraEffects_candidate[index].wCounter--;
                    g_aCameraFocusSlots[index].focus = g_aCameraEffects_candidate[index].pTarget->pos;
                }
            }
        }
        else
        {
            g_aCameraEffects_candidate[index].wCounter--;
        }
    }
    else if (state == 3)
    {
        if (g_aCameraEffects_candidate[index].dwRunForever != 0 || (framesLeft = g_aCameraEffects_candidate[index].dwFramesLeft, g_aCameraEffects_candidate[index].dwFramesLeft = framesLeft - 1, framesLeft != 0))
        {
            pos = g_aCameraFocusSlots[index].pTarget->pos;
            g_aCameraFocusSlots[index].focus.x = pos.x;
            g_aCameraFocusSlots[index].focus.y = pos.y;
            counter = g_aCameraEffects_candidate[index].wCounter++;
            if (counter != 0)
            {
                g_aCameraEffects_candidate[index].wCounter = 0;
                g_aCameraEffects_candidate[index].nStep = -g_aCameraEffects_candidate[index].nStep;
            }
            g_aCameraFocusSlots[index].focus.y += g_aCameraEffects_candidate[index].nStep * g_aCameraEffects_candidate[index].wCounter;
        }
        else
        {
            g_aCameraEffects_candidate[index].bState = 0;
            RespawnGroupAndRunChain(g_aCameraEffects_candidate[index].bRespawnRow, g_aCameraEffects_candidate[index].bChainRow);
            StopSoundEffect(g_bCameraShakeSoundHandle);
        }
    }
    else if (g_aCameraFocusSlots[index].wPinned == 0)
    {
        pos = g_aCameraFocusSlots[index].pTarget->pos;
        g_aCameraFocusSlots[index].focus.x = pos.x;
        g_aCameraFocusSlots[index].focus.y = pos.y;
    }
}

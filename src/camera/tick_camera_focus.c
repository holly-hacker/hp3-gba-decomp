#include "area.h"
#include "camera.h"
#include "sound.h"
#include "overworld/overworld.h"
#include "commands.h"
#include "hero.h"

// Per-frame update of one camera focus slot: pan toward the target, shake, or follow.
void TickCameraFocus(u8 slot)
{
    u32 index = slot;
    Actor *pControlled = g_OverworldControlState.aSlots[index].pActor;
    u8 state = g_aCameraEffects[index].bState;
    u32 framesLeft;
    u16 counter;
    FixedPoint pos;

    if (state == 1)
    {
        if (g_aCameraEffects[index].pTarget != pControlled || g_aCameraEffects[index].wCounter == 0)
        {
            if (MoveCameraFocusToward(g_aCameraEffects[index].pTarget->pos, g_aCameraEffects[index].nStep, index) == CAMERA_FOCUS_ARRIVED)
            {
                if (g_aCameraEffects[index].wCounter == 0)
                {
                    if (g_aCameraEffects[index].pTarget == pControlled)
                    {
                        g_aCameraEffects[index].bState = 0;
                        pControlled->vel = g_aCameraEffects[index].savedVel;
                        SetActorActionSubState(pControlled, g_aCameraEffects[index].bSavedActionSubState);
                    }

                    if (g_aCameraEffects[index].bChainRan == 0)
                    {
                        g_aCameraEffects[index].bChainRan = 1;
                        RespawnGroupAndRunChain(g_aCameraEffects[index].bRespawnRow, g_aCameraEffects[index].bChainRow);
                    }

                    if (g_aCameraEffects[index].dwResumeScript != 0)
                    {
                        g_aCameraEffects[index].dwResumeScript = 0;
                        ResumeRoomScriptChain();
                    }
                }
                else
                {
                    g_aCameraEffects[index].wCounter--;
                    g_aCameraFocusSlots[index].focus = g_aCameraEffects[index].pTarget->pos;
                }
            }
        }
        else
        {
            g_aCameraEffects[index].wCounter--;
        }
    }
    else if (state == 3)
    {
        if (g_aCameraEffects[index].dwRunForever != 0 || (framesLeft = g_aCameraEffects[index].dwFramesLeft, g_aCameraEffects[index].dwFramesLeft = framesLeft - 1, framesLeft != 0))
        {
            pos = g_aCameraFocusSlots[index].pTarget->pos;
            g_aCameraFocusSlots[index].focus.x = pos.x;
            g_aCameraFocusSlots[index].focus.y = pos.y;
            counter = g_aCameraEffects[index].wCounter++;
            if (counter != 0)
            {
                g_aCameraEffects[index].wCounter = 0;
                g_aCameraEffects[index].nStep = -g_aCameraEffects[index].nStep;
            }
            g_aCameraFocusSlots[index].focus.y += g_aCameraEffects[index].nStep * g_aCameraEffects[index].wCounter;
        }
        else
        {
            g_aCameraEffects[index].bState = 0;
            RespawnGroupAndRunChain(g_aCameraEffects[index].bRespawnRow, g_aCameraEffects[index].bChainRow);
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

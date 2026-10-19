#include "types.h"
#include "combat_fx.h"
#include "screen_transitions.h"
#include "sound.h"
#include "windows.h"

// Runs the per-tick effects an effect script actor's bBehaviorFlags enable.
void ProcessActorFlagBehaviors(Actor *actor)
{
    u16 slot;
    u16 sx;
    u16 sy;

    if (actor->modeState.effect.bBehaviorFlags & EffectBehaviorAffineWobble)
    {
        slot = AllocActorAffineSlot(actor);
        sx = g_aObjAffineSetSource[slot].sx + (s8)actor->modeState.effect.abParams[0];
        sy = g_aObjAffineSetSource[slot].sy + (s8)actor->modeState.effect.abParams[1];
        if (actor->modeState.effect.abParams[2] != 0)
        {
            actor->modeState.effect.abParams[3] += actor->modeState.effect.abParams[2];
            if (actor->modeState.effect.abParams[3] == 0)
            {
                if (actor->modeState.effect.abParams[2] > 200)
                    actor->modeState.effect.abParams[3] = 31;
                else
                    actor->modeState.effect.abParams[3] = 1;
            }
            else if (actor->modeState.effect.abParams[3] > 200)
                actor->modeState.effect.abParams[3] = -actor->modeState.effect.abParams[3];
            else if (actor->modeState.effect.abParams[3] > 31)
                actor->modeState.effect.abParams[3] -= 31;
        }
        g_aObjAffineSetSource[slot].sx = sx;
        g_aObjAffineSetSource[slot].sy = sy;
        g_aObjAffineSetSource[slot].theta = actor->modeState.effect.abParams[3] * -0x7FF;
    }

    if (actor->modeState.effect.bBehaviorFlags & EffectBehaviorShrinkOrbit)
    {
        if (++actor->modeState.effect.bParam6D == actor->modeState.effect.bParam6C)
        {
            SetActorOrbitRadii(actor,
                               actor->orbitState.orbit.wRadiusX - actor->modeState.effect.abParams[0],
                               actor->orbitState.orbit.wRadiusY - actor->modeState.effect.abParams[1]);
            actor->modeState.effect.bParam6D = 0;
        }
    }

    if (actor->modeState.effect.bBehaviorFlags & EffectBehaviorPlaySound)
        PlaySoundById(actor->modeState.effect.abLocal[1]);

    if (actor->modeState.effect.bBehaviorFlags & EffectBehaviorAlphaFadeOut)
    {
        if (actor->modeState.effect.abLocal[1] != 0)
        {
            SetAlphaBlendCoefficients(actor->modeState.effect.abLocal[1], 16 - actor->modeState.effect.abLocal[1]);
            actor->modeState.effect.abLocal[1]--;
        }
    }

    if (actor->modeState.effect.bBehaviorFlags & EffectBehaviorAlphaFadeIn)
    {
        if (actor->modeState.effect.abLocal[1] > actor->modeState.effect.abParams[4])
        {
            if (--actor->modeState.effect.bParam6D == 0xFF)
            {
                actor->modeState.effect.bParam6D = actor->modeState.effect.bParam6C;
                SetAlphaBlendCoefficients(16 - actor->modeState.effect.abLocal[1], actor->modeState.effect.abLocal[1]);
                actor->modeState.effect.abLocal[1]--;
            }
        }
        else
            actor->modeState.effect.bBehaviorFlags &= ~EffectBehaviorAlphaFadeIn;
    }

    if (actor->modeState.effect.bBehaviorFlags & EffectBehaviorGrowWindow)
    {
        g_aScreenWindows[0].aCorners[0].nX -= 0x28000;
        g_aScreenWindows[0].aCorners[0].nY -= 0x20000;
        g_aScreenWindows[0].aCorners[1].nX += 0x2C000;
        g_aScreenWindows[0].aCorners[1].nY += 0x8000;
        g_aScreenWindows[0].dwFlags |= 1;
    }
}

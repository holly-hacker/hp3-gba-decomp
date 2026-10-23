#include "types.h"
#include "actor.h"
#include "move.h"
#include "random.h"

// pfnTick of a Diffindo effect: flies in its facing until it hits something (sub-state 0x10 or
// 0x11, set by HandleFieldSpellHit) or its 45 ticks run out (5), then plays its last animation.
void TickDiffindoEffect(Actor *effect)
{
    u32 spell = effect->wSubtype;

    if (effect->bActionSubState == 3 && (u16)--effect->timer84.nFlightTicks == 0xFFFF)
    {
        effect->dwFlags &= ~ActorFlagWantsCollisionCheck;
        SetActorActionSubState(effect, 5);
    }

    switch (effect->bActionSubState)
    {
    case 0:
        effect->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision;
        effect->bTerrainBlockResponse = TerrainBlockEndFlight;
        effect->dwStateTimer = 5;
        SetActorVelocityFromFacing(effect);
        SetActorActionSubState(effect, 3);
        break;
    case 3:
        if (effect->dwStateTimer != 0)
            effect->dwStateTimer--;
        break;
    case 0x10:
        StopActorMotion(effect);
        effect->dwFlags |= ActorFlagVisible;
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_abDiffindoHitAnim, 0);
        SetActorActionSubState(effect, 0x12);
        effect->oam.hFlip = Mt19937RandMax(1);
        break;
    case 5:
    case 0x11:
        StopActorMotion(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_abDiffindoEndAnim, 0);
        SetActorActionSubState(effect, 0x12);
        if (effect->timer84.nFlightTicks > 0)
            PlayFieldSpellHitSound(effect);
        break;
    case 0x12:
        if (effect->dwFlags & ActorFlagActionAnimDone)
            EndFieldSpellEffect(effect);
        break;
    }
}

#include "types.h"
#include "actor.h"
#include "combat.h"
#include "combat_gauge.h"
#include "gen/graphics/battle.h"
#include "screen_transitions.h"

// Spawns the SP gauge above a fighter. A nonzero amount fades the gauge in, drains that much
// from it and fades it out again; zero shows the gauge until DestroySlotSpGauge removes it.
Actor *SpawnSpGauge(s32 fighterIndex, u32 amount)
{
    Actor *fighterActor;
    Actor *gauge;
    SpGaugeState *state;
    u32 drainRate;

    fighterActor = g_pFightState->pFighters[fighterIndex].pActor;
    gauge = SpawnActor(fighterActor->wActorType, (fighterActor->pos.x >> 16) + 15,
                       (fighterActor->pos.y >> 16) - 54, (const ObjPalette *)gBattleHudItem003Palette);
    fighterActor->pLinkedActor = gauge;
    gauge->pLinkedActor = fighterActor;
    gauge->wSubtype = fighterIndex;

    state = SP_GAUGE_STATE(gauge);
    state->wValue = g_pFightState->pFighters[fighterIndex].stats.wHp;
    state->wMax = g_pFightState->pFighters[fighterIndex].wHp_max;
    state->wDrainTotal = state->wValue <= amount ? state->wValue : amount;
    state->wDrained = 0;
    state->nDrainStep = 0;
    drainRate = (amount << 8) / 40;
    state->wDrainRate = drainRate < 32 ? 32 : drainRate;

    gauge->bActionSubState = SpGaugeFadeIn;
    gauge->dwStateTimer = 8;
    if (fighterActor->wActorType <= 3)
        SetActorAssetRecord(gauge, &g_aSpGaugeGfx[0]);
    else
        SetActorAssetRecord(gauge, &g_aSpGaugeGfx[1]);
    UpdateSpGaugeFrame(gauge);
    SetAlphaBlendCoefficients(0, 16);

    if (amount != 0)
    {
        gauge->pfnTick = TickSpGauge;
        gauge->oam.objMode = 1;
    }
    else
    {
        gauge->oam.objMode = 0;
    }
    return gauge;
}

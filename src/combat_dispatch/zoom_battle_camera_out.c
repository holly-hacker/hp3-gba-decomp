#include "types.h"
#include "actor.h"
#include "combat.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "interrupts.h"
#include "modes.h"
#include "mode7.h"

// Undoes ZoomBattleCameraIn over 8 frames, then frees the fighters' affine slots.
void ZoomBattleCameraOut(void)
{
    u32 i;
    u32 frame;

    SetFloorForwardSpeed(-0x300);

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        StartActorAffineScaleTween(g_pFightState->pFighters[i].pActor, 0x10000, 0x10000, 8);
        if (HasShadowActor(i))
            StartActorAffineScaleTween(g_pFightState->pFighters[i].pActor->pShadowActor, 0x10000,
                                       0x10000, 8);

        if (g_pFightState->pFighters[i].bFighterType != Enemy)
            SetActorVelocity(g_pFightState->pFighters[i].pActor, 0, -0x30000);
        else
            SetActorVelocity(g_pFightState->pFighters[i].pActor, 0, -0x20000);
    }

    for (i = 0; i < g_pFightState->bFaintedAllyCount; i++) {
        StartActorAffineScaleTween(g_pFightState->pFaintedAllies[i].pActor, 0x10000, 0x10000, 8);
        SetActorVelocity(g_pFightState->pFaintedAllies[i].pActor, 0, -0x30000);
    }

    frame = 1;
    do {
        WaitForVBlankIntr();
        WaitForVBlankIntr();
        g_pFightState->bWallEndLine--;
        UpdateFloorAffineTable();
        TickFrameSystems();
    } while (frame++ < 8);

    SetFloorForwardSpeed(0);

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        if (g_pFightState->pFighters[i].pActor->oam.affineMode == 3)
            ReleaseActorAffineSlot(g_pFightState->pFighters[i].pActor);
        SetActorVelocity(g_pFightState->pFighters[i].pActor, 0, 0);
        if (HasShadowActor(i))
            ReleaseActorAffineSlot(g_pFightState->pFighters[i].pActor->pShadowActor);
    }

    for (i = 0; i < g_pFightState->bFaintedAllyCount; i++) {
        if (g_pFightState->pFaintedAllies[i].pActor->oam.affineMode == 3)
            ReleaseActorAffineSlot(g_pFightState->pFaintedAllies[i].pActor);
        SetActorVelocity(g_pFightState->pFaintedAllies[i].pActor, 0, 0);
    }
}

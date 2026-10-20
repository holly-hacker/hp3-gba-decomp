#include "types.h"
#include "actor.h"
#include "combat.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "interrupts.h"
#include "modes.h"
#include "mode7.h"

// Moves the camera toward the enemies over 8 frames: every fighter grows to 1.4x and slides
// down the screen, the floor scrolls forward and the wall band lowers.
void ZoomBattleCameraIn(void)
{
    u32 i;
    u32 frame;

    SetFloorForwardSpeed(0x300);

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        SetActorAffineTransform(g_pFightState->pFighters[i].pActor, 0x10000, 0x10000, 0, 3);
        StartActorAffineScaleTween(g_pFightState->pFighters[i].pActor, 0x16666, 0x16666, 8);
        if (HasShadowActor(i)) {
            SetActorAffineTransform(g_pFightState->pFighters[i].pActor->pShadowActor, 0x10000,
                                    0x10000, 0, 3);
            StartActorAffineScaleTween(g_pFightState->pFighters[i].pActor->pShadowActor, 0x16666,
                                       0x16666, 8);
        }

        if (g_pFightState->pFighters[i].bFighterType != Enemy)
            SetActorVelocity(g_pFightState->pFighters[i].pActor, 0, 0x30000);
        else
            SetActorVelocity(g_pFightState->pFighters[i].pActor, 0, 0x20000);
    }

    for (i = 0; i < g_pFightState->bFaintedAllyCount; i++) {
        SetActorAffineTransform(g_pFightState->pFaintedAllies[i].pActor, 0x10000, 0x10000, 0, 3);
        StartActorAffineScaleTween(g_pFightState->pFaintedAllies[i].pActor, 0x16666, 0x16666, 8);
        SetActorVelocity(g_pFightState->pFaintedAllies[i].pActor, 0, 0x30000);
    }

    frame = 1;
    do {
        WaitForVBlankIntr();
        WaitForVBlankIntr();
        g_pFightState->bWallEndLine++;
        UpdateFloorAffineTable();
        TickFrameSystems();
    } while (frame++ < 8);

    SetFloorForwardSpeed(0);

    for (i = 0; i < g_pFightState->bFighterCount; i++)
        SetActorVelocity(g_pFightState->pFighters[i].pActor, 0, 0);

    for (i = 0; i < g_pFightState->bFaintedAllyCount; i++)
        SetActorVelocity(g_pFightState->pFaintedAllies[i].pActor, 0, 0);
}

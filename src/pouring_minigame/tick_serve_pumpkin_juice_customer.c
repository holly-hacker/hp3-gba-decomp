#include "types.h"
#include "actor.h"
#include "modes.h"
#include "random.h"
#include "pouring_minigame.h"

// Action states: 0 waits, 1 steps towards the bar, 2 drinks, 4 leaves. A customer pushed
// past the left edge leaves and scores; one reaching the bar loses the game. After
// drinking, a customer may slide the empty goblet back.
void TickServePumpkinJuiceCustomer(Actor *customer)
{
    if (g_GameModeStackContext.dwModeState != ServePumpkinJuiceStatePlaying)
        return;

    customer->wTimedMoveTicks++;
    if (customer->bActionState == 4)
    {
        g_ServePumpkinJuice.adwCustomerCount[customer->bActionSubState]--;
        customer->pLinkedActor->pOwnerActor = NULL;
        g_ServePumpkinJuice.dwCustomerTypesInUse &=
            ~g_adwServePumpkinJuiceCustomerTypeBits[customer->wSubtype];
        customer->pLinkedActor->dwFlags &= ~ActorFlagVisible;
        customer->pLinkedActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        customer->dwFlags = (customer->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        return;
    }

    if ((customer->pos.x >> 16) < 0)
    {
        customer->bActionState = 4;
        g_ServePumpkinJuice.dwScore += (2 << g_GameModeStackContext.dwCurrentGameModeArg3) * 50;
        g_ServePumpkinJuice.dwScoreChanged = 1;
    }

    if ((customer->pos.x >> 16) > g_ServePumpkinJuice.aLanePos[customer->bActionSubState].x - 32)
        g_GameModeStackContext.dwModeState = ServePumpkinJuiceStateResults;

    if (customer->bActionState == 2 && customer->wTimedMoveTicks == 5
        && (customer->dwFlags & ActorFlagActionAnimDone))
    {
        customer->dwFlags &= ~ActorFlagActionAnimDone;
        customer->bActionState = 0;
        customer->wTimedMoveTicks = 0;
        customer->wActionVariant = 0;
        SetActorAnimFrame(customer, 0);
        if (Mt19937RandRange(0, 8) < g_GameModeStackContext.dwCurrentGameModeArg3 + 3)
        {
            SpawnServePumpkinJuiceEmptyGoblet(customer->bActionSubState, customer->pos.x >> 16);
            if (customer->wSubtype == 6)
                SpawnServePumpkinJuiceEmptyGoblet(customer->bActionSubState, (customer->pos.x >> 16) + 15);
        }
    }

    if (customer->bActionState == 1 && customer->wTimedMoveTicks > 20)
    {
        customer->bActionState = 0;
        customer->wTimedMoveTicks = 0;
        if (customer->wSubtype == 6 && customer->wActionVariant != 0)
            SetActorAnimFrame(customer, 3);
        else
            SetActorAnimFrame(customer, 0);
    }

    if (customer->bActionState == 0
        && customer->wTimedMoveTicks > 30 - g_GameModeStackContext.dwCurrentGameModeArg3 * 2
        && Mt19937RandRange(0, 100) <= 4)
    {
        // Steps 12 pixels plus a difficulty bonus, +-5; lanes further down shift right.
        s32 jitter = Mt19937RandRange(-5, 5);
        s32 step = (2 << g_GameModeStackContext.dwCurrentGameModeArg3) + 12;
        s32 x = jitter + step;

        x += customer->pos.x >> 16;
        x -= 2;
        x += customer->bActionSubState;
        customer->bActionState = 1;
        SetActorMoveTargetWithDuration(customer, x, customer->pos.y >> 16, 20);
        customer->wTimedMoveTicks = 0;
        if (customer->wSubtype == 6)
            SetActorAnimData(customer, g_aapServePumpkinJuiceCustomerSpriteRows[customer->wSubtype][0],
                             g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimWalkVariant
                                                                 + customer->wActionVariant],
                             0);
        else
            SetActorAnimData(customer, g_aapServePumpkinJuiceCustomerSpriteRows[customer->wSubtype][0],
                             g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimWalk], 0);
    }
}

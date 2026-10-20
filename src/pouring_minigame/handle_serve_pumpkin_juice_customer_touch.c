#include "types.h"
#include "actor.h"
#include "modes.h"
#include "random.h"
#include "pouring_minigame.h"

// A full goblet in the customer's lane is drunk: the customer is pushed back towards
// the left and the goblet is destroyed. A type 6 customer drinks only on the second
// goblet; the first switches its walk to the variant.
void HandleServePumpkinJuiceCustomerTouch(Actor *customer, Actor *other)
{
    // Kind and action state together: a full goblet still sliding (state 0).
    if (g_GameModeStackContext.dwModeState == ServePumpkinJuiceStatePlaying
        && *(u16 *)&other->bRoomActorKind_candidate == ServePumpkinJuiceActorFullGoblet
        && customer->bActionState != 2
        && other->bActionSubState == customer->bActionSubState)
    {
        other->bActionState = 4;
        if (customer->wCharacterId_candidate != 6 || customer->wActionVariant == 1)
        {
            // Pushed back 45 pixels less a difficulty bonus, +-5.
            s32 x = Mt19937RandRange(-5, 5) - 45;

            x += customer->pos.x >> 16;
            x += 2 << g_GameModeStackContext.dwCurrentGameModeArg3;
            x -= 2;
            x += customer->bActionSubState;
            SetActorMoveTargetWithDuration(customer, x, customer->pos.y >> 16, 14);
            customer->wTimedMoveTicks = 0;
        }

        if (customer->wCharacterId_candidate == 6)
        {
            if (customer->wActionVariant == 1)
            {
                SetActorAnimData(customer, g_aapServePumpkinJuiceCustomerSpriteRows[customer->wCharacterId_candidate][0],
                                 g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimDrinkVariant], 0);
                customer->bActionState = 2;
                customer->wTimedMoveTicks = 0;
            }
            else
            {
                if (customer->bActionState == 1)
                    SetActorAnimData(customer, g_aapServePumpkinJuiceCustomerSpriteRows[customer->wCharacterId_candidate][0],
                                     g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimWalkVariant + 1], 0);
                else
                    SetActorAnimFrame(customer, 3);

                customer->wActionVariant = 1;
            }
        }
        else
        {
            SetActorAnimData(customer, g_aapServePumpkinJuiceCustomerSpriteRows[customer->wCharacterId_candidate][0],
                             g_aabServePumpkinJuiceCustomerAnims[ServePumpkinJuiceCustomerAnimDrink], 0);
            customer->bActionState = 2;
            customer->wTimedMoveTicks = 0;
        }
    }
}

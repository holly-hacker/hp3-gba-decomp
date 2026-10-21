#include "types.h"
#include "actor.h"
#include "random.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"
#include "gen/graphics/minigames/owl_care.h"

// One dropping in the cage for every 5 points of the Clean counter above 10.
void UpdateOwlDroppings(void)
{
    s32 count;
    s32 shown;

    count = (g_saveStateBlock.owlCareKit.abCareCounters[1] - 10) / 5;
    shown = g_OwlCareKitScreen.bDroppingCount;
    if (count >= OWL_CARE_KIT_MAX_DROPPINGS)
        count = OWL_CARE_KIT_MAX_DROPPINGS;
    if (count < 0)
        count = 0;

    if (shown != count)
    {
        if (shown < count)
        {
            for (; shown < count; shown++)
            {
                g_OwlCareKitScreen.apDroppings[shown] =
                    SpawnActor(0, Mt19937RandRange(64, 192), Mt19937RandRange(98, 125), (const void *)gOwlCareDroppingPalette);
                SetActorDrawLayer(g_OwlCareKitScreen.apDroppings[shown], 2);
                SetActorAssetRecord(g_OwlCareKitScreen.apDroppings[shown], &g_aOwlCareSprites[2]);
            }
        }
        else
        {
            while (shown > count)
            {
                shown--;
                g_OwlCareKitScreen.apDroppings[shown]->dwFlags |= ActorFlagPendingDestroy;
                g_OwlCareKitScreen.apDroppings[shown] = NULL;
            }
        }
    }

    g_OwlCareKitScreen.bDroppingCount = count;
}

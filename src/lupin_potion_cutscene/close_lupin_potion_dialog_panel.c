#include "lupin_potion_cutscene.h"
#include "background.h"
#include "text_actor.h"

void CloseLupinPotionDialogPanel(void)
{
    s32 i;

    ClearBgTilemapRect(2, 0, 20, 30, 12);
    if (g_apTextActors[0] != NULL)
    {
        g_apTextActors[0]->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        g_apTextActors[0] = NULL;
    }
    for (i = 0; i < ARRAY_COUNT(g_LupinPotionCutscene.apPanelActor); i++)
    {
        if (g_LupinPotionCutscene.apPanelActor[i] != NULL)
        {
            g_LupinPotionCutscene.apPanelActor[i]->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
            g_LupinPotionCutscene.apPanelActor[i] = NULL;
        }
    }
}

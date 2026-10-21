#include "lupin_potion_cutscene.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "text_actor.h"

// Draws the next line of the dialog page with its speaker's portrait, first raising a
// fresh panel when the page starts. Returns 0 once the page has no more lines.
u32 ShowNextLupinPotionDialogLine(void)
{
    const u8 *pText;
    s32 i;

    if (g_apTextActors[0] != NULL)
    {
        g_apTextActors[0]->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        g_apTextActors[0] = NULL;
    }

    if (g_LupinPotionCutscene.wDialogLine == 0)
    {
        for (i = 0; i < LUPIN_POTION_PANEL_PIECES; i++)
        {
            if (g_LupinPotionCutscene.apPanelActor[i] != NULL)
            {
                g_LupinPotionCutscene.apPanelActor[i]->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
                g_LupinPotionCutscene.apPanelActor[i] = NULL;
            }
            g_LupinPotionCutscene.apPanelActor[i] = SpawnLupinPotionPanelActor(0);
            SetActorPosition(g_LupinPotionCutscene.apPanelActor[i], i << 5,
                             g_LupinPotionCutscene.nPanelOffset + 0x9F);
        }
    }

    if (g_aLupinPotionDialog[g_LupinPotionCutscene.wDialogPage][g_LupinPotionCutscene.wDialogLine].dwTextId != 0)
    {
        pText = GetDialogText(
            g_aLupinPotionDialog[g_LupinPotionCutscene.wDialogPage][g_LupinPotionCutscene.wDialogLine].dwTextId);
        ClearBgTilemapRect(2, 0, 20, 30, 12);
        DrawTextLines(0x120, 0x40, 200, 0xA9, 0x20, &pText, 0);
        if (g_LupinPotionCutscene.apPanelActor[LUPIN_POTION_PANEL_PIECES] != NULL)
        {
            g_LupinPotionCutscene.apPanelActor[LUPIN_POTION_PANEL_PIECES]->dwFlags |=
                ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
            g_LupinPotionCutscene.apPanelActor[LUPIN_POTION_PANEL_PIECES] = NULL;
        }
        g_LupinPotionCutscene.apPanelActor[LUPIN_POTION_PANEL_PIECES] = SpawnLupinPotionPanelActor(
            g_aLupinPotionDialog[g_LupinPotionCutscene.wDialogPage][g_LupinPotionCutscene.wDialogLine].dwSpeaker);
        SetActorPosition(g_LupinPotionCutscene.apPanelActor[LUPIN_POTION_PANEL_PIECES], 0,
                         g_LupinPotionCutscene.nPanelOffset + 0x9F);
        g_LupinPotionCutscene.wDialogLine++;
        return 1;
    }
    return 0;
}

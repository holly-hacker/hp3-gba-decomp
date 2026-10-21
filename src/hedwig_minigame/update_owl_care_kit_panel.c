#include "types.h"
#include "actor.h"
#include "background.h"
#include "cursor.h"
#include "modes.h"
#include "sound.h"
#include "hedwig_minigame.h"
#include "gen/graphics/minigames/owl_care.h"

void UpdateOwlCareKitPanel(void)
{
    switch (g_OwlCareKitScreen.pOwl->bActionState)
    {
    case OwlStateAway:
        if (g_OwlCareKitScreen.bPanel != OwlCareKitPanelAway)
        {
            EnableBg(0);
            DrawOwlCareKitTextPanel();
            DrawOwlAwayMessage();
            if (g_OwlCareKitScreen.pCursor != NULL)
            {
                ReleaseMenuCursor(g_OwlCareKitScreen.pCursor);
                g_OwlCareKitScreen.pCursor = NULL;
            }
        }
        g_OwlCareKitScreen.bPanel = OwlCareKitPanelAway;
        break;
    case OwlStateMailDelivered:
        if (g_OwlCareKitScreen.bPanel != OwlCareKitPanelMail)
        {
            EnableBg(0);
            DrawOwlCareKitTextPanel();
            ProcessOwlMailReward();
            if (g_OwlCareKitScreen.pCursor != NULL)
            {
                ReleaseMenuCursor(g_OwlCareKitScreen.pCursor);
                g_OwlCareKitScreen.pCursor = NULL;
            }
        }
        g_OwlCareKitScreen.bPanel = OwlCareKitPanelMail;
        break;
    case OwlStateMailDepart:
    case OwlStateMailReturn:
        if (g_OwlCareKitScreen.bPanel != OwlCareKitPanelNone)
        {
            DisableBg(0);
            if (g_OwlCareKitScreen.pCursor != NULL)
            {
                ReleaseMenuCursor(g_OwlCareKitScreen.pCursor);
                g_OwlCareKitScreen.pCursor = NULL;
            }
        }
        g_OwlCareKitScreen.bPanel = OwlCareKitPanelNone;
        break;
    default:
        if (g_OwlCareKitScreen.bPanel != OwlCareKitPanelMenu)
        {
            EnableBg(0);
            FillBgTile(0, 0x28B, 0);
            SetBgPriority(0, 1);
            g_BgState.aLayers[0].pTilemap = LoadBgGraphic(0, gOwlCareGraphic003, 0x156, 0, 0, 0);
            DrawOwlName();
            DrawOwlCareKitMenuLabel();
            UpdateOwlStatMeterBars();
            if (g_OwlCareKitScreen.pCursor == NULL)
            {
                g_OwlCareKitScreen.pCursor = SpawnMenuCursorActor(4);
                g_OwlCareKitScreen.pCursor->pfnTick = TickOwlCareKitCursor;
            }
        }
        else
        {
            UpdateOwlStatMeterBars();
            if (g_OwlCareKitScreen.bShownSelection != g_GameModeStackContext.dwModeScratchB)
            {
                PlaySoundById(0);
                DrawOwlCareKitMenuIcon(g_OwlCareKitScreen.bShownSelection, 0);
                DrawOwlCareKitMenuLabel();
            }
        }
        g_OwlCareKitScreen.bPanel = OwlCareKitPanelMenu;
        break;
    }
}

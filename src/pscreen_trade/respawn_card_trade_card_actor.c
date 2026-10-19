#include "types.h"
#include "menu_icon.h"
#include "actor.h"
#include "pscreen_folio_universitas.h"
#include "pscreen_trade.h"

void RespawnCardTradeCardActor(u32 side, u32 card)
{
    if (g_apMenuIconActors[side] != NULL)
    {
        g_apMenuIconActors[side]->dwFlags |= ActorFlagPendingDestroy;
        g_apMenuIconActors[side] = NULL;
    }

    if (card != CARD_TRADE_NO_CARD)
        RegisterMenuIconActor(side, SpawnFolioCardThumbnail(card, g_aCardTradeSlotPositions[side].bX,
                                                            g_aCardTradeSlotPositions[side].bY));
}

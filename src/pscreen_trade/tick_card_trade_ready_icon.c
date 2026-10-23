#include "actor.h"
#include "palette.h"
#include "pscreen_trade.h"

// Swaps the icon's sprite when its side's ready flag changes.
void TickCardTradeReadyIcon(Actor *pIcon)
{
    CardTradeSide *pSide = &g_CardTradeState.aSides[pIcon->bKind];

    if (pIcon->bActionState != pSide->bReady)
    {
        pIcon->bActionState = pSide->bReady;
        SetActorAssetRecord(pIcon, &g_aCardTradeReadyIconAssets[pSide->bReady]);
        ReleaseActorPalette(pIcon);
        AttachActorPalette(pIcon, g_aCardTradeReadyIconAssets[pSide->bReady].pPalette);
    }
}

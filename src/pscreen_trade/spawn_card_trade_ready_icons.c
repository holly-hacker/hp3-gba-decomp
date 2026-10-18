#include "types.h"
#include "modes.h"
#include "actor.h"
#include "pscreen_trade.h"

void SpawnCardTradeReadyIcons(void)
{
    u32 side;
    CardTradeSide *pSide;
    Actor *pIcon;

    for (side = 0; side < 2; side++)
    {
        pSide = &g_CardTradeState.aSides[side];
        pIcon = SpawnActor(0x13, g_aCardTradeSlotPositions[side].bX + 0x40,
                           g_aCardTradeSlotPositions[side].bY + 8,
                           g_aCardTradeReadyIconAssets[pSide->bReady].pPalette);
        RegisterMenuIconActor(side + 2, pIcon);
        pIcon->bRoomActorKind_candidate = side;  // TickCardTradeReadyIcon: which side
        pIcon->bActionState = pSide->bReady;     // TickCardTradeReadyIcon: state shown
        pIcon->pfnTick = TickCardTradeReadyIcon;
        pIcon->bDepthSortBias = 0xFF;
        SetActorAssetRecord(pIcon, &g_aCardTradeReadyIconAssets[pSide->bReady]);
    }
}

#include "types.h"
#include "pscreen_trade.h"

void RefreshCardTradeSlots(void)
{
    u32 side;

    for (side = 0; side < 2; side++)
        SetCardTradeSlotCard(side, g_CardTradeState.aSides[side].bOffer);
}

#include "store.h"

void TickShopMenuCursor(Actor *pCursor)
{
    SetActorMoveTargetWithDuration(pCursor, 0x1E, g_FredAndGeorgesShop.bCursor * 16 + 0x28, 2);
}

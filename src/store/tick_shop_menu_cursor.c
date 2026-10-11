#include "types.h"
#include "menu/minigame_menu.h"
#include "shop.h"

void TickShopMenuCursor(Actor *pCursor)
{
    SetActorMoveTargetWithDuration_candidate(pCursor, 0x1E, g_FredAndGeorgesShop.bCursor * 16 + 0x28, 2);
}

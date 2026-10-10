#include "types.h"
#include "graphics/display.h"
#include "shop.h"

void ExitFredAndGeorgesShop(void)
{
    SetScreenDarkenParams_candidate(0, 8);
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ExitShopMainMenu();
}

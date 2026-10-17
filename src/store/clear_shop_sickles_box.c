#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "store.h"

void ClearShopSicklesBox(void)
{
    ClearBgTilemapRect(2, 1, 0x11, 0x11, 2);
}

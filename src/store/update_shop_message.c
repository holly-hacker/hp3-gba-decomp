#include "types.h"
#include "graphics/audio.h"
#include "hw/input.h"
#include "shop.h"

void UpdateShopMessage(void)
{
    if (g_wKeysPressed & (KeyA | KeyB))
    {
        PlaySoundById(1);
        StartShopScreenTransition(ShopScreenMainMenu);
    }
}

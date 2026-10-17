#include "types.h"
#include "sound.h"
#include "input.h"
#include "store.h"

void UpdateShopMessage(void)
{
    if (g_wKeysPressed & (KeyA | KeyB))
    {
        PlaySoundById(1);
        StartShopScreenTransition(ShopScreenMainMenu);
    }
}

#include "types.h"
#include "game/items.h"
#include "game/save.h"

// Reads the item quantity array (SAVE_ITEM_QUANTITIES_SIZE bytes), a word at
// a time.
void DeserializeItemQuantities(void)
{
    u8 *pQuantities = g_abItemQuantities;
    s32 i;

    for (i = SAVE_ITEM_QUANTITIES_SIZE / 4 - 1; i >= 0; i--)
    {
        UnpackBytesFromSaveStream(pQuantities, 4);
        pQuantities += 4;
    }
}

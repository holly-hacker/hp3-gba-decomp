#include "types.h"
#include "game/items.h"
#include "game/save.h"

// Writes the item quantity array (SAVE_ITEM_QUANTITIES_SIZE bytes), a word at
// a time.
void SerializeItemQuantities(void)
{
    u8 *pQuantities = g_abItemQuantities;
    s32 i;

    for (i = SAVE_ITEM_QUANTITIES_SIZE / 4 - 1; i >= 0; i--)
    {
        PackBytesToSaveStream(pQuantities, 4);
        pQuantities += 4;
    }
}

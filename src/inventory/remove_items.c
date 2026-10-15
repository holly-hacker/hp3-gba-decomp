#include "types.h"
#include "inventory.h"
#include "inventory_inline.h"

// Removes up to `count` of an item and returns how many are left.
u32 RemoveItems(u32 item, u32 count)
{
    return RemoveItemsInline(item, count);
}

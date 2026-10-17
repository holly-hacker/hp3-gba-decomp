#include "types.h"
#include "items.h"
#include "items_inline.h"

// Removes up to `count` of an item and returns how many are left.
u32 RemoveItems(u32 item, u32 count)
{
    return RemoveItemsInline(item, count);
}

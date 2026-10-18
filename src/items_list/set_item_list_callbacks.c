#include "types.h"
#include "items_list.h"

void SetItemListCallbacks(void (*onCursorMove)(u32 item), void (*onClear)(void))
{
    g_ItemList.pfnOnCursorMove = onCursorMove;
    g_ItemList.pfnOnClear = onClear;
}

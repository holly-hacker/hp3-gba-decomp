#include "types.h"
#include "color.h"
#include "palette.h"
#include "gen/graphics/menus.h"
#include "items_list.h"

void InitItemList(s32 x, s32 y, u32 textMode, u32 maxRows, s32 character)
{
    u32 i;

    g_ItemList.pCursor = NULL;
    g_ItemList.dwMaxRows = maxRows;
    g_ItemList.nCharacter = character;
    g_ItemList.dwWithRemove = 0;
    g_ItemList.dwCursorTargetSet = 0;
    g_ItemList.dwTextMode = textMode;
    g_ItemList.nX = x;
    g_ItemList.nY = y;
    g_ItemList.pfnOnCursorMove = NULL;
    g_ItemList.pfnOnClear = NULL;

    for (i = 0; i < g_ItemList.dwMaxRows + 1; i++)
        g_ItemList.abIconGfxUsed[i] = 0;

    ReserveObjPaletteSlot(0);
    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 16);
    g_ItemList.dwScrolledDown = 0;
    g_ItemList.dwScrolledUp = 0;
    g_bItemListScroll = 0;
    g_bItemListCursorRow = 0;
    g_ItemList.dwState = ItemListIdle;
    SpawnItemListActors();
}

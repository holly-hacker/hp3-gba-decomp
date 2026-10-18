#include "types.h"
#include "input.h"
#include "sound.h"
#include "items_list.h"

void TickItemList(void)
{
    u32 up;
    u32 down;
    s32 prevItem;

    up = 0;
    down = 0;

    switch (g_ItemList.dwState)
    {
    case ItemListIdle:
        if (g_ItemList.dwScrolledUp)
        {
            g_ItemList.dwScrolledUp = 0;
            if (g_wKeysHeld & KeyUp)
                up = 1;
        }
        else if (g_ItemList.dwScrolledDown)
        {
            g_ItemList.dwScrolledDown = 0;
            if (g_wKeysHeld & KeyDown)
                down = 1;
        }
        else if (g_wKeysPressed & KeyUp)
            up = 1;
        else if (g_wKeysPressed & KeyDown)
            down = 1;

        prevItem = g_bItemListCursorRow + g_bItemListScroll;
        if (up)
        {
            if (g_bItemListCursorRow == 0)
                ScrollItemListUp(1);
            else
                SetItemListCursorRow(g_bItemListCursorRow - 1);
        }
        else if (down)
        {
            if (g_bItemListCursorRow == g_ItemList.bRowCount - 1)
                ScrollItemListDown(1);
            else
                SetItemListCursorRow(g_bItemListCursorRow + 1);
        }

        if (prevItem != g_bItemListCursorRow + g_bItemListScroll)
            PlaySoundById(0);
        break;

    case ItemListScrollingUp:
        g_ItemList.wBlendCoeffA += 3;
        g_ItemList.wBlendCoeffB -= 3;
        OffsetItemListRows(6);
        if (--g_ItemList.bScrollFrames == 0)
        {
            FinishItemListScroll(1);
            g_ItemList.dwState = ItemListIdle;
        }
        break;

    case ItemListScrollingDown:
        g_ItemList.wBlendCoeffA -= 3;
        g_ItemList.wBlendCoeffB += 3;
        OffsetItemListRows(-6);
        if (--g_ItemList.bScrollFrames == 0)
        {
            FinishItemListScroll(-1);
            g_ItemList.dwState = ItemListIdle;
        }
        break;
    }
}

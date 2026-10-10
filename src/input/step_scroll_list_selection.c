#include "input_inline.h"

// Moves the scrolling-list cursor with held Up/Down and returns the selected
// row. A list that fits in visibleRows moves only the cursor, wrapping if
// wrap is nonzero. A longer list keeps the cursor in the middle of the
// window and scrolls, without wrapping.
u32 StepScrollListSelection(u32 visibleRows, s32 wrap, u32 player)
{
    u32 rowCount = g_dwScrollListRowCount;

    if (rowCount != 0)
    {
        if (rowCount <= visibleRows)
        {
            StepCursorUpDownHeld(&g_dwScrollListCursorRow, 0, rowCount - 1, wrap, player);
        }
        else if (g_awPlayerKeysHeld[player] & KeyUp)
        {
            if (g_dwScrollListCursorRow >= visibleRows / 2)
                g_dwScrollListCursorRow--;
            else if (g_dwScrollListTopRow != 0)
                g_dwScrollListTopRow--;
            else if (g_dwScrollListCursorRow != 0)
                g_dwScrollListCursorRow--;
        }
        // BUG: This should test KeyDown. Without it, the cursor steps down whenever Up is not held.
        else
        {
            if (g_dwScrollListCursorRow < visibleRows / 2)
                g_dwScrollListCursorRow++;
            else if (g_dwScrollListTopRow < rowCount - visibleRows)
                g_dwScrollListTopRow++;
            else if (g_dwScrollListCursorRow < visibleRows - 1)
                g_dwScrollListCursorRow++;
        }
    }
    return g_dwScrollListTopRow + g_dwScrollListCursorRow;
}

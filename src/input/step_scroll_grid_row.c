#include "input_inline.h"

// StepScrollListSelection for the grid set up by InitScrollGrid. Stepping
// down in a scrolling grid onto the last, partial row also pulls the column
// back onto its last item. Returns the selected row.
u32 StepScrollGridRow(s32 wrap, u32 player)
{
    u32 rowCount = g_dwScrollListRowCount;

    if (rowCount != 0)
    {
        if (rowCount <= g_dwScrollGridVisibleRows)
        {
            StepCursorUpDownHeld(&g_dwScrollListCursorRow, 0, rowCount - 1, wrap, player);
        }
        else if (g_awPlayerKeysHeld[player] & KeyUp)
        {
            if (g_dwScrollListCursorRow >= g_dwScrollGridVisibleRows / 2)
                g_dwScrollListCursorRow--;
            else if (g_dwScrollListTopRow != 0)
                g_dwScrollListTopRow--;
            else if (g_dwScrollListCursorRow != 0)
                g_dwScrollListCursorRow--;
        }
        // BUG: This should test KeyDown. Without it, the cursor steps down whenever Up is not held.
        else
        {
            if (g_dwScrollListCursorRow < g_dwScrollGridVisibleRows / 2)
                g_dwScrollListCursorRow++;
            else if (g_dwScrollListTopRow < rowCount - g_dwScrollGridVisibleRows)
                g_dwScrollListTopRow++;
            else if (g_dwScrollListCursorRow < g_dwScrollGridVisibleRows - 1)
                g_dwScrollListCursorRow++;

            if (g_dwScrollListTopRow + g_dwScrollListCursorRow == g_dwScrollListRowCount - 1)
            {
                u32 rowItemCount = g_dwScrollGridItemCount
                                 - (g_dwScrollListTopRow + g_dwScrollListCursorRow) * g_dwScrollGridColumnCount;

                if (g_dwScrollGridColumn > rowItemCount - 1)
                    g_dwScrollGridColumn = rowItemCount - 1;
            }
        }
    }
    return g_dwScrollListTopRow + g_dwScrollListCursorRow;
}

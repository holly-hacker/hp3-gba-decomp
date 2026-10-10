#include "input_inline.h"

// Moves the grid cursor column with held Left/Right within the current row,
// wrapping if wrap is nonzero; the last row may be partial. Returns the
// column.
u32 StepScrollGridColumn(s32 wrap, u32 player)
{
    u32 itemCount = g_dwScrollGridItemCount;

    if (itemCount != 0)
    {
        if (itemCount <= g_dwScrollGridColumnCount)
        {
            StepCursorLeftRightHeld(&g_dwScrollGridColumn, 0, itemCount - 1, wrap, player);
        }
        else
        {
            u32 row = g_dwScrollListTopRow + g_dwScrollListCursorRow;

            if (row < g_dwScrollListRowCount - 1)
                StepCursorLeftRightHeld(&g_dwScrollGridColumn, 0, g_dwScrollGridColumnCount - 1, wrap, player);
            else
                StepCursorLeftRightHeld(&g_dwScrollGridColumn, 0,
                                        itemCount - row * g_dwScrollGridColumnCount - 1, wrap, player);
        }
    }
    return g_dwScrollGridColumn;
}

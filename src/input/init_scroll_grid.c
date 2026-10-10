#include "input.h"
#include "math.h"

// Lays itemCount items out in rows of columnCount, visibleRows at a time, and
// places the cursor on item `selection`, scrolling so its row is visible.
void InitScrollGrid(u32 selection, u32 itemCount, u32 columnCount, u32 visibleRows)
{
    g_dwScrollGridItemCount = itemCount;
    g_dwScrollGridColumnCount = columnCount;
    g_dwScrollGridVisibleRows = visibleRows;
    g_dwScrollListRowCount = iwramDivideSignedQuotient(itemCount + columnCount - 1, columnCount);
    g_dwScrollListTopRow = 0;
    g_dwScrollListCursorRow = iwramDivideSignedRemainder(selection, columnCount, (s32 *)&g_dwScrollGridColumn);
    if (g_dwScrollListCursorRow >= visibleRows)
    {
        g_dwScrollListTopRow = g_dwScrollListCursorRow + (1 - visibleRows);
        g_dwScrollListCursorRow = visibleRows - 1;
    }
}

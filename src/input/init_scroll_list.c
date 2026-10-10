#include "input.h"

void InitScrollList(u32 rowCount)
{
    g_dwScrollListRowCount = rowCount;
    g_dwScrollListCursorRow = 0;
    g_dwScrollListTopRow = 0;
}

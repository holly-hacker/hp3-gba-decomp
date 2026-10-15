#include "types.h"
#include "background.h"
#include "language_select.h"

// Copies the entry's normal or highlighted label (10 rows lower in the source).
// The first row of each column is three tiles tall, the rest two.
void DrawLanguageSelectEntry(u32 index, u32 selectedIndex)
{
    u32 highlighted;
    u32 row;
    u32 height;
    u32 x;

    highlighted = 0;
    if (index == selectedIndex)
        highlighted = 1;

    row = index & 3;
    height = row ? 2 : 3;
    x = index < 4 ? 4 : 16;

    CopyBgScreenRect(1, 10, height, x, highlighted * 10 + 20 + (row ? row * 2 + 1 : 0),
                     index < 4 ? 4 : 16, (index & 3) ? (index & 3) * 2 + 11 : 10);
}

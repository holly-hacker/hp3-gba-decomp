#include "types.h"
#include "background.h"
#include "language_select.h"

// Flags are 12x9 tiles, two per row, from row 20 of the BG2 tilemap.
void DrawLanguageSelectFlag(u32 selectedIndex)
{
    CopyBgScreenRect(2, 12, 9, (selectedIndex & 1) ? 12 : 0, (selectedIndex >> 1) * 9 + 20, 9, 1);
}

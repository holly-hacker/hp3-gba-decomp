#include "types.h"
#include "cheat.h"
#include "font.h"
#include "text.h"

void DrawCheatEntries(void)
{
    u32 tileCursor;
    s32 i;
    s32 y;

    tileCursor = 0;
    for (i = 0, y = 0x28; i < 6; y += 0x10, i++)
    {
        // 0x64A.. "Map", "Select Character Level and Quest", "Select Party Member",
        // "Select Test Sound and Music", "View Collector's Cards", "View Portraits"
        tileCursor = DrawStringAligned(tileCursor + 1, 0x79, y, GetDialogText(0x64A + i), 1);
    }
}

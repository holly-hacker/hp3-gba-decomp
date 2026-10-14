#include "types.h"
#include "cheat_map.h"
#include "font.h"
#include "text.h"

void DrawCheatMapNames(void)
{
    u32 tileCursor;
    s32 i;
    s32 y;
    u8 *text;

    tileCursor = 0;
    for (i = 0, y = 8; i < 0x37; y += 8, i++)
    {
        text = GetDialogText(0x54A + i);  // 0x54A "Defense Against the Dark Arts Classroom" .. 0x580 "Diagon Alley Test Map 5"
        tileCursor = DrawStringAligned(tileCursor + 1, 0x79, y, text, 1);
    }
}

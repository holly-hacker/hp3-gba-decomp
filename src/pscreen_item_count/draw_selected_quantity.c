#include "types.h"
#include "modes.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "pscreen_item_count.h"

void DrawSelectedQuantity(void)
{
    const u8 *text;

    ClearBgTilemapRect(2, 0xD, 0xC, 4, 3);
    SelectTextFont(3, 0, -1);
    SetTextMacro1Number(g_GameModeStackContext.dwModeScratchB);
    text = GetDialogText(0x8F7);  // "@1"
    DrawTextLines(0xE0, 0x78, 0x60, 0x50, 0x18, &text, 1);
}

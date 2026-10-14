#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "cheat_party_inline.h"

void DrawCheatPartyRows(void)
{
    u32 tileCursor;
    s32 i;
    s32 y;
    u8 *text;

    tileCursor = 0;
    FillBgTilemapRect(1, 0x15, 5, 4, 0xC, 0);
    SelectTextFont(5, 0, -1);
    for (i = 0, y = 0x32; i < 3; y += 0x12, i++)
    {
        text = GetDialogText(0x523 + i);  // "Lead Hero", "Second Follow", "Third Follow"
        tileCursor = PrintTextBox(tileCursor + 1, 0x50, y, 0x64, text, 1);
    }
    g_CheatPartyState.dwTileCursor = tileCursor;

    DrawCheatPartyCharacters();
}

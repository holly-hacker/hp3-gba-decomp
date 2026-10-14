#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "cheat_sound_test_inline.h"

void DrawCheatSoundTestRows(void)
{
    u32 tileCursor;
    s32 i;

    tileCursor = 0;
    FillBgTilemapRect(1, 0x15, 5, 4, 0xC, 0);
    for (i = 0; i < 2; i++)
    {
        u8 *label = GetDialogText(0x65F + i);  // "Sound FX", "Music"

        tileCursor = PrintTextBox(tileCursor + 1, 0x50, 0x32 + i * 0x12, 0x64, label, 1);
    }
    g_CheatSoundTestState.dwTileCursor = tileCursor;

    DrawCheatSoundTestValues();
}

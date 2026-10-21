#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "pop_it_minigame.h"

void DrawWizardCrackerPopItPauseMenu(void)
{
    u32 tileCursor;

    FillBgTilemapRect(3, 0, 8, 30, 6, 0);
    tileCursor = DrawStringAligned(0x61, 120, 64, GetDialogText(0xA58), 1);  // "Resume Game"
    tileCursor = DrawStringAligned(tileCursor, 120, 80, GetDialogText(0xA59), 1);  // "Replay"
    DrawStringAligned(tileCursor, 120, 96, GetDialogText(0xA5A), 1);  // "Exit Game"
}

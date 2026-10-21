#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "pop_it_minigame.h"

void DrawWizardCrackerPopItResultsMenu(void)
{
    u32 tileCursor;

    FillBgTilemapRect(3, 0, 8, 30, 4, 0);
    tileCursor = DrawStringAligned(0x61, 120, 64, GetDialogText(0xA5B), 1);  // "New Game"
    DrawStringAligned(tileCursor, 120, 80, GetDialogText(0xA5C), 1);  // "Exit Game"
}

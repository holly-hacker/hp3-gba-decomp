#include "types.h"
#include "background.h"
#include "cursor.h"
#include "font.h"
#include "landmarks.h"
#include "modes.h"
#include "text.h"

static inline void ClearTextPanel(u16 tileOffset)
{
    CopyBgTilemapRect(1, g_pUnusedHogwartsMapBg1Tilemap, tileOffset, 0, 2, 17, 2, 17, 13, 2);
}

void DrawUnusedHogwartsMapSelection(void)
{
    ClearTextPanel(0x181);
    SetTextTargetFromBgControl(g_dwUnusedHogwartsMapBg1Control);
    SelectTextFont(7, 0, -1);
    // "Go to the cellar and find Crookshanks."
    PrintTextBox(0x1C0, 0x6C, 0x88, 0x9C, GetDialogText(0x90C), 1);
    SetMenuCursorPosition(g_pUnusedHogwartsMapCursor, 0xD5,
                          g_GameModeStackContext.dwCurrentGameModeArg2 * 16 + 16);
}

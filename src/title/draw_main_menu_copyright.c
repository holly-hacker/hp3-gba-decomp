#include "types.h"
#include "font.h"
#include "text.h"
#include "title.h"

#ifdef VERSION_JP
#define COPYRIGHT_FIRST_LINE_HEIGHT 0x18
#else
#define COPYRIGHT_FIRST_LINE_HEIGHT 0x10
#endif

void DrawMainMenuCopyright(void)
{
    u8 *pText;

    SetTextTargetFromBgControl(g_dwMainMenuBg1Control);
    SelectTextFont(0, 0, -1);
    pText = GetDialogText(0x8E7);  // "© 2004 Electronic Arts Inc.\nAll rights reserved."
    g_nMainMenuTextCursor = DrawTextLines(0x118, 0x78, 0x71, 0xB4, COPYRIGHT_FIRST_LINE_HEIGHT, &pText, 1);
    pText = GetDialogText(0x8E6);  // "LICENSED BY NINTENDO"
    g_nMainMenuTextCursor = DrawTextLines(g_nMainMenuTextCursor, 0x78, 0x83, 0xB4, 0x10, &pText, 1);
}

#include "types.h"
#include "modes.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "title_options.h"

void DrawOptionsLanguageHint(void)
{
#ifndef VERSION_JP
    const u8 *pText;

    if (g_GameModeStackContext.dwModeScratchB == OptionsRowLanguage)
    {
        SelectTextFont(0, 0, 0);
        pText = GetDialogText(0x8E0);  // "Press A Button to change the language."
        DrawTextLines(0x1C0, 0x78, 0x78, 0xB8, 0x10, &pText, 1);
    }
    else
#endif
    {
        ClearBgTilemapRect(2, 2, 0xF, 0x1C, 1);
    }
}

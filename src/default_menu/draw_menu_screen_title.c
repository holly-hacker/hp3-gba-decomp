#include "types.h"
#include "background.h"
#include "default_menu.h"
#include "font.h"
#include "text.h"

#ifdef VERSION_JP
#define TITLE_Y 4
#else
#define TITLE_Y 3
#endif

void DrawMenuScreenTitle(u32 stringId)
{
    const u8 *pText;

    ClearBgTilemapRect(2, 0, 0, 30, 2);

    if (stringId != 0xACF)  // no text
    {
        SetTextTargetFromBgControl(g_dwCommonBg2Control);
        SelectTextFont(3, 0, 0);
        pText = GetDialogText(stringId);
        DrawTextLines(1, 120, TITLE_Y, 240, 24, &pText, 1);
    }
}

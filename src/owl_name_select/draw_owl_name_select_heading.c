#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "modes.h"
#include "owl_name_select.h"

void DrawOwlNameSelectHeading(void)
{
    s32 textId;

    FillBgTilemapRect(2, 3, 0, 24, 3, 0);
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
        textId = 0x672;  // "Select Owl Name"
    else
        textId = 0x671;  // "Select Owl Type"
    SelectTextFont(3, 0, 0);
    DrawStringAligned(1, 120, 4, GetDialogText(textId), 1);
}

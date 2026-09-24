#include "types.h"
#include "game_modes.h"
#include "menu.h"
#include "text.h"

void DrawListMenuRow(u32 row)
{
    u32 color;
    const u8 *pText;

    color = (row == g_GameModeStackContext.dwModeScratchB) ? 6 : 0;

    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(g_ListMenuState.pDefinition->wFont, color, -1);

    pText = GetDialogText(g_ListMenuState.pDefinition->pEntries[row].wStringId);
    DrawString(row * 0x30 + 0x61,
               g_ListMenuState.pDefinition->wStrideX * row + g_ListMenuState.pDefinition->wBaseX,
               g_ListMenuState.pDefinition->wStrideY * row + g_ListMenuState.pDefinition->wBaseY,
               pText);
}

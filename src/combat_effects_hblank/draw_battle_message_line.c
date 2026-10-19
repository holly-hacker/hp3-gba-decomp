#include "types.h"
#include "combat.h"
#include "combat_effects_hblank.h"
#include "font.h"
#include "text.h"

void DrawBattleMessageLine_unused(s32 textId, s32 y, u32 align)
{
    s32 x;
    const u8 *text;

    if (align & 1)
        x = 0xA0;
    else
        x = 0x58;
    text = GetDialogText(textId);
    g_pFightState->dwTextTileCursor =
        DrawTextLines(g_pFightState->dwTextTileCursor, x, y, 0x90, 0x18, &text, align);
}

#include "types.h"
#include "battle/battle.h"
#include "combat_2.h"
#include "font.h"
#include "text.h"
#include "combat_result.h"
#include "hero.h"
#include "combat.h"

#define FIGHTER(pos) g_aPartyMasterStats[g_abCombatResultPartySlots[pos]]
#define MAX_DISPLAY_LEVEL 98

// Draws the XP phase: the headline, each party member's Exp, Level and Next
// values, then the XP gained. The tile cursors of the values are kept in
// g_aCombatResultPartyRows for TickCombatResultXpCounter to redraw in place.
void InitializeCombatResultXp(void)
{
    u8 *pText;
    s32 x;
    s32 width;

    SetTextTargetFromBgControl(g_dwCombatResultBg0Control);
    SelectTextFont(3, 0, -1);
    pText = GetDialogText(0x527);  // "You are victorious!"
    g_wCombatResultTextTileCursor = DrawStringAligned(1, 0x78, 3, pText, 1);
    SelectTextFont(0, 0, -1);

    if (GetPartySize() > 1)
    {
        pText = GetDialogText(0x529);  // "Exp:"
        g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x14, 0x68, pText, 0);
        pText = GetDialogText(0x8F7);  // "@1"
        SetTextMacro1Number(GetPartyMemberTotalXp(g_abCombatResultPartySlots[0]));
        g_aCombatResultPartyRows[0].wExpTileCursor = g_wCombatResultTextTileCursor;
        DrawStringAligned(g_wCombatResultTextTileCursor, 0x4C, 0x68, pText, 2);
        g_wCombatResultTextTileCursor += 8;
        pText = GetDialogText(0x52A);  // "Level:"
        g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x14, 0x70, pText, 0);
        pText = GetDialogText(0x8F7);  // "@1"
        SetTextMacro1Number(FIGHTER(0).bLevel + 1);
        g_aCombatResultPartyRows[0].wLevelTileCursor = g_wCombatResultTextTileCursor;
        DrawStringAligned(g_wCombatResultTextTileCursor, 0x4C, 0x70, pText, 2);
        g_wCombatResultTextTileCursor += 8;
        if (FIGHTER(0).bLevel <= MAX_DISPLAY_LEVEL)
        {
            pText = GetDialogText(0x52F);  // "Next:"
            g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x14, 0x78, pText, 0);
            pText = GetDialogText(0x8F7);  // "@1"
            g_aCombatResultPartyRows[0].nXpToNextLevel = GetPartyMemberXpToNextLevel(g_abCombatResultPartySlots[0]);
            if (FIGHTER(0).bLevel <= MAX_DISPLAY_LEVEL)
                SetTextMacro1Number(g_aCombatResultPartyRows[0].nXpToNextLevel);
            else
                SetTextMacro1Number(0);
            g_aCombatResultPartyRows[0].wNextTileCursor = g_wCombatResultTextTileCursor;
            DrawStringAligned(g_wCombatResultTextTileCursor, 0x4C, 0x78, pText, 2);
            g_wCombatResultTextTileCursor += 8;
        }
        g_aCombatResultPartyRows[0].wLevelUpTileCursor = g_wCombatResultTextTileCursor;
        g_wCombatResultTextTileCursor += MeasureMacroString(GetDialogText(0x52E));  // "Level Up!"

        pText = GetDialogText(0x529);  // "Exp:"
        g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0xA4, 0x68, pText, 0);
        pText = GetDialogText(0x8F7);  // "@1"
        SetTextMacro1Number(GetPartyMemberTotalXp(g_abCombatResultPartySlots[1]));
        g_aCombatResultPartyRows[1].wExpTileCursor = g_wCombatResultTextTileCursor;
        DrawStringAligned(g_wCombatResultTextTileCursor, 0xDC, 0x68, pText, 2);
        g_wCombatResultTextTileCursor += 8;
        pText = GetDialogText(0x52A);  // "Level:"
        g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0xA4, 0x70, pText, 0);
        pText = GetDialogText(0x8F7);  // "@1"
        SetTextMacro1Number(FIGHTER(1).bLevel + 1);
        g_aCombatResultPartyRows[1].wLevelTileCursor = g_wCombatResultTextTileCursor;
        DrawStringAligned(g_wCombatResultTextTileCursor, 0xDC, 0x70, pText, 2);
        g_wCombatResultTextTileCursor += 8;
        if (FIGHTER(1).bLevel <= MAX_DISPLAY_LEVEL)
        {
            pText = GetDialogText(0x52F);  // "Next:"
            g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0xA4, 0x78, pText, 0);
            pText = GetDialogText(0x8F7);  // "@1"
            g_aCombatResultPartyRows[1].nXpToNextLevel = GetPartyMemberXpToNextLevel(g_abCombatResultPartySlots[1]);
            if (FIGHTER(1).bLevel <= MAX_DISPLAY_LEVEL)
                SetTextMacro1Number(g_aCombatResultPartyRows[1].nXpToNextLevel);
            else
                SetTextMacro1Number(0);
            g_aCombatResultPartyRows[1].wNextTileCursor = g_wCombatResultTextTileCursor;
            DrawStringAligned(g_wCombatResultTextTileCursor, 0xDC, 0x78, pText, 2);
            g_wCombatResultTextTileCursor += 8;
        }
        g_aCombatResultPartyRows[1].wLevelUpTileCursor = g_wCombatResultTextTileCursor;
        g_wCombatResultTextTileCursor += MeasureMacroString(GetDialogText(0x52E));  // "Level Up!"
    }

    if (GetPartySize() != 2)
    {
        pText = GetDialogText(0x529);  // "Exp:"
        g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x5C, 0x68, pText, 0);
        pText = GetDialogText(0x8F7);  // "@1"
        SetTextMacro1Number(GetPartyMemberTotalXp(g_abCombatResultPartySlots[2]));
        g_aCombatResultPartyRows[2].wExpTileCursor = g_wCombatResultTextTileCursor;
        DrawStringAligned(g_wCombatResultTextTileCursor, 0x94, 0x68, pText, 2);
        g_wCombatResultTextTileCursor += 8;
        pText = GetDialogText(0x52A);  // "Level:"
        g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x5C, 0x70, pText, 0);
        pText = GetDialogText(0x8F7);  // "@1"
        SetTextMacro1Number(FIGHTER(2).bLevel + 1);
        g_aCombatResultPartyRows[2].wLevelTileCursor = g_wCombatResultTextTileCursor;
        DrawStringAligned(g_wCombatResultTextTileCursor, 0x94, 0x70, pText, 2);
        g_wCombatResultTextTileCursor += 8;
        if (FIGHTER(2).bLevel <= MAX_DISPLAY_LEVEL)
        {
            pText = GetDialogText(0x52F);  // "Next:"
            g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x5C, 0x78, pText, 0);
            pText = GetDialogText(0x8F7);  // "@1"
            g_aCombatResultPartyRows[2].nXpToNextLevel = GetPartyMemberXpToNextLevel(g_abCombatResultPartySlots[2]);
            if (FIGHTER(2).bLevel <= MAX_DISPLAY_LEVEL)
                SetTextMacro1Number(g_aCombatResultPartyRows[2].nXpToNextLevel);
            else
                SetTextMacro1Number(0);
            g_aCombatResultPartyRows[2].wNextTileCursor = g_wCombatResultTextTileCursor;
            DrawStringAligned(g_wCombatResultTextTileCursor, 0x94, 0x78, pText, 2);
            g_wCombatResultTextTileCursor += 8;
        }
        g_aCombatResultPartyRows[2].wLevelUpTileCursor = g_wCombatResultTextTileCursor;
        g_wCombatResultTextTileCursor += MeasureMacroString(GetDialogText(0x52E));  // "Level Up!"
    }

    SelectTextFont(2, 0, -1);
    SetTextMacro1String(g_sCombatResultMacro1Space);
    pText = GetDialogText(0x52B);  // "You gained experience: @1"
    x = 0x78;
#ifdef VERSION_US
    if (GetLanguage() == 6)
        x = 0x6C;
#endif
    g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, x, 0x94, pText, 1);
    width = MeasureMacroString(GetDialogText(0x52B));
    x = width / 2 + 0x84;
#ifdef VERSION_US
    if (GetLanguage() == 6)
        x -= 0x10;
#endif
    g_wCombatResultXpNumberX = x;
    SetTextMacro1Number(g_dwCombatResultXpRemaining);
    g_wCombatResultXpTileCursor = g_wCombatResultTextTileCursor;
    pText = GetDialogText(0x8F7);  // "@1"
    g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultXpTileCursor, x, 0x94, pText, 0);
}

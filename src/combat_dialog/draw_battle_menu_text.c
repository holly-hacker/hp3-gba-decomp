#include "types.h"
#include "background.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_fighter.h"
#include "font.h"
#include "gen/graphics/battle.h"
#include "items.h"
#include "text.h"

// Draws the label of the highlighted battle menu row above the menu icons: the top menu
// entry, spell, Special Move or item name, or for a spell cast level its name and cost.
void DrawBattleMenuText(void)
{
    BattleFighter *fighter;
    u8 fighterType;
    const u8 *text;
    u8 spellId = 0;

    fighter = &g_pFightState->pFighters[g_pFightState->bMenuFighterIndex];
    fighterType = fighter->bFighterType;
#ifdef VERSION_JP
    CopyBgTilemapRect(0, GetGraphicBlobTilemap(1, gBattleHudPanel), 1, 0, 10, 0, 10, 24, 20, 2);
#else
    CopyBgTilemapRect(0, GetGraphicBlobTilemap(1, gBattleHudPanel), 1, 0, 10, 1, 10, 25, 20, 1);
#endif
    g_pFightState->dwTextTileCursor = 0xA0;
    SetTextTargetFromBgControl(g_dwBattleBg0Control);
    SelectTextFont(7, 0, 0);

    text = NULL;
    switch (g_pFightState->bMenuScreen) {
    case BattleMenuTop:
        text = GetDialogText(g_adwBattleTopMenuTextIds[g_pFightState->bMenuCursor]);  // "Cast Spell", ...
        break;

    case BattleMenuSpellChoice:
        // The spell name: "Flipendo", ...
        text = GetDialogText(g_aabFighterSpellMenu[fighterType][g_pFightState->bMenuCursor] + 0x95F);
        break;

    case BattleMenuSpecialMove:
        if (fighterType == Hermione)
            text = GetDialogText(g_pFightState->bMenuCursor + 0x8FA);  // "Be More Careful", ...
        else
            text = GetDialogText(g_pFightState->bMenuCursor + 0x8FD);  // "Stink Pellet", ...
        break;

    case BattleMenuSpellTier:
        spellId = g_aabFighterSpellMenu[fighterType][g_pFightState->bSpellMenuCursor];
        text = GetDialogText(spellId + 0x95F);  // "Flipendo", ...
        SetTextMacro2String(text);
        SetTextMacro1Number(g_awSpellMpCost[spellId][g_pFightState->bMenuCursor]);
        // Spells with a single cast level don't name the level.
        if (spellId == Diffindo || spellId == Informus || spellId == WingardiumLeviosa
            || spellId == Spongify) {
            text = GetDialogText(0x900);  // "@1 MP: @2"
        } else {
            text = GetDialogText(g_pFightState->bMenuCursor + 0x969);  // "Uno", "Duo", "Tria"
            SetTextMacro3String(text);
            text = GetDialogText(0x8F9);  // "@1 MP: @2 @3"
        }
        break;

    case BattleMenuItem:
        // The potion's name: "Wiggenweld Potion", ...
        text = GetDialogText(GetRewardNameStringId_candidate(g_pFightState->bMenuCursor + 0x38));
        break;

    case BattleMenuEnemyTarget:
    case BattleMenuAllyTarget:
    case BattleMenuFaintedAlly:
        break;
    }

    if (text != NULL)
        g_pFightState->dwTextTileCursor =
            DrawStringAligned(g_pFightState->dwTextTileCursor, 0xA0, BATTLE_TEXT_ROW0_Y, text, 1);
}

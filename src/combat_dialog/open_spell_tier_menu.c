#include "types.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_fighter.h"

// Opens the cast-level menu of the spell on spellRow of the fighter's spell list, one row per
// level the fighter has learned, graying the levels it can't pay for. The cursor starts on
// the level last chosen.
void OpenSpellTierMenu(u8 fighterIndex, u8 spellRow)
{
    BattleFighter *fighter;
    u8 fighterType;
    u8 spellId;
    u32 level;
    u32 enabled;

    fighter = &g_pFightState->pFighters[fighterIndex];
    fighterType = fighter->bFighterType;
    spellId = g_aabFighterSpellMenu[fighterType][spellRow];
    g_pFightState->bMenuScreen = BattleMenuSpellTier;
    g_pFightState->bSpellMenuCursor = spellRow;
    ClearBattleTextPanel();
    DrawBattleMenuFrame();
    DrawFighterStatsUi(fighterType, 0);

    for (level = 0; level < fighter->stats.aSpellCastLevel[spellId]; level++) {
        enabled = 1;
        if (g_awSpellMpCost[spellId][level] > fighter->stats.wMp)
            enabled = 0;
        SetBattleMenuIconState(spellId + 4, level, fighterType, enabled);
    }

    g_pFightState->bMenuCursor = fighter->bSpellLevel;
    SelectBattleMenuIcon(g_pFightState->bMenuCursor);
    DrawBattleMenuText();
}

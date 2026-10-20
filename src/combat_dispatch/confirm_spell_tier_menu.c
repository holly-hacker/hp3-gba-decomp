#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "combat_fighter.h"
#include "modes.h"
#include "sound.h"

// The spell id and cast level bytes read as one halfword.
#define SPELL_AND_LEVEL(fighter) (*(u16 *)&(fighter)->bSpellId)
#define SPELL_LEVEL_PAIR(spell, level) ((level) << 8 | (spell))

// Casts the spell at the cursor's level if the fighter has the MP. Informus is refused in
// scripted battles. Most casts pick an enemy; Fumos Duo picks an ally, and Petrificus Totalus
// Duo and every Tria but Incendio's take effect at once.
void ConfirmSpellTierMenu(u32 fighterType, BattleFighter *pFighter)
{
    if (g_awSpellMpCost[pFighter->bSpellId][g_pFightState->bMenuCursor] > pFighter->stats.wMp
        || (pFighter->bSpellId == Informus && g_dwPendingGameMode.dwCurrentGameModeArg3 == 0xFF)) {
        PlaySoundById(3);
        return;
    }

    pFighter->bSpellLevel = g_pFightState->bMenuCursor;
    if (SPELL_AND_LEVEL(pFighter) == SPELL_LEVEL_PAIR(Fumos, 1)
        || SPELL_AND_LEVEL(pFighter) == SPELL_LEVEL_PAIR(PetrificusTotalus, 1)
        || (pFighter->bSpellLevel == 2 && pFighter->bSpellId != Incendio)) {
        pFighter->bSelectedActionIndex = 0xFE;
        g_pFightState->bMenuScreen = BattleMenuNone;
        PlaySoundById(1);
    } else if (pFighter->bSpellId == Fumos) {
        PlaySoundById(0);
        OpenAllyTargetMenu(g_pFightState->bMenuFighterIndex);
    } else {
        PlaySoundById(0);
        ShowEnemyTargetMenu(g_pFightState->bMenuFighterIndex);
    }
}

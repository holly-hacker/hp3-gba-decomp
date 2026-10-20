#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "sound.h"

// Takes the spell on the cursor row and opens its cast level menu.
void ConfirmSpellChoiceMenu(u32 fighterType, BattleFighter *pFighter)
{
    pFighter->bPendingActionKind = PendingActionNone;
    pFighter->bSpellId = g_aabFighterSpellMenu[fighterType][g_pFightState->bMenuCursor];
    pFighter->bSpellLevel = 0;
    PlaySoundById(0);
    OpenSpellTierMenu(g_pFightState->bMenuFighterIndex, g_pFightState->bMenuCursor);
}

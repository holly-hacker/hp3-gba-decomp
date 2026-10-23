#include "types.h"
#include "combat_dialog.h"
#include "combat_fighter.h"
#include "combat.h"

// Ends the attack animation and reports g_nLastDamage against targetIndex: a
// value above 999 is a critical hit of (value - 999), 0 a miss. Any pending
// status message follows the damage message.
void ShowAttackResult(Actor *actor, s32 targetIndex)
{
    actor->scriptState.bytes.bAttackOutcomeState = 0;
    g_pFightState->pAttackOutcomeActor = 0;
    g_pFightState->bAttackOutcomeState = 0;

    if (g_nLastDamage > 999)
    {
        ShowBattleMessage(AttackResult, g_nLastDamage, 0);
        if (g_pFightState->bPendingStatusMessageVariant != NO_PENDING_STATUS_MESSAGE_VARIANT)
            ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant);
        g_nLastDamage -= 999;
        ShowFloatingDamageNumber(g_nLastDamage, 3, targetIndex, 0);
    }
    else if (g_nLastDamage != 0)
    {
        ShowBattleMessage(AttackResult, g_nLastDamage, 0);
        if (g_pFightState->bPendingStatusMessageVariant != NO_PENDING_STATUS_MESSAGE_VARIANT)
            ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant);
        ShowFloatingDamageNumber(g_nLastDamage, 0, targetIndex, 0);
    }
    else
    {
        ShowBattleMessage(AttackResult, g_nLastDamage, 1);
        if (g_pFightState->bPendingStatusMessageVariant != NO_PENDING_STATUS_MESSAGE_VARIANT)
            ShowBattleMessage(AttackResult, 0, g_pFightState->bPendingStatusMessageVariant);
        ShowFloatingDamageNumber(g_nLastDamage, 2, targetIndex, 0);
    }
}

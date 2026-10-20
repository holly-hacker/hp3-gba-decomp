#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "sound.h"

// Takes the Special Move on the cursor. Hermione's lectures target an ally and Ron's moves an
// enemy, except Hermione's second lecture and Ron's third move, which take effect at once.
void ConfirmSpecialMoveMenu(u32 fighterType, BattleFighter *pFighter)
{
    pFighter->bSpellId = g_pFightState->bMenuCursor;
    pFighter->bPendingActionKind = PendingActionSpecialMove;

    if (fighterType == Hermione) {
        if (pFighter->bSpellId == 1) {
            pFighter->bSelectedActionIndex = 0xFE;
            g_pFightState->bMenuScreen = BattleMenuNone;
            PlaySoundById(1);
        } else {
            PlaySoundById(0);
            OpenAllyTargetMenu(g_pFightState->bMenuFighterIndex);
        }
    } else {
        if (pFighter->bSpellId == 2) {
            pFighter->bSelectedActionIndex = 0xFE;
            g_pFightState->bMenuScreen = BattleMenuNone;
            PlaySoundById(1);
        } else {
            PlaySoundById(0);
            ShowEnemyTargetMenu(g_pFightState->bMenuFighterIndex);
        }
    }
}

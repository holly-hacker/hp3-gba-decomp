#include "types.h"
#include "combat_menu.h"

// Indexed by bMenuScreen.
const BattleMenuInputHandler g_apfnBattleMenuConfirmHandlers[11] = {
    IgnoreBattleMenuInput,
    ConfirmBattleTopMenu,
    ConfirmSpellChoiceMenu,
    IgnoreBattleMenuInput,
    ConfirmSpecialMoveMenu,
    ConfirmSpellTierMenu,
    ConfirmEnemyTargetMenu,
    ConfirmItemMenu,
    ConfirmAllyTargetMenu,
    ConfirmPendingFighterMenu_candidate,
    IgnoreBattleMenuInput,
};

const BattleMenuInputHandler g_apfnBattleMenuCancelHandlers[11] = {
    IgnoreBattleMenuInput,
    CancelBattleTopMenu,
    CancelToBattleTopMenu,
    IgnoreBattleMenuInput,
    CancelToBattleTopMenu,
    CancelSpellTierMenu,
    CancelEnemyTargetMenu,
    CancelToBattleTopMenu,
    CancelAllyTargetMenu,
    CancelPendingFighterMenu_candidate,
    IgnoreBattleMenuInput,
};

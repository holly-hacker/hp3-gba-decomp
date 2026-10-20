#include "combat_dialog.h"
#include "combat_dispatch.h"

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
    ConfirmFaintedAllyMenu,
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
    CancelFaintedAllyMenu,
    IgnoreBattleMenuInput,
};

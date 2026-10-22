#include "types.h"
#include "combat_board.h"
#include "combat_core.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_fighter.h"
#include "modes.h"
#include "combat.h"
#include "input.h"

static inline void TransitionBattleState(int newState)
{
    if (g_pFightState->bBattleState != 6 && g_pFightState->bBattleState != 7) {
        g_pFightState->bSavedBattleState = g_pFightState->bBattleState;
        g_pFightState->bBattleState = newState;
        g_pFightState->dwStateJustEntered = 1;
    }
}

void TickBattleTurnStateMachine(void)
{
    u32 i;
    u8 rollResult;
    u8 fighterType;
    u8 savedState;

    switch (g_pFightState->bBattleState) {
    case 0:
        if (g_pFightState->dwStateJustEntered)
            g_pFightState->dwStateJustEntered = 0;

        break;

    case 1:
        if (g_pFightState->dwStateJustEntered) {
            g_pFightState->dwStateJustEntered = 0;
            g_pFightState->bPendingStatusMessageVariant_candidate = 0x12;

            SetFighterTurnOrderIconDone(g_pFightState->bActiveFighterIndex);

            g_pFightState->bActiveFighterIndex++;
            g_pFightState->wBattleStateTimer = 0x10;

            if (g_pFightState->bActiveFighterIndex < g_pFightState->bFighterCount)
                SetFighterTurnOrderIconActive(g_pFightState->bActiveFighterIndex);
        }
        else if (g_pFightState->wBattleStateTimer == 0) {
            // wait for every fighter's turn-order icon (pActor->pLinkedActor_candidate) to clear
            for (i = 0; i < g_pFightState->bFighterCount; i++) {
                if (g_pFightState->pFighters[i].pActor->pLinkedActor_candidate != 0)
                    break;
            }

            if (i < g_pFightState->bFighterCount)
                break;

            if (g_pFightState->bActiveFighterIndex >= g_pFightState->bFighterCount) {
                TransitionBattleState(2);
            } else {
                EndFighterTurnStub(g_pFightState->bActiveFighterIndex - 1);

                if (ACTIVE_FIGHTER.bFighterType == Enemy) {
                    TransitionBattleState(4);
                } else {
                    TransitionBattleState(3);
                }
            }
        } else {
            g_pFightState->wBattleStateTimer--;
        }
        break;

    case 2:
        if (g_pFightState->dwStateJustEntered) {
            g_pFightState->dwStateJustEntered = 0;
            g_pFightState->wBattleStateTimer = 0x1e;
            g_pFightState->dwDefeatCheckPending_candidate = 0;

            for (i = 0; i < g_pFightState->bFighterCount; i++) {
                if (g_pFightState->pFighters[i].bStatusFlags & Poisoned) {
                    ShowFloatingDamageNumber(g_pFightState->pFighters[i].bPoisonDamage, 4, i, 0);
                    ApplyDamageToAllyFighter(g_pFightState->pFighters[i].bPoisonDamage, i);
                    g_pFightState->wBattleStateTimer = 0x3c;
                }
            }

            if (g_pFightState->dwDefeatCheckPending_candidate == 0)
                break;

            CheckBattleDefeat();

            if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xfe)
                break;

            PruneFaintedAndRebuildTurnOrder_candidate(0);

            g_pFightState->wBattleStateTimer = 0x5a;
            break;
        }

        if (--g_pFightState->wBattleStateTimer == 0xffff) {
            if (g_pFightState->dwDefeatCheckPending_candidate != 0) {
                g_pFightState->dwDefeatCheckPending_candidate = 0;
                SetFighterTurnOrderIconActive(0);
                EndFighterTurnStub(g_pFightState->bFighterCount - 1);
            }

            g_pFightState->bActiveFighterIndex = 0;

            if (ACTIVE_FIGHTER.bFighterType != Enemy) {
                TransitionBattleState(3);
            } else {
                TransitionBattleState(4);
            }
            break;
        }

        if (g_pFightState->wBattleStateTimer == 0x10) {
            SetFighterTurnOrderIconActive(0);
            EndFighterTurnStub(g_pFightState->bFighterCount - 1);
        }

        break;

    case 3:
        if (g_pFightState->dwStateJustEntered) {
            g_pFightState->dwStateJustEntered = 0;
            rollResult = RollFighterParalysisEscape(g_pFightState->bActiveFighterIndex);
            if (rollResult != 0) {
                g_pFightState->bBattleState = 1;
                DrawFighterStatsUi(ACTIVE_FIGHTER.bFighterType, 0);

                if (rollResult == 3)
                    ShowBattleMessage(CanMoveAgain, 0, 0);
                else
                    ShowBattleMessage(CantMove, 0, 0);

                TransitionBattleState(5);
            } else {
                g_pFightState->bMenuFighterIndex = g_pFightState->bActiveFighterIndex;
                OpenBattleTopMenu(g_pFightState->bMenuFighterIndex, 0);
            }
        } else {
            TickBattleMenuInput();

            if (g_pFightState->bMenuScreen == BattleMenuNone) {
                DrawFighterStatsUi(ACTIVE_FIGHTER.bFighterType, 0);

                TransitionBattleState(4);
            }
        }
        break;

    case 4:
        fighterType = ACTIVE_FIGHTER.bFighterType;
        if (fighterType == Enemy) {
            DrawEnemyStatsUi(g_pFightState->bActiveFighterIndex, 0);
            rollResult = RollFighterParalysisEscape(g_pFightState->bActiveFighterIndex);
            if (rollResult != 0) {
                g_pFightState->bBattleState = 1;

                if (rollResult == 3)
                    ShowBattleMessage(CanMoveAgain, 0, 0);
                else
                    ShowBattleMessage(CantMove, 0, 0);

                TransitionBattleState(5);
                break;
            }
            ShowBattleMessage(ActionAnnounce, 0, 0);
            SetActorActionState(ACTIVE_FIGHTER.pActor, 0x1a);
            ACTIVE_FIGHTER.pActor->bActionFlags = 0x21;
            TransitionBattleState(0);
        } else {
            DispatchPendingAction(fighterType);
            TransitionBattleState(0);
        }
        break;

    case 5:
        if (g_pFightState->dwStateJustEntered) {
            g_pFightState->dwStateJustEntered = 0;
            g_pFightState->wBattleStateTimer = 0x1e;
            break;
        }

        if (--g_pFightState->wBattleStateTimer == 0xffff || (g_wKeysPressed & KeyA) != 0) {
            savedState = g_pFightState->bSavedBattleState;
            TransitionBattleState(savedState);

            g_pFightState->wBattleStateTimer = 0;
        }

        break;

    case 6:
        if (g_pFightState->dwStateJustEntered) {
            g_pFightState->dwStateJustEntered = 0;
            g_pFightState->wBattleStateTimer = 0x96;
        }

        if (--g_pFightState->wBattleStateTimer == 0xffff) {
            g_pFightState->wBattleStateTimer = 0xff;
            PushGameMode_2(Overworld, 0, g_pFightState->bDefeatWarpTarget);
        }

        break;

    case 7:
        if (g_pFightState->dwStateJustEntered) {
            g_pFightState->dwStateJustEntered = 0;
            g_pFightState->wBattleStateTimer = 0x1e;
        }
        if (--g_pFightState->wBattleStateTimer == 0xffff) {
            g_pFightState->wBattleStateTimer = 0xff;
            PushGameMode(CombatResult);
        }
        break;
    }
}

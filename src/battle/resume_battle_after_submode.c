#include "types.h"
#include "battle/battle.h"
#include "game/game_modes.h"

// Re-enters the battle after returning from a submode (or starting a fresh
// battle): applies a Folio Universitas card choice, sets up the first round,
// or reopens the battle menu after the Help screen.
void ResumeBattleAfterSubmode_candidate(void)
{
    BattleFighter *fighter = &g_pFightState->pFighters[g_pFightState->bMenuFighterIndex];
    u32 i;
    u8 targetKind;

    if (g_PrevGameModeStackContext.dwCurrentGameMode != FolioUniversitas) {
        if (g_PrevGameModeStackContext.dwCurrentGameMode != HelpTopicScreen) {
            g_pFightState->wBattleStateTimer = 0;
            g_pFightState->bActiveFighterIndex = 0xFF;
            g_pFightState->wNextFighterTurnKey_candidate = g_pFightState->pFighters[0].nFaintedFlag;
            i = 0;
            g_pFightState->bMenuFighterIndex = 0xFF;

            while (g_pFightState->bMenuFighterIndex == 0xFF) {
                if (g_pFightState->pFighters[i].bFighterType != Enemy && g_pFightState->pFighters[i].wHp != 0)
                    g_pFightState->bMenuFighterIndex = i;

                i++;
            }

            PushBattleState(2);
            g_pFightState->bScreenShakeTimer_candidate = 0x1E;
            return;
        }
    } else {
        if (g_nFolioUniversitasSlot < 0xFF) {
            fighter->bPendingActionKind = PendingActionSpecialMove;
            targetKind = g_aCardTargetingMeta[g_nFolioUniversitasSlot][0];

            if (targetKind == 1) {
                OpenEnemyTargetMenu_candidate(g_pFightState->bMenuFighterIndex);
                g_pFightState->bBattleState = 3;
            } else if (targetKind == 2) {
                OpenAllyTargetMenu(g_pFightState->bMenuFighterIndex);
                g_pFightState->bBattleState = 3;
            } else if (targetKind == 3) {
                OpenPendingFighterMenu_candidate(g_pFightState->bMenuFighterIndex);
                g_pFightState->bBattleState = 3;
            } else {
                fighter->bSelectedActionIndex = 0x2A;
                g_pFightState->bMenuScreen = 0;
            }

            return;
        }
    }

    if (g_pFightState->bMenuScreen == 1) {
        if (g_PrevGameModeStackContext.dwCurrentGameMode == HelpTopicScreen) {
            OpenBattleTopMenu(g_pFightState->bMenuFighterIndex, 6);
        } else if (fighter->bPendingActionKind == PendingActionSpecialMove) {
            OpenBattleTopMenu(g_pFightState->bMenuFighterIndex, 1);
            fighter->bPendingActionKind = PendingActionNone;
        } else {
            OpenBattleTopMenu(g_pFightState->bMenuFighterIndex, 5);
        }
    }
}

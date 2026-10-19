#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_gauge.h"
#include "input.h"
#include "sound.h"

// Runs the open battle menu screen for the menu fighter: Left/Right move the cursor (target
// screens move between fighter slots), A and B call the screen's confirm and cancel handlers.
void TickBattleMenuInput(void)
{
    BattleFighter *fighter;
    u32 fighterType;
    u8 prevCursor;
    s32 step;
    u32 lastRow;

    fighter = &g_pFightState->pFighters[g_pFightState->bMenuFighterIndex];
    fighterType = fighter->bFighterType;
    prevCursor = g_pFightState->bMenuCursor;

    if (g_pFightState->bMenuScreen & 0x80 || g_pFightState->bMenuScreen == BattleMenuNone
        || g_pFightState->bMenuScreen == BattleMenuInactive)
        return;

    TickBattleMenuStub();

    if (g_wKeysPressed & KeyLeft) {
        PlaySoundById(0);
        g_pFightState->bMenuCursor--;
    } else if (g_wKeysPressed & KeyRight) {
        PlaySoundById(0);
        g_pFightState->bMenuCursor++;
    }

    step = g_pFightState->bMenuCursor - prevCursor;
    if (step != 0) {
        switch (g_pFightState->bMenuScreen) {
        case BattleMenuEnemyTarget:
            StopEnemyTargetFlash(prevCursor);
            DestroySlotSpGauge(prevCursor, 0);
            MoveEnemyTargetCursor(step);
            SpawnSpGauge(g_pFightState->aEnemySlotTurnOrderIndex[g_pFightState->bMenuCursor], 0);
            FlashEnemyTarget(g_pFightState->bMenuCursor);
            break;

        case BattleMenuAllyTarget:
            // The ally slots run right to left on screen.
            StopAllyTargetFlash(prevCursor);
            DestroySlotSpGauge(prevCursor, 1);
            step = -step;
            g_pFightState->bMenuCursor = prevCursor + step;
            MoveAllyTargetCursor(step);
            SpawnSpGauge(g_pFightState->aAllySlotTurnOrderIndex[g_pFightState->bMenuCursor], 0);
            FlashAllyTarget(g_pFightState->bMenuCursor);
            DrawAllyTargetStats(g_pFightState->bMenuCursor);
            break;

        case BattleMenuPendingFighter:
            StopPendingFighterFlash(prevCursor);
            g_pFightState->bMenuCursor = prevCursor;
            TogglePendingFighterCursor_candidate();
            FlashPendingFighter(g_pFightState->bMenuCursor);
            break;

        case BattleMenuSpellChoice:
            lastRow = fighter->stats.bKnownSpellCount - 1;
            g_pFightState->bMenuCursor = WrapBattleMenuCursor(g_pFightState->bMenuCursor, lastRow);
            SelectBattleMenuIcon(g_pFightState->bMenuCursor);
            break;

        case BattleMenuSpellTier:
            g_pFightState->bMenuCursor = WrapBattleMenuCursor(
                g_pFightState->bMenuCursor, fighter->stats.aSpellCastLevel[fighter->bSpellId] - 1);
            SelectBattleMenuIcon(g_pFightState->bMenuCursor);
            break;

        case BattleMenuItem:
            g_pFightState->bMenuCursor = WrapBattleMenuCursor(g_pFightState->bMenuCursor, 5);
            SelectBattleMenuIcon(g_pFightState->bMenuCursor);
            break;

        case BattleMenuSpecialMove:
            g_pFightState->bMenuCursor = WrapBattleMenuCursor(g_pFightState->bMenuCursor, 2);
            SelectBattleMenuIcon(g_pFightState->bMenuCursor);
            break;

        case BattleMenuTop:
            g_pFightState->bMenuCursor = WrapBattleMenuCursor(g_pFightState->bMenuCursor, 6);
            SelectBattleMenuIcon(g_pFightState->bMenuCursor);
            break;
        }

        DrawBattleMenuText();
    } else if (g_wKeysPressed & KeyA) {
        g_apfnBattleMenuConfirmHandlers[g_pFightState->bMenuScreen](fighterType, fighter);
    } else if (g_wKeysPressed & KeyB) {
        if (g_pFightState->bMenuScreen == BattleMenuTop)
            PlaySoundById(3);
        else
            PlaySoundById(2);

        g_apfnBattleMenuCancelHandlers[g_pFightState->bMenuScreen](fighterType, fighter);
    }
}

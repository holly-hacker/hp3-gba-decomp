#pragma once

#include "combat.h"
#include "palette.h"
#include "video.h"

// The stats panel portrait's palette, copied into FightState.awPalette by HandleBattleVBlank
// two frames after QueueStatsPortraitPalette.
typedef struct {
    u8 bBank;        // first OBJ palette bank + 16, 0xFF when nothing is queued
    u8 bCountdown;   // the copy runs when it wraps past 0
    const ObjPalette *pPalette;
} StatsPortraitPaletteLoad;

// Gives the fighter every spell its FighterType can learn (Hermione 7, the others 6) at the
// maximum cast level, in both stats and its g_aPartyMasterStats record.
extern void LearnAllSpells(u32 fighterType, SavedFighterStats *stats);
extern void StopBgTileAnimationsAfterCard(void);  // stops all BG tile animations
// The camera moves toward the enemies (fighters grow to 1.4x and slide down, the floor scrolls
// forward) and back, each over 8 frames; around the enemy target menu.
extern void ZoomBattleCameraIn(void);
extern void ZoomBattleCameraOut(void);
// Requeues g_aBattleScanlineEffects with the wall band ending at FightState.bWallEndLine.
extern void RestoreBattleScanlineEffects(void);
// RestoreBattleScanlineEffects, then waits for the queue and restores the battle alpha blend.
extern void ResetBattleDisplayEffects(void);
extern void ClearBattleTextPanel(void);  // clears the HUD panel and hides the battle menu icons
extern void MoveEnemyTargetCursor(s32 step);
extern void MoveAllyTargetCursor(s32 step);
// Wait for scanline 42, then end the target flash started by FlashEnemyTarget and its siblings.
extern void StopEnemyTargetFlash(u32 slot);
extern void StopAllyTargetFlash(u32 slot);
extern void StopFaintedAllyFlash(u32 faintedIndex);
extern void SelectBattleMenuIcon(u32 row);  // enlarges row's menu icon and shrinks the previous one
extern u32 WrapBattleMenuCursor(u32 cursor, u32 lastRow);
extern void DrawAllyTargetStats(u32 slot);
extern void DrawBattleMenuFrame(void);
extern void ClearBattleMessageLine(u8 line);
// Clears the battle message box and hides the battle menu icons.
extern void ClearBattleMessageBox(void);
// The room's battle background floor and wall graphic blobs from g_aBattleBackgroundPairs, or
// the alternate pair in rooms 8-15 while QUEST_ALT_PRESENTATION is set.
extern const u8 *GetBattleWallGraphic(void);
extern const u8 *GetBattleFloorGraphic(void);
extern void PushBattleState(s32 state);
extern void OpenEnemyTargetMenu(u8 fighterIndex);  // bMenuScreen 6
extern void HideBattleMenuIcon(u8 row);
extern s32 FighterHasShadowActor(u32 fighterIndex);  // 1 if the fighter has a shadow Actor (monsters 45-47)
extern void SetFighterTurnOrderIconDone(s32 fighterIndex);  // sets fighterIndex's turn-order icon to its idle frame
extern void ToggleFaintedAllyCursor(void);
// Does nothing; called with the fighter whose turn just ended.
// Does nothing; called with the fighter whose turn just ended.
extern void EndFighterTurnStub(u8 fighterIndex);
extern void OpenFaintedAllyMenu(u8 fighterIndex);  // bMenuScreen 9

extern void IgnoreBattleMenuInput(u32 fighterType, BattleFighter *pFighter);  // does nothing; screens 0, 3 and 10
extern void ConfirmBattleTopMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmSpellChoiceMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmSpecialMoveMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmSpellTierMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmEnemyTargetMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmItemMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmAllyTargetMenu(u32 fighterType, BattleFighter *pFighter);
extern void ConfirmFaintedAllyMenu(u32 fighterType, BattleFighter *pFighter);
extern void CancelBattleTopMenu(u32 fighterType, BattleFighter *pFighter);  // does nothing
// Reopens the top menu on the row that opened the current screen (spell, special move or item).
extern void CancelToBattleTopMenu(u32 fighterType, BattleFighter *pFighter);
extern void CancelSpellTierMenu(u32 fighterType, BattleFighter *pFighter);  // back to the spell choice menu
extern void CancelEnemyTargetMenu(u32 fighterType, BattleFighter *pFighter);
extern void CancelAllyTargetMenu(u32 fighterType, BattleFighter *pFighter);
extern void CancelFaintedAllyMenu(u32 fighterType, BattleFighter *pFighter);  // reopens the top menu on row 1

extern u32 g_dwSelectedBattleMenuIcon;  // row whose icon SelectBattleMenuIcon enlarged
// The row of battle menu icons along the bottom of the screen, one Actor per menu row.
extern Actor *g_apBattleMenuIconActors[7];
// The 40x40 face beside the battle stats panel, of the fighter whose stats are drawn.
extern Actor *g_pStatsPortraitActor;
extern StatsPortraitPaletteLoad g_StatsPortraitPaletteLoad;
extern s32 g_anFaintedRosterIndices[4];
extern void ShowAllyStatsPortrait(u32 fighterType);
extern void ShowEnemyStatsPortrait(u32 monsterId);
// g_aBattleScanlineEffects with entry 1 moved to FightState.bWallEndLine.
extern ScanlineEffectEntry g_aBattleScanlineEffectBuffer[4];
// Clears OBJ palettes 0-3 in FightState.awPalette, then has HandleBattleVBlank copy 4 palettes
// from palette to bank two frames later. Ignored while palette is already queued.
extern void QueueStatsPortraitPalette(u32 bank, const ObjPalette *palette);
extern void ClearStatsPortraitPalette(void);
// Item id the ally target menu consumes once a potion's target is chosen.
extern u32 g_dwBattleItemToConsume;

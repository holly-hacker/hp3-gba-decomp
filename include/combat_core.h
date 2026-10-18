#pragma once

#include "actor.h"

extern void InitBattleBackground_candidate(void);
extern void SetupBattleRoster(void);
extern void RestoreFighterActors_candidate(void);
extern void ResumeBattleAfterSubmode_candidate(void);
extern void TickBattleTurnStateMachine(void);
extern void SetFighterTurnOrderIconActive(s32 fighterIndex);  // sets fighterIndex's turn-order icon to its highlighted frame, bringing it to the front
extern u8 RollFighterParalysisEscape(u8 fighterIndex);  // 0 = acts normally, 1 = still paralyzed, 3 = escape roll succeeded
extern void TrackSpellFamiliarity(u8 fighterType, u8 spellId, u8 spellLevel, u16 *pHp);  // 0x08010008
extern void DispatchPendingAction(s32 fighterIndex);

extern const ActorAssetRecord g_BattleEffect001Asset;  // 0x0804D7F8, passed to sub_08030A1C by InitBattleBackground_candidate

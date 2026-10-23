#pragma once

#include "actor.h"
#include "save.h"

extern void InitBattleDisplay(void);
extern void SetupBattleRoster(void);
extern void RestoreFighterActors(void);
extern void StartOrResumeBattle(void);
extern void TickBattleTurnStateMachine(void);
extern void SetFighterTurnOrderIconActive(s32 fighterIndex);  // sets fighterIndex's turn-order icon to its highlighted frame, bringing it to the front
extern u8 RollFighterParalysisEscape(u8 fighterIndex);  // 0 = acts normally, 1 = still paralyzed, 3 = escape roll succeeded
extern void TrackSpellFamiliarity(u32 fighterType, u32 spellId, s32 spellLevel, SavedFighterStats *pStats);
extern void DispatchPendingAction(s32 fighterIndex);

extern const ActorAssetRecord g_BattleEffect001Asset;  // 0x0804D7F8, passed to LoadParticleGfx by InitBattleDisplay

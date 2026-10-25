#pragma once

#include "types.h"
#include "actor.h"
#include "math.h"
#include "minigame_high_score.h"

extern u32 g_dwDementorMinigameForceOverworldExit;  // 0x03002E10; set by StartMinigame

// Harry vs Dementors, game mode 0x33 (DementorMinigame). Four Dementors, one per
// direction (0 right, 1 down, 2 left, 3 up), fly toward Harry at the center; a
// spell cast in a Dementor's direction drives it back.

// adwDementorStates values.
typedef enum {
    DementorIdle = 0,         // waiting at its start position
    DementorApproaching = 1,  // flying toward Harry
    DementorRetreating = 2,   // driven back to its start position
} DementorState;

// The mode's screen state at 0x03002E18, driven by g_GameModeStackContext.dwModeState.
typedef struct {
    Actor *apDementors[4];   // 0x00; indexed by direction
    Actor *pHarry;           // 0x10
    Actor *pCursorActor;     // 0x14; released on exit when set
    Actor *pSpellActor;      // 0x18; hidden when dwSpellHideTimer expires
    Actor *pDamageActor;     // 0x1C; shown when a Dementor reaches Harry
    MinigameTextPanel *pScorePanel;   // 0x20; freed on exit
    MinigameTextPanel *pLivesPanel;   // 0x24; freed on exit
    MinigameTextPanel *pMissesPanel;  // 0x28; freed on exit
    s32 dwHarryDirection;    // 0x2C; direction of the last cast
    u32 adwDementorStates[4];  // 0x30; DementorState, indexed by direction
    s32 dwLastDementor;      // 0x40; direction of the last Dementor launched, -1 before the first
    s32 dwScore;             // 0x44
    u32 dwStartDelay;        // 0x48; 1 until dwModeTimer first runs out
    u8 bLives;               // 0x4C
    s32 dwRepelled;          // 0x50; Dementors driven back so far
    u8 bMisses;              // 0x54; spells cast at no Dementor, a life lost every third
    u32 dwPhase;             // 0x58; up to dwPhase + 1 Dementors approach at once
    u32 dwSpellHideTimer;    // 0x5C; frames until pSpellActor is hidden
    u32 dwSpellTimer;        // 0x60; frames until ShowDementorMinigameSpell(dwSpellDirection)
    u32 dwSpellDirection;    // 0x64
    u32 dwDamageHideTimer;   // 0x68; frames until pDamageActor is hidden
} DementorMinigameState;

extern DementorMinigameState g_DementorMinigame;  // 0x03002E18

// Sprite resources. Each record is followed by its palette, which the code
// passes to SpawnActor directly instead.
typedef struct {
    ActorAssetRecord asset;
    const ObjPalette *pPalette;
} DementorMinigameSprite;

extern const DementorMinigameSprite g_DementorMinigameDementorSprite;
extern const DementorMinigameSprite g_DementorMinigameHarrySprite;
extern const DementorMinigameSprite g_DementorMinigameHarryCastSprite;
extern const DementorMinigameSprite g_DementorMinigameSpellSprite;
extern const DementorMinigameSprite g_DementorMinigameDamageSprite;

extern const u32 g_dwDementorMinigameBg0Control;
extern const u32 g_dwDementorMinigameBg3Control;

extern const IntPoint g_aDementorStartPositions[4];

// Animation command streams by direction; see actor_anim.h.
extern const u8 g_aabDementorStopAnimData[4][2];
extern const u8 g_aabDementorFlyAnimData[4][18];
extern const u8 g_aabDementorMinigameHarryCastAnimData[4][14];
extern const u8 g_aabDementorMinigameSpellAnimData[4][6];

extern const IntPoint g_aDementorMinigameSpellPositions[4];

extern const u8 g_abDementorMinigameDamageAnimData[34];

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    DementorMinigameStatePlaying = 0,
    DementorMinigameStateResultsMenu = 1,
    DementorMinigameStatePauseMenu = 2,
} DementorMinigameMode;

extern void InitializeDementorMinigame(void);
extern void UpdateDementorMinigame(void);
extern void ExitDementorMinigame(void);

extern void SpawnDementorMinigameActors(void);
extern void ShowDementorMinigameResultsMenu(void);
extern void ShowDementorMinigamePauseMenu(void);
extern void UpdateDementorMinigameLaunches(void);
extern s32 GetDementorMinigameDementorVelocity(u32 positive, s32 multiplier);
extern void UpdateDementorMinigameDementors(void);
extern void StartDementorMinigameDementorRetreat(s32 direction);
extern void CastDementorMinigameSpell(s32 direction);
extern void ResetDementorMinigameActors(void);
extern void ShowDementorMinigameSpell(s32 direction);
extern void LeaveDementorMinigame(void);
extern void RepelDementorMinigameDementor(s32 direction);
extern void LaunchRandomDementorMinigameDementor(void);
extern void DrawDementorMinigameLives(void);
extern void DrawDementorMinigameScore(void);
extern void ResumeDementorMinigame(void);
extern void StartDementorMinigameDementorApproach(s32 direction);
extern void MoveDementorMinigameMenuCursor(Actor *pCursor);
extern void DrawDementorMinigameMisses(void);
extern void ShowDementorMinigameDamage(void);
extern void AddDementorMinigameScore(s32 points);
extern s32 GetDementorMinigameRoundPoints(void);
extern void LaunchDementorMinigameDementor(s32 direction);

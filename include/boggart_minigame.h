#pragma once

#include "types.h"
#include "actor.h"
#include "math.h"
#include "palette.h"
#include "minigame_high_score.h"

extern u32 g_dwBoggartMinigameScriptFlag_candidate;  // 0x03002040; set by StartMinigame

// Riddikulus Boggart Challenge, game mode 0x2F (BoggartMinigame).

// The mode's screen state at 0x03002048, driven by g_GameModeStackContext.dwModeState.
typedef struct {
    Actor *apStudents[4];  // 0x00; indexed by direction 0-3
    Actor *pActor;         // 0x10; the Boggart
    Actor *pCastEffectActor;  // 0x14; spark spawned on a successful cast
    Actor *pCursorActor;   // 0x18; released on exit when set
    MinigameTextPanel *pScorePanel;   // 0x1C; freed on exit
    MinigameTextPanel *pLivesPanel;   // 0x20; freed on exit
    s32 dwBoggartDirection;  // 0x24; -1 before the first round
    u32 dwChosenDirection;   // 0x28; direction the player cast
    s32 dwScore;             // 0x2C; compared against the saved high score
    s32 dwCountdown;         // 0x30; frames until the current state advances
    u8 bLives;               // 0x34
    u8 bRound;               // 0x35
    u8 abUnmapped_36[2];
    u32 dwExitToMenu;        // 0x38; 1 requests a return to the minigame menu
} BoggartMinigameState;

extern BoggartMinigameState g_BoggartMinigame;  // 0x03002048

// Sprite resources, indexed by direction. The form and form palette tables have
// a fifth entry for the form the Boggart takes once the charm lands.
extern const ActorAssetRecord g_aBoggartStudentAssets[4];          // US 0x0804C0AC
extern const ObjPalette *const g_apBoggartStudentPalettes[4];      // US 0x0804C0EC
extern const ActorAssetRecord g_aBoggartCastEffectAssets[4];       // US 0x0804C0FC
extern const ObjPalette *const g_apBoggartCastEffectPalettes[4];   // US 0x0804C13C
extern const ActorAssetRecord g_aBoggartFormAssets[5];             // US 0x0804C14C
extern const ObjPalette *const g_apBoggartFormPalettes[5];         // US 0x0804C19C

extern const u32 g_dwBoggartMinigameBg0Control;  // US 0x0804C1B0
extern const u32 g_dwBoggartMinigameBg3Control;  // US 0x0804C1B4

extern const IntPoint g_aBoggartStudentPositions[4];  // US 0x0804C1B8

// Animation command streams; see actor_anim.h.
extern const u8 g_abBoggartStudentCastAnimData[14];  // US 0x0804C1D8
extern const u8 g_abBoggartCastEffectAnimData[12];   // US 0x0804C1E6
extern const u8 g_abBoggartStopAnimData[2];          // US 0x0804C1F2
extern const u8 g_aabBoggartWalkAnimData[4][30];     // US 0x0804C1F4
extern const u8 g_aabBoggartHitAnimData[4][6];       // US 0x0804C26C

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    BoggartMinigameStateIntro = 0,
    BoggartMinigameStateAwaitInput = 1,
    BoggartMinigameStateInput = 2,
    BoggartMinigameStateResolve = 3,
    BoggartMinigameStateRoundEnd = 4,
    BoggartMinigameStateNextRound = 5,
    BoggartMinigameStateResultsMenu = 6,
    BoggartMinigameStatePauseMenu = 7,
} BoggartMinigameMode;

extern void InitializeBoggartMinigame(void);
extern void UpdateBoggartMinigame(void);
extern void ExitBoggartMinigame(void);

extern void SpawnBoggartMinigameActors(void);
extern void StartBoggartMinigameBoggartMotion(void);
extern u32 CheckBoggartMinigameBoggartReachedStudent(void);
extern void ResolveBoggartMinigameCast(void);
extern void HandleBoggartMinigameMiss(u32 playSound);
extern void HandleBoggartMinigameHit(void);
extern s32 GetBoggartMinigameBoggartVelocity(u32 forward);
extern s32 GetBoggartMinigameRoundPoints(void);
extern void AddBoggartMinigameScore(s32 points);
extern void ShowBoggartMinigameResultsMenu(void);
extern void ShowBoggartMinigamePauseMenu(void);
extern void StartBoggartMinigameCast(u32 direction);
extern void DrawBoggartMinigameScore(void);
extern void DrawBoggartMinigameLives(void);
extern void SpawnBoggartMinigameBoggart(void);
extern void ClearBoggartMinigameMessage(void);
extern void ResetBoggartMinigameActors(void);
extern u32 HasBoggartMinigameBoggartReturnedToCenter(void);
extern void MoveBoggartMinigameMenuCursor(Actor *pCursor);
extern void ResumeBoggartMinigame(void);
extern void LeaveBoggartMinigame(void);

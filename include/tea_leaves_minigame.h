#pragma once

#include "types.h"
#include "char_block.h"
#include "actor.h"

// Tea Leaf Divination, game mode 0x1C (DivinationTeaMinigame).

#define DIVINATION_TEA_LEAF_COUNT 16

// One tea leaf actor. Its affine scale words are fixed-point with 8
// fractional bits; wAngle is a 16-bit angle advanced every frame.
typedef struct {
    Actor *pActor;      // 0x00
    ActorOrbit orbit;   // 0x04, copied into the actor at spawn
    s16 wScaleX;        // 0x10
    s16 wScaleY;        // 0x12
    s16 wAngle;         // 0x14
    s16 wOrbitSpeed;    // 0x16, the actor's orbit angle velocity, nudged toward dwSwirlSpeed
} DivinationTeaLeaf;    // 0x18

// The mode's screen state at 0x03005B28, driven by g_GameModeStackContext.dwModeState.
typedef struct {
    DivinationTeaLeaf aLeaves[DIVINATION_TEA_LEAF_COUNT];  // 0x000
    Actor *apCupActors[4];   // 0x180; switched to a new animation when B is pressed
    Actor *apFadeActors[8];  // 0x190; text frame sprites, semi-transparent until the fade-in ends
    s32 nBlendEvb;             // 0x1B0
    s32 nBlendEva;             // 0x1B4
    u32 dwFadeStep;            // 0x1B8; 0..0x10, advanced by 2 per frame while fading
    u32 dwFrame;               // 0x1BC; frames since the mode started
    u32 dwStopped;             // 0x1C0; set once B has been pressed
    u32 dwSettled;             // 0x1C4; set when the cross-fade after B ends
    const u8 *pFortuneText;    // 0x1C8; dialog text 0xA5F + random 0..0x5A
    u32 dwFortuneTextCursor;   // 0x1CC; PrintTextBox result for pFortuneText
    u32 dwSwirlSpeed;          // 0x1D0; BG2 rotation step, 0x40..0xFFF
    u32 dwLastStirFrame;       // 0x1D4; dwFrame at the last A press
    u32 dwPaused;              // 0x1D8; the pause menu is open
    Actor *pCursorActor;     // 0x1DC; pause menu cursor
} DivinationTeaState;          // 0x1E0

extern DivinationTeaState g_DivinationTea;  // 0x03005B28

// BG control words for BG2, BG0 and BG1, and the sprites and cup animation.
extern const u8 g_DivinationTeaCupAnimData[68];                // 0x0806BB00
extern const u32 g_dwDivinationTeaBg2Control;                  // 0x0806BB44
extern const u32 g_dwDivinationTeaBg0Control;                  // 0x0806BB48
extern const u32 g_dwDivinationTeaBg1Control;                  // 0x0806BB4C
extern const ActorGfxRecord g_DivinationTeaLeafSprite;        // 0x0806BB50
extern const ActorGfxRecord g_DivinationTeaCupSprite;         // 0x0806BB58
extern const ActorAssetRecord g_DivinationTeaTextFrameAsset;  // 0x0806BB60, eight spawned by StartDivinationTeaFortune
extern const BgTileAnimation64 g_DivinationTeaTable;  // 0x0806BB70

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    DivinationTeaStateIntro = 0,
    DivinationTeaStateFadeIn = 1,
    DivinationTeaStateReveal = 2,
    DivinationTeaStateFadeText = 3,
    DivinationTeaStateShowFortune = 4,
} DivinationTeaMode;

void InitializeDivinationTeaMinigame(void);
void UpdateDivinationTeaMinigame(void);
void SpawnDivinationTeaActors(void);
void SettleDivinationTeaLeaves(void);
void StartDivinationTeaFortune(void);
void SlowDivinationTeaLeaves(void);
void UpdateDivinationTeaLeafSpeeds(void);
void ShowDivinationTeaPauseMenu(void);
void ExitDivinationTeaMinigame(void);
void SetDivinationTeaSwirlSpeed(u32 speed);
void UpdateDivinationTeaPauseMenu(void);
void MoveDivinationTeaMenuCursor(Actor *pCursor);
void ResumeDivinationTeaMinigame(void);

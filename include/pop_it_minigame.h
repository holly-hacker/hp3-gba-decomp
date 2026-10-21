#pragma once

#include "types.h"
#include "actor.h"

// Wizard Cracker Pop-it, game mode 0x1B (WizardCrackerPopItMinigame).

#define WIZARD_CRACKER_POP_IT_COLUMNS 9
#define WIZARD_CRACKER_POP_IT_ROWS     6
#define WIZARD_CRACKER_POP_IT_KINDS    5

// Actor.wCharacterId_candidate of a cracker. Named after the sprites' shapes.
typedef enum {
    WizardCrackerPopItKindWrapped = 0,
    WizardCrackerPopItKindTriangle = 1,
    WizardCrackerPopItKindOval = 2,
    WizardCrackerPopItKindDumbbell = 3,
    WizardCrackerPopItKindSweet = 4,
} WizardCrackerPopItKind;

// wActorType values of the minigame's actors; see RoomActorType in actor.h.
typedef enum {
    WizardCrackerPopItActorType_Cracker = 2,  // SpawnWizardCrackerPopItCracker
} WizardCrackerPopItActorType;

// A cell byte: id, the kind + 1, in both nibbles.
#define WIZARD_CRACKER_POP_IT_CELL(id) ((id) + ((id) << 4))

// One cracker kind's idle animation state; see TickWizardCrackerPopItKinds.
typedef struct {
    s32 nTimer;             // 0x00, ticks until the next idle animation change
    u32 dwVariant;          // 0x04, idle animation stream; see SetWizardCrackerPopItCrackerAnim
    u32 dwCount;            // 0x08, crackers of this kind dealt
    u32 dwPendingVariant;   // 0x0C, variant to switch to when nTimer runs out; 0xFF none
    s32 nUnk10;             // 0x10, 2-6 for a dealt kind, else -1; never read
} WizardCrackerPopItKindState;  // 0x14

// Allocated by InitializeWizardCrackerPopItMinigame, freed by
// ExitWizardCrackerPopItMinigame. The board is 9 columns of up to 6 crackers,
// 24 pixels apart, stacked from row 0 at the top; a cracker's
// Actor.wActionVariant is its cell, row * 9 + column.
// A cell byte holds the cracker kind + 1 (0 empty) in both nibbles; the
// group flood fill clears the high nibble of each cell it selects.
typedef struct {
    Actor *pCursor;         // 0x000
    Actor *apCrackers[WIZARD_CRACKER_POP_IT_COLUMNS * WIZARD_CRACKER_POP_IT_ROWS];
                            // 0x004, by dealt cell; NULL once popped
    WizardCrackerPopItKindState aKinds[WIZARD_CRACKER_POP_IT_KINDS];  // 0x0DC
    s8 abColumnHeights[WIZARD_CRACKER_POP_IT_COLUMNS];           // 0x140
    u8 aabCells[WIZARD_CRACKER_POP_IT_COLUMNS][WIZARD_CRACKER_POP_IT_ROWS];  // 0x149
    u8 pad_17F;
    u8 bBlendStep;          // 0x180, 0-31 selection blend pulse
    u8 bSettleTimer;        // 0x181, ticks until the next row settles
    u8 bSettleRow;          // 0x182, rows 0-5 rise into gaps, 6 closes columns, 7 done
    u8 abColumnGaps[WIZARD_CRACKER_POP_IT_COLUMNS];  // 0x183, empty cells above bSettleRow
    u8 bLandSoundId;        // 0x18C, 0xAA-0xB1, rising with each cracker that lands
    s32 nCursorColumn;      // 0x190
    s32 nCursorRow;         // 0x194
    s32 nColumnCount;       // 0x198, columns still holding crackers
    u32 dwSelectedCount;    // 0x19C, crackers in the selected group
    u32 dwScore;            // 0x1A0, compared against the saved high score
    u32 dwPopBonus;         // 0x1A4, points for the next pop; grows within a group
    s32 nFrameCounter;      // 0x1A8
} WizardCrackerPopItState;  // 0x1AC

extern WizardCrackerPopItState *g_pWizardCrackerPopIt;  // 0x03005230

// Set by the StartMinigame room script opcode.
// While nonzero, ExitWizardCrackerPopItMinigame sets the pending mode's
// arg1 to 3 and arg3 to 0xFF. The name is provisional.
extern u32 g_dwWizardCrackerPopItForceOverworldExit;  // 0x03005228

// nFrameCounter when the selection blend last reached a full step, holding it
// for 24 frames; -1 while pulsing.
extern s32 g_nWizardCrackerPopItBlendHoldFrame;  // 0x0300522C

// One cracker kind's palette, loaded into two OBJ palette slots. The selected
// slots are pulsed by StartWizardCrackerPopItPaletteEffects.
typedef struct {
    const void *pPalette;  // 0x00
    u8 bIdleSlot;          // 0x04
    u8 bSelectedSlot;      // 0x05
    u8 abPad_6[2];
} WizardCrackerPopItPaletteEntry;

extern const WizardCrackerPopItPaletteEntry g_aWizardCrackerPopItPalettes[WIZARD_CRACKER_POP_IT_KINDS];  // 0x08068D14

extern const u32 g_dwWizardCrackerPopItBg1Control;  // 0x08068D04
extern const u32 g_dwWizardCrackerPopItBg2Control;  // 0x08068D08
extern const u32 g_dwWizardCrackerPopItBg0Control;  // 0x08068D0C
extern const u32 g_dwWizardCrackerPopItBg3Control;  // 0x08068D10

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    WizardCrackerPopItStateSelect = 0,
    WizardCrackerPopItStatePopping = 1,
    WizardCrackerPopItStateSettling = 2,
    WizardCrackerPopItStatePauseMenu = 3,
    WizardCrackerPopItStateResultsMenu = 4,
    WizardCrackerPopItStateFadeIn = 5,
    WizardCrackerPopItStateRoundWon = 6,
    WizardCrackerPopItStateRoundLost = 7,
} WizardCrackerPopItMode;

extern void InitializeWizardCrackerPopItMinigame(void);
extern void UpdateWizardCrackerPopItMinigame(void);
extern void ExitWizardCrackerPopItMinigame(void);

// Cracker sprites and animations, by WizardCrackerPopItKind. The wrapped
// cracker pops within its own sprite; the others switch to a pop sprite from
// g_aWizardCrackerPopItPopAssets, whose wrapped entry is empty.
extern const ActorAssetRecord g_aWizardCrackerPopItPopAssets[WIZARD_CRACKER_POP_IT_KINDS];  // 0x08068D3C
extern const ActorAssetRecord g_aWizardCrackerPopItCrackerAssets[WIZARD_CRACKER_POP_IT_KINDS];  // 0x08068D8C
extern const u8 g_aWizardCrackerPopItSweetAnims[2][40];  // 0x08068DDC
extern const u8 g_aWizardCrackerPopItDumbbellAnims[2][18];  // 0x08068E2C
extern const u8 g_aWizardCrackerPopItTriangleAnims[2][38];  // 0x08068E50
extern const u8 g_aWizardCrackerPopItOvalAnims[3][22];  // 0x08068E9C
// Variants 1 and 3 are the short turns into 2 and 0.
extern const u8 g_aWizardCrackerPopItWrappedAnims[4][20];  // 0x08068EDE
extern const u8 g_aWizardCrackerPopItPopAnims[WIZARD_CRACKER_POP_IT_KINDS - 1][48];  // 0x08068F2E, from the triangle
extern const u8 g_aWizardCrackerPopItWrappedPopAnims[2][36];  // 0x08068FEE, by variant / 2

extern void InitializeWizardCrackerPopItMinigame(void);
extern void UpdateWizardCrackerPopItMinigame(void);
extern void ExitWizardCrackerPopItMinigame(void);

extern void ClampWizardCrackerPopItCursor(void);
extern void AddWizardCrackerPopItClearBonus(void);
extern u32 HasWizardCrackerPopItMoves(void);
extern void StartWizardCrackerPopItRound(void);
extern void RebuildWizardCrackerPopItGrid(void);
extern void CloseWizardCrackerPopItEmptyColumns(void);
extern u32 SettleWizardCrackerPopItBoard(void);
extern void HandleWizardCrackerPopItCursorInput(void);
extern void TickWizardCrackerPopItCracker(Actor *pCracker);
extern void PopWizardCrackerPopItSelection(void);
extern void TickWizardCrackerPopItSelectionBlend(void);
extern void ClearWizardCrackerPopItSelection(void);
extern void SelectWizardCrackerPopItCracker(s32 column, s32 row, u8 order);
extern void FloodSelectWizardCrackerPopItGroup(s32 column, s32 row, u8 kind, u8 order);
extern void FillWizardCrackerPopItBoard(s32 kindCount);
extern void SetWizardCrackerPopItCrackerAnim(Actor *pCracker, u32 kind);
extern void TickWizardCrackerPopItKinds(void);
extern Actor *SpawnWizardCrackerPopItCracker(u32 kind, s32 x, s32 y);
extern void SetWizardCrackerPopItCrackerPopAnim(Actor *pCracker);
extern void AnimateWizardCrackerPopItKind(u32 kind, u32 animCounter);
extern void SetWizardCrackerPopItKindVariant(u32 kind, u32 variant, s32 timer);
extern void TickWizardCrackerPopItCursor(Actor *pCursor);
extern void SelectWizardCrackerPopItGroup(s32 column, s32 row);
extern u32 AreWizardCrackerPopItCrackersIdle(void);
extern void ResetWizardCrackerPopItSettle(void);
extern void DrawWizardCrackerPopItScore(void);
extern void DrawWizardCrackerPopItPauseMenu(void);
extern u32 IsWizardCrackerPopItBoardClear(void);
extern void DrawWizardCrackerPopItResultsMenu(void);
extern void StartWizardCrackerPopItPaletteEffects(void);
extern void QuitWizardCrackerPopItMinigame(void);

#pragma once

#include "types.h"
#include "object.h"

// Wizard Cracker Pop-it, game mode 0x1B (WizardCrackerPopItMinigame).

// Allocated by InitializeWizardCrackerPopItMinigame, freed by
// ExitWizardCrackerPopItMinigame.
typedef struct {
    Object *pObject0;         // 0x00; released on exit
    u8 abUnmapped_4[0x17C];
    u8 bUnk180;
    u8 abUnmapped_181[0xB];
    u8 bUnk18C;               // 0x18C; set to 0xAA when a round starts
    u8 abUnmapped_18D[3];
    u32 dwUnk190;
    u32 dwUnk194;
    u8 abUnmapped_198[4];
    u32 dwUnk19C;             // 0x19C; A only starts a round while nonzero
    u32 dwScore;              // 0x1A0; compared against the saved high score
    u32 dwUnk1A4;
    u32 dwUnk1A8;
} WizardCrackerPopItState;    // 0x1AC

extern WizardCrackerPopItState *g_pWizardCrackerPopIt;  // 0x03005230

// Set by the StartMinigame room script opcode (docs/formats/room_scripts.md).
// While nonzero, ExitWizardCrackerPopItMinigame sets the pending mode's
// arg1 to 3 and arg3 to 0xFF. The name is provisional.
extern u32 g_dwWizardCrackerPopItForceOverworldExit;  // 0x03005228

// One entry per palette-fade slot pair; the table is the 5-entry list at
// g_aWizardCrackerPopItPalettes, walked on init and exit.
typedef struct {
    const void *pPalette;  // 0x00
    u8 bSlotA;             // 0x04
    u8 bSlotB;             // 0x05
    u8 abPad_6[2];
} WizardCrackerPopItPaletteEntry;

extern const WizardCrackerPopItPaletteEntry g_aWizardCrackerPopItPalettes[5];  // 0x08068D14

extern const u32 g_dwWizardCrackerPopItBg1Control;  // 0x08068D04
extern const u32 g_dwWizardCrackerPopItBg2Control;  // 0x08068D08
extern const u32 g_dwWizardCrackerPopItBg0Control;  // 0x08068D0C
extern const u32 g_dwWizardCrackerPopItBg3Control;  // 0x08068D10
extern const u8 g_WizardCrackerPopItBg0Graphic[];   // 0x08D7FF44
extern const u8 g_WizardCrackerPopItBg1Graphic[];   // 0x08D7E528
extern const u8 g_WizardCrackerPopItBg2Graphic[];   // 0x08D8CDD4

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    WizardCrackerPopItStateWaitStart = 0,
    WizardCrackerPopItStateRoundSetup = 1,
    WizardCrackerPopItStatePlaying = 2,
    WizardCrackerPopItStatePauseMenu = 3,
    WizardCrackerPopItStateResultsMenu = 4,
    WizardCrackerPopItStateFadeIn = 5,
    WizardCrackerPopItStateRoundWon = 6,
    WizardCrackerPopItStateRoundLost = 7,
} WizardCrackerPopItMode;

extern void *sub_080077C8(u32 bg, const void *pResource, u32 tileOffset, u32 palBank, u32 x, u32 y);
extern void sub_08032894(void);
extern void sub_080328FC(void);
extern u32 sub_0803296C(void);
extern void sub_08032AA8(void);
extern void sub_08032B88(void);
extern u32 sub_08032CFC(void);
extern void sub_08032E5C(void);
extern void sub_080330C8(void);
extern void sub_080331D4(void);
extern void sub_08033710(void);
extern void sub_08033B28(u32 arg0, u32 arg1);
extern u32 sub_08033B74(void);
extern void sub_08033BE4(void);
extern void sub_08033C30(void);
extern u32 sub_08033CA0(void);
extern void sub_08033CE0(void);
extern void sub_08033D34(void);
extern void sub_08033D6C(void);

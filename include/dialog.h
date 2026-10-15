#pragma once

#include "types.h"
#include "actor.h"
#include "graphics/scanline_effects.h"

// Dialog box state at 0x03002E88; only the fields room scripts touch and the lifetime
// functions use are named.
typedef struct DialogState {
    u32 dwState;                // 0x00, 0 = no box, 1 = open (InitializeDialog), 2 = closed by
                                //       ExitDialog; the next vblank's RestoreBgAboveDialogBox resets 2 to 0
    const u8 *pText;            // 0x04, text still to be drawn; ShowDialogLine sets it, 0 byte = end
    const u8 *pLineStart;       // 0x08, start of the line being revealed
    u16 wBlockId;               // 0x0C, g_aDialogBlocks index, set by ShowRoomDialogBox_candidate
    u16 wLineIndex;             // 0x0E, line of the block being shown, cleared by InitializeDialog
    u16 wRevealCount;           // 0x10, characters of the current line revealed so far
    u16 wTextHeightLeft;        // 0x12, pixels left below the last drawn line
    u16 wTileCursor;            // 0x14, next free text tile
    u16 wRevealStep;            // 0x16, added to wRevealCount per StepDialogTextReveal; defaults to 1
    u8 bTextAlign;              // 0x18, text drawers' align argument; the text starts at x 0x40 + 56 * this
    u8 bRevealText;             // 0x19, nonzero reveals text gradually, 0 draws each page at once
    u8 bTextY;                  // 0x1A, pixel row of the next text line
    u8 bPhase;                  // 0x1B, DialogPhase
    u8 bArg1C;     // 0x1C, forwarded from room-script dialog opcodes
    u8 bArg1D;     // 0x1D
} DialogState;
extern DialogState g_DialogState_candidate;

// Destination for expanding text macros (@1, @2, ...) into a dialog string
// before it is drawn (ExpandTextMacros); allocated once by InitDialogBox.
#define DIALOG_MACRO_EXPAND_BUFFER_SIZE 0x400
extern u8 *g_pDialogMacroExpandBuffer;

// DialogState.bPhase, stepped by UpdateDialogBox.
typedef enum {
    DialogPhaseText = 0,      // text is being shown
    DialogPhaseTextStart = 1, // same, but the first text of the box
    DialogPhaseSlideUp = 2,   // the box rises into place
    DialogPhaseSlideDown = 3, // the box drops out of view
    DialogPhaseDone = 4,      // pops the dialog mode
} DialogPhase;

// Vertical position of the dialog box panel while it is hidden and when fully shown.
#define DIALOG_BOX_HIDDEN_Y 0x9F
#define DIALOG_BOX_SHOWN_Y 0x7B

// Text area of the box: its top edge in pixels below the box's tile row, and its height.
#ifdef VERSION_JP
#define DIALOG_TEXT_TOP 12
#define DIALOG_TEXT_HEIGHT 28
#else
#define DIALOG_TEXT_TOP 8
#define DIALOG_TEXT_HEIGHT 32
#endif
#define DIALOG_TEXT_MAX_WIDTH 169
#define DIALOG_TEXT_FIRST_TILE 0x248
#define DIALOG_BOX_FIRST_TILE 0x210

// Room script dialog blocks: each shows its lines' text ids in turn. A block with
// no lines still shows pTextIds[0].
typedef struct DialogBlock {
    const u32 *pTextIds;
    u8 bLineCount;
} DialogBlock;

// Per dialog text id: the speaker's g_aDialogPortraits index, and a number to
// fill macro @1 with (its absolute value) before the text is drawn.
typedef struct DialogTextInfo {
    u32 dwPortrait;
    const s16 *pMacroNumber;
} DialogTextInfo;

extern const u32 g_adwDialogBlockTextIds[979];              // US 0x0805BC04
extern const DialogBlock g_aDialogBlocks[666];               // US 0x0805CB50
extern const u8 g_abPartySlotDialogPortraits[4];             // US 0x0805E29C
extern const ActorAssetRecord g_aDialogPortraits[135];       // US 0x0805E2A0
extern const DialogTextInfo g_aDialogTextInfo[2767];         // US 0x08FAAF10

extern void InitializeDialog(void);
extern void UpdateDialogBox(void);
extern void ExitDialog(void);

extern Actor *AllocDialogPortraitActor(void);
extern void SetDialogPortrait(Actor *actor);
extern u32 DrawDialogTextLine(s32 charBudget);
extern void ShowDialogLine(void);
extern void AdvanceDialog(void);
extern void LoadDialogBoxGraphics(void);

extern u16 g_awSavedBgPalette0[16];         // 0x03002EAC, BG palette bank 0 saved while a box is up
extern u32 g_adwSavedBgPriority[2];         // 0x03002ED0, BG0/BG1 priority saved while a box is up
extern u32 g_dwDialogTextId;                // 0x03002ED8
extern u32 g_dwDialogPortrait;              // 0x03002EDC
extern const u16 *g_pDialogBoxTilemap;      // 0x03002EE0
extern Actor *g_pDialogPortraitActor;       // 0x03002EE4
extern u32 g_dwDialogBoxY;                  // 0x03002EE8
extern Actor *g_pDialogCursorActor;         // 0x03002EEC
extern u32 g_dwDialogPageFull;              // 0x03002EF0
extern u32 g_dwDialogBoxTileRow;            // 0x03002EF4
extern u16 g_awDialogBoxPalette[16];        // 0x03002EF8
extern const ScanlineEffectEntry g_aDialogScanlineEffects[1];  // 0x0805E28C

extern void sub_08024BD4(void);

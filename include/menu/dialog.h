#pragma once

#include "types.h"
#include "graphics/object.h"
#include "graphics/scanline_effects.h"

// Dialog box state at 0x03002E88; only the fields room scripts touch and the lifetime
// functions use are named.
typedef struct DialogState {
    u32 dwState;                // 0x00, 0 = no box, 1 = open (InitializeDialogue), 2 = closed by
                                //       ExitDialogue; the next vblank's sub_0801FBBC resets 2 to 0
    const u8 *pText;            // 0x04, text still to be drawn; sub_0801F968 sets it, 0 byte = end
    u8 pad_08[0x04];
    u16 wBlockId;               // 0x0C, set by ShowRoomDialogBox_candidate
    u16 wLineIndex;             // 0x0E, line of the block being shown, cleared by InitializeDialogue
    u8 pad_10[0x06];
    u16 wRevealStep_candidate;  // 0x16, added to the halfword at 0x10 per reveal step (sub_0801FD64); defaults to 1
    u8 bArg18;                  // 0x18, set by sub_0801FBA4
    u8 bArg19;                  // 0x19, set by sub_0801FBB0
    u8 pad_1A;
    u8 bPhase;                  // 0x1B, DialoguePhase
    u8 bArg1C;     // 0x1C, forwarded from room-script dialog opcodes
    u8 bArg1D;     // 0x1D
} DialogState;
extern DialogState g_DialogState_candidate;

// Destination for expanding text macros (@1, @2, ...) into a dialog string
// before it is drawn (ExpandTextMacros); allocated once by InitDialogBox.
#define DIALOG_MACRO_EXPAND_BUFFER_SIZE 0x400
extern u8 *g_pDialogMacroExpandBuffer;

extern void InitDialogBox(void);

// Dialog string id for a reward id (item, card or Sickles).
extern u32 GetRewardNameStringId_candidate(u32 rewardId);
// Sets the dialog block to show and pushes the dialog game mode.
extern void ShowRoomDialogBox_candidate(u32 blockId);

extern void sub_0801FBA4(u32 arg);  // stores a byte at DialogState + 0x18
extern void sub_0801FBB0(u32 arg);  // stores a byte at DialogState + 0x19

// DialogState.bPhase, stepped by UpdateDialogueBox.
typedef enum {
    DialoguePhaseText = 0,      // text is being shown
    DialoguePhaseTextStart = 1, // same, but the first text of the box
    DialoguePhaseSlideUp = 2,   // the box rises into place
    DialoguePhaseSlideDown = 3, // the box drops out of view
    DialoguePhaseDone = 4,      // pops the dialogue mode
} DialoguePhase;

// Vertical position of the dialog box panel while it is hidden and when fully shown.
#define DIALOG_BOX_HIDDEN_Y 0x9F
#define DIALOG_BOX_SHOWN_Y 0x7B

extern void InitializeDialogue(void);
extern void UpdateDialogueBox(void);
extern void ExitDialogue(void);

extern u16 g_awSavedBgPalette0[16];         // 0x03002EAC, BG palette bank 0 saved while a box is up
extern u32 g_adwSavedBgPriority[2];         // 0x03002ED0, BG0/BG1 priority saved while a box is up
extern u32 g_dwDialogTextId;                // 0x03002ED8
extern u32 g_dwDialogTextEntry;             // 0x03002EDC
extern void *g_pDialogBoxTilemap;           // 0x03002EE0
extern Object *g_pDialogBoxObject;          // 0x03002EE4
extern u32 g_dwDialogBoxY;                  // 0x03002EE8
extern Object *g_pDialogCursorObject;       // 0x03002EEC
extern u32 g_dwDialogTextActive;            // 0x03002EF0
extern u32 g_dwDialogBoxTileRow;            // 0x03002EF4
extern const ScanlineEffectEntry g_aDialogScanlineEffects[1];  // 0x0805E28C

extern void sub_0801FC58(u32 *pPayload0, u32 *pPayload1);  // scanline callback of the box panel
extern Object *sub_0801F7AC(void);  // allocates the box panel object
extern void sub_0801F968(void);
extern void sub_0801FA18(void);
extern void sub_0801FCFC(u32 arg);
extern void sub_0801FD2C(void);
extern void sub_0801FD64(void);
extern void sub_08024BD4(void);

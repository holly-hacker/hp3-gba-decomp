#pragma once

#include "types.h"

extern void InitDialogBox(void);

// Sets the dialog block to show and pushes the dialog game mode.
extern void ShowDialogBlock(u32 blockId);

extern void SetDialogTextAlign(u32 align);    // DialogState.bTextAlign
extern void SetDialogTextReveal(u32 reveal);  // DialogState.bRevealText
extern void SetDialogRevealStep(u32 step);    // DialogState.wRevealStep; unreferenced

// Vblank: while a box is up, restores BG palette bank 0 and the BG0/BG1 priorities that
// BeginDialogBoxPanelScanline swapped for the box, then finishes a close (dwState 2 -> 0).
extern void RestoreBgAboveDialogBox(void);

// Scanline callback at the box's top line: switches BG palette bank 0 to the box's palette,
// raises BG1 above BG0 and scrolls BG1 so the box's tile row starts at this line.
extern void BeginDialogBoxPanelScanline(u32 *pPayload0, u32 *pPayload1);

// The BG tile row the box is drawn at, from the camera's y; unreferenced (InitializeDialog
// computes it inline).
extern u32 GetDialogBoxTileRow(void);

// GetDialogText after filling macro @1 from g_aDialogTextInfo.
extern const u8 *GetDialogLineText(u32 textId);

extern void SetDialogCursorVisible(u32 visible);
extern void DrawDialogTextPage(void);    // draws the rest of the page at once
extern void StepDialogTextReveal(void);  // reveals wRevealStep more characters
extern void DialogBoxNop(void);          // empty; unreferenced

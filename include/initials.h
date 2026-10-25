#pragma once

#include "types.h"
#include "actor.h"

// High score name entry, game mode 0x1D (HighScoreNameEntryUnused). A 6x6 keypad
// of letters and digits plus a row holding the "Done" entry; nothing in the
// retail game pushes this mode.

extern void InitializeHighScoreNameEntryScreen(void);
extern void UpdateHighScoreNameEntry(void);
extern void ExitHighScoreNameEntry(void);

#define HIGH_SCORE_NAME_LENGTH 3

// Keypad rows and columns; the cursor sits at (dwRow, dwColumn).
#define HIGH_SCORE_KEYPAD_ROWS 6
#define HIGH_SCORE_KEYPAD_COLUMNS 6

typedef struct {
    Actor *pCursor;                              // 0x00; the menu cursor actor
    s32 dwRow;                                    // 0x04; keypad row, 6 is the "Done" row
    s32 dwColumn;                                 // 0x08; keypad column
    u8 abName[HIGH_SCORE_NAME_LENGTH + 1];        // 0x0C; entered characters, NUL-terminated
    u8 abCandidate[2];                            // 0x10; the character under the cursor, NUL-terminated
    s32 dwNameLength;                             // 0x14; characters entered so far
    u32 dwTileCursor;                             // 0x18; next free text tile
} HighScoreNameEntryState;                        // 0x1C

extern HighScoreNameEntryState g_HighScoreNameEntry;  // 0x030034D0

extern const u32 g_dwHighScoreNameEntryBg2Control;
extern const u32 g_dwHighScoreNameEntryBg3Control;
extern const u32 g_dwHighScoreNameEntryBg0Control;
extern const u8 g_abHighScoreNameEntryKeyTemplate[];
extern const u8 g_abHighScoreNameEntryDoneText[];

extern void DrawHighScoreNameEntryKeypad(void);
extern void DrawHighScoreNameEntryPreview(void);
extern void HighScoreNameEntryCursorTick(Actor *pActor);
extern void UpdateHighScoreNameEntrySelectedChar(void);
extern void ClearHighScoreNameEntryTail(void);

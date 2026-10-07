#pragma once

#include "types.h"
#include "graphics/object.h"

// High score name entry, game mode 0x1D (HighScoreNameEntryUnused). A 6x6 keypad
// of letters and digits plus a row holding the "Done" entry; nothing in the
// retail game pushes this mode.

#define HIGH_SCORE_NAME_LENGTH 3

// Keypad rows and columns; the cursor sits at (dwRow, dwColumn).
#define HIGH_SCORE_KEYPAD_ROWS 6
#define HIGH_SCORE_KEYPAD_COLUMNS 6

typedef struct {
    Object *pCursor;                              // 0x00; the menu cursor object
    s32 dwRow;                                    // 0x04; keypad row, 6 is the "Done" row
    s32 dwColumn;                                 // 0x08; keypad column
    u8 abName[HIGH_SCORE_NAME_LENGTH + 1];        // 0x0C; entered characters, NUL-terminated
    u8 abCandidate[2];                            // 0x10; the character under the cursor, NUL-terminated
    s32 dwNameLength;                             // 0x14; characters entered so far
    u32 dwTileCursor;                             // 0x18; next free text tile
} HighScoreNameEntryState;                        // 0x1C

extern HighScoreNameEntryState g_HighScoreNameEntry;  // 0x030034D0

extern const u32 g_dwHighScoreNameEntryBg2Control;  // 0x08060E64
extern const u32 g_dwHighScoreNameEntryBg3Control;  // 0x08060E68
extern const u32 g_dwHighScoreNameEntryBg0Control;  // 0x08060E6C
extern const u8 g_abHighScoreNameEntryKeyTemplate[];  // 0x08060E70
extern const u8 g_abHighScoreNameEntryDoneText[];     // 0x08060E74

extern void DrawHighScoreNameEntryKeypad(void);
extern void DrawHighScoreNameEntryPreview(void);
extern void HighScoreNameEntryCursorTick(Object *pObject);

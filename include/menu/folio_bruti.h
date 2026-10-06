#pragma once

#include "types.h"
#include "graphics/object.h"

extern const u32 g_dwFolioBrutiBg3Control;  // 0x08069568
extern const u32 g_dwFolioBrutiBg2Control;  // 0x0806956C
extern const u32 g_dwFolioBrutiBg1Control;  // 0x08069570

extern const u16 g_aFolioBrutiBlankObjPalette[16];  // 0x08069574

// The grid cursor and the spell-effectiveness dot.
extern const ObjectGfxRecord g_aFolioBrutiObjectGfx[2];  // 0x08069594
#define FOLIO_BRUTI_CURSOR_GFX    (&g_aFolioBrutiObjectGfx[0])
#define FOLIO_BRUTI_SPELL_DOT_GFX (&g_aFolioBrutiObjectGfx[1])

extern const u8 g_aFolioBrutiCursorAnim[];          // 0x080695A4
extern const u8 g_aFolioBrutiDotUnknownAnim[14];    // 0x080695CE
extern const u8 g_aFolioBrutiDotAnims[4][14];       // 0x080695DC

extern const u32 g_adwFolioBrutiMonsterScale[69];  // 0x0804FA88

// Folio Bruti screen state: the grid has 9 columns by 6 rows, the monster at (column, row) being
// MonsterTable[row * 9 + column]; the last cell is unused, so only the first 53 monsters show.
typedef struct {
    u32 dwUnk0;                // 0x00: cleared on entry, never read
    u32 dwDetailTileCursor;    // 0x04: first free text tile after the spell labels
    u32 dwHeadingTileCursor;   // 0x08: first free text tile after the heading
    u32 dwRow;                 // 0x0C
    u32 dwColumn;              // 0x10
    Object *pCursor;           // 0x14
    Object *pMonster;          // 0x18: the selected monster's sprite
    Object *apSpellDots[8];    // 0x1C: one marker per spell on the effectiveness bars
    void *pGridTilemap;        // 0x3C: tilemap of the grid background, whose tiles mark each monster's state
} FolioBrutiState;
extern FolioBrutiState g_FolioBrutiState;  // 0x03005300

extern u32 DrawFolioBrutiSpellLabels(u32 tileCursor);
extern void DrawFolioBrutiHeading(void);
extern void ClearMonsterDexNewFlags(void);
extern void DrawFolioBrutiGrid(void);
extern void DrawFolioBrutiMonsterPanel(void);
extern void DrawFolioBrutiMonsterText(void);

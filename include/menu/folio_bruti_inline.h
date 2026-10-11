#pragma once

#include "types.h"
#include "game/save.h"
#include "font.h"
#include "text.h"
#include "menu/folio_bruti.h"

// The ROM compiles these two routines into DrawFolioBrutiMonsterPanel and also keeps an
// out-of-line copy, as one translation unit with inline definitions would. The panel includes
// this header; the files that emit the out-of-line copies define the linkage macros as empty.
#ifndef FOLIO_BRUTI_SPELL_LABELS_LINKAGE
#define FOLIO_BRUTI_SPELL_LABELS_LINKAGE extern inline
#endif
#ifndef FOLIO_BRUTI_MONSTER_TEXT_LINKAGE
#define FOLIO_BRUTI_MONSTER_TEXT_LINKAGE extern inline
#endif

#ifdef VERSION_JP
#define SPELL_LABEL_FONT 0xB
#define SPELL_LABEL_COLOR 3
#else
#define SPELL_LABEL_FONT 9
#define SPELL_LABEL_COLOR 1
#endif

// Prints the eight spell names beside the effectiveness bars; returns the next free text tile.
FOLIO_BRUTI_SPELL_LABELS_LINKAGE u32 DrawFolioBrutiSpellLabels(u32 tileCursor)
{
    u32 spell;

    SelectTextFont(SPELL_LABEL_FONT, SPELL_LABEL_COLOR, -1);
    for (spell = 0; spell < 8; spell++)
        tileCursor = DrawString(tileCursor, 0x32, 0x58 + spell * 8, GetDialogText(0x498 + spell));

    return tileCursor;
}

// Prints the selected monster's name and description, once it has been analyzed.
FOLIO_BRUTI_MONSTER_TEXT_LINKAGE void DrawFolioBrutiMonsterText(void)
{
    u32 monster = g_FolioBrutiState.dwRow * 9 + g_FolioBrutiState.dwColumn;
    u32 tileCursor;

    if (g_saveStateBlock.abMonsterDocLevel[monster] > 2)
    {
        SelectTextFont(2, 0, -1);
        tileCursor = PrintTextBox(g_FolioBrutiState.dwDetailTileCursor, 0xB8, 0x54, 0x70,
                                  GetDialogText(monster + 0x4A2), 1);
        SelectTextFont(8, 0, -1);
        PrintTextBox(tileCursor, 0x7C, 0x68, 0x72, GetDialogText(monster + 0x4E6), 0);
    }
}

#pragma once

#include "types.h"
#include "game/save.h"
#include "menu/folio_universitas.h"

// The ROM compiles GetFolioUniversitasSelectedCombo and IsFolioUniversitasCardSeen into some of the
// screen's other routines and also keeps an out-of-line copy. Routines that inline them include
// this header; the files that emit the out-of-line copies define the linkage macros as empty.
#ifndef FOLIO_UNIVERSITAS_SELECTED_COMBO_LINKAGE
#define FOLIO_UNIVERSITAS_SELECTED_COMBO_LINKAGE extern inline
#endif

#ifndef FOLIO_UNIVERSITAS_CARD_SEEN_LINKAGE
#define FOLIO_UNIVERSITAS_CARD_SEEN_LINKAGE extern inline
#endif

FOLIO_UNIVERSITAS_CARD_SEEN_LINKAGE u32 IsFolioUniversitasCardSeen(u32 cardIndex)
{
    u32 byteIndex = cardIndex >> 3;
    u32 bit = cardIndex & 7;

    if ((g_saveStateBlock.abFolioUniversitasSeen[byteIndex] >> bit) & 1)
        return 1;
    return 0;
}

// Returns the first card of the combo the cursor is in.
FOLIO_UNIVERSITAS_SELECTED_COMBO_LINKAGE u32 GetFolioUniversitasSelectedCombo(void)
{
    u32 card = g_FolioUniversitasState.dwCategory * 10 + g_FolioUniversitasState.dwSlot;

    return card - g_FolioUniversitasState.dwSlot % 3;
}

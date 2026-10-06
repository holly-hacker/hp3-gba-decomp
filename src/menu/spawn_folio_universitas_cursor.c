#include "types.h"
#include "game/game_modes.h"
#include "gen/graphics/overworld.h"
#include "graphics/object.h"
#include "menu/folio_universitas.h"

void SpawnFolioUniversitasCursor(void)
{
    FolioUniversitasState *pState = &g_FolioUniversitasState;
    u32 column = pState->dwSlot;

    column += column / 3;
    pState->pCursor = SpawnObject(0, column * 8 + 0x78, pState->dwCategory * 8 + 0x20,
                                  (const ObjPalette *)gFolioBrutiSpellDotPalette);
    pState->pCursor->oam.priority = 0;

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == FolioUniversitasPickCombo)
        SetObjectAnimData(pState->pCursor, FOLIO_UNIVERSITAS_CURSOR_GFX, g_aFolioUniversitasBattleCursorAnim, 0);
    else
        SetObjectAnimData(pState->pCursor, FOLIO_UNIVERSITAS_CURSOR_GFX, g_aFolioUniversitasCursorAnim, 0);
}

#include "types.h"
#include "game/game_modes.h"
#include "gen/graphics/overworld.h"
#include "actor.h"
#include "menu/folio_universitas.h"

void SpawnFolioUniversitasCursor(void)
{
    FolioUniversitasState *pState = &g_FolioUniversitasState;
    u32 column = pState->dwSlot;

    column += column / 3;
    pState->pCursor = SpawnActor(0, column * 8 + 0x78, pState->dwCategory * 8 + 0x20,
                                  (const ObjPalette *)gFolioBrutiSpellDotPalette);
    pState->pCursor->oam.priority = 0;

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == FolioUniversitasPickCombo)
        SetActorAnimData(pState->pCursor, FOLIO_UNIVERSITAS_CURSOR_GFX, g_aFolioUniversitasBattleCursorAnim, 0);
    else
        SetActorAnimData(pState->pCursor, FOLIO_UNIVERSITAS_CURSOR_GFX, g_aFolioUniversitasCursorAnim, 0);
}

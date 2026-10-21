#include "types.h"
#include "actor.h"
#include "cursor.h"
#include "modes.h"
#include "palette.h"
#include "pop_it_minigame.h"

void StartWizardCrackerPopItRound(void)
{
    s32 i;
    Actor *pCursor;

    for (i = 0; i < ARRAY_COUNT(g_aWizardCrackerPopItPalettes); i++)
    {
        UnreserveObjPaletteSlot(g_aWizardCrackerPopItPalettes[i].bSelectedSlot);
        UnreserveObjPaletteSlot(g_aWizardCrackerPopItPalettes[i].bIdleSlot);
    }

    ReleaseMenuCursor(g_pWizardCrackerPopIt->pCursor);
    FreeAllActors(&g_ActiveActorListState.pHead);
    g_pWizardCrackerPopIt->dwScore = 0;
    g_pWizardCrackerPopIt->dwPopBonus = 0;
    g_pWizardCrackerPopIt->nCursorColumn = 0;
    g_pWizardCrackerPopIt->nCursorRow = 0;
    ClearObjPaletteSlots();

    for (i = 0; i < ARRAY_COUNT(g_aWizardCrackerPopItPalettes); i++)
    {
        ReserveObjPaletteSlot(g_aWizardCrackerPopItPalettes[i].bSelectedSlot);
        ReserveObjPaletteSlot(g_aWizardCrackerPopItPalettes[i].bIdleSlot);
    }

    pCursor = SpawnMenuCursorActor(4);
    g_pWizardCrackerPopIt->pCursor = pCursor;
    pCursor->pfnTick = TickWizardCrackerPopItCursor;
    SetActorPosition(pCursor, g_pWizardCrackerPopIt->nCursorColumn * 24 + 28,
                     g_pWizardCrackerPopIt->nCursorRow * 24 + 16);

    FillWizardCrackerPopItBoard(g_GameModeStackContext.dwCurrentGameModeArg3 + 3);
    ResetWizardCrackerPopItSettle();
    ClearWizardCrackerPopItSelection();
    SelectWizardCrackerPopItGroup(g_pWizardCrackerPopIt->nCursorColumn, g_pWizardCrackerPopIt->nCursorRow);
    DrawWizardCrackerPopItScore();
}

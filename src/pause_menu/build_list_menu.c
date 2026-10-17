#include "types.h"
#include "modes.h"
#include "pause_menu.h"
#include "actor.h"
#include "cursor.h"
#include "default_menu.h"

void BuildListMenu(const ListMenuDefinition *pDefinition)
{
    Actor *pActor;
    u32 row;

    g_ListMenuState.pDefinition = pDefinition;

    BeginMenuScreen(pDefinition->wTitleStringId, 4, 1);
    g_pMenuCursorActor->oam.objMode = 1;
    g_pMenuCursorActor->oam.hFlip = 1;
    g_pMenuCursorActor->pfnTick = ListMenuCursorTick_candidate;
    SetMenuCursorPosition(g_pMenuCursorActor,
                 g_ListMenuState.pDefinition->stride.x * g_GameModeStackContext.dwModeScratchB
                     + g_ListMenuState.pDefinition->base.x
                     + g_ListMenuState.pDefinition->cursorOffset.x,
                 g_ListMenuState.pDefinition->stride.y * g_GameModeStackContext.dwModeScratchB
                     + g_ListMenuState.pDefinition->base.y
                     + g_ListMenuState.pDefinition->cursorOffset.y);

    // TODO: codegen hack
    if (pDefinition->wEntryCount != 0)
    {
        for (row = 0; row < pDefinition->wEntryCount; row++)
            DrawListMenuRow(row);
    }

    for (row = 0; row < pDefinition->wRowActorCount; row++)
    {
        pActor = SpawnMenuIconActor(row, 0);
        pActor->dwFlags |= ActorFlagKeepPaletteSlot | ActorFlagHasAnimation;
        SetActorPosition(pActor,
                          pDefinition->stride.x * row + pDefinition->base.x
                              + pDefinition->rowActorOffset.x,
                          pDefinition->stride.y * row + pDefinition->base.y
                              + pDefinition->rowActorOffset.y);
        AttachActorPalette(pActor, pDefinition->pRowActors->pPalette);
        SetActorSprite(pActor, &pDefinition->pRowActors[row]);
    }
}

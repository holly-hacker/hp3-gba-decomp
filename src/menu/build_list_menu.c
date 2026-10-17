#include "types.h"
#include "modes.h"
#include "menu/menu.h"
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
                 g_ListMenuState.pDefinition->wStrideX * g_GameModeStackContext.dwModeScratchB
                     + g_ListMenuState.pDefinition->wBaseX
                     + g_ListMenuState.pDefinition->wCursorOffsetX,
                 g_ListMenuState.pDefinition->wStrideY * g_GameModeStackContext.dwModeScratchB
                     + g_ListMenuState.pDefinition->wBaseY
                     + g_ListMenuState.pDefinition->wCursorOffsetY);

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
                          pDefinition->wStrideX * row + pDefinition->wBaseX
                              + pDefinition->wRowActorOffsetX,
                          pDefinition->wStrideY * row + pDefinition->wBaseY
                              + pDefinition->wRowActorOffsetY);
        AttachActorPalette(pActor, pDefinition->pRowActors->pPalette);
        SetActorSprite(pActor, &pDefinition->pRowActors[row]);
    }
}

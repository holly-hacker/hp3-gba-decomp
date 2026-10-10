#include "types.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "menu/menu.h"
#include "graphics/object.h"

void BuildListMenu(const ListMenuDefinition *pDefinition)
{
    Object *pObject;
    u32 row;

    g_ListMenuState.pDefinition = pDefinition;

    BeginMenuScreen(pDefinition->wTitleStringId, 4, 1);
    g_pMenuCursorObject->oam.objMode = 1;
    g_pMenuCursorObject->oam.hFlip = 1;
    g_pMenuCursorObject->pfnTick = ListMenuCursorTick_candidate;
    SetMenuCursorPosition(g_pMenuCursorObject,
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

    for (row = 0; row < pDefinition->wRowObjectCount; row++)
    {
        pObject = SpawnMenuIconObject(row, 0);
        pObject->dwFlags |= ObjectFlagSuppressEffectBinding | ObjectFlagHasAnimation;
        SetObjectPosition(pObject,
                          pDefinition->wStrideX * row + pDefinition->wBaseX
                              + pDefinition->wRowObjectOffsetX,
                          pDefinition->wStrideY * row + pDefinition->wBaseY
                              + pDefinition->wRowObjectOffsetY);
        AttachObjectPalette(pObject, pDefinition->pRowObjects->pPalette);
        sub_08001690(pObject, &pDefinition->pRowObjects[row]);
    }
}

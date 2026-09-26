#include "types.h"
#include "game_modes.h"
#include "main_menu.h"
#include "menu.h"
#include "object.h"

void BuildListMenu(const ListMenuDefinition *pDefinition)
{
    Object *pObject;
    u32 row;

    g_ListMenuState.pDefinition = pDefinition;

    sub_0801E05C(pDefinition->wTitleStringId, 4, 1);
    g_pMenuCursorObject->bField2To3_candidate = 1;
    g_pMenuCursorObject->bXFlip = 1;
    g_pMenuCursorObject->pfnTick = ListMenuCursorTick_candidate;
    sub_0801DCC4(g_pMenuCursorObject,
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
        pObject = sub_0802C90C(row, 0);
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

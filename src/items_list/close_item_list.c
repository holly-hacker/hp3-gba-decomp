#include "types.h"
#include "cursor.h"
#include "palette.h"
#include "items_list.h"

void CloseItemList(void)
{
    if (g_ItemList.pCursor)
    {
        ReleaseMenuCursor(g_ItemList.pCursor);
        g_ItemList.pCursor = NULL;
        FreeAllParticleEmitters();
        FreeAllParticles();
    }

    UnreserveObjPaletteSlot(0);
    FreeItemListRows();
    FreeAllActors(&g_ActiveActorListState.pHead);
}

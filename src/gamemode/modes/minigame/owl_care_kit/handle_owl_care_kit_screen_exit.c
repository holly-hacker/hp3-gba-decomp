#include "types.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "graphics/palette.h"
#include "battle/battle.h"
#include "hw/mem.h"
#include "actor.h"
#include "menu/main_menu.h"
#include "minigame/owlcare.h"
#include "cursor.h"

void HandleOwlCareKitScreenExit(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);

    if (g_OwlCareKitScreen.pCursor != NULL)
        ReleaseMenuCursor(g_OwlCareKitScreen.pCursor);

    sub_080233C0(g_OwlCareKitScreen.pUnk08);
    FreeAllParticles();
    FreeAllParticleEmitters();
    ResetPaletteAnimations();
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeBgTileAnimations();
    UnreserveObjPaletteSlot(0);
}

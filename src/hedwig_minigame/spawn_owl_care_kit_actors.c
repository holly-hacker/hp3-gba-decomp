#include "types.h"
#include "actor.h"
#include "color.h"
#include "menu_icon.h"
#include "palette.h"
#include "owl_actor_inline.h"
#include "gen/graphics/menus.h"
#include "gen/graphics/minigames/owl_care.h"

const void *const g_apOwlTypePalettes[3] = {
    gOwlCareWhiteOwlPalette,
    gOwlCareBrownOwlPalette,
    gOwlCareGrayOwlPalette,
};

void SpawnOwlCareKitActors(void)
{
    Actor *pDoor;

    ClearObjPaletteSlots();
    ReserveObjPaletteSlot(0);
    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 16);
    g_OwlCareKitScreen.pCursor = NULL;
    // BUG: positions the cursor it has just cleared, so SetActorPosition gets NULL.
    SetActorPosition(g_OwlCareKitScreen.pCursor, g_GameModeStackContext.dwModeScratchB * 24 + 20, 156);
    InitializeOwlActorSprite();

    pDoor = SpawnMenuIconActor(2, NULL);
    pDoor->dwFlags |= ActorFlagHasAnimation;
    pDoor->oam.priority = 3;
    pDoor->pfnTick = TickOwlCageDoor;
    BindObjPaletteSlot(2, pDoor, g_OwlCageDoorSprite.pPalette);
    SetActorSprite(pDoor, &g_OwlCageDoorSprite);
    SetActorPosition(pDoor, 64, 0);

    if (g_saveStateBlock.owlCareKit.bFlags & OwlCareKitFlagMailOut)
    {
        SetOwlCageDoorAnim(2);
        SetOwlState(OwlStateAway);
    }
    else
        SetOwlCageDoorAnim(0);
}

#include "types.h"
#include "battle/battle.h"
#include "gen/graphics/battle.h"

// Creates the turn-order icon for the fighter at turnOrderIndex: a container
// Object (stored in apTurnOrderIconObjects) carrying the fighter's icon
// graphic, with a linked portrait-frame sprite on top. Icons are laid out
// right-aligned, 20 pixels apart. isAlly selects the party or enemy asset
// table and the idle frame; gfxSlot is the fighter Object's palette slot.
Object *SpawnTurnOrderIcon(u32 rosterIndexOrFighterType, u32 isAlly, u32 turnOrderIndex, u32 gfxSlot)
{
    Object *container;
    u8 x;

    container = AllocDefaultObject();
    container->wObjectType = 0x2A;

    x = 240 - (g_pFightState->bFighterCount - turnOrderIndex) * 20;
    container->pLinkedObject_candidate = SpawnObject(0x2A, x, 20, (const ObjPalette *)gBattleHudItem001Palette);
    container->pLinkedObject_candidate->bDepthSortBias = 0xFF;
    sub_08001690(container->pLinkedObject_candidate, &g_TurnOrderIconContainerAsset);

    if (isAlly) {
        SnapObjectPosition(container, x << 16, 24 << 16);
        SetObjectAssetRecord(container, &g_aAllyTurnOrderIconAssets[rosterIndexOrFighterType]);
        SetObjectAnimFrame(container->pLinkedObject_candidate, 0);
    } else {
        SnapObjectPosition(container, x << 16, 20 << 16);
        SetObjectAssetRecord(container, &g_aEnemyTurnOrderIconAssets[rosterIndexOrFighterType]);
        SetObjectAnimFrame(container->pLinkedObject_candidate, 1);
    }

    container->oam.priority = 0;
    container->oam.paletteNum = gfxSlot;
    container->dwFlags = ObjectFlagSuppressEffectBinding | ObjectFlagHasAnimation | ObjectFlagHasTickLogic | ObjectFlagVisible;
    container->bDepthSortBias = 0x80;
    g_pFightState->apTurnOrderIconObjects[turnOrderIndex] = container;
    return container;
}

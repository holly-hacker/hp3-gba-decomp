#include "types.h"
#include "combat_fighter.h"
#include "gen/graphics/battle.h"
#include "combat.h"

// Creates the turn-order icon for the fighter at turnOrderIndex: a container
// Actor (stored in apTurnOrderIconActors) carrying the fighter's icon
// graphic, with a linked portrait-frame sprite on top. Icons are laid out
// right-aligned, 20 pixels apart. isAlly selects the party or enemy asset
// table and the idle frame; gfxSlot is the fighter Actor's palette slot.
Actor *SpawnTurnOrderIcon(u32 rosterIndexOrFighterType, u32 isAlly, u32 turnOrderIndex, u32 gfxSlot)
{
    Actor *container;
    u8 x;

    container = AllocDefaultActor();
    container->wActorType = 0x2A;

    x = 240 - (g_pFightState->bFighterCount - turnOrderIndex) * 20;
    container->pLinkedActor = SpawnActor(0x2A, x, 20, (const ObjPalette *)gBattleHudItem001Palette);
    container->pLinkedActor->bDepthSortBias = 0xFF;
    SetActorSprite(container->pLinkedActor, &g_TurnOrderIconContainerAsset);

    if (isAlly) {
        SnapActorPosition(container, x << 16, 24 << 16);
        SetActorAssetRecord(container, &g_aAllyTurnOrderIconAssets[rosterIndexOrFighterType]);
        SetActorAnimFrame(container->pLinkedActor, 0);
    } else {
        SnapActorPosition(container, x << 16, 20 << 16);
        SetActorAssetRecord(container, &g_aEnemyTurnOrderIconAssets[rosterIndexOrFighterType]);
        SetActorAnimFrame(container->pLinkedActor, 1);
    }

    container->oam.priority = 0;
    container->oam.paletteNum = gfxSlot;
    container->dwFlags = ActorFlagKeepPaletteSlot | ActorFlagHasAnimation | ActorFlagHasTickLogic | ActorFlagVisible;
    container->bDepthSortBias = 0x80;
    g_pFightState->apTurnOrderIconActors[turnOrderIndex] = container;
    return container;
}

#include "types.h"
#include "actor.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "mem.h"

// Shows the icon for row of a battle menu, grayed (semi-transparent) unless enabled. kind
// picks the menu: 0 top menu, 1 spell list, 2 items, 3 Special Moves, 4 + spell id the
// spell's cast levels.
void SetBattleMenuIconState(u32 kind, u32 row, u32 fighterType, u32 enabled)
{
    Actor *actor;
    u32 icon;

    icon = 0;
    actor = g_apBattleMenuIconActors[row];
    switch (kind) {
    case 0:
        // Hermione and Ron have their own Special Move icons.
        icon = row;
        if (icon == 1 && fighterType != Harry)
            icon = fighterType + 6;
        break;

    case 1:
        icon = g_aabFighterSpellMenu[fighterType][row] + 9;
        break;

    case 2:
        icon = row + 19;
        break;

    case 3:
        icon = row + 25;
        if (fighterType == Ron)
            icon += 3;
        break;

    case 5:  // 4 + Informus, which has no cast levels
        break;

    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        icon = row + 31;
        icon += (kind - 4) * 3;
        break;
    }

    SetActorAssetRecord(actor, &g_aBattleMenuIconAssets[icon]);
    SetActorAnimFrame(actor, 0);
    if (enabled)
        actor->oam.objMode = 0;
    else
        actor->oam.objMode = 1;

    CopyMemory(&g_pFightState->awPalette[256 + actor->oam.paletteNum * 16],
               g_aBattleMenuIconAssets[icon].pPalette, 0x20);
    actor->dwFlags |= ActorFlagVisible;
}

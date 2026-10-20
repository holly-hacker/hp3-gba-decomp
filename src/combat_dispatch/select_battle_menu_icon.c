#include "types.h"
#include "actor.h"
#include "combat_dispatch.h"

// Returns the enlarged icon to its normal size and grows row's icon to 1.5x over 5 frames.
void SelectBattleMenuIcon(u32 row)
{
    SetActorAffineTransform(g_apBattleMenuIconActors[g_dwSelectedBattleMenuIcon], 0x10000, 0x10000, 0, 3);
    StartActorAffineScaleTween(g_apBattleMenuIconActors[g_dwSelectedBattleMenuIcon], 0x10000, 0x10000, 0);
    ReleaseActorAffineSlot(g_apBattleMenuIconActors[g_dwSelectedBattleMenuIcon]);
    SetActorAffineTransform(g_apBattleMenuIconActors[row], 0x10000, 0x10000, 0, 3);
    StartActorAffineScaleTween(g_apBattleMenuIconActors[row], 0x18000, 0x18000, 5);
    g_dwSelectedBattleMenuIcon = row;
}

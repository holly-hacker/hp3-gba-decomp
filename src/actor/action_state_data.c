#include "types.h"
#include "actor.h"
#include "gen/graphics/overworld.h"

// The direction facing away from each Direction, then each Direction4, for
// TickActorTurnAround; the same values as g_abOppositeDirection8/4.
const u8 g_abTurnAroundDirection[8] = { 4, 5, 6, 7, 0, 1, 2, 3 };
const u8 g_abTurnAroundDirection4[4] = { 2, 3, 0, 1 };

// The coin the player holds up after receiving Sickles; see TickActorReceiveReward.
const ActorAssetRecord g_CoinIconAsset = { (void *)gUnnamed004Tiles, (void *)gUnnamed004Frames,
                                           (const ObjPalette *)gUnnamed004Palette, 0 };

// Text macro 2 for a received item whose name needs no suffix.
const u8 g_sSpace[] = " ";

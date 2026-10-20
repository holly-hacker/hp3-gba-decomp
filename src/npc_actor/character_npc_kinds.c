#include "types.h"
#include "npc_actor.h"

// NPC kind (index into g_aActorTypeAssets) of a party member left behind as an
// NPC, by character id; see SpawnCharacterNpcActor.
const u8 g_abCharacterNpcKinds[12] = { 7, 6, 7, 7, 7, 7, 6, 7, 0, 0, 0, 0 };

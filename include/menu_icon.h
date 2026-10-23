#pragma once

#include "types.h"

struct Actor;

// Icon actors filed by slot, shared by the pause menu lists, combat results,
// card trade, GameCube link, Hedwig Care and Owl Name Select screens. Freeing
// an actor clears its slot.
extern struct Actor *g_apMenuIconActors[8];  // 0x03003F68
// Allocates a type 0x13 actor, registers it under slot and installs pfnTick.
extern struct Actor *SpawnMenuIconActor(u32 slot, void (*pfnTick)(struct Actor *actor));
// Stores the actor in g_apMenuIconActors[slot] and its slot in
// Actor.wSubtype, and installs UnregisterMenuIconActor as its destructor.
extern void RegisterMenuIconActor(u32 slot, struct Actor *actor);
// Destructor: clears the actor's g_apMenuIconActors slot if it still holds this actor.
extern void UnregisterMenuIconActor(struct Actor *actor);

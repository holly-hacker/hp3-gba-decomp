#pragma once

#include "types.h"

// One random-encounter id's 3 kinds x 4 random variants of enemy slots.
// At spawn time one variant is picked with Mt19937RandMax(3) and stored
// on the wandering-monster object; touching it starts a battle with
// exactly that cell as the enemy roster. Each variant is 4 monster ids,
// one per enemy slot; 255 (0xFF) = empty slot (see SetupBattleRoster,
// docs/formats/encounters.md).
typedef struct {
    u8 aVariants[4][4];
} RandomEncounterKind;

typedef struct {
    RandomEncounterKind aKinds[3];
} RandomEncounter;

// One fight's four enemy slots; 255 (0xFF) = empty slot.
extern const u8 g_aScriptedEncounters[15][4];
extern const RandomEncounter g_aRandomEncounters[30];

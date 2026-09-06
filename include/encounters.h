#pragma once

#include "types.h"

// One fight's four enemy slots (see SetupBattleRoster,
// docs/formats/encounters.md). Each entry is a monster id;
// 255 (0xFF) = empty slot.
typedef struct {
    u8 bSlot0MonsterId;
    u8 bSlot1MonsterId;
    u8 bSlot2MonsterId;
    u8 bSlot3MonsterId;
} EncounterSlots;

// One random-encounter id's 3 kinds x 4 random variants of enemy slots.
// At spawn time one variant is picked with Mt19937RandMax(3) and stored
// on the wandering-monster object; touching it starts a battle with
// exactly that cell as the enemy roster.
typedef struct {
    EncounterSlots aVariants[4];
} RandomEncounterKind;

typedef struct {
    RandomEncounterKind aKinds[3];
} RandomEncounter;

extern const EncounterSlots g_aScriptedEncounters[15];
extern const RandomEncounter g_aRandomEncounters[30];

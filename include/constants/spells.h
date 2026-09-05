#pragma once

#include "types.h"

// Rows of every per-spell table, in spell-id order: Flipendo, Informus,
// Verdimillious, Diffindo, Incendio, WingardiumLeviosa, PetrificusTotalus,
// Glacius, Fumos, Spongify.
#define SPELL_COUNT  10

// Each spell is learnable at three levels; tables index spellId * 3 +
// spellLevel. See docs/memory-map/battle.md.
#define SPELL_LEVELS 3

extern const u16 g_awSpellPowerBase[SPELL_COUNT][SPELL_LEVELS];
extern const u16 g_awSpellPowerScale[SPELL_COUNT][SPELL_LEVELS];

#pragma once

// Rows of every per-spell table, in spell-id order: Flipendo, Informus,
// Verdimillious, Diffindo, Incendio, WingardiumLeviosa, PetrificusTotalus,
// Glacius, Fumos, Spongify.
#define SPELL_COUNT  10

// Each spell is learnable at three levels; tables index spellId * 3 +
// spellLevel. See docs/memory-map/battle.md.
#define SPELL_LEVELS 3

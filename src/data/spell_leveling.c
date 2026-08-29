#include "types.h"
#include "constants/spells.h"

// Gates TrackSpellFamiliarity: a spell can never be cast above its own cap.
const u8 g_abSpellMaxLevel[SPELL_COUNT] = {
    3,  // Flipendo
    1,  // Informus
    3,  // Verdimillious
    1,  // Diffindo
    3,  // Incendio
    1,  // WingardiumLeviosa
    2,  // PetrificusTotalus
    2,  // Glacius
    2,  // Fumos
    1,  // Spongify
};

// Indexed by g_abSpellCastLevel[spellId] - 1: a spell starts at cast level 1
// (Uno) automatically, so no entry is needed to reach it. Uno->Duo takes 25
// uses, Duo->Tria takes 50.
const u8 g_abSpellLevelUpThreshold[2] = { 25, 50 };

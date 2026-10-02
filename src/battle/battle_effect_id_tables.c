#include "types.h"
#include "battle/battle.h"

// Battle effect ids per Folio Universitas card slot (Harry's special moves),
// followed by the Hermione lecture and Harry-party special move effect ids
// indexed by the active fighter's bSpellId. Slots 16-21 of the two card
// tables are zero.
const u8 g_abHarryCardEffectId[22] = {
    15,  5, 10, 42, 52, 18, 37, 35,
    53, 48, 40, 14, 41, 47, 39, 43,
     0,  0,  0,  0,  0,  0,
};

// [0] is the target type read by TickPlayerActionState. [1] is nonzero for
// cards whose resolution calls StopBgTileAnimationsAfterCard_candidate.
const u8 g_aCardTargetingMeta[22][2] = {
    { 0, 1 }, { 1, 1 }, { 0, 1 }, { 2, 0 }, { 0, 0 }, { 0, 0 }, { 3, 0 }, { 0, 1 },
    { 0, 0 }, { 2, 1 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 1, 0 }, { 0, 1 }, { 2, 1 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};

const u8 g_abSpecialMoveEffectId[3] = { 44, 46, 45 };

const u8 g_abHermioneLectureEffectId[3] = { 49, 51, 50 };

#pragma once

#include "types.h"

// Number of collector's cards in the Folio Universitas, indexed 0-50.
#define FOLIO_UNIVERSITAS_CARD_COUNT 51

// Adds one copy of a card (count saturates at 9), marking it seen and new the
// first time, and returns the card's count. See docs/formats/save.md.
u32 IncrementFolioUniversitasCard(u32 cardIndex);

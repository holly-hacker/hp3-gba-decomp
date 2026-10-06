#include "types.h"
#include "menu/folio_universitas.h"

void DrawFolioUniversitasCardSlots(void)
{
    u32 cardIndex;

    for (cardIndex = 0; cardIndex < FOLIO_UNIVERSITAS_CARD_COUNT; cardIndex++)
        DrawFolioCardSlot(cardIndex);
}

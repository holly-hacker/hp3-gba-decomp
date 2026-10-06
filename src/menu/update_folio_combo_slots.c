#include "types.h"
#include "divide.h"
#include "menu/folio_universitas_inline.h"

// Fills the three combo slots with the combo under the cursor. Cards that were never collected
// show as a face-down blank (index 0x33); the last card of a row, which has no combo, and
// the 51st card are shown alone in the middle slot.
void UpdateFolioComboSlots(void)
{
    u32 cardIndex;
    u32 slot;
    s32 nextSlot;

    cardIndex = GetFolioUniversitasSelectedCombo();
    iwramDivideSignedRemainder(g_FolioUniversitasState.dwSlot + 1, 10, &nextSlot);

    if (nextSlot == 0 || cardIndex == 0x32)
    {
        SetFolioComboSlot(-1, 0);
        if (FOLIO_CARD_SEEN(cardIndex))
            SetFolioComboSlot(cardIndex, 1);
        else
            SetFolioComboSlot(0x33, 1);
        SetFolioComboSlot(-1, 2);
    }
    else
    {
        for (slot = 0; slot < 3; slot++)
        {
            if (FOLIO_CARD_SEEN(cardIndex))
                SetFolioComboSlot(cardIndex, slot);
            else
                SetFolioComboSlot(0x33, slot);
            cardIndex++;
        }
    }
}

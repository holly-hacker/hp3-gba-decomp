#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "pscreen_status_equip.h"

#ifdef VERSION_JP
#define SLOT_NAME_TILE_ROW 0x11
#else
#define SLOT_NAME_TILE_ROW 0x10
#endif

void DrawStatusEquipSlotName(void)
{
    const u8 *text;

    ClearBgTilemapRect(2, 1, SLOT_NAME_TILE_ROW, 0xE, 3);
    if (IsStatusEquipSlotSelectable())
        SelectTextFont(2, 6, 0);
    else
        SelectTextFont(2, 1, 0);

    text = GetDialogText(g_aStatusEquipSlots[g_bStatusEquipSlot].dwTextId);  // "Equip Belt", ...
    DrawTextLines(0x165, 0x3C, SLOT_NAME_TILE_ROW * 8, 0x68, 0x18, &text, 1);
}

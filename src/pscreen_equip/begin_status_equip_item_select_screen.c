#include "font.h"
#include "text.h"
#include "cursor.h"
#include "default_menu.h"
#include "pscreen_character.h"
#include "pscreen_equip.h"
#include "items.h"
#include "items_list.h"

void BeginStatusEquipItemSelectScreen(void)
{
    s32 i;
    const u8 *text;
    u32 tileCursor;

    g_StatusEquipItemSelect.dwHasItems = 0;
    g_StatusEquipItemSelect.dwUnk0 = 0;
    BeginMenuScreen(0xA41, 9, 0);  // "Status/Equip"

    // The Remove row is listed only while the slot holds an item.
    g_StatusEquipItemSelect.dwItemListOpen = OpenFilteredItemList(
        g_dwStatusEquipSlotType, 0x23, 0x50, 1,
        GetEquippedItem(g_dwStatusEquipCharacter, g_dwStatusEquipSlotType) != 0xFF, 3,
        g_dwStatusEquipCharacter);
    if (g_StatusEquipItemSelect.dwItemListOpen != 0)
    {
        g_StatusEquipItemSelect.dwHasItems = 1;
        SetItemListCallbacks(DrawEquipItemStatComparison, NULL);
    }

    for (i = 0; i < ARRAY_COUNT(g_StatusEquipItemSelect.apStatArrows); i++)
    {
        g_StatusEquipItemSelect.apStatArrows[i] = SpawnMenuCursorActor(2);
        SetMenuCursorPosition(g_StatusEquipItemSelect.apStatArrows[i], 0xCD, EQUIP_STAT_ROW(i) + 4);
        g_StatusEquipItemSelect.apStatArrows[i]->dwFlags &= ~ActorFlagVisible;
    }

    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(6, 1, -1);
    text = GetDialogText(g_adwStatusEquipCharacterNameTextIds[g_dwStatusEquipCharacter]);
    tileCursor = DrawTextLines(0x30, 0x10, 0x19, 0x60, 0x18, &text, 0);
    SelectTextFont(2, 0, -1);
    text = GetDialogText(g_dwStatusEquipSlotType + 0x3F7);  // "Change Belt" etc.
    tileCursor = DrawTextLines(tileCursor, 0x10, 0x28, 0x70, 0x10, &text, 0);

    if (g_StatusEquipItemSelect.dwHasItems != 0)
    {
        SelectTextFont(2, 0, -1);
        text = GetDialogText(0x59D);  // "Def:"
        tileCursor = DrawTextLines(tileCursor, EQUIP_STAT_LABEL_X,
                                   EQUIP_STAT_ROW(0), 0x30, EQUIP_STAT_ROW_HEIGHT, &text, 0);
        text = GetDialogText(0x59E);  // "Agi:"
        tileCursor = DrawTextLines(tileCursor, EQUIP_STAT_LABEL_X,
                                   EQUIP_STAT_ROW(1), 0x30, EQUIP_STAT_ROW_HEIGHT, &text, 0);
        text = GetDialogText(0x59F);  // "M.Def:"
        tileCursor = DrawTextLines(tileCursor, EQUIP_STAT_LABEL_X,
                                   EQUIP_STAT_ROW(2), 0x30, EQUIP_STAT_ROW_HEIGHT, &text, 0);
        g_StatusEquipItemSelect.dwTextCursor = tileCursor;
        DrawEquipItemStatComparison(GetItemListSelection());
    }
    else
    {
        SelectTextFont(2, 0, -1);
        text = GetDialogText(0x667);  // "There are no items to display. ..."
        DrawTextLines(tileCursor, 0x78, 0x50, 0xC0, 0x20, &text, 1);
    }
}

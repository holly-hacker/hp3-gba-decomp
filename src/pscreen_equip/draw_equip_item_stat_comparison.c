#include "font.h"
#include "text.h"
#include "background.h"
#include "combat.h"
#include "pscreen_character.h"
#include "pscreen_equip.h"
#include "items.h"
#include "constants/items.h"

void DrawEquipItemStatComparison(u32 item)
{
    u32 tileCursor;
    u32 equipped;
    s32 defenseDelta;
    s32 agilityDelta;
    s32 magicDefenseDelta;
    s32 defense;
    s32 agility;
    s32 magicDefense;
    s32 newDefense;
    s32 newAgility;
    s32 newMagicDefense;
    const u8 *text;

    tileCursor = g_StatusEquipItemSelect.dwTextCursor;
    ClearBgTilemapRect(2, 0x17, EQUIP_STAT_CLEAR_ROW, 6, EQUIP_STAT_CLEAR_ROWS);

    // Equip `item` in place of the slot's item to read the resulting stats,
    // then put the original item back.
    equipped = GetEquippedItem(g_dwStatusEquipCharacter, g_dwStatusEquipSlotType);
    defense = g_aPartyMasterStats[g_dwStatusEquipCharacter].bDefenseFactorPercent;
    magicDefense = g_aPartyMasterStats[g_dwStatusEquipCharacter].bMagicDefensePercent;
    agility = g_aPartyMasterStats[g_dwStatusEquipCharacter].bAgility;

    UnequipItemFromSlot(g_dwStatusEquipCharacter, g_dwStatusEquipSlotType);

    if (item != ITEM_REMOVE)
        EquipItemInSlot(g_dwStatusEquipCharacter, item);

    newDefense = g_aPartyMasterStats[g_dwStatusEquipCharacter].bDefenseFactorPercent;
    newMagicDefense = g_aPartyMasterStats[g_dwStatusEquipCharacter].bMagicDefensePercent;
    newAgility = g_aPartyMasterStats[g_dwStatusEquipCharacter].bAgility;

    if (equipped != 0xFF)
        EquipItemInSlot(g_dwStatusEquipCharacter, equipped);
    else
        UnequipItemFromSlot(g_dwStatusEquipCharacter, g_dwStatusEquipSlotType);

    // The stats are stored inverted (lower is better), so a positive delta is an improvement.
    defenseDelta = defense - newDefense;
    agilityDelta = agility - newAgility;
    magicDefenseDelta = magicDefense - newMagicDefense;

    // Arrow frame 4 points up, 5 down; no change hides the arrow.
    if (defenseDelta == 0)
        g_StatusEquipItemSelect.apStatArrows[0]->dwFlags &= ~ActorFlagVisible;
    else
    {
        if (defenseDelta > 0)
            SetActorAnimFrame(g_StatusEquipItemSelect.apStatArrows[0], 4);
        else
            SetActorAnimFrame(g_StatusEquipItemSelect.apStatArrows[0], 5);
        g_StatusEquipItemSelect.apStatArrows[0]->dwFlags |= ActorFlagVisible;
    }

    if (agilityDelta == 0)
        g_StatusEquipItemSelect.apStatArrows[1]->dwFlags &= ~ActorFlagVisible;
    else
    {
        if (agilityDelta > 0)
            SetActorAnimFrame(g_StatusEquipItemSelect.apStatArrows[1], 4);
        else
            SetActorAnimFrame(g_StatusEquipItemSelect.apStatArrows[1], 5);
        g_StatusEquipItemSelect.apStatArrows[1]->dwFlags |= ActorFlagVisible;
    }

    if (magicDefenseDelta == 0)
        g_StatusEquipItemSelect.apStatArrows[2]->dwFlags &= ~ActorFlagVisible;
    else
    {
        if (magicDefenseDelta > 0)
            SetActorAnimFrame(g_StatusEquipItemSelect.apStatArrows[2], 4);
        else
            SetActorAnimFrame(g_StatusEquipItemSelect.apStatArrows[2], 5);
        g_StatusEquipItemSelect.apStatArrows[2]->dwFlags |= ActorFlagVisible;
    }

    // Def: 100 - defense factor percent.
    SelectTextFont(1, 0, -1);
    SetTextMacro1Number(100 - g_aPartyMasterStats[g_dwStatusEquipCharacter].bDefenseFactorPercent);
    text = GetDialogText(0x8F7);  // "@1 "
    tileCursor = DrawTextLines(tileCursor, 0xC2, EQUIP_STAT_ROW(0), 0x18, EQUIP_STAT_ROW_HEIGHT, &text, 1);

    if (defenseDelta > 0)
        SelectTextFont(1, 3, -1);
    else if (defenseDelta < 0)
        SelectTextFont(1, 5, -1);
    else
        SelectTextFont(1, 0, -1);

    SetTextMacro1Number(
        100 - (g_aPartyMasterStats[g_dwStatusEquipCharacter].bDefenseFactorPercent - defenseDelta));
    text = GetDialogText(0x8F7);
    tileCursor = DrawTextLines(tileCursor, 0xDA, EQUIP_STAT_ROW(0), 0x18, EQUIP_STAT_ROW_HEIGHT, &text, 1);

    // Agi: 255 - agility.
    SelectTextFont(1, 0, -1);
    SetTextMacro1Number(0xFF - g_aPartyMasterStats[g_dwStatusEquipCharacter].bAgility);
    text = GetDialogText(0x8F7);
    tileCursor = DrawTextLines(tileCursor, 0xC2, EQUIP_STAT_ROW(1), 0x18, EQUIP_STAT_ROW_HEIGHT, &text, 1);

    if (agilityDelta > 0)
        SelectTextFont(1, 3, -1);
    else if (agilityDelta < 0)
        SelectTextFont(1, 5, -1);
    else
        SelectTextFont(1, 0, -1);

    SetTextMacro1Number(0xFF - (g_aPartyMasterStats[g_dwStatusEquipCharacter].bAgility - agilityDelta));
    text = GetDialogText(0x8F7);
    tileCursor = DrawTextLines(tileCursor, 0xDA, EQUIP_STAT_ROW(1), 0x18, EQUIP_STAT_ROW_HEIGHT, &text, 1);

    // M.Def: 100 - magic defense percent.
    SelectTextFont(1, 0, -1);
    SetTextMacro1Number(100 - g_aPartyMasterStats[g_dwStatusEquipCharacter].bMagicDefensePercent);
    text = GetDialogText(0x8F7);
    tileCursor = DrawTextLines(tileCursor, 0xC2, EQUIP_STAT_ROW(2), 0x18, EQUIP_STAT_ROW_HEIGHT, &text, 1);

    if (magicDefenseDelta > 0)
        SelectTextFont(1, 3, -1);
    else if (magicDefenseDelta < 0)
        SelectTextFont(1, 5, -1);
    else
        SelectTextFont(1, 0, -1);

    SetTextMacro1Number(
        100 - (g_aPartyMasterStats[g_dwStatusEquipCharacter].bMagicDefensePercent - magicDefenseDelta));
    text = GetDialogText(0x8F7);
    DrawTextLines(tileCursor, 0xDA, EQUIP_STAT_ROW(2), 0x18, EQUIP_STAT_ROW_HEIGHT, &text, 1);
}

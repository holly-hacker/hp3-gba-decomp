#include "pscreen_character.h"
#include "pscreen_status_equip.h"
#include "actor.h"
#include "background.h"
#include "default_menu.h"
#include "hero.h"
#include "gen/graphics/minigames/hippogriff.h"

void BeginStatusEquipCharacterSelectScreen(void)
{
    u32 presence;
    s32 slot;
    s32 i;
    u32 titleStringId;
    u8 column;

    ResetStatusEquipSlot();
    // Presence bits: 0 Harry, 1 Ron, 2 Hermione.
    presence = GetPartyPresenceMask();
    g_StatusEquipCharacterSelect.adwSlotPresent[0] = (presence >> 2) & 1;
    if (presence & 1)
        g_StatusEquipCharacterSelect.adwSlotPresent[1] = 1;
    else
        g_StatusEquipCharacterSelect.adwSlotPresent[1] = 0;
    g_StatusEquipCharacterSelect.adwSlotPresent[2] = (presence >> 1) & 1;

    // The cursor starts on Harry, else on the first member present.
    if (presence & 1)
    {
        g_bStatusEquipCharacterSlot = 1;
    }
    else
    {
        i = 0;
        do
        {
            if (g_StatusEquipCharacterSelect.adwSlotPresent[i])
            {
                g_bStatusEquipCharacterSlot = i;
                break;
            }
            i++;
        } while (i < 3);
    }

    switch (g_StatusEquipNextMode)
    {
    case StatusEquipSlotSelect:
        titleStringId = 0x530;  // "Status/Equip"
        break;
    case QuantitySelectScreen:
        titleStringId = 0x531;  // "Items"
        break;
    default:
        titleStringId = 0;
        break;
    }
    BeginMenuScreen(titleStringId, 4, 0);

    SetBgControl(1, g_dwCommonBg1Control);
    ClearBgTilemap(1);
    LoadBgGraphic(1, gHippogriffLanguageMinigameBgs025, MENU_SCREEN_OVERLAY_TILE_OFFSET, 0, 2, 10);
    SetBgScrollFixed(1, 0, -8 << 16);

    SetBgControl(3, g_dwStatusEquipCharacterSelectBg3Control);
    ClearBgTilemap(3);
    LoadBgGraphic(3, gHippogriffLanguageMinigameBgs026, 0x180, 0, 0, 0);
    SetBgScrollFixed(3, 0, 8 << 16);

    // BG3 holds a panel per column. A lone member's panel moves to the centre column; a pair
    // uses the outer columns.
    switch (GetPartySize())
    {
    case 1:
        ClearBgTilemapRect(1, 2, 10, 8, 8);
        ClearBgTilemapRect(1, 20, 10, 8, 8);
        if (g_StatusEquipCharacterSelect.adwSlotPresent[0])
        {
            CopyBgScreenRect(3, 7, 11, 3, 3, 12, 3);
            ClearBgTilemapRect(3, 3, 3, 7, 11);
            ClearBgTilemapRect(3, 21, 3, 7, 11);
        }
        else if (g_StatusEquipCharacterSelect.adwSlotPresent[1])
        {
            ClearBgTilemapRect(3, 3, 3, 7, 11);
            ClearBgTilemapRect(3, 21, 3, 7, 11);
        }
        else if (g_StatusEquipCharacterSelect.adwSlotPresent[2])
        {
            CopyBgScreenRect(3, 7, 11, 21, 3, 12, 3);
            ClearBgTilemapRect(3, 3, 3, 7, 11);
            ClearBgTilemapRect(3, 21, 3, 7, 11);
        }
        break;

    case 2:
        ClearBgTilemapRect(1, 11, 10, 8, 8);
        if (g_StatusEquipCharacterSelect.adwSlotPresent[0] && g_StatusEquipCharacterSelect.adwSlotPresent[1])
        {
            CopyBgScreenRect(3, 7, 11, 12, 3, 21, 3);
            ClearBgTilemapRect(3, 12, 3, 7, 11);
        }
        else if (g_StatusEquipCharacterSelect.adwSlotPresent[1] && g_StatusEquipCharacterSelect.adwSlotPresent[2])
        {
            CopyBgScreenRect(3, 7, 11, 12, 3, 3, 3);
            ClearBgTilemapRect(3, 12, 3, 7, 11);
        }
        else if (g_StatusEquipCharacterSelect.adwSlotPresent[0] && g_StatusEquipCharacterSelect.adwSlotPresent[2])
        {
            ClearBgTilemapRect(3, 12, 3, 7, 11);
        }
        break;

    case 3:  // every column in place
        break;
    }

    g_pMenuCursorActor->oam.objMode = 1;
    g_pMenuCursorActor->oam.hFlip = 1;
    column = StatusEquipSlotToColumn(g_bStatusEquipCharacterSlot);
    SetActorPosition(g_pMenuCursorActor, column * 72 + 24, 68);
    g_pMenuCursorActor->pfnTick = TickStatusEquipCharacterCursor;

    for (slot = 0; slot < 3; slot++)
    {
        if (g_StatusEquipCharacterSelect.adwSlotPresent[slot])
            DrawStatusEquipCharacterStats(slot, slot == g_bStatusEquipCharacterSlot ? 6 : 1);
    }
    NoopStatusEquipCharacterSelectDrawn();

    g_GameModeStackContext.dwModeState = 1;
    g_GameModeStackContext.dwModeSubState = 0x10;
}

#include "types.h"
#include "actor.h"
#include "items.h"
#include "pscreen_character.h"
#include "pscreen_status_equip.h"
#include "gen/graphics/overworld.h"

void SpawnStatusEquipSlotActors(void)
{
    const void *palette;
    const void *tiles;
    const void *frames;
    Actor *pItem;
    s32 x;
    s32 y;
    s32 i;
    u32 item;

    for (i = 0; i < 6; i++)
    {
        x = g_aStatusEquipSlots[i].nX;
        y = g_aStatusEquipSlots[i].nY;
        g_StatusEquipSlotSelect.apSlotFrames[i] = SpawnActor(i, x, y, (const ObjPalette *)gActorSprite094Palette);
        g_StatusEquipSlotSelect.apSlotFrames[i]->oam.objMode = 1;
        g_StatusEquipSlotSelect.apSlotFrames[i]->oam.priority = 2;
        SetActorSprite(g_StatusEquipSlotSelect.apSlotFrames[i], &g_StatusEquipSlotFrameAsset);

        item = GetEquippedItem(g_dwStatusEquipCharacter, g_aStatusEquipSlots[i].dwType);
        if (item != 0xFF)
        {
            GetItemImageData(item, &palette, &tiles, &frames);
            pItem = SpawnActor(i, x + 12, y + 12, palette);
            pItem->oam.priority = 1;
            g_StatusEquipSlotSelect.apItemGfx[i][0] = (void *)tiles;
            g_StatusEquipSlotSelect.apItemGfx[i][1] = (void *)frames;
            SetActorAssetRecord(pItem, g_StatusEquipSlotSelect.apItemGfx[i]);
            SetActorScaleStep(pItem, 0);
            g_StatusEquipSlotSelect.apSlotItems[i] = pItem;
        }
        else
            g_StatusEquipSlotSelect.apSlotItems[i] = NULL;
    }
}

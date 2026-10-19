#include "types.h"
#include "clock.h"
#include "save.h"
#include "font.h"
#include "text.h"
#include "default_menu.h"
#include "title_load.h"

void DrawSaveSlot(u32 slot, u32 selectedSlot)
{
    u32 color;
    u8 playtimeText[32];
    const u8 *pText;
    Playtime playtime;

    color = 1;
    if (slot == selectedSlot)
        color = 6;

    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(1, color, -1);

    if (g_saveManager.adwSlotValid[slot]
        && (g_saveManager.aSlotPreview[slot].bSaveFlags & PlaytimeCounterActive))
    {
        // Objective texts start at "Talk to Cornelius Fudge".
        pText = GetDialogText(g_saveManager.aSlotPreview[slot].bMainMenuObjectiveIndex + 0x924);
        DrawTextLines(slot * 128 + 0x40, 0x1F, slot * 28 + 0x32, 0xB4, 0x10, &pText, 0);
        SetTextMacro1Number(g_saveManager.aSlotPreview[slot].bPartyLeaderDisplayLevel);
        playtime.bHours = g_saveManager.aSlotPreview[slot].bPlaytimeHours;
        playtime.bMinutes = g_saveManager.aSlotPreview[slot].bPlaytimeMinutes;
        FormatPlaytimeText(&playtime, playtimeText, 0x686);  // "@hh:@mm"
        SetTextMacro2String(playtimeText);
        DrawStringAligned(slot * 128 + 0xA0, 0xD0, slot * 28 + 0x3D, GetDialogText(0x685), 2);  // "Level: @1 @2"
    }
    else
    {
        DrawStringAligned(slot * 128 + 0x40, 0x78, slot * 28 + 0x38, GetDialogText(0x684), 1);  // "Empty"
    }
}

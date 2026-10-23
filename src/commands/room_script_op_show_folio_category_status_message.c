#include "types.h"
#include "commands.h"
#include "dialog.h"
#include "dialog_box.h"
#include "font.h"
#include "text.h"

typedef struct ShowFolioCategoryStatusMessageRecord {
    u32 dwOpcode;
    u8 bCategory;
    u8 bComplete;
    u8 bDialogArg1C;
    u8 bDialogArg1D;
} ShowFolioCategoryStatusMessageRecord;

void RoomScriptOpShowFolioCategoryStatusMessage(ShowFolioCategoryStatusMessageRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    SetTextMacro1String(GetDialogText(pRecord->bCategory + 0x405));
    SetTextMacro3String(GetDialogText(pRecord->bCategory + 0x405));
    if (pRecord->bComplete != 0)
        ShowDialogBlock(0x291);
    else
        ShowDialogBlock(0x290);
    g_DialogState.bArg1C = pRecord->bDialogArg1C;
    g_DialogState.bArg1D = pRecord->bDialogArg1D;
}

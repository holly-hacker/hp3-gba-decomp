#include "types.h"
#include "audio.h"
#include "dialog.h"
#include "save.h"
#include "text.h"
#include "room_script.h"

void RoomScriptOpShowSpellLearnedMessage(RoomScriptRecord *pRecord)
{
    if (pRecord->operand.ab[1] == 0 || (g_saveStateBlock.bSaveFlags & Unknown_0x04) == 0)
    {
        if (g_dwRoomScriptRunState == 1)
            g_dwRoomScriptRunState = 2;
        PlaySoundEffect_candidate(0x1a);
        SetTextMacro1String(GetDialogText(pRecord->operand.ab[0] + 0xac2));
        SetTextMacro3String(GetDialogText(pRecord->operand.ab[0] + 0xac2));
        ShowRoomDialogBox_candidate(0x28f);
        g_DialogState_candidate.bArg1C = pRecord->operand.ab[2];
        g_DialogState_candidate.bArg1D = pRecord->operand.ab[3];
    }
}

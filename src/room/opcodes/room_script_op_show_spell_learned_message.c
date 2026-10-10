#include "types.h"
#include "graphics/audio.h"
#include "menu/dialog.h"
#include "game/save.h"
#include "font.h"
#include "graphics/text.h"
#include "overworld/room_script.h"

typedef struct ShowSpellLearnedMessageRecord {
    u32 dwOpcode;
    u8 bSpellId;
    u8 bSkipIfSaveFlag;  // nonzero: skipped while save flag 0x04 is set
    u8 bDialogArg1C;
    u8 bDialogArg1D;
} ShowSpellLearnedMessageRecord;

void RoomScriptOpShowSpellLearnedMessage(ShowSpellLearnedMessageRecord *pRecord)
{
    if (pRecord->bSkipIfSaveFlag == 0 || (g_saveStateBlock.bSaveFlags & Unknown_0x04) == 0)
    {
        if (g_dwRoomScriptRunState == 1)
            g_dwRoomScriptRunState = 2;
        PlaySoundEffect_candidate(0x1a);
        SetTextMacro1String(GetDialogText(pRecord->bSpellId + 0xac2));
        SetTextMacro3String(GetDialogText(pRecord->bSpellId + 0xac2));
        ShowRoomDialogBox_candidate(0x28f);
        g_DialogState_candidate.bArg1C = pRecord->bDialogArg1C;
        g_DialogState_candidate.bArg1D = pRecord->bDialogArg1D;
    }
}

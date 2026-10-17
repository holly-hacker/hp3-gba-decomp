#include "types.h"
#include "modes.h"
#include "dialog.h"
#include "dialog_box.h"

void ShowRoomDialogBox_candidate(u32 blockId)
{
    g_DialogState_candidate.wBlockId = blockId;
    g_dwGameModeFlags |= 1;
    PushGameMode(Dialog);
}

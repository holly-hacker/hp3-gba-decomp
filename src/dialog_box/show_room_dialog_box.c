#include "types.h"
#include "modes.h"
#include "dialog.h"
#include "dialog_box.h"
#include "main.h"

void ShowRoomDialogBox_candidate(u32 blockId)
{
    g_DialogState_candidate.wBlockId = blockId;
    g_dwGameModeFlags |= GameModeFlagOverlayMode;
    PushGameMode(Dialog);
}

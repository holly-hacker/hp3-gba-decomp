#include "types.h"
#include "modes.h"
#include "dialog.h"
#include "dialog_box.h"
#include "main.h"

// Opens the dialog box on block blockId of g_aDialogBlocks.
void ShowDialogBlock(u32 blockId)
{
    g_DialogState.wBlockId = blockId;
    g_dwGameModeFlags |= GameModeFlagOverlayMode;
    PushGameMode(Dialog);
}

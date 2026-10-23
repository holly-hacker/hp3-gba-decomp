#include "types.h"
#include "commands.h"
#include "dialog.h"
#include "dialog_box.h"
#include "font.h"
#include "text.h"

typedef struct ShowMinigameUnlockedMessageRecord {
    u32 dwOpcode;
    u8 bMinigameId;
    u8 bDialogArg1C;
    u8 bDialogArg1D;
} ShowMinigameUnlockedMessageRecord;

void RoomScriptOpShowMinigameUnlockedMessage(ShowMinigameUnlockedMessageRecord *pRecord)
{
    s16 blockId;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    // Tea Leaf Divination (3) gets its own message: "Tea Leaf Divination can now be accessed
    // from the Mini-Games menu found on the Title Screen."
    if (pRecord->bMinigameId == 3)
        blockId = 0x299;
    else
    {
        // Minigame names from 0xa4a: "Wizard Cracker Pop-it", "Buckbeak's Hippogriff Glide",
        // "Riddikulus Boggart Challenge", "Tea Leaf Divination", "Dementor Challenge".
        SetTextMacro1String(GetDialogText(pRecord->bMinigameId + 0xa4a));
        SetTextMacro3String(GetDialogText(pRecord->bMinigameId + 0xa4a));
        // "You've unlocked: @3."
        blockId = 0x292;
    }
    ShowDialogBlock(blockId);
    g_DialogState.bArg1C = pRecord->bDialogArg1C;
    g_DialogState.bArg1D = pRecord->bDialogArg1D;
}

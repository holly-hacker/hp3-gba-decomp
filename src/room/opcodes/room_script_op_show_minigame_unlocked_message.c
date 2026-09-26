#include "types.h"
#include "dialog.h"
#include "text.h"
#include "room_script.h"

void RoomScriptOpShowMinigameUnlockedMessage(RoomScriptRecord *pRecord)
{
    s16 blockId;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    // Tea Leaf Divination (3) gets its own message: "Tea Leaf Divination can now be accessed
    // from the Mini-Games menu found on the Title Screen."
    if (pRecord->operand.ab[0] == 3)
        blockId = 0x299;
    else
    {
        // Minigame names from 0xa4a: "Wizard Cracker Pop-it", "Buckbeak's Hippogriff Glide",
        // "Riddikulus Boggart Challenge", "Tea Leaf Divination", "Dementor Challenge".
        SetTextMacro1String(GetDialogText(pRecord->operand.ab[0] + 0xa4a));
        SetTextMacro3String(GetDialogText(pRecord->operand.ab[0] + 0xa4a));
        // "You've unlocked: @3."
        blockId = 0x292;
    }
    ShowRoomDialogBox_candidate(blockId);
    g_DialogState_candidate.bArg1C = pRecord->operand.ab[1];
    g_DialogState_candidate.bArg1D = pRecord->operand.ab[2];
}

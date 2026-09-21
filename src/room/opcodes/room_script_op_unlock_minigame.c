#include "types.h"
#include "save.h"
#include "room_script.h"

void RoomScriptOpUnlockMinigame(RoomScriptRecord *pRecord)
{
    switch (pRecord->operand.ab[0])
    {
    case 0:
        g_saveManager.header.bHeaderFlags.bits.bMinigame1Unlocked = 1;
        break;
    case 1:
        g_saveManager.header.bHeaderFlags.bits.bMinigame2Unlocked = 1;
        break;
    case 2:
        g_saveManager.header.bHeaderFlags.bits.bMinigame3Unlocked = 1;
        break;
    case 3:
        g_saveManager.header.bHeaderFlags.bits.bMinigame4Unlocked = 1;
        break;
    case 4:
        g_saveManager.header.bHeaderFlags.bits.bMinigame5Unlocked = 1;
        break;
    }
}

#include "types.h"
#include "commands.h"
#include "save.h"

typedef struct UnlockMinigameRecord {
    u32 dwOpcode;
    u8 bMinigameId;
} UnlockMinigameRecord;

void RoomScriptOpUnlockMinigame(UnlockMinigameRecord *pRecord)
{
    switch (pRecord->bMinigameId)
    {
    case 0:
        g_saveManager.header.bHeaderFlags.bits.bWizardCrackerPopItUnlocked = 1;
        break;
    case 1:
        g_saveManager.header.bHeaderFlags.bits.bBuckbeakUnlocked = 1;
        break;
    case 2:
        g_saveManager.header.bHeaderFlags.bits.bBoggartUnlocked = 1;
        break;
    case 3:
        g_saveManager.header.bHeaderFlags.bits.bTeaLeafDivinationUnlocked = 1;
        break;
    case 4:
        g_saveManager.header.bHeaderFlags.bits.bHarryVsDementorsUnlocked = 1;
        break;
    }
}

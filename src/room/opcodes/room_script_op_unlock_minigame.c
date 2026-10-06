#include "types.h"
#include "game/save.h"
#include "overworld/room_script.h"

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
        g_saveManager.header.bHeaderFlags.bits.bHippogriffGlideUnlocked = 1;
        break;
    case 2:
        g_saveManager.header.bHeaderFlags.bits.bRiddikulusUnlocked = 1;
        break;
    case 3:
        g_saveManager.header.bHeaderFlags.bits.bTeaLeafDivinationUnlocked = 1;
        break;
    case 4:
        g_saveManager.header.bHeaderFlags.bits.bHarryVsDementorsUnlocked = 1;
        break;
    }
}

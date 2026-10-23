#include "types.h"
#include "commands.h"
#include "modes.h"
#include "dementor_minigame.h"
#include "buckbeak_minigame.h"
#include "boggart_minigame.h"
#include "pop_it_minigame.h"
#include "combat.h"

typedef struct StartMinigameRecord {
    u32 dwOpcode;
    u8 bMinigameId;
    u8 bParam;
    u8 bShowHelp;
    u8 bPendingRow;
    u8 bPendingChain;
} StartMinigameRecord;

void RoomScriptOpStartMinigame(StartMinigameRecord *pRecord)
{
    g_bPendingRoomScriptChain = pRecord->bPendingChain;
    g_bPendingRoomScriptRow = pRecord->bPendingRow;

    switch (pRecord->bMinigameId)
    {
    case 0:
        g_dwWizardCrackerPopItForceOverworldExit = 1;
        if (pRecord->bShowHelp)
            PushGameMode_3(HelpTopicScreen, 6, 0, pRecord->bParam);
        else
            PushGameMode_3(WizardCrackerPopItMinigame, 6, 0, pRecord->bParam);
        break;
    case 2:
        g_dwBoggartMinigameForceOverworldExit = 1;
        if (pRecord->bShowHelp)
            PushGameMode_3(HelpTopicScreen, 6, 2, pRecord->bParam);
        else
            PushGameMode_3(BoggartMinigame, 6, 0, pRecord->bParam);
        break;
    case 1:
        g_dwBuckbeakMinigameForceOverworldExit = 1;
        if (pRecord->bShowHelp)
            PushGameMode_3(HelpTopicScreen, 6, 1, pRecord->bParam);
        else
            PushGameMode_3(BuckbeakMinigame, 6, 0, pRecord->bParam);
        break;
    case 4:
        g_dwDementorMinigameForceOverworldExit = 1;
        if (pRecord->bShowHelp)
            PushGameMode_3(HelpTopicScreen, 6, 4, pRecord->bParam);
        else
            PushGameMode_3(DementorMinigame, 6, 0, pRecord->bParam);
        break;
    }
}

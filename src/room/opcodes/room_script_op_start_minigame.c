#include "types.h"
#include "game_modes.h"
#include "harry_vs_dementors.h"
#include "hippogriff_glide.h"
#include "riddikulus.h"
#include "room_script.h"
#include "wizard_cracker_pop_it.h"

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
        g_dwRiddikulusMinigameScriptFlag_candidate = 1;
        if (pRecord->bShowHelp)
            PushGameMode_3(HelpTopicScreen, 6, 2, pRecord->bParam);
        else
            PushGameMode_3(RiddikulusMinigame, 6, 0, pRecord->bParam);
        break;
    case 1:
        g_dwHippogriffForceOverworldExit = 1;
        if (pRecord->bShowHelp)
            PushGameMode_3(HelpTopicScreen, 6, 1, pRecord->bParam);
        else
            PushGameMode_3(HippogriffGlideMinigame, 6, 0, pRecord->bParam);
        break;
    case 4:
        g_dwHarryVsDementorsMinigameScriptFlag_candidate = 1;
        if (pRecord->bShowHelp)
            PushGameMode_3(HelpTopicScreen, 6, 4, pRecord->bParam);
        else
            PushGameMode_3(HarryVsDementorsMinigame, 6, 0, pRecord->bParam);
        break;
    }
}

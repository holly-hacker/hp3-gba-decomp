#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "room_script.h"

typedef struct PlayCutsceneRecord {
    u32 dwOpcode;
    u8 bCutsceneId;
    u8 bPendingRow;
    u8 bPendingChain;
} PlayCutsceneRecord;

void RoomScriptOpPlayCutscene(PlayCutsceneRecord *pRecord)
{
    g_bPendingRoomScriptChain = pRecord->bPendingChain;
    g_bPendingRoomScriptRow = pRecord->bPendingRow;

    switch (pRecord->bCutsceneId)
    {
    case 0:
        PushGameMode(ClockSkipCutscene);
        break;
    case 1:
        PushGameMode(HogwartsUpNightCutscene);
        break;
    case 2:
    case 3:
        PushGameMode(CoolTrainCutscene);
        break;
    case 4:
        PushGameMode(Intro);
        break;
    case 5:
        PushGameMode(HarryArrivedAtHogwartsCutscene);
        break;
    case 6:
        PushGameMode(UnusedChristmasArrivedCutscene);
        break;
    case 7:
        PushGameMode(SiriusBlackCutscene);
        break;
    case 8:
        PushGameMode(PeterPettigrewCutscene);
        break;
    case 9:
        PushGameMode(RonSleepingCutscene);
        break;
    case 10:
        PushGameMode(TimeTurnerPermissionCutscene);
        break;
    case 11:
        PushGameMode(HippogriffFliesIntoAirCutscene);
        break;
    case 12:
        PushGameMode(LupinPotionCutscene);
        break;
    case 13:
        PlayMusicModule(0x31);
        PushGameMode(HarryPatronusCutscene);
        break;
    case 14:
        PlayMusicModule(0x31);
        PushGameMode_2(HarryPatronusCutscene, 1, 0);
        break;
    case 15:
        PushGameMode(HarryHermionePortInTimeCutscene);
        break;
    }
}

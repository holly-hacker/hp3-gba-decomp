#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "room_script.h"

typedef struct StartBattleRecord {
    u32 dwOpcode;
    u8 bBattleId;
    u8 bPendingRow;
    u8 bPendingChain;
} StartBattleRecord;

void RoomScriptOpStartBattle(StartBattleRecord *pRecord)
{
    g_bRoomScriptCallStackDepth = 0;
    g_bPendingRoomScriptChain = pRecord->bPendingChain;
    g_bPendingRoomScriptRow = pRecord->bPendingRow;
    PlaySoundById(6);
    PushGameMode_3(Battle, pRecord->bBattleId, 0, 0xff);
}

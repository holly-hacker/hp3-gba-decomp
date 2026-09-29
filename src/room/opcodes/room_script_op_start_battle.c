#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "overworld/room_script.h"

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

#include "types.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct SetBattleDefeatStateRecord {
    u32 dwOpcode;
    u8 bValue;
} SetBattleDefeatStateRecord;

void RoomScriptOpSetBattleDefeatState(SetBattleDefeatStateRecord *pRecord)
{
    g_abQuestEventState[0x10] = pRecord->bValue;
}

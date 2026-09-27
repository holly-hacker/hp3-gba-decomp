#include "types.h"
#include "room.h"
#include "room_script.h"

typedef struct SetBattleDefeatStateRecord {
    u32 dwOpcode;
    u8 bValue;
} SetBattleDefeatStateRecord;

void RoomScriptOpSetBattleDefeatState(SetBattleDefeatStateRecord *pRecord)
{
    g_abQuestEventState[0x10] = pRecord->bValue;
}

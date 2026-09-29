#include "types.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

typedef struct SetPauseMenuLockedRecord {
    u32 dwOpcode;
    u8 bLocked;
} SetPauseMenuLockedRecord;

void RoomScriptOpSetPauseMenuLocked(SetPauseMenuLockedRecord *pRecord)
{
    g_dwPauseMenuLocked = pRecord->bLocked;
}

#include "types.h"
#include "overworld.h"
#include "room_script.h"

typedef struct SetPauseMenuLockedRecord {
    u32 dwOpcode;
    u8 bLocked;
} SetPauseMenuLockedRecord;

void RoomScriptOpSetPauseMenuLocked(SetPauseMenuLockedRecord *pRecord)
{
    g_dwPauseMenuLocked = pRecord->bLocked;
}

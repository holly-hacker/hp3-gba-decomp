#include "types.h"
#include "commands.h"
#include "modes.h"
#include "main.h"

typedef struct ShowChooseCharacterRecord {
    u32 dwOpcode;
    u8 bModeArg1;
    u8 bModeArg2;
    u8 bModeArg3;
} ShowChooseCharacterRecord;

void RoomScriptOpShowChooseCharacter(ShowChooseCharacterRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    g_dwGameModeFlags |= 1;
    PushGameMode_3(ChooseCharacter, pRecord->bModeArg1, pRecord->bModeArg2, pRecord->bModeArg3);
}

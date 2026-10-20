#include "types.h"
#include "commands.h"
#include "overworld/room_script.h"

typedef struct SetPartyLeaderCharacterRecord {
    u32 dwOpcode;
    u8 bCharacterId;
} SetPartyLeaderCharacterRecord;

// Scripts pass character 5 or 6.
void RoomScriptOpSetPartyLeaderCharacter(SetPartyLeaderCharacterRecord *pRecord)
{
    SetPartyLeaderCharacter(pRecord->bCharacterId);
}

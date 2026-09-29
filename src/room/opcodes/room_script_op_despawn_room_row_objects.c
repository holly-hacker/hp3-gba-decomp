#include "types.h"
#include "overworld/room_script.h"

typedef struct DespawnRoomRowObjectsRecord {
    u32 dwOpcode;
    u8 bRow;
} DespawnRoomRowObjectsRecord;

void RoomScriptOpDespawnRoomRowObjects(DespawnRoomRowObjectsRecord *pRecord)
{
    u8 row = pRecord->bRow;
    u16 columnCount;
    u8 col;
    Object *pObject;

    if (ShouldRunRoomScriptRow_candidate(row))
    {
        columnCount = GetRoomRowColumnCount_candidate(row);
        for (col = 0; col < columnCount; col++)
        {
            pObject = GetRoomObjectField_candidate(row, col);
            if (pObject != NULL)
            {
                if (pObject->pLinkedObject_candidate != NULL)
                    pObject->pLinkedObject_candidate->dwFlags |= 0x82;
                pObject->dwFlags |= 0x82;
            }
        }
    }
}

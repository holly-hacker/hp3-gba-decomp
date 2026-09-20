#include "types.h"
#include "room_script.h"

void RoomScriptOpDespawnRoomRowObjects(RoomScriptRecord *pRecord)
{
    u8 row = pRecord->operand.ab[0];
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

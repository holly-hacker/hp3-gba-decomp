#include "types.h"
#include "overworld/room_script.h"

typedef struct Op42Record {
    u32 dwOpcode;
    u8 bArg;
} Op42Record;

void RoomScriptOp42(Op42Record *pRecord)
{
    sub_080237D0(pRecord->bArg);
}

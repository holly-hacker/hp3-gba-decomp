#include "types.h"
#include "overworld/room_script.h"

typedef struct Op42Record {
    u32 dwOpcode;
    u8 bArg;
} Op42Record;

// Unnamed; scripts pass 5 or 6. sub_080237D0 reads r7 without setting it, so it also depends on
// caller registers.
void RoomScriptOp42(Op42Record *pRecord)
{
    sub_080237D0(pRecord->bArg);
}

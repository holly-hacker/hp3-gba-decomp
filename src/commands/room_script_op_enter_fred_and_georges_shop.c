#include "types.h"
#include "commands.h"
#include "modes.h"
#include "combat.h"

typedef struct EnterFredAndGeorgesShopRecord {
    u32 dwOpcode;
    u8 bModeArg;
    u8 bPendingRow;
    u8 bPendingChain;
} EnterFredAndGeorgesShopRecord;

void RoomScriptOpEnterFredAndGeorgesShop(EnterFredAndGeorgesShopRecord *pRecord)
{
    g_bPendingRoomScriptChain = pRecord->bPendingChain;
    g_bPendingRoomScriptRow = pRecord->bPendingRow;
    PushGameMode_3(FredAndGeorgesShop, 0, pRecord->bModeArg, 0);
}

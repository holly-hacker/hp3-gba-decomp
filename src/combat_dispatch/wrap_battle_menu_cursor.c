#include "types.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"

u32 WrapBattleMenuCursor(u32 cursor, u32 lastRow)
{
    return WrapMenuCursor(cursor, lastRow);
}

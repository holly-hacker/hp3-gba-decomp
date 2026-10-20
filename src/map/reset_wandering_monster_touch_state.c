#include "types.h"
#include "mem.h"
#include "map.h"

void ResetWanderingMonsterTouchState(void)
{
    g_bTouchedMonsterRecordCount = 0;
    g_pTouchedWanderingMonster = NULL;
    memset(g_aTouchedMonsterRecords, 0, sizeof(g_aTouchedMonsterRecords));
}

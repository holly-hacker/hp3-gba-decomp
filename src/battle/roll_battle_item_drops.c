#include "types.h"
#include "battle.h"
#include "mt19937.h"
#include "monster_drop_table.h"

#define NO_ITEM 0x85
#define MAX_FAINTED_MONSTERS 4

#define ROSTER_INDEX (*(s32 *)((u8 *)g_anFaintedRosterIndices + offset))
#define DROP_ENTRY (g_pMonsterDropTable[ROSTER_INDEX])

// Rolls up to 2 dropped items from up to 4 fainted monsters, one roll per
// monster, stopping once 2 items are found (a 3rd+ hit is discarded). Each
// monster's two drop-table slots are adjacent ranges on a single 0-99 roll,
// mutually exclusive -- except ForceItemDrop (Ron's Wizard Cracker) forces
// the roll to 0, guaranteeing slot0 (slot0's chance is never 0).
void RollBattleItemDrops(int *pItemId0, int *pItemId1)
{
    s32 firstSlotEmpty = 1;
    s32 count;
    s32 offset;

    *pItemId0 = NO_ITEM;
    *pItemId1 = NO_ITEM;
    count = 0;

    if (g_anFaintedRosterIndices[0] == -1)
        return;

    offset = 0;
    do
    {
        s32 roll;
        s32 slot;

        if (g_dwBattleRewardFlagsSnapshot & ForceItemDrop)
            roll = 0;
        else
            roll = Mt19937RandRange(0, 99);

        slot = -1;
        if (roll < DROP_ENTRY.slot[0].chance)
            slot = 0;
        else if (roll < DROP_ENTRY.slot[0].chance + DROP_ENTRY.slot[1].chance)
            slot = 1;

        if (slot != -1)
        {
            if (firstSlotEmpty)
            {
                *pItemId0 = DROP_ENTRY.slot[slot].itemId;
                firstSlotEmpty = 0;
            }
            else
            {
                *pItemId1 = DROP_ENTRY.slot[slot].itemId;
                return;
            }
        }

        offset += 4;
        count++;
        if (count > 3)
            return;
    } while (ROSTER_INDEX != -1);
}

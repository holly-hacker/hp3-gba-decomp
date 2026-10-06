#include "types.h"
#include "hw/mem.h"
#include "game/save.h"
#include "overworld/room.h"
#include "overworld/room_object.h"

#define STARTING_ROOM_ID 0x2A

// Resets the room, chest and quest event state. A plain new game also
// clears Sickles and the inventory; a New Game+ (nonzero argument) instead
// resets the party and keeps the completion count, incremented.
void ResetQuestStateForNewGame(u32 newGamePlus)
{
    u8 completionCount = g_abQuestEventState[QUEST_COMPLETION_COUNT];

    g_bCurrentRoomId = STARTING_ROOM_ID;
    g_dwOverworldMonstersDisabled = 0;
    memset(g_abOpenedChestFlags, 0, sizeof(g_abOpenedChestFlags));
    memset(g_abQuestEventState, 0, 0x100);
    InitRoomState();

    if (newGamePlus)
    {
        ResetPartyHpMpAndStats();
        g_abQuestEventState[QUEST_COMPLETION_COUNT] = completionCount + 1;
    }
    else
    {
        SetSickles(0);
        ClearItemInventoryForNewGame_candidate();
    }
}

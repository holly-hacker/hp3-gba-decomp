#include "types.h"
#include "battle/battle.h"
#include "chest_actor.h"
#include "game/save.h"
#include "inventory.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_actor.h"

// Packs the live game state into the slot stream. The first six values are
// the ones UnpackSaveSlotPreview reads back for the save menus.
void SerializeGameStateToSaveBuffer(void)
{
    u8 leaderDisplayLevel;

    PackBytesToSaveStream(&g_saveStateBlock.dwMoney, 4);
    PackBytesToSaveStream(&g_saveStateBlock.stPlaytime.bHours, 4);
    PackBytesToSaveStream(&g_bCurrentRoomId, 1);
    PackBytesToSaveStream(&g_saveStateBlock.bSaveFlags, 1);
    PackBytesToSaveStream(&g_abQuestEventState[QUEST_OBJECTIVE_INDEX], 1);
    leaderDisplayLevel = g_aPartyMasterStats[0].bLevel + 1;
    PackBytesToSaveStream(&leaderDisplayLevel, 1);
    PackBytesToSaveStream(&g_bPartyCharId0, 1);
    PackBytesToSaveStream(&g_bPartyCharId1, 1);
    PackBytesToSaveStream(&g_bPartyCharId2, 1);
    PackBitsToSaveStream((u8 *)&g_dwOverworldMonstersDisabled, 1);
    PackBytesToSaveStream(&g_bSelectedFieldSpell, 1);
    SerializeItemQuantities();
    SerializePartyStats();
    SerializeRoomActorState();
    PackBytesToSaveStream(g_abOpenedChestFlags, sizeof(g_abOpenedChestFlags));
    PackBytesToSaveStream(g_abQuestEventState, 0x100);
    SerializeMonsterDexLevels();
    SerializeFolioUniversitas();
    SerializeOwlCareKit();
}

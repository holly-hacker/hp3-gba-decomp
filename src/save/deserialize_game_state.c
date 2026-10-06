#include "types.h"
#include "battle/battle.h"
#include "hw/mem.h"
#include "game/save.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_object.h"

// Rebuilds the live game state from the slot buffer, in the order
// SerializeGameStateToSaveBuffer wrote it.
void DeserializeGameStateFromSaveBuffer(void)
{
    u8 leaderDisplayLevel;

    memset(&g_saveStateBlock, 0, sizeof(SaveStateBlock));
    UnpackBytesFromSaveStream(&g_saveStateBlock.dwMoney, 4);
    InitializePlaytimeStruct(&g_saveStateBlock.stPlaytime);
    UnpackBytesFromSaveStream(&g_saveStateBlock.stPlaytime.bHours, 4);
    UnpackBytesFromSaveStream(&g_bCurrentRoomId, 1);
    UnpackBytesFromSaveStream(&g_saveStateBlock.bSaveFlags, 1);
    UnpackBytesFromSaveStream(&g_abQuestEventState[QUEST_OBJECTIVE_INDEX], 1);
    UnpackBytesFromSaveStream(&leaderDisplayLevel, 1);
    g_aPartyMasterStats[0].bLevel = leaderDisplayLevel - 1;
    UnpackBytesFromSaveStream(&g_bPartyCharId0, 1);
    UnpackBytesFromSaveStream(&g_bPartyCharId1, 1);
    UnpackBytesFromSaveStream(&g_bPartyCharId2, 1);
    UnpackBitsFromSaveStream((u8 *)&g_dwOverworldMonstersDisabled, 1);
    UnpackBytesFromSaveStream(&g_bSelectedFieldSpell, 1);
    DeserializeItemQuantities();
    DeserializePartyStats();
    DeserializeRoomObjectState();
    UnpackBytesFromSaveStream(g_abOpenedChestFlags, sizeof(g_abOpenedChestFlags));
    UnpackBytesFromSaveStream(g_abQuestEventState, 0x100);
    DeserializeMonsterDexLevels();
    DeserializeFolioUniversitas();
    DeserializeOwlCareKit();
}

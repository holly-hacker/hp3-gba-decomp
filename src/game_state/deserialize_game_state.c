#include "types.h"
#include "chest_actor.h"
#include "clock.h"
#include "combat_fighter.h"
#include "mem.h"
#include "save.h"
#include "game_state.h"
#include "items.h"
#include "overworld/room.h"
#include "hedwig_minigame.h"
#include "map.h"
#include "pscreen_folio_bruti.h"
#include "pscreen_folio_universitas.h"
#include "combat.h"
#include "commands.h"
#include "hero.h"

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
    g_aPartyMasterStats[0].stats.bLevel = leaderDisplayLevel - 1;
    UnpackBytesFromSaveStream(&g_bPartyCharId0, 1);
    UnpackBytesFromSaveStream(&g_bPartyCharId1, 1);
    UnpackBytesFromSaveStream(&g_bPartyCharId2, 1);
    UnpackBitsFromSaveStream((u8 *)&g_dwOverworldMonstersDisabled, 1);
    UnpackBytesFromSaveStream(&g_bSelectedFieldSpell, 1);
    DeserializeItemQuantities();
    DeserializePartyStats();
    DeserializeRoomActorState();
    UnpackBytesFromSaveStream(g_abOpenedChestFlags, sizeof(g_abOpenedChestFlags));
    UnpackBytesFromSaveStream(g_abQuestEventState, 0x100);
    DeserializeMonsterDexLevels();
    DeserializeFolioUniversitas();
    DeserializeOwlCareKit();
}

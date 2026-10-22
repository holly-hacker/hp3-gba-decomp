#include "combat_fighter.h"
#include "overworld/room.h"

// Room id the overworld warps to after a battle defeat, indexed by
// g_abQuestEventState[QUEST_DEFEAT_WARP_SELECTOR] (set by the
// SetDefeatWarpSelector room-script opcode). Read by CheckBattleDefeat.
const u32 g_aDefeatWarpRoomId[20] = {
    RoomLeakyCauldronHarrysRoom,        // 0
    RoomHogwartsExpressPassengerCar,    // 1
    RoomHospitalWing,                   // 2
    RoomTransfigurationClassroomMaze,   // 3
    RoomPotionsClassroomMaze,           // 4
    RoomHagridsGardenMaze,              // 5
    RoomRooftop,                        // 6
    RoomShriekingShackPath,             // 7
    RoomHogwartsGroundsWhompingWillow,  // 8
    RoomShriekingShackInterior,         // 9
    RoomShriekingShackPath2,            // 10
    RoomShriekingShackPath3,            // 11
    RoomShriekingShackPath4,            // 12
    RoomShriekingShackPath5,            // 13
    RoomShriekingShackPath6,            // 14
    RoomLeakyCauldronCellar2,           // 15
    RoomLeakyCauldronCellar1,           // 16
    RoomPathToHagridsHut,               // 17
    RoomHogwartsExpressBaggageCar,      // 18
    RoomRooftop,                        // 19
};

#include "types.h"
#include "battle/battle.h"
#include "gen/graphics/battle.h"

// Floor and wall graphic blobs of the battle background, indexed by g_bCurrentRoomId
// (docs/formats/graphic_blob.md).
const BattleBackgroundPair g_aBattleBackgroundPairs[55] = {
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 0: defense_against_the_dark_arts_classroom
    { (void *)gBattleFloor02, (void *)gBattleWall02 }, // 1: potions_classroom
    { (void *)gBattleFloor03, (void *)gBattleWall03 }, // 2: potions_classroom_maze
    { (void *)gBattleFloor04, (void *)gBattleWall04 }, // 3: transfiguration_classroom
    { (void *)gBattleFloor05, (void *)gBattleWall05 }, // 4: transfiguration_classroom_maze
    { (void *)gBattleFloor06, (void *)gBattleWall06 }, // 5: hogwarts_express_baggage_car
    { (void *)gBattleFloor06, (void *)gBattleWall06 }, // 6: hogwarts_express_passenger_car
    { (void *)gBattleFloor06, (void *)gBattleWall06 }, // 7: hogwarts_express_buffet_car
    { (void *)gBattleFloor07, (void *)gBattleWall07 }, // 8: hogwarts_grounds_castle_doors
    { (void *)gBattleFloor07, (void *)gBattleWall07 }, // 9: hogwarts_grounds_boathouse
    { (void *)gBattleFloor07, (void *)gBattleWall07 }, // 10: hogwarts_grounds_greenhouses
    { (void *)gBattleFloor07, (void *)gBattleWall07 }, // 11: hagrids_hut
    { (void *)gBattleFloor08, (void *)gBattleWall08 }, // 12: hagrids_garden_maze
    { (void *)gBattleFloor07, (void *)gBattleWall07 }, // 13: hogwarts_grounds_lake
    { (void *)gBattleFloor07, (void *)gBattleWall07 }, // 14: path_to_hagrids_hut
    { (void *)gBattleFloor07, (void *)gBattleWall07 }, // 15: hogwarts_grounds_whomping_willow
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 16: entrance_hall
    { (void *)gBattleFloor04, (void *)gBattleWall04 }, // 17: great_hall
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 18: hogwarts_dungeons
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 19: second_floor
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 20: third_floor
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 21: fourth_floor
    { (void *)gBattleFloor10, (void *)gBattleWall10 }, // 22: fifth_floor
    { (void *)gBattleFloor10, (void *)gBattleWall10 }, // 23: sixth_floor
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 24: seventh_floor
    { (void *)gBattleFloor11, (void *)gBattleWall11 }, // 25: rooftop
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 26: lupins_office
    { (void *)gBattleFloor12, (void *)gBattleWall12 }, // 27: staff_room
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 28: gryffindor_boys_dormitory
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 29: gryffindor_common_room
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 30: grand_staircase
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 31: portrait_room
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 32: portrait_room_passage
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 33: hospital_wing
    { (void *)gBattleFloor13, (void *)gBattleWall13 }, // 34: library
    { (void *)gBattleFloor13, (void *)gBattleWall13 }, // 35: library_2
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 36: fred_and_georges_shop
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 37: wizard_card_collectors_club
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 38: leaky_cauldron_cellar_1
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 39: leaky_cauldron_cellar_2
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 40: leaky_cauldron_hallway
    { (void *)gBattleFloor14, (void *)gBattleWall14 }, // 41: leaky_cauldron_harrys_room
    { (void *)gBattleFloor09, (void *)gBattleWall09 }, // 42: leaky_cauldron_main
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 43: shrieking_shack_interior
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 44: shrieking_shack_path
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 45: shrieking_shack_path_2
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 46: shrieking_shack_path_3
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 47: shrieking_shack_path_4
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 48: shrieking_shack_path_5
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 49: shrieking_shack_path_6
    { (void *)gBattleFloor05, (void *)gBattleWall05 }, // 50: diagon_alley_test_map1
    { (void *)gBattleFloor01, (void *)gBattleWall01 }, // 51: diagon_alley_test_map_2
    { (void *)gBattleFloor12, (void *)gBattleWall12 }, // 52: diagon_alley_test_map_3
    { (void *)gBattleFloor08, (void *)gBattleWall08 }, // 53: diagon_alley_test_map_4
    { (void *)gBattleFloor03, (void *)gBattleWall03 }, // 54: diagon_alley_test_map_5
};

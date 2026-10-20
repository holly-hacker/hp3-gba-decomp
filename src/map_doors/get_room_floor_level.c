#include "types.h"
#include "map_doors.h"

// Ranks a room by castle floor, for HandlePortraitDoorTouch to pick the
// direction of the portrait passage walk. second_floor (19) to seventh_floor
// (24) keep their ids, the ground-floor rooms entrance_hall (16), great_hall
// (17) and portrait_room (31) rank 18, and hogwarts_dungeons (18) ranks 17,
// below them.
s32 GetRoomFloorLevel(s32 roomId)
{
    if (roomId == 31 || roomId == 16 || roomId == 17)
        return 18;
    if (roomId == 18)
        return 17;
    return roomId;
}

#include "types.h"
#include "camera.h"
#include "commands.h"
#include "hero.h"
#include "hw/io_regs.h"
#include "overworld/room.h"
#include "scroll.h"

// Returns the scroll position that centres camera focus slot 0 on screen (raised by the camera Y
// offsets), clamped to the room's scroll bounds.
IntPoint GetCameraTargetPosition(void)
{
    IntPoint position;
    IntPoint min;
    IntPoint max;
    s32 yOffset;

    yOffset = g_nCameraYOffset + (s8)g_abQuestEventState[QUEST_CAMERA_Y_OFFSET];
    GetCameraFocusPosition(&position, 0);
    position.x >>= 16;
    position.y >>= 16;
    position.x -= SCREEN_WIDTH / 2;
    position.y -= SCREEN_HEIGHT / 2 + yOffset;
    GetRoomScrollBounds(&min, &max, g_RoomSizePixels.dwWidth, g_RoomSizePixels.dwHeight);
    min.x += 9;
    min.y += 9;
    max.x -= SCREEN_WIDTH + 9;
    max.y -= SCREEN_HEIGHT + 9;

    if (position.x < min.x)
        position.x = min.x;
    else if (position.x >= max.x)
        position.x = max.x;
    if (position.y < min.y)
        position.y = min.y;
    else if (position.y >= max.y)
        position.y = max.y;
    return position;
}

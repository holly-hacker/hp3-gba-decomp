#include "flipbook.h"
#include "map.h"
#include "scroll.h"

// Ticks camera focus slot 0, the BG scroll and the room's tile animations.
void TickOverworldView(void)
{
    TickCameraFocus(0);
    UpdateOverworldCamera(0);
    TickRoomTileAnimations();
}

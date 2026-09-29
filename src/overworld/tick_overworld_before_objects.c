#include "types.h"
#include "overworld/overworld.h"

void TickOverworldBeforeObjects_candidate(void)
{
    TickCameraFocus_candidate(0);
    UpdateOverworldCamera_candidate(0);
    TickRoomTileAnimations_candidate();
}

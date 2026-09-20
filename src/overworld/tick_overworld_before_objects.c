#include "types.h"
#include "overworld.h"

void TickOverworldBeforeObjects_candidate(void)
{
    TickQueuedObjectMove_candidate(0);
    UpdateOverworldCamera_candidate(0);
    TickRoomTileAnimations_candidate();
}

#include "types.h"
#include "overworld/overworld.h"
#include "flipbook.h"
#include "map.h"
#include "scroll.h"

void TickOverworldBeforeActors_candidate(void)
{
    TickCameraFocus_candidate(0);
    UpdateOverworldCamera_candidate(0);
    TickRoomTileAnimations_candidate();
}

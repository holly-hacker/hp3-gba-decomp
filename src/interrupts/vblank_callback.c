#include "types.h"
#include "graphics/display.h"
#include "actor.h"
#include "hw/vblank.h"

// The default vblank callback installed by AgbMain.
void VBlankCallback(void)
{
    CommitQueuedActorTileUpdates();
    CommitBgTileAnimations();
}

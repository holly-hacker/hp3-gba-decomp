#include "types.h"
#include "graphics/display.h"
#include "graphics/object.h"
#include "hw/vblank.h"

// The default vblank callback installed by AgbMain.
void VBlankCallback(void)
{
    CommitQueuedObjectTileUpdates();
    CommitBgTileAnimations();
}

#include "char_block.h"
#include "actor.h"
#include "interrupts.h"

// The default vblank callback installed by AgbMain.
void VBlankCallback(void)
{
    CommitQueuedActorTileUpdates();
    CommitBgTileAnimations();
}

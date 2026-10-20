#include "actor.h"
#include "char_block.h"
#include "map.h"

void OverworldVBlankCallback(void)
{
    CommitQueuedActorTileUpdates();
    CommitBgTileAnimations();
}

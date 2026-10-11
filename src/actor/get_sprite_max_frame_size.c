#include "actor.h"

// Writes the largest frame width and height of a sprite record, in pixels, to dims[0]
// and dims[1].
void GetSpriteMaxFrameSize(const ActorAssetRecord *record, u32 *dims)
{
    ActorFrameData *frameData;

    frameData = record->pFrameData;
    dims[0] = frameData->bMaxFrameWidth;
    dims[1] = frameData->bMaxFrameHeight;
}

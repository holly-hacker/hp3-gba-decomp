#include "actor.h"

// Writes the pixel width and height of one frame of a sprite record to dims[0] and dims[1].
void GetSpriteFrameSize(const ActorAssetRecord *record, u32 *dims, u8 frame)
{
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;

    frameData = record->pFrameData;
    frameDesc = (ActorFrameDesc *)((u8 *)frameData->awFrameOffsets + frameData->awFrameOffsets[frame]);
    dims[0] = frameDesc->bWidth;
    dims[1] = frameDesc->bHeight;
}

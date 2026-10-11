#include "actor.h"

// Returns the ActorFrameTileCodec of one frame's tiles.
u32 GetFrameTileCodec(ActorFrameData *frameData, u16 frame)
{
    ActorFrameDesc *frameDesc;

    frameDesc = (ActorFrameDesc *)((u8 *)frameData->awFrameOffsets + frameData->awFrameOffsets[frame]);
    if (frameDesc->bCellCount & 0x20)
        return ActorFrameTileCodecRle;
    if (frameDesc->bCellCount & 0x40)
        return ActorFrameTileCodecLzRle;
    return ActorFrameTileCodecGammaLz;
}

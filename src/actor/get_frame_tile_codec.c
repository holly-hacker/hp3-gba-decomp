#include "actor.h"

// Returns the ActorFrameTileCodec of one frame's tiles.
u32 GetFrameTileCodec(ActorFrameData *frameData, u16 frame)
{
    ActorFrameDesc *frameDesc;

    frameDesc = ACTOR_FRAME_DESC(frameData, frame);
    if (frameDesc->bCellCount & 0x20)
        return ActorFrameTileCodecRle;
    if (frameDesc->bCellCount & 0x40)
        return ActorFrameTileCodecLzRle;
    return ActorFrameTileCodecGammaLz;
}

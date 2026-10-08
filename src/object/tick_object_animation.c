#include "graphics/object.h"

// Counts down the current frame's ticks. When they run out, an object with a
// command stream runs its next commands; one without cycles through every frame
// of its sprite record, reloading the counter from bAnimFrameDelay.
void TickObjectAnimation(Object *obj)
{
    u8 *cursor;
    u8 frame;
    ObjectFrameData *frameData;

    if (!(obj->dwFlags & ObjectFlagHasAnimation) || obj->anim.bAnimFrameCounter == 0
        || (obj->dwFlags & ObjectFlagAnimPaused))
        return;

    if (--obj->anim.bAnimFrameCounter != 0)
        return;

    cursor = obj->anim.pAnimFrameCursor;
    if (cursor == NULL) {
        obj->anim.bLastAnimFrameValue++;
        if (obj->anim.bLastAnimFrameValue >= ((ObjectFrameData *)obj->anim.pAnimTable->pFrameData)->wFrameCount)
            obj->anim.bLastAnimFrameValue = 0;

        frame = obj->anim.bLastAnimFrameValue;
        frameData = obj->anim.pAnimTable->pFrameData;
        if (frame == frameData->wFrameCount - 1 || frameData->wFrameCount == 1)
            obj->dwFlags |= ObjectFlagActionAnimDone;

        obj->anim.bAnimFrameCounter = obj->anim.bAnimFrameDelay;
        LoadObjectAnimFrameBounds(obj);
    }
    else if (!(obj->dwFlags & ObjectFlagActionAnimDone)) {
        obj->anim.pAnimFrameCursor = cursor + 2;
        RunObjectAnimCommands(obj);
        LoadObjectAnimFrameBounds(obj);
    }
}

#include "graphics/object.h"

// Switches to the given animation frame, reloading its cells when the frame changed
// or the object is flagged for a reload; always clears ObjectFlagActionAnimDone.
void SetObjectAnimFrame(Object *obj, u8 frameIndex)
{
    if (obj->bLastAnimFrameValue != frameIndex || (obj->dwFlags & ObjectFlagAnimFrameLoaded)) {
        obj->bLastAnimFrameValue = frameIndex;
        obj->bAnimFrameCounter = obj->bAnimFrameDelay;
        sub_080023B4(obj);
    }

    obj->dwFlags &= ~ObjectFlagActionAnimDone;
}

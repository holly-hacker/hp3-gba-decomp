#include "graphics/object.h"

// Switches to the given animation frame, reloading its cells when the frame changed
// or the object is flagged for a reload; always clears ObjectFlagActionAnimDone.
void SetObjectAnimFrame(Object *obj, u8 frameIndex)
{
    if (obj->anim.bLastAnimFrameValue != frameIndex || (obj->dwFlags & ObjectFlagAnimFrameLoaded)) {
        obj->anim.bLastAnimFrameValue = frameIndex;
        obj->anim.bAnimFrameCounter = obj->anim.bAnimFrameDelay;
        LoadObjectAnimFrameBounds(obj);
    }

    obj->dwFlags &= ~ObjectFlagActionAnimDone;
}

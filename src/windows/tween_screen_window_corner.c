#include "types.h"
#include "windows.h"
#include "windows_inline.h"

void TweenScreenWindowCorner(u32 windowId, u32 corner, s32 x, s32 y, u16 frames)
{
    TweenScreenWindowCornerInline(windowId, corner, x, y, frames);
}

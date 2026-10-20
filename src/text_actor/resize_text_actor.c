#include "types.h"
#include "font.h"
#include "vram.h"
#include "text_actor.h"

// Sizes a text actor for pText and reallocates its VRAM tiles when the size
// in tiles changed.
void ResizeTextActor(Actor *pActor, const u8 *pText)
{
    u16 width;
    u16 height;
    u16 pixelCount;
    s32 size;

    width = MeasureMacroString(pText);
    height = GetTextHeight(pText);
    size = width;
    if (width > TEXT_ACTOR_MAX_WIDTH)
        size = TEXT_ACTOR_MAX_WIDTH;
    TEXT_ACTOR_WIDTH(pActor) = size;
    size = height;
    if (height > TEXT_ACTOR_MAX_HEIGHT)
        size = TEXT_ACTOR_MAX_HEIGHT;
    TEXT_ACTOR_HEIGHT(pActor) = size;

    // Strips are 32 pixels wide, sized from the unclamped width.
    size = width + 31;
    size /= 32;
    pActor->anim.unk_DC.wOamStripCount = size;
    width = size * 4;
    height = (height + 7) / 8;
    pixelCount = width * height * 64;
    if (pixelCount != pActor->wVramPixelCount)
    {
        if (pActor->wVramPixelCount != 0)
            FreeObjVramTileAllocation(pActor->wVramTileAllocId, pActor->wVramPixelCount, pActor->oam.bpp8);
        pActor->wVramPixelCount = pixelCount;
        AllocActorVramTiles(pActor, NULL);
    }
}

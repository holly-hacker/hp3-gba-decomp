#include "types.h"
#include "font.h"
#include "text_actor.h"

// Unreferenced. Places a text actor at (x, y), aligned by TextActorAlign
// flags measured against pText.
void SetTextActorAlignedPosition(Actor *pActor, const u8 *pText, s16 x, s16 y, u32 align)
{
    if (align & TextActorAlignCenterX)
        x -= (s32)(MeasureMacroString(pText) + 1) / 2;
    if (align & TextActorAlignRight)
        x -= (s32)MeasureMacroString(pText);
    if (align & TextActorAlignCenterY)
        y -= (s32)(GetTextHeight(pText) + 1) / 2;
    if (align & TextActorAlignBottom)
        y -= (s32)GetTextHeight(pText);
    SnapActorPosition(pActor, x << 16, y << 16);
}

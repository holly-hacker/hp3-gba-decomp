#include "types.h"
#include "audio.h"
#include "display.h"
#include "input.h"
#include "linear_cutscene.h"
#include "text.h"

// A advances the text; the object is shown while more text remains, and A on
// the last page leaves the cutscene.
void UpdateLinearCutscene(void)
{
    if (g_wKeysPressed & KeyA)
    {
        PlaySoundById(1);

        if (*g_pLinearCutsceneText != 0)
        {
            ClearBgTilemap(1);
            DrawTextLines(1, 2, 0x7A, 0xE6, 0x24, &g_pLinearCutsceneText, 0);

            if (*g_pLinearCutsceneText != 0)
                g_pLinearCutsceneObject->dwFlags |= ObjectFlagVisible;
            else
                g_pLinearCutsceneObject->dwFlags &= ~ObjectFlagVisible;
        }
        else
            sub_0801D6DC();
    }
}

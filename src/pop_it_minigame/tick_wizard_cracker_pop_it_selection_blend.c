#include "types.h"
#include "screen_transitions.h"
#include "pop_it_minigame.h"

// Pulses the alpha blend of the selected crackers, holding 24 frames at
// each end of the pulse.
void TickWizardCrackerPopItSelectionBlend(void)
{
    s32 frame;

    frame = ++g_pWizardCrackerPopIt->nFrameCounter;
    if (g_nWizardCrackerPopItBlendHoldFrame == -1 || frame - g_nWizardCrackerPopItBlendHoldFrame > 24)
    {
        if (frame & 3)
        {
            g_pWizardCrackerPopIt->bBlendStep++;
            g_pWizardCrackerPopIt->bBlendStep %= 32;
            if (((g_pWizardCrackerPopIt->bBlendStep + 1) & 0xF) == 0)
                g_nWizardCrackerPopItBlendHoldFrame = g_pWizardCrackerPopIt->nFrameCounter;
            else
                g_nWizardCrackerPopItBlendHoldFrame = -1;

            if (g_pWizardCrackerPopIt->bBlendStep < 16)
                SetAlphaBlendCoefficients(g_pWizardCrackerPopIt->bBlendStep, 16 - g_pWizardCrackerPopIt->bBlendStep);
            else
                SetAlphaBlendCoefficients(32 - g_pWizardCrackerPopIt->bBlendStep, g_pWizardCrackerPopIt->bBlendStep - 16);
        }
    }
}

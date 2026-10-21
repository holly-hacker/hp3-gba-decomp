#include "types.h"
#include "actor.h"
#include "pop_it_minigame.h"

// Starts the idle animation of the kind's current variant.
void SetWizardCrackerPopItCrackerAnim(Actor *pCracker, u32 kind)
{
    const u8 *pAnim;

    switch (kind)
    {
    case WizardCrackerPopItKindWrapped:
        pAnim = g_aWizardCrackerPopItWrappedAnims[g_pWizardCrackerPopIt->aKinds[kind].dwVariant];
        break;
    case WizardCrackerPopItKindTriangle:
        pAnim = g_aWizardCrackerPopItTriangleAnims[g_pWizardCrackerPopIt->aKinds[kind].dwVariant];
        break;
    case WizardCrackerPopItKindOval:
        pAnim = g_aWizardCrackerPopItOvalAnims[g_pWizardCrackerPopIt->aKinds[kind].dwVariant];
        break;
    case WizardCrackerPopItKindDumbbell:
        pAnim = g_aWizardCrackerPopItDumbbellAnims[g_pWizardCrackerPopIt->aKinds[kind].dwVariant];
        break;
    case WizardCrackerPopItKindSweet:
        pAnim = g_aWizardCrackerPopItSweetAnims[g_pWizardCrackerPopIt->aKinds[kind].dwVariant];
        break;
    default:
        pAnim = NULL;
        break;
    }

    SetActorAnimData(pCracker, &g_aWizardCrackerPopItCrackerAssets[kind], pAnim, 0);
}

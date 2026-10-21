#include "types.h"
#include "random.h"
#include "pop_it_minigame.h"

static inline void ApplyWizardCrackerPopItKindPending(s32 kind)
{
    s32 timer;

    switch (kind)
    {
    case WizardCrackerPopItKindTriangle:
        timer = Mt19937RandRange(80, 120);
        break;
    case WizardCrackerPopItKindOval:
        timer = Mt19937RandRange(60, 90);
        break;
    case WizardCrackerPopItKindWrapped:
    case WizardCrackerPopItKindDumbbell:
    case WizardCrackerPopItKindSweet:
        timer = Mt19937RandRange(40, 65);
        break;
    default:
        timer = 0;
        break;
    }

    SetWizardCrackerPopItKindVariant(kind, g_pWizardCrackerPopIt->aKinds[kind].dwPendingVariant, timer);
    g_pWizardCrackerPopIt->aKinds[kind].dwPendingVariant = 0xFF;
}

// When a kind's timer runs out, either replays its idle animation or
// switches it to another variant.
void TickWizardCrackerPopItKinds(void)
{
    s32 kind;

    for (kind = 0; kind < WIZARD_CRACKER_POP_IT_KINDS; kind++)
    {
        if (--g_pWizardCrackerPopIt->aKinds[kind].nTimer != -1)
            continue;

        if (g_pWizardCrackerPopIt->aKinds[kind].dwPendingVariant != 0xFF)
        {
            ApplyWizardCrackerPopItKindPending(kind);
        }
        else if (Mt19937RandMax(2))
        {
            AnimateWizardCrackerPopItKind(kind, 1);
        }
        else
        {
            switch (kind)
            {
            case WizardCrackerPopItKindWrapped:
                // Turns through a 12-tick transition variant.
                if (g_pWizardCrackerPopIt->aKinds[kind].dwVariant == 0)
                    g_pWizardCrackerPopIt->aKinds[kind].dwPendingVariant = 2;
                else if (g_pWizardCrackerPopIt->aKinds[kind].dwVariant == 2)
                    g_pWizardCrackerPopIt->aKinds[kind].dwPendingVariant = 0;
                SetWizardCrackerPopItKindVariant(kind, g_pWizardCrackerPopIt->aKinds[kind].dwVariant + 1, 12);
                continue;
            case WizardCrackerPopItKindTriangle:
            case WizardCrackerPopItKindDumbbell:
            case WizardCrackerPopItKindSweet:
                g_pWizardCrackerPopIt->aKinds[kind].dwVariant ^= 1;
                break;
            case WizardCrackerPopItKindOval:
                g_pWizardCrackerPopIt->aKinds[kind].dwVariant = Mt19937RandMax(2);
                break;
            }
            ApplyWizardCrackerPopItKindPending(kind);
        }
    }
}

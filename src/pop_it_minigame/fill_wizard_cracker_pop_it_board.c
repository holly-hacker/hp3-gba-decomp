#include "types.h"
#include "actor.h"
#include "math.h"
#include "random.h"
#include "pop_it_minigame.h"

// Deals a full board of random crackers from the first kindCount kinds.
void FillWizardCrackerPopItBoard(s32 kindCount)
{
    u8 dealtKinds;
    s32 i;
    u32 kind;
    s32 row;
    s32 column;

    dealtKinds = 0;
    for (i = 0; i < WIZARD_CRACKER_POP_IT_COLUMNS; i++)
        g_pWizardCrackerPopIt->abColumnHeights[i] = WIZARD_CRACKER_POP_IT_ROWS;
    g_pWizardCrackerPopIt->nCursorColumn = 0;
    g_pWizardCrackerPopIt->nCursorRow = 0;
    g_pWizardCrackerPopIt->nColumnCount = WIZARD_CRACKER_POP_IT_COLUMNS;

    for (i = 0; i < WIZARD_CRACKER_POP_IT_KINDS; i++)
    {
        g_pWizardCrackerPopIt->aKinds[i].nTimer = Mt19937RandRange(20, 40);
        g_pWizardCrackerPopIt->aKinds[i].dwVariant = 0;
        g_pWizardCrackerPopIt->aKinds[i].dwPendingVariant = 0xFF;
        g_pWizardCrackerPopIt->aKinds[i].nUnk10 = -1;
    }

    for (i = 0; i < ARRAY_COUNT(g_pWizardCrackerPopIt->apCrackers); i++)
    {
        kind = Mt19937RandMax(kindCount - 1);
        if (g_pWizardCrackerPopIt->aKinds[kind].nUnk10 == -1)
        {
            g_pWizardCrackerPopIt->aKinds[kind].nUnk10 = dealtKinds % 5 + 2;
            dealtKinds++;
        }

        row = iwramDivideSignedRemainder(i, WIZARD_CRACKER_POP_IT_COLUMNS, &column);
        g_pWizardCrackerPopIt->aKinds[kind].dwCount++;
        g_pWizardCrackerPopIt->apCrackers[i] = SpawnWizardCrackerPopItCracker(kind, column * 24 + 12, row * 24);
        g_pWizardCrackerPopIt->apCrackers[i]->bActorPoolAuxSlot = kind;
        g_pWizardCrackerPopIt->apCrackers[i]->bDrawFlags |= ActorDrawFlagShareTiles;
        g_pWizardCrackerPopIt->apCrackers[i]->wActionVariant = i;
        kind++;
        g_pWizardCrackerPopIt->aabCells[column][row] = WIZARD_CRACKER_POP_IT_CELL(kind);
    }
}

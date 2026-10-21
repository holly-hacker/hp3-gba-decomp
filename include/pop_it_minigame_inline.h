#pragma once

#include "types.h"
#include "actor.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "pop_it_minigame.h"

// TickWizardCrackerPopItCracker inlines these; the files that emit the
// out-of-line copies define the linkage macro as empty.
#ifndef SET_WIZARD_CRACKER_POP_IT_CRACKER_POP_ANIM_LINKAGE
#define SET_WIZARD_CRACKER_POP_IT_CRACKER_POP_ANIM_LINKAGE extern inline
#endif
#ifndef DRAW_WIZARD_CRACKER_POP_IT_SCORE_LINKAGE
#define DRAW_WIZARD_CRACKER_POP_IT_SCORE_LINKAGE extern inline
#endif

SET_WIZARD_CRACKER_POP_IT_CRACKER_POP_ANIM_LINKAGE void SetWizardCrackerPopItCrackerPopAnim(Actor *pCracker)
{
    if (pCracker->wCharacterId_candidate == WizardCrackerPopItKindWrapped)
        SetActorAnimData(pCracker, &g_aWizardCrackerPopItCrackerAssets[pCracker->wCharacterId_candidate],
                         g_aWizardCrackerPopItWrappedPopAnims[g_pWizardCrackerPopIt->aKinds[pCracker->wCharacterId_candidate].dwVariant / 2],
                         0);
    else
        SetActorAnimData(pCracker, &g_aWizardCrackerPopItPopAssets[pCracker->wCharacterId_candidate],
                         g_aWizardCrackerPopItPopAnims[pCracker->wCharacterId_candidate - WizardCrackerPopItKindTriangle], 0);
}

DRAW_WIZARD_CRACKER_POP_IT_SCORE_LINKAGE void DrawWizardCrackerPopItScore(void)
{
    FillBgTilemapRect(3, 0, 18, 15, 2, 0);
    SetTextMacro1Number(g_pWizardCrackerPopIt->dwScore);
    DrawStringAligned(0x41, 6, 0x90, GetDialogText(0xA5D), 0);  // "Score: @1"
}

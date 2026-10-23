#include "types.h"
#include "actor.h"
#include "pop_it_minigame.h"

Actor *SpawnWizardCrackerPopItCracker(u32 kind, s32 x, s32 y)
{
    Actor *pCracker;

    pCracker = SpawnActor(WizardCrackerPopItActorType_Cracker, x, y, NULL);
    pCracker->oam.paletteNum = g_aWizardCrackerPopItPalettes[kind].bIdleSlot;
    SetWizardCrackerPopItCrackerAnim(pCracker, kind);
    pCracker->wSubtype = kind;
    pCracker->pfnTick = TickWizardCrackerPopItCracker;
    SetActorActionState(pCracker, 0);
    pCracker->oam.priority = 1;
    pCracker->moveTarget = pCracker->pos;
    return pCracker;
}

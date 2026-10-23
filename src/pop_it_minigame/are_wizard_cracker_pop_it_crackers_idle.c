#include "types.h"
#include "actor.h"
#include "pop_it_minigame.h"

u32 AreWizardCrackerPopItCrackersIdle(void)
{
    Actor *pActor;
    Actor *pNext;

    for (pActor = (Actor *)g_ActiveActorListState.pTail; pActor != NULL; pActor = pNext)
    {
        pNext = (Actor *)pActor->node.pPrev;
        if (pActor->wActorType == WizardCrackerPopItActorType_Cracker && pActor->bActionState != 0)
            return 0;
    }

    return 1;
}

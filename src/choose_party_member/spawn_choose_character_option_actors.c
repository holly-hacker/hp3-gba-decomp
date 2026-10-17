#include "types.h"
#include "actor.h"
#include "choose_party_member.h"
#include "overworld/overworld.h"
#include "palette.h"
#include "hero.h"

void SpawnChooseCharacterOptionActors(void)
{
    s32 i;
    Actor *pActor;

    for (i = 0; i < CHOOSE_CHARACTER_OPTION_COUNT; i++)
    {
        pActor = AllocActorOfType(0x17);
        g_ChooseCharacterState.apOptionActors[i] = pActor;
        pActor->wCharacterId_candidate = i;
        pActor->anim.bAnimFrameDelay = 0;
        pActor->oam.objMode = 0;
        pActor->oam.bpp8 = 0;
        pActor->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasSpriteCells;
        pActor->oam.priority = 0;
        pActor->bDepthSortBias = 0x80;
        SetActorAssetRecord(pActor, &g_aPartyWalkAssets[5 + i]);
        AttachActorPalette(pActor, g_aPartyWalkAssets[5 + i].pPalette);
        SetActorAnimFrame(pActor, 0);

        if (!((g_aabChooseCharacterOptionRows[g_ChooseCharacterState.bStageRow][3] >> i) & 1))
            g_ChooseCharacterState.apOptionActors[i]->dwFlags &= ~ActorFlagVisible;
    }
}

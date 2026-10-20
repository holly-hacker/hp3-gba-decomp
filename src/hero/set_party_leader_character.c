#include "types.h"
#include "actor.h"
#include "hero.h"
#include "palette.h"
#include "overworld/room_script.h"
#include "overworld/overworld.h"

// Also selects the new character's first field spell.
void SetPartyLeaderCharacter(u8 characterId)
{
    g_bPartyCharId0 = characterId;
    g_pPlayerActor->dwFlags &= ~ActorFlagVisible;
    g_pPlayerActor->wCharacterId_candidate = characterId;
    if (g_pPlayerActor->pPendingPalette == NULL)
        ReleaseActorPalette(g_pPlayerActor);
    AttachActorPalette(g_pPlayerActor, g_aPartyWalkAssets[characterId].pPalette);
    SetActorAssetRecord(g_pPlayerActor, &g_aPartyWalkAssets[characterId]);
    SetActorAnimFrame(g_pPlayerActor, g_abPartyStandFrames[g_pPlayerActor->bFacing]);
    g_bSelectedFieldSpell = GetPartyMasterStatsSlot_candidate(characterId) * 3;
    RefreshFieldSpellHud(g_pFieldSpellIconActor);
    g_pPlayerActor->dwFlags |= ActorFlagVisible;
}

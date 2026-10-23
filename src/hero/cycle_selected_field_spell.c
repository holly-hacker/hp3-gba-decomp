#include "types.h"
#include "actor.h"
#include "combat.h"
#include "hero.h"
#include "hero_inline.h"
#include "overworld/room_script.h"
#include "sound.h"

// Steps g_bSelectedFieldSpell to the previous (direction 0) or next (1) field spell, or
// back to the first (2), skipping spells whose character is not in the party or has not
// learned them yet. When the spell's character is a follower, that follower takes the
// lead.
void CycleSelectedFieldSpell(Actor *pLeader, u8 direction)
{
    s32 aPartyPosBySlot[3];  // by stats slot: 0 leader, 1-2 follower, -1 not in the party
    s32 i;
    s32 learned;
    s32 present;

    for (i = 0; i < 3; i++)
        aPartyPosBySlot[i] = -1;

    aPartyPosBySlot[GetCharacterFighterType(g_pPlayerActor->wSubtype)] = 0;
    if (g_pFollowerActor0 != NULL)
        aPartyPosBySlot[GetCharacterFighterType(g_pFollowerActor0->wSubtype)] = 1;
    if (g_pFollowerActor1 != NULL)
        aPartyPosBySlot[GetCharacterFighterType(g_pFollowerActor1->wSubtype)] = 2;

    do
    {
        switch ((s8)direction)
        {
        case 1:
            if (++g_bSelectedFieldSpell > FIELD_SPELL_COUNT - 1)
                g_bSelectedFieldSpell = 0;
            break;
        case 0:
            if (--g_bSelectedFieldSpell > FIELD_SPELL_COUNT - 1)
                g_bSelectedFieldSpell = FIELD_SPELL_COUNT - 1;
            break;
        case 2:
            g_bSelectedFieldSpell = 0;
            break;
        }
        present = aPartyPosBySlot[g_aFieldSpells[g_bSelectedFieldSpell].bFighterType] != -1;
        if (!present)
            continue;
        learned = 0;
        if (g_aPartyMasterStats[g_aFieldSpells[g_bSelectedFieldSpell].bFighterType].stats.bKnownSpellCount
            >= g_aFieldSpells[g_bSelectedFieldSpell].bMinKnownSpells)
            learned = 1;
    } while (!present || !learned);

    switch (aPartyPosBySlot[g_aFieldSpells[g_bSelectedFieldSpell].bFighterType])
    {
    case 0:
        PlaySoundById(4);
        break;
    case 1:
        PlaySoundById(7);
        SwapPartyMemberCharacters(pLeader, g_pFollowerActor0);
        g_bPartyCharId1 = g_pFollowerActor0->wSubtype;
        if (g_pFollowerActor1 != NULL)
            g_bPartyCharId2 = g_pFollowerActor1->wSubtype;
        break;
    case 2:
        PlaySoundById(7);
        SwapPartyMemberCharacters(pLeader, g_pFollowerActor1);
        if (g_pFollowerActor0 != NULL)
            g_bPartyCharId1 = g_pFollowerActor0->wSubtype;
        g_bPartyCharId2 = g_pFollowerActor1->wSubtype;
        break;
    }

    RefreshFieldSpellHud(g_pFieldSpellIconActor);
}

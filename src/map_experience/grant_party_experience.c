#include "types.h"
#include "actor.h"
#include "combat_end.h"
#include "font.h"
#include "hero.h"
#include "map_experience.h"
#include "sound.h"
#include "text.h"
#include "text_actor.h"

void GrantPartyExperience(u32 xp)
{
    u8 aCharIds[3];
    IntPoint pos;
    const u8 *pText;
    u32 count;
    u32 i;
    Actor *pTextActor;

    count = 1;
    aCharIds[0] = g_bPartyCharId0;
    if (g_bPartyCharId1 != 0xFF)
    {
        count = 2;
        aCharIds[1] = g_bPartyCharId1;
        if (g_bPartyCharId2 != 0xFF)
        {
            count = 3;
            aCharIds[2] = g_bPartyCharId2;
        }
    }

    for (i = 0; i < count; i++)
    {
        // Character ids above 4 share the stats of id - 5.
        if (aCharIds[i] > 4)
            aCharIds[i] -= 5;

        // Each member's popup sits 8 pixels below the previous one.
        GetActorAnchor(g_pPlayerActor, 0, &pos);
        pos.x += (s16)(g_pPlayerActor->pos.x >> 16);
        pos.y += (s16)(g_pPlayerActor->pos.y >> 16) + i * 8;
        SelectTextFont(7, 0, 0);

        // The popup rises 2 pixels per tick for 25 ticks, then TickExperiencePopup removes it.
        if (GrantPartyMemberXp(aCharIds[i], xp) != 0)
        {
            PlayJingle(0x1B);
            pText = GetDialogText(0x52E);  // "Level Up!"
            pTextActor = SpawnUnslottedTextActor(&pText);
            SetTextActorCenterPosition_candidate(pTextActor, (s16)pos.x, (s16)pos.y);
            pTextActor->oam.priority = 0;
            pTextActor->oam.paletteNum = 2;
            pTextActor->pfnTick = TickExperiencePopup;
            pTextActor->dwStateTimer = 25;
            pTextActor->vel.y = -0x20000;
        }
        else
        {
            SetTextMacro1Number(xp);
            pText = GetDialogText(0x52D);  // "@1 Exp!"
            pTextActor = SpawnUnslottedTextActor(&pText);
            SetTextActorCenterPosition_candidate(pTextActor, (s16)pos.x, (s16)pos.y);
            pTextActor->oam.priority = 0;
            pTextActor->oam.paletteNum = 2;
            pTextActor->pfnTick = TickExperiencePopup;
            pTextActor->dwStateTimer = 25;
            pTextActor->vel.y = -0x20000;
        }
    }
}

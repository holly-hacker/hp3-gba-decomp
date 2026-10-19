#include "types.h"
#include "actor.h"
#include "combat_fighter.h"
#include "combat_gauge.h"
#include "font.h"
#include "text.h"
#include "text_actor.h"
#include "combat.h"

// Floats a number in the given font color over a fighter, bobbing a few times
// before it disappears (TickFloatingDamageNumber). A damage of 0 without
// showZero reads "Miss!". Damage (colors other than 6 and 13, the MP and HP
// restore colors) also spawns an SP gauge.
void ShowFloatingDamageNumber(s32 damage, s32 color, s32 fighterIndex, s32 showZero)
{
    Actor *fighterActor;
    IntPoint pos;
    const u8 *text;
    Actor *textActor;

    fighterActor = g_pFightState->pFighters[fighterIndex].pActor;
    GetActorAnchor(fighterActor, 0, &pos);
    pos.x += (s16)(fighterActor->pos.x >> 16);
    pos.y += (s16)(fighterActor->pos.y >> 16);
    SelectTextFont(7, color, 0);
    if (damage == 0 && showZero == 0)
    {
        text = GetDialogText(0x8F8);  // "Miss!"
        SetTextMacro1String(text);
    }
    else
    {
        SetTextMacro1Number(damage);
    }

    text = GetDialogText(0x8F7);  // "@1"
    textActor = SpawnUnslottedTextActor(&text);
    SetTextActorCenterPosition_candidate(textActor, (s16)pos.x, (s16)pos.y);
    textActor->oam.priority = 0;
    textActor->pfnTick = TickFloatingDamageNumber;
    textActor->dwStateTimer = 16;
    textActor->wTimedMoveTicks = 3;
    SetActorOrbitY(textActor, 0x76, 0xA00, 12);
    if (damage != 0 && color != 13 && color != 6)
        SpawnSpGauge(fighterIndex, damage);
}

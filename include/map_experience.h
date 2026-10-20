#pragma once

#include "types.h"
#include "actor.h"

// Gives every party member xp, floating "@1 Exp!" or "Level Up!" over the player.
extern void GrantPartyExperience(u32 xp);
extern void TickExperiencePopup(Actor *pActor);

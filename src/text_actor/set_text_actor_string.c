#include "types.h"
#include "text_actor.h"

void SetTextActorString(Actor *pActor, const u8 *pText)
{
    DrawTextActorText(pActor, &pText);
}

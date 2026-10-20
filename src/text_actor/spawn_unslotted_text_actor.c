#include "types.h"
#include "text_actor.h"
#include "text_actor_inline.h"

Actor *SpawnUnslottedTextActor(const u8 **ppText)
{
    return AllocTextActor(ppText);
}

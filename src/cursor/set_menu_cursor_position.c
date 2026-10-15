#include "types.h"
#include "actor.h"
#include "cursor.h"

void SetMenuCursorPosition(Actor *pActor, s32 x, s32 y)
{
    SetActorPosition(pActor, x, y);
}

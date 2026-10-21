#include "types.h"
#include "actor.h"
#include "cursor.h"
#include "menu_icon.h"
#include "hedwig_minigame.h"
#include "owl_name_select.h"

void SpawnOwlNameSelectActors(void)
{
    Actor *pActor;

    pActor = SpawnMenuCursorActor(5);
    SetActorPosition(pActor, 80, 80);
    RegisterMenuIconActor(0, pActor);

    pActor = SpawnMenuCursorActor(5);
    pActor->oam.hFlip = 1;
    SetActorPosition(pActor, 160, 80);
    RegisterMenuIconActor(1, pActor);

    pActor = InitializeOwlActorSprite();
    SetActorPosition(pActor, 120, 96);
    RegisterMenuIconActor(2, pActor);
}

#include "types.h"
#include "actor.h"
#include "pscreen_folio_universitas.h"
#include "gen/graphics/overworld.h"

const u32 g_dwFolioUniversitasBg3Control = 0x3F03;
const u32 g_dwFolioUniversitasBg1Control = 0x3E0A;
const u32 g_dwFolioUniversitasBg0Control = 0x1D05;

#define ACTOR_GFX(name) { (void *)g##name##Tiles, (void *)g##name##Frames }

const ActorGfxRecord g_aFolioUniversitasActorGfx[6] = {
    ACTOR_GFX(FolioUniversitasCursor),
    ACTOR_GFX(ButtonPrompts),
    ACTOR_GFX(ActorSprite030),
    ACTOR_GFX(ActorSprite031),
    ACTOR_GFX(ActorSprite032),
    ACTOR_GFX(FolioUniversitasCountBadges),
};

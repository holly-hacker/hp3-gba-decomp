#include "types.h"
#include "actor.h"
#include "cheat_portraits.h"
#include "graphics/display.h"

void ShowCheatPortrait(void)
{
    if (g_CheatPortraitsState.pPortraitActor != NULL)
        FreeActor(g_CheatPortraitsState.pPortraitActor);

    g_CheatPortraitsState.pPortraitActor = SpawnActor(0, 0x64, 0x9E, NULL);
    g_CheatPortraitsState.pPortraitActor->oam.paletteNum = 0;

    QueueObjPaletteLoad((const u16 *)g_apPortraitTable[g_CheatPortraitsState.dwSelection].pPalette,
                        0, 0x100);
    SetActorAssetRecord(g_CheatPortraitsState.pPortraitActor,
                        &g_apPortraitTable[g_CheatPortraitsState.dwSelection]);
    SetActorAnimFrame(g_CheatPortraitsState.pPortraitActor, 0);
    g_CheatPortraitsState.pPortraitActor->oam.bpp8 = 1;
    g_CheatPortraitsState.pPortraitActor->oam.priority = 0;
}

#include "types.h"
#include "audio.h"
#include "display.h"
#include "io_regs.h"
#include "minigame_menu.h"
#include "object.h"
#include "overworld.h"
#include "room.h"
#include "room_script.h"
#include "vblank.h"

extern void sub_08024518(Object *pObject, u32 arg1);

typedef struct SpecialSceneEffectRecord {
    u32 dwOpcode;
    u8 bMode;
} SpecialSceneEffectRecord;

void RoomScriptOpPlaySpecialSceneEffect(SpecialSceneEffectRecord *pRecord)
{
    volatile u16 savedBlendControl;
    u32 i;
    const void *bgResource;

    switch (pRecord->bMode)
    {
    case 2:
        sub_0800A914();
        sub_0800A598(g_aSpecialSceneBg2, g_aSpecialSceneBgControls, 0);
        sub_0802B138();
        g_abQuestEventState[0x1d] = 0;
        break;
    case 0:
        sub_0800A914();
        bgResource = g_aSpecialSceneBg0;
        goto installBg;
    case 1:
        sub_0800A914();
        bgResource = g_aSpecialSceneBg1;
    installBg:
        sub_0800A598(bgResource, g_aSpecialSceneBgControls, 0);
        g_abQuestEventState[0x1d] = 1;
        g_aCameraEffects_candidate[0].bState = 0;
        g_aCameraEffects_candidate[0].dwFramesLeft = 0;
        g_aCameraEffects_candidate[0].dwRunForever = 0;
        break;
    case 3:
        savedBlendControl = REG_BLDCNT;
        PlaySoundById(0x45);
        for (i = 0; i <= 8; i++)
        {
            SetFadeToWhite(0x3f, ((i & 2) << 20) >> 16);
            WaitForVBlank();
        }
        g_abQuestEventState[0x1a] = 1;
        LoadEmbeddedPalette_candidate(g_aSpecialScenePalette, 0, 16);
        PlayMusicModule(9);
        for (i = 0; i <= 9; i++)
        {
            SetFadeToWhite(0x3f, ((i & 2) << 20) >> 16);
            WaitForVBlank();
        }
        REG_BLDCNT = savedBlendControl;
        REG_BLDY = 0;
        break;
    case 4:
        g_pPlayerObject->bFacing = 6;
        sub_08024518(g_pPlayerObject, 1);
        g_pPlayerObject->nVelX = 0xFFFDC71C;
        g_pPlayerObject->nVelY = 0x00011C72;
        break;
    case 5:
        g_pPlayerObject->bFacing = 2;
        sub_08024518(g_pPlayerObject, 1);
        g_pPlayerObject->nVelX = 0x000238E4;
        g_pPlayerObject->nVelY = 0xFFFEE38E;
        break;
    }
}

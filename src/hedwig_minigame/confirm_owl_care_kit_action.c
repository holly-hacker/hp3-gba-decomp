#include "types.h"
#include "actor.h"
#include "math.h"
#include "modes.h"
#include "save.h"
#include "sound.h"
#include "game_state.h"
#include "hedwig_minigame.h"

u32 ConfirmOwlCareKitAction(void)
{
    Actor *pOwl = g_OwlCareKitScreen.pOwl;
    s32 care;

    if (g_GameModeStackContext.dwModeState != 0)
        return 0;

    if (pOwl->bActionState == OwlStateIdle && g_OwlCareKitScreen.pCleaner == NULL)
    {
        switch (g_GameModeStackContext.dwModeScratchB)
        {
        case 0:
            ProcessOwlCareAction(0);
            break;
        case 1:
            ProcessOwlCareAction(1);
            break;
        case 2:
            ProcessOwlCareAction(2);
            break;
        case 3:
            ProcessOwlCareAction(3);
            break;
        case 4:
            ProcessOwlCareAction(4);
            break;
        case 5:
            ProcessOwlCareAction(5);
            break;
        case 6:
            // Mail: the owl only leaves when no care counter is too high.
            if (g_saveStateBlock.owlCareKit.abCareCounters[0] <= OWL_CARE_NEED_THRESHOLD
                && g_saveStateBlock.owlCareKit.abCareCounters[1] <= OWL_CARE_NEED_THRESHOLD
                && g_saveStateBlock.owlCareKit.abCareCounters[2] <= OWL_CARE_NEED_THRESHOLD
                && g_saveStateBlock.owlCareKit.abCareCounters[3] <= OWL_CARE_NEED_THRESHOLD
                && g_saveStateBlock.owlCareKit.abCareCounters[4] <= OWL_CARE_NEED_THRESHOLD
                && g_saveStateBlock.owlCareKit.abCareCounters[5] <= OWL_CARE_NEED_THRESHOLD)
            {
                SetOwlCageDoorAnim(1);
                SetOwlState(OwlStateMailDepart);
                pOwl->vel.x = FixedDivide((120 << 16) - pOwl->pos.x, 92 << 16);
                pOwl->oam.hFlip = (u32)pOwl->vel.x >> 31;
            }
            else
            {
                care = FindOwlNeediestCare();
                PlaySoundById(49);
                SetOwlState(g_aOwlCareActionStates[care].bNeedState);
            }
            break;
        case 7:
            PushGameMode_2(GameCubeLink, 1, 0);
            break;
        }
        return 1;
    }

    if (pOwl->bActionState == OwlStateMailDelivered)
        SetOwlState(OwlStateIdle);
    return 0;
}

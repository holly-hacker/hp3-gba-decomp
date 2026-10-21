#include "types.h"
#include "save.h"
#include "sound.h"
#include "game_state.h"
#include "hedwig_minigame.h"

// Performs a care action on the owl; nonzero if the owl accepted it.
u32 ProcessOwlCareAction(u32 action)
{
    u32 accepted;

    if (g_saveStateBlock.owlCareKit.abCareCounters[action] <= OWL_CARE_NEED_THRESHOLD)
        accepted = 1;
    else
        accepted = 0;

    if (action == 1)
        accepted = StartOwlCleaning();
    else if (accepted)
        g_saveStateBlock.owlCareKit.abCareCounters[action] /= 2;
    else
        g_saveStateBlock.owlCareKit.abCareCounters[action] -= g_saveStateBlock.owlCareKit.abCareCounters[action] / 8;

    if (accepted)
    {
        PlaySoundById(49);
        SetOwlState(g_aOwlCareActionStates[action].bCareState);
    }
    else
        SetOwlState(g_aOwlCareActionStates[action].bRefuseState);

    return accepted;
}

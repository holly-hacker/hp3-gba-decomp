#include "sound.h"
#include "input.h"
#include "hedwig_minigame.h"

void HandleOwlCareKitScreenTick(void)
{
    if (g_wKeysPressed & KeyA)
    {
        if (ConfirmOwlCareKitAction() != 0)
            PlaySoundById(1);
        else
            PlaySoundById(2);
    }
    else if (g_wKeysPressed & KeyB)
        HandleOwlCareKitCancel();
    else if (g_wKeysPressed & (KeyLeft | KeyRight))
    {
        PlaySoundById(0);
        StepOwlCareKitSelection();
    }

    ProcessOwlCareKitTick(g_OwlCareKitScreen.pOwl->bActionState <= 4);
    ProcessOwlCareKitTick(g_OwlCareKitScreen.pOwl->bActionState <= 4);
    UpdateOwlCareKitPanel();
    UpdateOwlDroppings();
    TickOwlCareKitBackground();
}

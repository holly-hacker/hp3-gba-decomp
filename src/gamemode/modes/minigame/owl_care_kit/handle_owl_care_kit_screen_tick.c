#include "types.h"
#include "graphics/audio.h"
#include "hw/input.h"
#include "minigame/owlcare.h"

void HandleOwlCareKitScreenTick(void)
{
    if (g_wKeysPressed & KeyA)
    {
        if (sub_08022134() != 0)
            PlaySoundById(1);
        else
            PlaySoundById(2);
    }
    else if (g_wKeysPressed & KeyB)
        sub_08022EE4();
    else if (g_wKeysPressed & (KeyLeft | KeyRight))
    {
        PlaySoundById(0);
        sub_08022F28();
    }

    ProcessOwlCareKitTick(g_OwlCareKitScreen.pOwl->bActionState <= 4);
    ProcessOwlCareKitTick(g_OwlCareKitScreen.pOwl->bActionState <= 4);
    sub_08021E80();
    sub_08022B40();
    sub_0802238C();
}

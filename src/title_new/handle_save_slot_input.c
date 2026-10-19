#include "types.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "default_menu.h"
#include "title.h"
#include "title_new.h"

u32 HandleSaveSlotInput(void)
{
    UpdateMenuScreen();

    if (g_wKeysPressed & KeyA)
    {
        PlaySoundById(1);
        g_bSaveSlotScreenResult = SaveSlotResultConfirmed;
        return 1;
    }

    if (g_wKeysPressed & KeyB)
    {
        PlaySoundById(2);
        g_bSaveSlotScreenResult = SaveSlotResultCancelled;
        PushGameMode_2(MainMenu, 0, g_PrevGameModeStackContext.dwModeScratchB);
    }
    else if (g_wKeysPressed & (KeyUp | KeyDown))
    {
        MoveSaveSlotCursor();
    }

    return 0;
}

#include "types.h"
#include "sound.h"
#include "graphics/display.h"
#include "modes.h"
#include "input.h"
#include "save.h"
#include "text.h"
#include "language_select.h"

// The languages form a 2x4 grid: index >> 2 is the column, index & 3 the row.
void UpdateLanguageSelect(void)
{
    u8 selected;

    if (g_GameModeStackContext.dwModeTimer != 0)
    {
        g_GameModeStackContext.dwModeTimer--;
    }
    else if (g_wKeysPressed & (KeyRight | KeyLeft | KeyUp | KeyDown))
    {
        PlaySoundById(0);
        selected = g_GameModeStackContext.dwModeScratchB;

        if (g_wKeysPressed & (KeyRight | KeyLeft))
            selected = selected < 4 ? selected + 4 : selected - 4;

        if (g_wKeysPressed & KeyUp)
            selected = (selected & 3) ? selected - 1 : selected + 3;

        if (g_wKeysPressed & KeyDown)
            selected = (selected & 3) == 3 ? selected - 3 : selected + 1;

        DrawLanguageSelectEntry(g_GameModeStackContext.dwModeScratchB, selected);
        g_GameModeStackContext.dwModeScratchB = selected;
        DrawLanguageSelectEntry(selected, selected);
        DrawLanguageSelectFlag(g_GameModeStackContext.dwModeScratchB);
    }
    else if ((g_wKeysPressed & KeyA)
             || ((g_wKeysPressed & KeyB) && g_PrevGameModeStackContext.dwCurrentGameMode != 0))
    {
        if (g_wKeysPressed & (KeyStart | KeyA))
        {
            PlaySoundById(1);
            SetLanguage(g_GameModeStackContext.dwModeScratchB);
            SetSaveLanguageFlag();
            DisableKrawall();
            SyncSaveHeaderIfDirty();
            EnableKrawall();
        }
        else
            PlaySoundById(2);

        if (g_PrevGameModeStackContext.dwCurrentGameMode == 0)
            PushGameMode(Startup);
        else
            PushGameMode(Options);
    }
}

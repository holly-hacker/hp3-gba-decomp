#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "input.h"
#include "main_menu.h"
#include "text.h"

static inline void DrawEntry(u32 entry, u32 selectedEntry)
{
    u32 slot;
    u32 color;

    // Load Game's row is skipped when it is unavailable.
    slot = entry;
    if (!g_MainMenuState.dwLoadGameAvailable && slot > 1)
        slot--;

    color = 0;
    if (entry == selectedEntry)
        color = 6;

    SetTextTargetFromBgControl_candidate(g_dwMainMenuBg1Control);
    SelectTextFont_candidate(2, color, -1);
    DrawStringAligned(slot * 0x30 + 0x118, 0x20, slot * 0xC + 0x58, GetDialogText(entry + 0x8CD), 0);
}

void MoveMainMenuCursor_candidate(void)
{
    u32 previous;

    previous = g_GameModeStackContext.dwModeScratchB_candidate;
    PlaySoundById(0);

    if (g_wKeysPressed & KeyUp)
    {
        g_GameModeStackContext.dwModeScratchB_candidate--;
        if (g_GameModeStackContext.dwModeScratchB_candidate == MainMenuLoadGame
            && !g_MainMenuState.dwLoadGameAvailable)
            g_GameModeStackContext.dwModeScratchB_candidate--;
        if (g_GameModeStackContext.dwModeScratchB_candidate > 3)
            g_GameModeStackContext.dwModeScratchB_candidate = 3;
    }
    else if (g_wKeysPressed & KeyDown)
    {
        g_GameModeStackContext.dwModeScratchB_candidate++;
        if (g_GameModeStackContext.dwModeScratchB_candidate == MainMenuLoadGame
            && !g_MainMenuState.dwLoadGameAvailable)
            g_GameModeStackContext.dwModeScratchB_candidate = MainMenuOptions;
        if (g_GameModeStackContext.dwModeScratchB_candidate > 3)
            g_GameModeStackContext.dwModeScratchB_candidate = 0;
    }

    DrawEntry(previous, g_GameModeStackContext.dwModeScratchB_candidate);
    DrawEntry(g_GameModeStackContext.dwModeScratchB_candidate, g_GameModeStackContext.dwModeScratchB_candidate);
    PositionMainMenuCursorObject_candidate(1);
}

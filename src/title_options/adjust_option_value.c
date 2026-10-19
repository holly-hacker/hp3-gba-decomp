#include "types.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "color.h"
#include "title_options.h"

void AdjustOptionValue(void)
{
    u32 value;

    value = g_OptionsState.adwValues[g_GameModeStackContext.dwModeScratchB];

    switch (g_GameModeStackContext.dwModeScratchB)
    {
    case OptionsRowSound:
        StepCursorLeftRightHeld(&value, 0, 10, 0, 0);
        SetSoundEffectVolume(value * 25);
        break;

    case OptionsRowMusic:
        StepCursorLeftRightHeld(&value, 0, 10, 0, 0);
        SetMusicVolume(value * 12, 0);
        break;

    case OptionsRowGamma:
        value = 1 - g_OptionsState.adwValues[OptionsRowGamma];
        if (value == 0)
            ApplyGammaRemapTable(g_abGammaNormalRemap);
        else
            ApplyGammaRemapTable(g_abGammaHighRemap);
        break;

#ifndef VERSION_JP
    case OptionsRowLanguage:
        return;
#endif
    }

    if (g_OptionsState.adwValues[g_GameModeStackContext.dwModeScratchB] != value)
    {
        g_OptionsState.adwValues[g_GameModeStackContext.dwModeScratchB] = value;
        DrawOptionValue(g_GameModeStackContext.dwModeScratchB, value);
        PlaySoundById(0);
    }
}

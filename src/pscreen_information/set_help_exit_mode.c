#include "pscreen_information.h"

void SetHelpExitMode(GameMode mode, s32 arg1, s32 arg2, s32 arg3)
{
    g_HelpState.dwExitMode = mode;
    g_HelpState.dwExitArg1 = arg1;
    g_HelpState.dwExitArg2 = arg2;
    g_HelpState.dwExitArg3 = arg3;
}

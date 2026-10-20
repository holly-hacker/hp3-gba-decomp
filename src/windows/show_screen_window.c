#include "types.h"
#include "background.h"
#include "windows.h"

void ShowScreenWindow(u32 windowId)
{
    SetDispcntFlag(g_awScreenWindowDispcntFlags[windowId]);
}

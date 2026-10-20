#include "types.h"
#include "background.h"
#include "windows.h"

void HideScreenWindow(u32 windowId)
{
    ClearDispcntFlag(g_awScreenWindowDispcntFlags[windowId]);
}

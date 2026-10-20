#include "types.h"
#include "background.h"
#include "hw/io_regs.h"
#include "windows.h"

// Sets the layers shown inside the window (its WININ byte) and outside every
// window (the low WINOUT byte), and shows the window.
void SetScreenWindowLayers(u32 windowId, u16 winIn, u16 winOut)
{
    if (windowId == 0)
    {
        REG_WININ = (REG_WININ & 0xFF00) | winIn;
        REG_WINOUT = (REG_WINOUT & 0xFF00) | winOut;
    }
    else if (windowId == 1)
    {
        REG_WININ = (REG_WININ_NONVOLATILE & 0xFF) | (winIn << 8);
        REG_WINOUT = (REG_WINOUT & 0xFF00) | winOut;
    }

    SetDispcntFlag(g_awScreenWindowDispcntFlags[windowId]);
}

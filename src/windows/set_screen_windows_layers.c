#include "types.h"
#include "hw/io_regs.h"
#include "windows.h"

// Sets both windows' inside layers and the low WINOUT byte (outside every window).
void SetScreenWindowsLayers(u16 win0In, u16 win1In, u16 winOut)
{
    REG_WININ = win0In | (win1In << 8);
    REG_WINOUT = (REG_WINOUT & 0xFF00) | winOut;
}

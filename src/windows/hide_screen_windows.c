#include "types.h"
#include "background.h"
#include "hw/io_regs.h"
#include "windows.h"

void HideScreenWindows(void)
{
    ClearDispcntFlag(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
}

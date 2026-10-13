#include "types.h"
#include "background.h"
#include "graphics/display.h"

void SetBgControl(u32 bg, u32 control)
{
    SetBgControlRegister(bg, control);
    SetDispcntFlag((u16)(0x100 << bg));
}

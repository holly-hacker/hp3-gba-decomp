#include "types.h"
#include "hw/mem.h"
#include "text.h"

// Selects the default language and allocates the buffer GetDialogText
// decompresses strings into.
void InitDialogTextEngine(void)
{
    SetLanguage(0);
    gDialogTextScratchBuf = AllocBlock(0x400);
}

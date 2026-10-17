#include "types.h"
#include "mem.h"
#include "sound.h"

// Copies the ROM images of the statically linked IWRAM and EWRAM sections
// (Krawall's mixer code and state among them) into RAM, then starts the
// audio engine. The section ends are masked down to their 24-bit offsets,
// which equal the sizes since both sections start at their region base.
void kramInstall(void)
{
    g_bUnk03005AC0 = 8;
    CopyMemory(g_KrawallIwramStart, g_KrawallIwramRomImage, (u32)g_KrawallIwramEnd & 0xFFFFFF);
    CopyMemory(g_KrawallEwramStart, g_KrawallEwramRomImage, (u32)g_KrawallEwramEnd & 0xFFFFFF);
    InitAudio();
}

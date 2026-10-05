#include "types.h"
#include "hw/mem.h"
#include "graphics/audio.h"

// Copies the ROM images of the statically linked IWRAM and EWRAM sections
// (Krawall's mixer code and state among them) into RAM, then starts the
// audio engine. The section ends are masked down to their 24-bit offsets,
// which equal the sizes since both sections start at their region base.
void kramInstall(void)
{
    g_bUnk03005AC0 = 8;
    CopyMemory(g_IwramSectionStart, g_IwramSectionRomImage, (u32)g_IwramSectionEnd & 0xFFFFFF);
    CopyMemory(g_EwramSectionStart, g_EwramSectionRomImage, (u32)g_EwramSectionEnd & 0xFFFFFF);
    InitAudio();
}

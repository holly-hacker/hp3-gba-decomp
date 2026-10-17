#include "types.h"
#include "background.h"
#include "buckbeak_minigame.h"

// Runs at the first vblank line: restores BG2 for the next frame.
void EndBuckbeakMinigameGroundScanline(u32 *pPayload0, u32 *pPayload1)
{
    SetBgMode(0);
    SetBgControlRegister(2, g_dwBuckbeakMinigameBg2GroundControl);
    RewriteBgControlRegisters();
    SetBgScroll(2, g_pBuckbeakMinigame->dwHeading.parts.wWhole * 3, 0x20);
}

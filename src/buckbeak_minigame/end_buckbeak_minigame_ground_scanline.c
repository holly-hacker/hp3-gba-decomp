#include "types.h"
#include "graphics/display.h"
#include "buckbeak_minigame.h"

// Runs at the first vblank line: restores BG2 for the next frame.
void EndBuckbeakMinigameGroundScanline(u32 *pPayload0, u32 *pPayload1)
{
    SetBgMode(0);
    SetBgControlRegister_candidate(2, g_dwBuckbeakMinigameBg2GroundControl);
    RewriteBgControlRegisters_candidate();
    SetBgScroll_candidate(2, g_pBuckbeakMinigame->dwHeading.parts.wWhole * 3, 0x20);
}

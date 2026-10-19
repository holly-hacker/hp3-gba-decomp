#include "types.h"
#include "background.h"
#include "interrupts.h"
#include "landmarks.h"

void ShowFirstUnusedHogwartsMapBackground(void)
{
    g_dwUnusedHogwartsMapShownBg = 0;
    SetBgScrollFixed(3, -8 << 16, 0);
    g_bForcePendingBgWritesFlush = 1;
    WaitForVBlankIntr();
    LoadBgGraphic(3, g_apUnusedHogwartsMapBackgrounds[g_dwUnusedHogwartsMapShownBg], 0x50, 0, 0, 0);
}

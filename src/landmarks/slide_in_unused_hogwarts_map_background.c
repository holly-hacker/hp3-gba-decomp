#include "types.h"
#include "background.h"
#include "interrupts.h"
#include "landmarks.h"
#include "modes.h"
#include "random.h"

// Moves the previously shown background to BG3, then slides the selected entry's background
// in on BG2 from a random side.
void SlideInUnusedHogwartsMapBackground(void)
{
    s32 direction;

    direction = Mt19937RandRange(0, 3);
    LoadBgGraphic(3, g_apUnusedHogwartsMapBackgrounds[g_dwUnusedHogwartsMapShownBg], 0x50, 0, 0, 0);

    switch (direction)
    {
    case 0:
        SetBgScrollFixed(2, -8 << 16, 224 << 16);
        break;
    case 1:
        SetBgScrollFixed(2, -8 << 16, -224 << 16);
        break;
    case 2:
        SetBgScrollFixed(2, -232 << 16, 0);
        break;
    case 3:
        SetBgScrollFixed(2, 200 << 16, 0);
        break;
    }

    g_bForcePendingBgWritesFlush = 1;
    WaitForVBlankIntr();
    LoadBgGraphic(2, g_apUnusedHogwartsMapBackgrounds[g_GameModeStackContext.dwCurrentGameModeArg2], 0x201, 0, 0,
                  0);
    SetBgScrollTarget(2, -8 << 16, 0, 16);
    g_dwUnusedHogwartsMapShownBg = g_GameModeStackContext.dwCurrentGameModeArg2;
}

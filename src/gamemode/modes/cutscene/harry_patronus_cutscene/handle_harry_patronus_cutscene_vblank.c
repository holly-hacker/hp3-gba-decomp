#include "types.h"
#include "display.h"
#include "harry_patronus_cutscene.h"
#include "object.h"

void HandleHarryPatronusCutsceneVBlank(void)
{
    sub_08000BC0();
    sub_08007C94(2, g_nPatronusBgOffset >> 16, 0);
    sub_08007C94(3, g_nPatronusBgOffset >> 16, 0);
    sub_08007CF4(2, g_swPatronusBgParam);
    sub_08007CF4(3, g_swPatronusBgParam);

    if (g_dwPatronusSwapPending != 0)
    {
        EnableBg(g_dwPatronusBgFront);
        DisableBg(g_dwPatronusBgBack);
        g_dwPatronusSwapPending = 0;
    }
}

#include "types.h"
#include "background.h"

void ResetBgLayers(void)
{
    u32 bg;

    for (bg = 0; bg < 4; bg++)
        ResetBgLayer(bg);
}

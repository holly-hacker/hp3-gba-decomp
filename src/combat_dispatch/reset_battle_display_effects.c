#include "types.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "interrupts.h"
#include "screen_transitions.h"

void ResetBattleDisplayEffects(void)
{
    QueueBattleScanlineEffects();
    while (!IsScanlineEffectQueueIdle())
        WaitForVBlankIntr();

    SetAlphaBlendTargets(0, 0x1F);
    SetAlphaBlendCoefficients(8, 8);
}

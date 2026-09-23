#include "types.h"
#include "audio.h"
#include "bios.h"
#include "cool_train_cutscene.h"
#include "display.h"
#include "io_regs.h"

void InitializeCoolTrainCutscene(void)
{
    volatile u16 zero;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwCoolTrainBg0Control);
    ClearBgTilemap(0);
    LoadBgGraphic(0, g_CoolTrainGraphic, 0, 0, 0, 0);
    SetMusicVolume(0, 1);
    PlaySoundById(0x43);
    PlaySoundById(0x3F);
    g_wCoolTrainTimer = 0x78;
    PlayScreenTransitionInByIndex(0x3F, 2);
}

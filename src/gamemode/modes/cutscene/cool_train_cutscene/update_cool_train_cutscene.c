#include "types.h"
#include "audio.h"
#include "battle.h"
#include "bios.h"
#include "cool_train_cutscene.h"
#include "display.h"
#include "game_modes.h"
#include "input.h"
#include "io_regs.h"

// Runs for 0x78 frames, or until A is pressed, then returns to the overworld
// in the current room.
void UpdateCoolTrainCutscene(void)
{
    volatile u16 zero;

    if (--g_wCoolTrainTimer == 0x4B)
        PlaySoundById(0x44);

    if (g_wCoolTrainTimer == 0 || (g_wKeysPressed & KeyA) != 0)
    {
        DisableBg(0);
        zero = 0;
        bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
        PushGameMode_2(Overworld, 0, g_bCurrentRoomId);
        UnmuteAllMusicChannels();
        SetMusicVolume(0x64, 0);
    }
}

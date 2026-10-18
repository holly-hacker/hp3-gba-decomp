#include "sound.h"
#include "pscreen_information.h"

void CancelHelpScreen(void)
{
    PlaySoundById(2);
    LeaveHelpScreen();
}

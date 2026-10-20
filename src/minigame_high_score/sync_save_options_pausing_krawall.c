#include "types.h"
#include "save.h"
#include "sound.h"
#include "minigame_high_score.h"

void SyncSaveOptionsPausingKrawall(void)
{
    DisableKrawall();
    SyncSaveOptionsIfDirty();
    EnableKrawall();
}

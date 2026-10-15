#include "types.h"
#include "dialog.h"
#include "dialog_box.h"

void SetDialogTextReveal(u32 arg)
{
    g_DialogState_candidate.bRevealText = arg;
}

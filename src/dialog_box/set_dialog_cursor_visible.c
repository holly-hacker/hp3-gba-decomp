#include "types.h"
#include "actor.h"
#include "dialog.h"
#include "dialog_box.h"

void SetDialogCursorVisible(u32 arg)
{
    if (arg)
        g_pDialogCursorActor->dwFlags |= ActorFlagVisible;
    else
        g_pDialogCursorActor->dwFlags &= ~ActorFlagVisible;
}

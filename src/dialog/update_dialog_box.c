#include "types.h"
#include "game/game_modes.h"
#include "actor.h"
#include "graphics/scanline_effects.h"
#include "input.h"
#include "dialog.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void UpdateDialogBox(void)
{
    switch (g_DialogState_candidate.bPhase)
    {
    case DialogPhaseText:
    case DialogPhaseTextStart:
        if (g_dwDialogPageFull == 0 && g_DialogState_candidate.bArg19 == 0)
        {
            sub_0801FD2C();
            g_dwDialogPageFull = 1;
        }
        else
            sub_0801FD64();

        if (g_dwDialogPageFull != 0)
        {
            if (g_wKeysPressed & KeyA)
                AdvanceDialog();
            else
                sub_0801FCFC(*g_DialogState_candidate.pText != 0);
        }
        else
        {
            sub_0801FCFC(0);
            if ((g_wKeysPressed & KeyA) || g_DialogState_candidate.bArg19 == 0)
            {
                sub_0801FD2C();
                g_dwDialogPageFull = 1;
            }
        }
        break;

    case DialogPhaseSlideUp:
        g_dwDialogBoxY -= 3;
        if (g_dwDialogBoxY <= DIALOG_BOX_SHOWN_Y)
        {
            g_DialogState_candidate.bPhase = DialogPhaseText;
            g_dwDialogBoxY = DIALOG_BOX_SHOWN_Y;
        }
        SetActorPosition(g_pDialogPortraitActor, 0, g_dwDialogBoxY + 0x28);
        QueueScanlineEffectEntry(0, g_dwDialogBoxY, 0, sub_0801FC58);
        break;

    case DialogPhaseSlideDown:
        g_dwDialogBoxY += 3;
        if (g_dwDialogBoxY > DIALOG_BOX_HIDDEN_Y - 1)
        {
            g_DialogState_candidate.bPhase = DialogPhaseDone;
            g_dwDialogBoxY = DIALOG_BOX_HIDDEN_Y;
            g_pDialogPortraitActor->dwFlags &= ~ActorFlagVisible;
        }
        SetActorPosition(g_pDialogPortraitActor, 0, g_dwDialogBoxY + 0x28);
        QueueScanlineEffectEntry(0, g_dwDialogBoxY, 0, sub_0801FC58);
        break;

    case DialogPhaseDone:
        g_dwGameModeFlags &= ~1;
        PushGameMode_2(g_PrevGameModeStackContext.dwCurrentGameMode, 9, g_bCurrentRoomId);
        break;
    }

    TickOverworldBeforeActors_candidate();
}

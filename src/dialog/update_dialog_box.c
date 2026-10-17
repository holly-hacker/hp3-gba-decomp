#include "types.h"
#include "modes.h"
#include "actor.h"
#include "video.h"
#include "input.h"
#include "dialog.h"
#include "dialog_box.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "map.h"

void UpdateDialogBox(void)
{
    switch (g_DialogState_candidate.bPhase)
    {
    case DialogPhaseText:
    case DialogPhaseTextStart:
        if (g_dwDialogPageFull == 0 && g_DialogState_candidate.bRevealText == 0)
        {
            DrawDialogTextPage();
            g_dwDialogPageFull = 1;
        }
        else
            StepDialogTextReveal();

        if (g_dwDialogPageFull != 0)
        {
            if (g_wKeysPressed & KeyA)
                AdvanceDialog();
            else
                SetDialogCursorVisible(*g_DialogState_candidate.pText != 0);
        }
        else
        {
            SetDialogCursorVisible(0);
            if ((g_wKeysPressed & KeyA) || g_DialogState_candidate.bRevealText == 0)
            {
                DrawDialogTextPage();
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
        QueueScanlineEffectEntry(0, g_dwDialogBoxY, 0, BeginDialogBoxPanelScanline);
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
        QueueScanlineEffectEntry(0, g_dwDialogBoxY, 0, BeginDialogBoxPanelScanline);
        break;

    case DialogPhaseDone:
        g_dwGameModeFlags &= ~1;
        PushGameMode_2(g_PrevGameModeStackContext.dwCurrentGameMode, 9, g_bCurrentRoomId);
        break;
    }

    TickOverworldBeforeActors_candidate();
}

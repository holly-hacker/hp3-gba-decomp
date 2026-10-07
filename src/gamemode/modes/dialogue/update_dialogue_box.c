#include "types.h"
#include "game/game_modes.h"
#include "graphics/object.h"
#include "graphics/scanline_effects.h"
#include "hw/input.h"
#include "menu/dialog.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void UpdateDialogueBox(void)
{
    switch (g_DialogState_candidate.bPhase)
    {
    case DialoguePhaseText:
    case DialoguePhaseTextStart:
        if (g_dwDialogTextActive == 0 && g_DialogState_candidate.bArg19 == 0)
        {
            sub_0801FD2C();
            g_dwDialogTextActive = 1;
        }
        else
            sub_0801FD64();

        if (g_dwDialogTextActive != 0)
        {
            if (g_wKeysPressed & KeyA)
                sub_0801FA18();
            else
                sub_0801FCFC(*g_DialogState_candidate.pText != 0);
        }
        else
        {
            sub_0801FCFC(0);
            if ((g_wKeysPressed & KeyA) || g_DialogState_candidate.bArg19 == 0)
            {
                sub_0801FD2C();
                g_dwDialogTextActive = 1;
            }
        }
        break;

    case DialoguePhaseSlideUp:
        g_dwDialogBoxY -= 3;
        if (g_dwDialogBoxY <= DIALOG_BOX_SHOWN_Y)
        {
            g_DialogState_candidate.bPhase = DialoguePhaseText;
            g_dwDialogBoxY = DIALOG_BOX_SHOWN_Y;
        }
        SetObjectPosition(g_pDialogBoxObject, 0, g_dwDialogBoxY + 0x28);
        QueueScanlineEffectEntry(0, g_dwDialogBoxY, 0, sub_0801FC58);
        break;

    case DialoguePhaseSlideDown:
        g_dwDialogBoxY += 3;
        if (g_dwDialogBoxY > DIALOG_BOX_HIDDEN_Y - 1)
        {
            g_DialogState_candidate.bPhase = DialoguePhaseDone;
            g_dwDialogBoxY = DIALOG_BOX_HIDDEN_Y;
            g_pDialogBoxObject->dwFlags &= ~ObjectFlagVisible;
        }
        SetObjectPosition(g_pDialogBoxObject, 0, g_dwDialogBoxY + 0x28);
        QueueScanlineEffectEntry(0, g_dwDialogBoxY, 0, sub_0801FC58);
        break;

    case DialoguePhaseDone:
        g_dwGameModeFlags &= ~1;
        PushGameMode_2(g_PrevGameModeStackContext.dwCurrentGameMode, 9, g_bCurrentRoomId);
        break;
    }

    TickOverworldBeforeObjects_candidate();
}

#include "types.h"
#include "background.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "graphics/display.h"
#include "actor.h"
#include "video.h"
#include "font.h"
#include "dialog.h"
#include "dialog_box.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "cursor.h"
#include "scroll.h"

void InitializeDialog(void)
{
    s32 cameraPosition[2];
    s32 row;

    if (g_DialogState_candidate.dwState == 0)
    {
        sub_08024BD4();
        g_adwSavedBgPriority[0] = REG_BG0CNT & 3;
        g_adwSavedBgPriority[1] = REG_BG1CNT & 3;

        GetCameraPosition(cameraPosition);
        cameraPosition[1] &= 0xFF;
        row = (cameraPosition[1] < 0x30 ? cameraPosition[1] + 0xB0 : cameraPosition[1] - 0x30) >> 3;
        g_dwDialogBoxTileRow = row;

        bios_CPUSet(BG_PLTT, g_awSavedBgPalette0, 0x10);
        g_DialogState_candidate.dwState = 1;
        WriteBgGraphicTilemap_candidate(1, g_pDialogBoxTilemap, DIALOG_BOX_FIRST_TILE, 0, 0, g_dwDialogBoxTileRow);
#ifdef VERSION_JP
        SelectTextFont(10, 0, -1);
#else
        SelectTextFont(7, 0, -1);
#endif
        SetDialogTextAlign(0);
        SetDialogTextReveal(1);
        SetActorActionState(g_pPlayerActor, 0x24);
        g_dwDialogTextId = 0;
        g_dwDialogBoxY = DIALOG_BOX_HIDDEN_Y;
        g_pDialogPortraitActor = AllocDialogPortraitActor();
        SetActorPosition(g_pDialogPortraitActor, 0, g_dwDialogBoxY + 0x28);
        g_pDialogCursorActor = SpawnMenuCursorActor(0);
        QueueScanlineEffectTable(g_aDialogScanlineEffects, 1);
        while (!IsScanlineEffectQueueIdle())
            ;
        StartScanlineEffects();
        g_DialogState_candidate.wLineIndex = 0;
        g_DialogState_candidate.bPhase = DialogPhaseSlideUp;
        ShowDialogLine();
    }
}

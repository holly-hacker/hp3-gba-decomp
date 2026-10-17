#include "background.h"
#include "hw/bios.h"
#include "font.h"
#include "dialog.h"
#include "dialog_box.h"
#include "gen/graphics/cutscenes.h"
#include "map.h"

void LoadDialogBoxGraphics(void)
{
    g_pDialogBoxTilemap = LoadGraphicBlobTiles(1, gDialogBoxGraphic, DIALOG_BOX_FIRST_TILE);
    bios_CPUSet(gDialogBoxGraphic + 2, g_awDialogBoxPalette, 16);
    SetTextTargetFromBgControl(g_dwBg1Control);
#ifdef VERSION_JP
    SelectTextFont(10, 0, -1);
#else
    SelectTextFont(7, 0, -1);
#endif
    SetDialogTextAlign(0);
    SetDialogTextReveal(1);
}

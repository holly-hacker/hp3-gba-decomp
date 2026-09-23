#include "types.h"
#include "audio.h"
#include "bios.h"
#include "display.h"
#include "divination_tea.h"
#include "game_modes.h"
#include "io_regs.h"
#include "minigame_menu.h"
#include "mt19937.h"
#include "room.h"
#include "text.h"

void InitializeDivinationTeaMinigame(void)
{
    u16 zero;
    u16 *pZero;
    u32 bgControl;

    InitObjTileAllocBitmaps(1);
    pZero = &zero;
    *pZero = 0;
    bios_CPUSet(pZero, VRAM_BASE, 0x01008000);
    ResetDisplayState(1);
    SetDispcntFlag(0x1000);
    SetBgControl(2, g_dwDivinationTeaBg2Control);
    bgControl = g_dwDivinationTeaBg0Control;
    SetBgControl(0, bgControl);
    SetBgControl(1, g_dwDivinationTeaBg1Control);

    REG_BG2Y_L = 0;
    REG_BG2X_L = 0;
    REG_BG2PA = 0x100;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 0x100;

    LoadBgGraphic(2, g_DivinationTeaBg2Graphic, 1, 0, 0, 0);
    LoadBgGraphic(1, g_DivinationTeaBg1Graphic, 1, 0, 0, 0);
    ClearBgTilemap(0);
    sub_0800A598(g_DivinationTeaTable, &g_dwDivinationTeaBg2Control, 8);
    SetTextTargetFromBgControl(bgControl);
    SelectTextFont(5, 0, -1);

    g_DivinationTea.dwUnk1D0 = 0x40;
    sub_08007C2C(2, 0, 0x40);
    sub_08007CB4(2, 1, 0x800);
    sub_08041D84();
    Mt19937AutoSeed();

    g_GameModeStackContext.dwModeState = DivinationTeaStateIntro;
    g_DivinationTea.dwUnk1D8 = 0;
    g_DivinationTea.pCursorObject = NULL;
    g_DivinationTea.dwUnk1C0 = 0;
    g_DivinationTea.dwUnk1C4 = 0;
    g_DivinationTea.pFortuneText = NULL;
    g_DivinationTea.dwBlendEvb = 0x10;
    g_DivinationTea.dwBlendEva = 0;
    g_DivinationTea.dwFrame = 0;
    g_DivinationTea.dwUnk1D4 = 0;

    SetAlphaBlendTargets(2, 4);
    SetAlphaBlendCoefficients(g_DivinationTea.dwBlendEva, g_DivinationTea.dwBlendEvb);
    PlayMusicModule(8);
    g_GameModeStackContext.dwModeTimer = 3;
    PlayScreenTransitionInByIndex(0x3F, 2);
}

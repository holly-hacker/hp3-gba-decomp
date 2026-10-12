#include "types.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "graphics/display.h"
#include "graphics/scanline_effects.h"
#include "font.h"
#include "game/game_modes.h"
#include "mt19937.h"
#include "buckbeak_minigame.h"

// Sets up the BGs, the floor, Buckbeak and the rings.
void SetUpBuckbeakMinigameScene(void)
{
    u16 zero;
    u16 *pZero;
    void *pTilemap;
    s32 i;
    s32 heading;
    const BuckbeakMinigameWorldPos *pPositions;

    g_pFloorAffineTable_candidate = AllocZeroed(0xA00);
    pZero = &zero;
    *pZero = 0;
    bios_CPUSet(pZero, VRAM_BASE, 0x01008000);
    ResetDisplayState(1);
    SetDispcntFlag(0x1000);
    SetFloorHorizonLineAndSkyScroll(0, 0);

    SetBgControl(0, g_dwBuckbeakMinigameBg0Control);
    LoadBgGraphic(0, g_aapBuckbeakMinigameBgGraphics[g_pBuckbeakMinigame->bDifficulty][1], 0xC0, 0, 0, 0);
    SetBgScroll_candidate(0, g_pBuckbeakMinigame->dwHeading.parts.wWhole * 2, 0xC0);

    SetBgControl(1, g_dwBuckbeakMinigameBg1Control);
    LoadGraphicBlob(1, g_aapBuckbeakMinigameBgGraphics[g_pBuckbeakMinigame->bDifficulty][0], 0x60, 0, 0, 0);
    SetBgScroll_candidate(1, g_pBuckbeakMinigame->dwHeading.parts.wWhole * 4, 0x20);

    SetBgControl(2, g_dwBuckbeakMinigameBg2Control);
    SelectTextFont(6, 0, 0);

    // The ground starts out unrotated and unscaled.
    REG_BG2Y_L = 0;
    REG_BG2X_L = 0;
    REG_BG2PA = 0x100;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 0x100;

    pTilemap = LoadGraphicBlobTiles(2, gBuckbeakMinigameGroundGraphic, 0);
    if (pTilemap != NULL)
        CopyBgTilemapRect(2, pTilemap, 0, 0, 0, 4, 0, 0, 0x80, 0x80);

    InitFloorEffect();
    SetFloorHorizonOffset(g_pBuckbeakMinigame->nHorizonOffset);
    SetFloorForwardSpeed(0);
    g_FloorEffect.dwCameraBackoff = 0;
    g_FloorEffect.dwCameraX = g_pBuckbeakMinigame->camera.x >> 8;
    g_FloorEffect.dwCameraY = g_pBuckbeakMinigame->camera.y >> 8;
    g_FloorEffect.dwCameraHeight = g_pBuckbeakMinigame->dwCameraHeight.parts.wWhole;
    heading = g_pBuckbeakMinigame->dwHeading.parts.wWhole;
    g_FloorEffect.bHeading = heading;
    QueueScanlineEffectTable(g_aBuckbeakMinigameScanlineEffects, 2);
    UpdateFloorAffineTable();

    g_pBuckbeakMinigame->dwBankState = 0;
    g_pBuckbeakMinigame->pBuckbeak = SpawnActor(0, 0x78, 0x60, (const ObjPalette *)gBuckbeakMinigamePalette002Palette);
    SetActorAnimData(g_pBuckbeakMinigame->pBuckbeak,
                     &g_aBuckbeakMinigameBuckbeakAssets[g_pBuckbeakMinigame->dwBankState],
                     g_abBuckbeakMinigameFlyAnimData, 0);
    g_pBuckbeakMinigame->pBuckbeak->oam.priority = 1;
    PlaceBuckbeakMinigameBuckbeak();
    RegisterBgTileAnimation(&g_BuckbeakMinigameWaterAnimation, &g_dwBuckbeakMinigameBg2Control, 8);

    pPositions = g_aBuckbeakMinigameRingPositions;
    for (i = 8; i >= 0; i--)
    {
        s32 index = FindFreeBuckbeakMinigameRing();

        SpawnBuckbeakMinigameRing(index, pPositions[index], 0);
    }
}

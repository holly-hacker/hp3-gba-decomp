#pragma once

#include "types.h"
#include "graphics/scanline_effects.h"
#include "hw/bios.h"

// One affine record per visible scanline.
#define FLOOR_SCANLINE_COUNT 160

// A perspective floor on BG2: one BG affine record per scanline, built by
// UpdateFloorAffineTable from these parameters into g_pFloorAffineTable
// and fed to BG2PA..BG2Y by an HBlank DMA (StartFloorAffineHBlankDma).
typedef struct FloorEffectState {
    s32 nHorizonOffset;   // 0x00; added, with a constant, to each scanline's index to form the
                          // floor's scale divisor, so a larger value moves the vanishing line up
    u8 bHeading;          // 0x04; index into g_anSineTable, 256 per turn
    s32 dwCameraHeight;   // 0x08; numerator of each floor scanline's scale
    s32 dwViewDistance;   // 0x0C; each floor scanline shows the ground this many of its own scaled
                          // rows ahead of the camera; also shifts the sky vertically
    s32 dwCameraBackoff;  // 0x10; the view is placed this far behind the camera along the heading
    s16 wForwardSpeed;    // 0x14; moves the camera along the heading by this much per update
    s32 dwCameraX;        // 0x18; 24.8 fixed-point pixels
    s32 dwCameraY;        // 0x1C
} FloorEffectState;

extern FloorEffectState g_FloorEffect;      // 0x03003F8C
extern BgAffineDst *g_pFloorAffineTable;    // 0x03003FAC
extern s32 g_nFloorHorizonLine;             // 0x03003FB0; scanlines above it are sky
extern u32 g_dwFloorScrollSky;              // 0x03003FB4; nonzero: BG1 scrolls with the heading

// One entry: line 0, StartFloorAffineHBlankDma.
extern const ScanlineEffectEntry g_aFloorScanlineEffects[1];

extern void NoopInit3(void);

// Sets up mode 1 with an optional sky on BG1 and floor on BG2, then InitFloorEffect.
// A null blob leaves that layer alone; each control is the layer's BGxCNT value.
extern void InitFloorDisplay(const u8 *pFloorBlob, const u32 *pFloorControl, const u8 *pSkyBlob,
                             const u32 *pSkyControl, s32 horizonLine, u32 scrollSky);
// Queues the floor's scanline table and sets default parameters.
extern void InitFloorEffect(void);
// Stops the DMA and frees the affine table.
extern void FreeFloorEffect(void);
// Scanlines above horizonLine use fixed sky parameters; a nonzero scrollSky also makes
// UpdateFloorAffineTable scroll BG1 with the heading.
extern void SetFloorHorizonLineAndSkyScroll(s32 horizonLine, u32 scrollSky);
// x and y are whole pixels.
extern void SetFloorCameraPositionAndHeading(u16 x, u16 y, u8 heading);
extern void SetFloorHeading(u8 heading);
extern void SetFloorForwardSpeed(s16 speed);
extern void SetFloorCameraHeight(u8 height);
extern void SetFloorHorizonOffset(s32 offset);
// Applies the forward speed, then rebuilds the affine table (BuildFloorAffineTable).
extern void UpdateFloorAffineTable(void);
// Writes the FLOOR_SCANLINE_COUNT scanline records of g_pFloorAffineTable.
extern void BuildFloorAffineTable(s32 heading, s32 cameraX, s32 cameraY, s32 cameraHeight,
                                  s32 viewDistance, s32 horizonOffset);
// Starts HBlank DMA 0 copying one 16-byte record of the table into BG2PA..BG2Y per scanline.
extern void StartFloorAffineHBlankDma(u32 *pPayload0, u32 *pPayload1);

#pragma once

#include "types.h"

// A perspective floor on BG2: one BG affine record per scanline, built by
// UpdateFloorAffineTable from these parameters into g_pFloorAffineTable_candidate
// and fed to BG2PA..BG2Y by an HBlank DMA (StartFloorAffineHBlankDma).
typedef struct FloorEffectState {
    s32 nHorizonOffset;   // 0x00; added, with a constant, to each scanline's index to form the
                          // floor's scale divisor, so a larger value moves the vanishing line up
    u8 bHeading;          // 0x04; index into g_anSineTable, 256 per turn
    s32 dwCameraHeight;   // 0x08
    s32 dwUnkC;           // 0x0C
    s32 dwCameraBackoff;  // 0x10; the view is placed this far behind the camera along the heading
    s16 wForwardSpeed;    // 0x14; moves the camera along the heading by this much per update
    s32 dwCameraX;        // 0x18; pixels
    s32 dwCameraY;        // 0x1C
} FloorEffectState;

extern FloorEffectState g_FloorEffect;      // 0x03003F8C
extern u8 *g_pFloorAffineTable_candidate;   // 0x03003FAC

// Queues the floor's scanline table and sets default parameters.
extern void InitFloorEffect(void);
// Stops the DMA and frees the affine table.
extern void FreeFloorEffect(void);
// Scanlines above horizonLine use fixed sky parameters; a nonzero scrollSky also makes
// UpdateFloorAffineTable scroll BG0 with the heading.
extern void SetFloorHorizonLineAndSkyScroll(u32 horizonLine, u32 scrollSky);
extern void SetFloorHeading(u8 heading);
extern void SetFloorForwardSpeed(s16 speed);
extern void SetFloorHorizonOffset(s32 offset);
// Applies the forward speed, then rebuilds the affine table (BuildFloorAffineTable).
extern void UpdateFloorAffineTable(void);
// Starts HBlank DMA 0 copying one 16-byte record of the table into BG2PA..BG2Y per scanline.
extern void StartFloorAffineHBlankDma(void);

#pragma once

#include "types.h"

// BG layer scroll/affine state and tile data decoding; see docs/memory-map/frame_systems.md.

// State of one BG layer, 0x6C bytes per layer starting at g_aBgLayers. The same array that
// g_aBgScrollState addresses four bytes earlier.
typedef struct BgLayer {
    u8 pad_00[0x18];
    u32 dwFlags;       // 0x18: BG_LAYER_*
    s32 nOutX;         // 0x1C: 16.16 scroll written to BGxHOFS
    s32 nOutY;         // 0x20: 16.16 scroll written to BGxVOFS
    s32 nScrollX;      // 0x24: 16.16
    s32 nScrollY;      // 0x28: 16.16
    s32 nStepX;        // 0x2C: per-frame scroll step, used when the tween has no frames
    s32 nStepY;        // 0x30
    s32 nTargetX;      // 0x34: tween target
    s32 nTargetY;      // 0x38
    u16 wTweenFrames;  // 0x3C: frames left; 0 steps by nStep each frame
    u16 wZoom;         // 0x3E: 8.8
    s16 nZoomStep;     // 0x40: per-frame change
    s16 nZoomMin;      // 0x42
    s16 nZoomMax;      // 0x44
    u16 wAngle;        // 0x46: the high byte indexes g_anSineTable
    u16 wAngleStep;    // 0x48
    s16 nCenterX;      // 0x4A: rotation centre offset in pixels
    s16 nCenterY;      // 0x4C
    s16 nPa;           // 0x4E: BG affine matrix, 8.8
    s16 nPb;           // 0x50
    s16 nPc;           // 0x52
    s16 nPd;           // 0x54
    u8 pad_56[0x02];
    s32 nRefX;         // 0x58: BG affine reference point
    s32 nRefY;         // 0x5C
    u16 wWobblePhaseX; // 0x60
    u16 wWobblePhaseY; // 0x62
    s16 nWobbleSpeedX; // 0x64
    s16 nWobbleSpeedY; // 0x66
    s16 nWobbleAmpX;   // 0x68
    s16 nWobbleAmpY;   // 0x6A
} BgLayer;
extern BgLayer g_aBgLayers[4];  // 0x03001E84

#define BG_LAYER_TWEEN        0x0001  // scroll toward nTarget over wTweenFrames
#define BG_LAYER_ROTATE       0x0002  // advance wAngle by wAngleStep
#define BG_LAYER_ZOOM_BOUNCE  0x0004  // bounce wZoom between nZoomMin and nZoomMax
#define BG_LAYER_WOBBLE       0x0008  // sine wobble added to the output scroll
#define BG_LAYER_MATRIX_DIRTY 0x4000  // rebuild the affine matrix and reference point
#define BG_LAYER_COMMIT       0x8000  // write the scroll registers at the next vblank

extern void ApplyBgLayerWobble(u32 bg);

// Steps the four BG layers; run by TickFrameSystems.
extern void TickBgLayers_candidate(void);

// The 4-byte header of tile data decoded by UnpackTileData.
typedef struct TileDataHeader {
    u8 bUnused : 5;
    u8 bCodec : 2;  // 0 copy, 1 run-length, 2 LZ77, 3 GammaLz
    u8 bUnused2 : 1;
    u8 pad_01;
    u16 wSize;      // bytes of tile data after the header
    u8 aData[0];    // the encoded data
} TileDataHeader;
extern void UnpackTileData(const TileDataHeader *pHeader, const void *pData, s32 size, void *pDest);

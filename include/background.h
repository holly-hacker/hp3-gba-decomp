#pragma once

#include "types.h"
#include "math.h"

// BG layer scroll/affine state and tile data decoding; see docs/memory-map/frame_systems.md.

// A BGxCNT value. dwControl in ROM tables is this word; the low half is the register.
typedef struct BgControl {
    u32 bPriority : 2;
    u32 bCharBlock : 2;    // 16 KB character block holding the tiles
    u32 bUnused : 2;
    u32 bMosaic : 1;
    u8 b8bpp : 1;
    u32 bScreenBlock : 5;  // 2 KB screen block holding the tilemap
    u32 bWrap : 1;
    u32 bSize : 2;         // 0 32x32, 1 64x32, 2 32x64, 3 64x64 tiles
    u32 dwUnused : 16;
} BgControl;

// The same word with its register half addressable as a halfword.
typedef union BgControlRegister {
    BgControl bits;
    u16 wRegister;
    u8 abBytes[2];
} BgControlRegister;

// Sine wobble added to a layer's scroll; phases are 8.8, one sine period per 0x100 units.
typedef struct BgWobble {
    u16 wPhaseX;
    u16 wPhaseY;
    s16 nSpeedX;  // phase added per frame
    s16 nSpeedY;
    s16 nAmpX;
    s16 nAmpY;
} BgWobble;

// Where GetGraphicBlobTileLoad found a graphic blob's raw VRAM block or tile stream.
typedef struct BgTileLoadInfo {
    const void *pSrc;
    void *pDest;
    u32 dwUnused;
    u32 dwSize;  // bytes
} BgTileLoadInfo;

// State of one BG layer, 0x6C bytes per layer.
typedef struct BgLayer {
    BgControlRegister control;  // 0x00
    const u16 *pTilemap;  // 0x04: LoadBgGraphic's result: u16 width, u16 height, then the cells
    u16 *pTilemapBuffer;  // 0x08
    u16 *pScreenBase;     // 0x0C: VRAM screen block selected by dwControl
    u16 *pScreenBaseAlt;  // 0x10: same address
    u8 *pCharBase;        // 0x14: VRAM character block selected by dwControl
    u32 dwFlags;       // 0x18: BG_LAYER_*
    FixedPoint out;       // 0x1C: scroll written to BGxHOFS/BGxVOFS
    FixedPoint scroll;    // 0x24
    FixedPoint step;      // 0x2C: per-frame scroll step, used when the tween has no frames
    FixedPoint target;    // 0x34: tween target
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
    BgWobble wobble;   // 0x60
} BgLayer;
// dwFlags (bit 0 unknown, bit 1+n: BG n's tilemap was written) followed by the layers.
typedef struct BgState {
    u32 dwFlags;
    BgLayer aLayers[4];
} BgState;
extern BgState g_BgState;  // 0x03001E80
// Nonzero forces one extra CommitBgLayers call this vblank; cleared right after.
extern u32 g_bForcePendingBgWritesFlush;

#define BG_LAYER_TWEEN        0x0001  // scroll toward nTarget over wTweenFrames
#define BG_LAYER_ROTATE       0x0002  // advance wAngle by wAngleStep
#define BG_LAYER_ZOOM_BOUNCE  0x0004  // bounce wZoom between nZoomMin and nZoomMax
#define BG_LAYER_WOBBLE       0x0008  // sine wobble added to the output scroll
#define BG_LAYER_MATRIX_DIRTY 0x4000  // rebuild the affine matrix and reference point
#define BG_LAYER_COMMIT       0x8000  // write the scroll registers at the next vblank

// Per-frame and vblank work.
extern void ApplyBgLayerWobble(u32 bg);
extern void TickBgLayers(void);   // steps the layers; run by TickFrameSystems
extern void CommitBgLayers(void);  // writes scroll and affine registers; run in vblank
extern void InitBackground(void);            // ResetDisplayState(0), clears the update flags
extern void ResetBgLayers(void);
extern void ResetBgLayer(u32 bg);            // scroll, step and flags back to zero

// Display registers. Bits 8-11 of DISPCNT enable BG0-3.
extern void ResetDisplayState(u16 mode);  // DISPCNT = mode | OBJ 1D mapping, resets every layer
extern void SetBgControl(u32 bg, u32 control);  // writes BGxCNT and enables the layer
// The write-only half of SetBgControl: writes BGxCNT and the tilemap/charblock
// VRAM bases, without enabling the layer via SetDispcntFlag.
// HACK: unprototyped so callers can pass the control word as a u32, while the
// definition takes it as a 4-byte struct (BgControlArg), which it needs to match.
extern void SetBgControlRegister();
extern void EnableBg(u32 bg);
extern void DisableBg(u32 bg);
extern void RewriteBgControlRegisters(void);  // layers with BG_LAYER_COMMIT and 0x200 set
extern u32 IsBg8bpp(u32 bg);
extern u32 GetBgMode(void);
extern void SetBgMode(u16 mode);
extern void SetDispcntLayerEnables(u16 layers);  // replaces DISPCNT bits 8-12
extern void ClearDispcntFlag(u16 flags);
extern void SetDispcntFlag(u16 flags);
extern void SetBgPriority(u32 bg, u8 priority);

// Tilemap and tile fills. Colors are 256-color indices; 16-color BGs use the low nibble for the
// tile pattern and the high nibble as the palette bank.
extern void ClearBgTilemap(u32 bg);
extern void FillBgTilemapWithTile(u32 bg, u16 tile);
extern void FillBgTilemap(u32 bg, u16 tile, u16 color);
extern void FillBgTile(u32 bg, u16 tile, u16 color);  // one tile of the character block
extern void CopyBgTiles(u32 bg, u16 firstTile, u16 tileCount, const void *pSrc);
extern void ClearBgTilemapRect(u32 bg, u32 x, u32 y, s32 w, s32 h);
extern void FillBgTilemapRect(u32 bg, u32 x, u32 y, s32 w, s32 h, u16 tile);
extern void FillTilemapRect(u16 *pTilemap, u32 x, u32 y, s32 w, s32 h, u16 tile);  // 32-tile-wide map
extern void FillTilemapRectAscending(u16 *pTilemap, u32 x, u32 y, s32 w, s32 h, u16 tile);
extern void SetBgTilemapRectPalette(u32 bg, u32 x, u32 y, s32 w, s32 h, u16 palBank);
extern void SetTilemapRectPalette(u16 *pTilemap, u32 x, u32 y, s32 w, s32 h, u16 palBank);
extern void GetBgSizePixels(u32 bg, u16 *pWidth, u16 *pHeight);
extern u16 GetTilemapCell(const u16 *pTilemap, u32 x, u32 y, u32 stride);

// The colors of a graphic blob's embedded palette, after its two flag bytes
// (see docs/formats/graphic_blob.md).
#define GRAPHIC_BLOB_PALETTE_COLORS(blob) ((const u16 *)((const u8 *)(blob) + 2))

// Graphic loading; the blob layout is in docs/formats/graphic_blob.md. The tilemap result is
// width, height, then the cells.
extern const u16 *LoadBgGraphic(u32 bg, const u8 *pBlob, u16 tileOffset, u16 palBank, u32 x, u32 y);
extern const u16 *LoadBgGraphicTiles(u32 bg, const u8 *pBlob, u16 tileOffset, u16 palBank);
extern const u16 *LoadGraphicBlob(u32 bg, const u8 *pBlob, u16 tileOffset, u16 palBank, u32 x, u32 y);
extern const u16 *LoadGraphicBlobTiles(u32 bg, const u8 *pBlob, u16 tileOffset);
extern const u16 *GetGraphicBlobTileLoad(u32 bg, const u8 *pBlob, u16 tileOffset, BgTileLoadInfo *pInfo);
extern const u16 *GetGraphicBlobTilemap(u32 unused, const u8 *pBlob);
extern u32 LoadEmbeddedPalette(const u8 *pBlob, u32 row, u32 rowCount);  // returns its size
extern u32 LoadEmbeddedPaletteFromRow(const u8 *pBlob, u32 row);
extern void WriteBgGraphicTilemap_candidate(u32 bg, const u16 *pTilemap, u32 tileOffset, u32 palBank, s32 x, s32 y);
// Copies a w x h rectangle of tiles from (srcX, srcY) of a loaded BG tilemap to (dstX, dstY) of the
// given BG, adding tileOffset to the tile numbers and palBank to their palette.
extern void CopyBgTilemapRect(u32 bg, const u16 *pTilemap, u16 tileOffset, u16 palBank, u32 srcX, u32 srcY,
                              u32 dstX, u32 dstY, u32 w, u32 h);
// Same arguments as CopyBgTilemapRect, but addresses each cell through the layer size and has no
// affine-BG path.
extern void CopyBgTilemapRectByCell(u32 bg, const u16 *pTilemap, u16 tileOffset, u16 palBank, u32 srcX,
                                    u32 srcY, u32 dstX, u32 dstY, u32 w, u32 h);
extern void CopyLoadedTilemapToBuffer(u32 bg);
extern void CopyLoadedTilemapRect(u32 bg, s32 w, s32 h, u32 srcX, u32 srcY, u32 dstX, u32 dstY);
extern void CopyBgScreenRect(u32 bg, s32 w, s32 h, u32 srcX, u32 srcY, u32 dstX, u32 dstY);
extern void CopyTilemapRect(s32 w, s32 h, u32 srcX, u32 srcY, u32 srcStride, const u16 *pSrc, u32 dstX, u32 dstY,
                            u32 dstStride, u16 *pDest);
extern void CopyTilemapRectOffset(u16 *pDest, const u16 *pSrc, u32 w, u32 h, u32 srcStride, u32 palBank,
                                  u32 tileOffset);  // adds palBank << 12 and tileOffset to each cell

// Layer scroll, rotation, zoom and wobble. Positions are 16.16 unless the name says Pixels.
extern void SetBgScroll(u32 bg, s32 x, s32 y);  // pixels, both axes, snaps instantly
extern void SetBgScrollFixed(u32 bg, s32 x, s32 y);
extern void SetBgScrollFixedX(u32 bg, s32 position);
extern void SetBgScrollFixedY(u32 bg, s32 position);
extern void SetBgScrollXPixels(u32 bg, s32 x);
extern void SetBgScrollYPixels(u32 bg, s32 y);
extern void SetBgScrollTarget(u32 bg, s32 x, s32 y, u32 frames);  // starts a tween
extern void SetBgScrollStep(u32 bg, s32 x, s32 y);
extern void SetBgScrollStepX(u32 bg, s32 x);
extern void SetBgScrollStepY(u32 bg, s32 y);
extern void SetBgScrollStepPixels(u32 bg, s32 x, s32 y);
extern void GetBgScroll(u32 bg, s32 *pX, s32 *pY);
extern void SetBgRotation(u32 bg, u32 angle, u32 step);  // 8.8 angle units, step per frame
extern void SetBgAngle(u32 bg, u32 angle);
extern void SetBgAngleStep(u32 bg, u32 step);
extern void SetBgRotationCenter(u32 bg, s32 x, s32 y);
extern void SetBgZoomRange(u32 bg, s32 min, s32 max);
extern void SetBgZoomStep(u32 bg, s32 step);  // starts the zoom bounce
extern void SetBgZoom(u32 bg, u32 zoom);
extern void ClearBgWobble(u32 bg);
extern void ClearBgWobbleX(u32 bg);
extern void ClearBgWobbleY(u32 bg);
extern void SetBgWobble(u32 bg, const BgWobble *pWobble);
extern void SetBgWobbleX(u32 bg, s32 phase, s32 speed, s32 amplitude);
extern void SetBgWobbleY(u32 bg, s32 phase, s32 speed, s32 amplitude);
extern void SetBgWobblePhase(u32 bg, s32 phaseX, s32 phaseY);
extern void SetBgWobbleSpeed(u32 bg, s32 speedX, s32 speedY);
extern void SetBgWobbleAmplitude(u32 bg, s32 ampX, s32 ampY);

// BgState.dwFlags helpers. Nothing in the ROM calls them or reads the word: bit 0 is only touched
// by the Flag0 pair, bits 1-4 are only set by CopyLoadedTilemapToBuffer.
extern void ClearBgStateFlag0(void);
extern void SetBgStateFlag0(void);
extern u32 TestBgStateFlags(u32 mask);
extern void ClearBgStateFlags(u32 mask);
extern void SetBgStateFlags(u32 mask);

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

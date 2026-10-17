#pragma once

#include "types.h"
#include "actor.h"
#include "pscreen_folio_universitas.h"

// Frame behind a card's picture on the card detail screen (the FolioCardFrame* graphics).
typedef enum {
    FolioCardFrameBlue,
    FolioCardFramePurple,
    FolioCardFrameRed,
} FolioCardFrame;

// A card's picture assets and the frame drawn behind it. The frame follows the card's place in
// its category: red for the rare tenth card (and the last card), purple for the last card of a
// combo, blue otherwise.
typedef struct {
    u32 dwFrame;  // FolioCardFrame
    ActorAssetRecord asset;
} FolioCardAsset;

extern const FolioCardAsset g_aFolioCardAssets[FOLIO_UNIVERSITAS_CARD_COUNT];  // 0x0806B3D8

extern const u32 g_dwFolioCardDetailBg3Control;  // 0x0806B3CC
extern const u32 g_dwFolioCardDetailBg2Control;  // 0x0806B3D0
extern const u32 g_dwFolioCardDetailBg1Control;  // 0x0806B3D4

// Spawns the sprite showing a card at the given screen position and loads its palette.
extern Actor *SpawnFolioCardActor(u32 cardIndex, s32 x, s32 y);

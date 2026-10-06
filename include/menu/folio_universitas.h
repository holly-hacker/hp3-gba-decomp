#pragma once

#include "types.h"
#include "graphics/object.h"
#include "game/save.h"

// Number of collector's cards in the Folio Universitas, indexed 0-50.
#define FOLIO_UNIVERSITAS_CARD_COUNT 51

// Folio Universitas screen state. The grid has one row per category (cards 10 * row ... 10 * row + 9)
// and cards are grouped three to a combo within a row; the last row holds only the 51st card.
typedef struct {
    Object *pCard;   // thumbnail of the combo's card
    Object *pCount;  // badge showing how many copies are owned
} FolioComboSlot;

typedef struct {
    u32 dwCategory;                // 0x00: row of the selected card, 0-5
    u32 dwSlot;                    // 0x04: column of the selected card within its row, 0-9
    FolioComboSlot aComboSlots[3]; // 0x08: the selected combo's cards
    Object *pCursor;               // 0x20
    void *pGridTilemap;            // 0x24: tilemap of the card grid background, whose tiles mark each card's state
    Object *pPrevArrow;            // 0x28
    Object *pNextArrow;            // 0x2C
} FolioUniversitasState;
extern FolioUniversitasState g_FolioUniversitasState;  // 0x03005340

// What the screen was opened for, in GameModeStackContext.dwCurrentGameModeArg1.
typedef enum {
    FolioUniversitasBrowse,
    FolioUniversitasPickCombo,  // from battle: choose a combo to use
    FolioUniversitasPickCard,   // from the card trade: choose a card to offer
} FolioUniversitasPurpose;

// Adds one copy of a card (count saturates at 9), marking it seen and new the
// first time, and returns the card's count. See docs/formats/save.md.
u32 IncrementFolioUniversitasCard(u32 cardIndex);

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
    ObjectAssetRecord asset;
} FolioCardAsset;

extern const FolioCardAsset g_aFolioCardAssets[FOLIO_UNIVERSITAS_CARD_COUNT];  // 0x0806B3D8

extern const u32 g_dwFolioCardDetailBg3Control;  // 0x0806B3CC
extern const u32 g_dwFolioCardDetailBg2Control;  // 0x0806B3D0
extern const u32 g_dwFolioCardDetailBg1Control;  // 0x0806B3D4

// Spawns the sprite showing a card at the given screen position and loads its palette.
extern Object *SpawnFolioCardObject(u32 cardIndex, s32 x, s32 y);

extern const u32 g_dwFolioUniversitasBg3Control;  // 0x080696B0
extern const u32 g_dwFolioUniversitasBg1Control;  // 0x080696B4
extern const u32 g_dwFolioUniversitasBg0Control;  // 0x080696B8

// Cursor, button prompts, three unused-looking sprites and the copy-count badges.
extern const ObjectGfxRecord g_aFolioUniversitasObjectGfx[6];  // 0x080696BC
#define FOLIO_UNIVERSITAS_CURSOR_GFX   (&g_aFolioUniversitasObjectGfx[0])
#define FOLIO_UNIVERSITAS_PROMPTS_GFX  (&g_aFolioUniversitasObjectGfx[1])
#define FOLIO_UNIVERSITAS_BADGES_GFX   (&g_aFolioUniversitasObjectGfx[5])

// Indexed by card number; entry 51 is the face-down card.
extern const ObjectAssetRecord g_aFolioCardThumbnails[FOLIO_UNIVERSITAS_CARD_COUNT + 1];  // 0x080696EC

extern const u8 g_aFolioUniversitasCursorAnim[];        // 0x08069614
extern const u8 g_aFolioUniversitasBattleCursorAnim[];  // 0x0806963E
extern const u8 g_aFolioButtonPromptAnims[4][18];       // 0x08069668

extern u32 GetFolioUniversitasSelectedCard(void);
extern u32 GetFolioUniversitasSelectedCombo(void);
extern u32 IsFolioUniversitasCardSeen(u32 cardIndex);
extern u32 IsFolioUniversitasCardNew(u32 cardIndex);
extern void ClearFolioUniversitasNewCards(void);
extern u32 IsFolioUniversitasCardUnavailable(s32 cardIndex);
extern Object *SpawnFolioCardThumbnail(u32 cardIndex, s32 x, s32 y);
extern void DrawFolioCardSlot(u32 cardIndex);
extern void DrawFolioUniversitasCardSlots(void);
extern void DrawFolioUniversitasHeadings(void);
extern void SpawnFolioUniversitasCursor(void);
extern void SpawnFolioUniversitasButtonPrompts(void);
extern void SetFolioComboSlot(u32 cardIndex, u32 slot);

extern void UpdateFolioComboSlots(void);
extern void HighlightFolioComboSlot(void);
extern void DrawFolioUniversitasNames(u32 drawComboName);
extern void DrawFolioUniversitasButtonHints(void);

// Whether the card has been collected at some point (the seen bit stays set while any copy is owned).
// The screen's code tests the bit inline rather than through IsFolioUniversitasCardSeen.
#define FOLIO_CARD_SEEN(cardIndex)                                                          \
    ({                                                                                        \
        u32 _card = (cardIndex);                                                              \
        u32 _byte = _card >> 3;                                                               \
        u32 _bit = _card & 7;                                                                 \
        (g_saveStateBlock.abFolioUniversitasSeen[_byte] >> _bit) & 1;                         \
    })

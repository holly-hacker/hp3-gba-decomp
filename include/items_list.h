#pragma once

#include "types.h"
#include "game/items.h"
#include "actor.h"

// Scrolling item list shared with the Status/Equip item select and the shop.
// Up to ITEM_LIST_SLOT_COUNT - 1 rows are on screen; while the list scrolls,
// the row scrolling in is spawned into slot ITEM_LIST_INCOMING_SLOT.
#define ITEM_LIST_MAX_ITEMS     79
#define ITEM_LIST_SLOT_COUNT    5
#define ITEM_LIST_INCOMING_SLOT 4
#define ITEM_LIST_ROW_HEIGHT    24
#define ITEM_LIST_NO_CHARACTER  (-1)  // dwCharacter: every row is drawn as usable

// ItemListState.dwState.
typedef enum {
    ItemListIdle = 1,
    ItemListScrollingUp,
    ItemListScrollingDown,
} ItemListPhase;

typedef struct ItemListState {
    s32 nX;                                          // 0x000: icon column
    s32 nY;                                          // 0x004: top row
    u32 dwScrolledDown;                              // 0x008: a held Down continues the scroll
    u32 dwScrolledUp;                                // 0x00C: a held Up continues the scroll
    Actor *pCursor;                                  // 0x010
    u32 dwState;                                     // 0x014: ItemListPhase
    u32 dwUnk18;                                     // 0x018
    ActorGfxRecord aIconGfx[ITEM_LIST_SLOT_COUNT];   // 0x01C: indexed by abIconGfxSlot
    u8 abIconGfxUsed[ITEM_LIST_SLOT_COUNT];          // 0x044
    u32 adwItems[ITEM_LIST_MAX_ITEMS];               // 0x04C
    long nItemCount;                                 // 0x188
    Actor *apIcons[ITEM_LIST_SLOT_COUNT];            // 0x18C
    Actor *apTextLine1[ITEM_LIST_SLOT_COUNT];        // 0x1A0: item name
    Actor *apTextLine2[ITEM_LIST_SLOT_COUNT];        // 0x1B4: text after a line break, if any
    Actor *pUpArrow;                                 // 0x1C8
    Actor *pDownArrow;                               // 0x1CC
    u8 abIconGfxSlot[ITEM_LIST_SLOT_COUNT];          // 0x1D0: aIconGfx entry of each slot's icon
    u8 bRowCount;                                    // 0x1D5: rows on screen
    u8 bScrollFrames;                                // 0x1D6: counts down 4..0; the scale step of the moving icons
    u16 wBlendCoeffA;                                // 0x1D8: stepped by 3 while scrolling
    u16 wBlendCoeffB;                                // 0x1DA: stepped by 3 while scrolling
    void (*pfnOnCursorMove)(u32 item);               // 0x1DC
    void (*pfnOnClear)(void);                        // 0x1E0: called when a scroll starts
    u32 dwTextMode;                                  // 0x1E4: 0 name ("@1"), 1 name and quantity ("@1 (x@2)"), else text 0
    u32 dwWithRemove;                                // 0x1E8: OpenFilteredItemList's withRemove
    u32 dwMaxRows;                                   // 0x1EC
    s32 nCharacter;                                  // 0x1F0: rows this character cannot equip are grayed
    u32 dwCursorTargetSet;                           // 0x1F4: the cursor moves to the target below
    s32 nCursorTargetX;                              // 0x1F8
    s32 nCursorTargetY;                              // 0x1FC
} ItemListState;
extern ItemListState g_ItemList;
extern s8 g_bItemListScroll;     // index of the item on the top row
extern s8 g_bItemListCursorRow;  // on-screen row of the cursor

// "." -- the text a row's text actors are spawned with before DrawItemListRowText.
extern const u8 g_abItemListPlaceholderText[];

// Each Open* call returns nonzero when the list is not empty.
extern u32 OpenFilteredItemList(u32 filter, s32 x, s32 y, u32 textMode, u32 withRemove, u32 maxRows,
                                s32 character);
// Lists an ITEM_COUNT-terminated item id array instead of a filter.
extern u32 OpenItemListFromIds(const u32 *pItems, s32 x, s32 y, u32 textMode, u32 maxRows);
extern void TickItemList(void);            // Up/Down cursor movement and row scrolling
extern u32 GetItemListSelection(void);     // item under the list cursor
extern void SetItemListCallbacks(void (*onCursorMove)(u32 item), void (*onClear)(void));
extern void SetItemListTranslucent(void);  // rows and cursor join the alpha-blend fade
extern void CloseItemList(void);

extern void SpawnItemListActors(void);
extern void OffsetItemListRows(s32 dy);
extern void SpawnItemListRow(s32 row);
extern void DrawItemListRowText(s32 row, u32 highlighted);
extern void ScrollItemListUp(s32 rows);
extern void ScrollItemListDown(u32 rows);
extern void FreeItemListRow(s32 slot);
extern void FinishItemListScroll(s32 direction);
extern void UpdateItemListScrollArrows(void);
// No callers: send the cursor to a fixed point / back to its row.
extern void SetItemListCursorTarget(s32 x, s32 y);
extern void ClearItemListCursorTarget(void);
extern void SpawnItemListRows(void);
extern void InitItemList(s32 x, s32 y, u32 textMode, u32 maxRows, s32 character);
extern void TickItemListCursor(Actor *pCursor);
extern void SetItemListCursorRow(s32 row);
extern void FreeItemListRows(void);
extern s32 AllocItemListIconGfx(void);
extern void FreeItemListIconGfx(u32 slot);
extern void NotifyItemListCursorMove(void);
extern void SpawnItemListScrollArrows(void);

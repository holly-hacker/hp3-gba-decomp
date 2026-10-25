#pragma once

#include "types.h"
#include "modes.h"
#include "actor.h"

// Help-screen engine shared by the Help and HelpTopicScreen game modes.

// One level of the page history: the entry that was selected and the page it opened.
typedef struct {
    u32 dwSelectedEntry;
    const u32 *pPage;
} HelpPageFrame;

// A selectable entry of a menu page (HELP_MENU_LINK / HELP_MENU_LINK_IF).
typedef struct {
    u32 dwTextId;
    const u32 *pPage;
    u32 bAvailable;  // 0 when its IsHelpTopicUnlocked predicate fails; drawn in a different text style
} HelpMenuEntry;

// Array capacities are the gaps between the fields in IWRAM.
typedef struct {
    Actor *pTitleActor;                // 0x00
    s32 dwPaletteEffect;                 // 0x04; palette effect handle, -1 when none
    HelpPageFrame aPageStack[12];        // 0x08
    u8 bPageDepth;                       // 0x68; pages opened from menus, 0 on the root menu
    u8 bPageKind;                        // 0x69; HelpPageKind of the page on screen
    u8 abPad_6A[2];
    const u32 *pPendingPage;             // 0x6C; page to load on the next frame, or NULL
    Actor *pCursor;                     // 0x70; the menu cursor, NULL on text pages
    u32 dwEntryCount;                    // 0x74
    HelpMenuEntry aEntries[14];          // 0x78
    u8 bSelectedEntry;                   // 0x120
    u8 abPad_121[3];
    u32 dwTextTileCursor;                // 0x124; next free text tile, passed to and returned by DrawTextLines
    Actor *apSprites[8];                // 0x128; the page's arrow sprites
    u32 dwSpriteCount;                   // 0x148
    const u32 *pNextPage;                // 0x14C; HELP_NEXT_PAGE
    const u32 *pPrevPage;                // 0x150; HELP_PREV_PAGE
    GameMode dwExitMode;                 // 0x154; the mode pushed when the screen is dismissed
    u32 dwExitArg1;                      // 0x158
    u32 dwExitArg2;                      // 0x15C
    u32 dwExitArg3;                      // 0x160
    u32 bStandalone;                     // 0x164; opened directly (HelpTopicScreen) rather than from
                                         // the pause menu
} HelpState;
extern HelpState g_HelpState;

// Builds the screen from a page table. A standalone screen (HelpTopicScreen) builds the
// pause-menu backdrop itself, opens and closes with a screen transition, and leaves straight
// to the exit mode from its first page.
extern void StartHelpScreen(const u32 *pPageTable, s32 bStandalone);

// Stores the PushGameMode_3 arguments used when the screen is dismissed.
extern void SetHelpExitMode(GameMode mode, s32 arg1, s32 arg2, s32 arg3);

// From a standalone screen's first page, pushes the stored mode and starts the screen
// transition out. Otherwise fades out (HelpScreenStateFadeOut) to the parent page, or out of
// the screen from the first page.
extern void LeaveHelpScreen(void);

// Frees the screen's actors and particles.
extern void FreeHelpScreen(void);

// Removes the current page's text, cursor and sprites.
extern void ClearHelpScreen(void);
// Opens the selected entry of a menu page.
extern void OpenSelectedHelpMenuEntry(void);
// Moves a menu page's selection to the given entry and redraws it.
extern void SetHelpMenuSelection(u32 entry);
extern void TurnToPrevHelpPage(void);
extern void TurnToNextHelpPage(void);
// B button: plays the cancel sound and leaves the screen.
extern void CancelHelpScreen(void);
// Draws a page from its script.
extern void RunHelpScript(const u32 *pScript);
// Spawns a page sprite (HELP_SPRITE); x 0xB4 is the right arrow, which is drawn flipped.
extern void SpawnHelpPageSprite(u32 x, u32 y, u32 assetIndex);
// Draws a menu entry's label; color is the SelectTextFont color of an available entry.
extern void DrawHelpMenuEntry(u32 entry, u32 color);
// Menu cursor tick: slides the cursor to the selected entry.
extern void TickHelpMenuCursor(Actor *pActor);
// Draws a text box (HELP_TEXT, HELP_TITLE).
extern void DrawHelpTextBox(s32 x, s32 y, s32 width, s32 height, u32 textId, u32 color);
// Loads the title palette and spawns the "Help" title.
extern void SpawnHelpScreenTitle(void);

// Menu entry rows: pixel height (also the line height) and text width.
#ifdef VERSION_JP
#define HELP_MENU_ROW_HEIGHT 9
#define HELP_MENU_ROW_WIDTH 0xD0
#else
#define HELP_MENU_ROW_HEIGHT 8
#define HELP_MENU_ROW_WIDTH 0xC8
#endif

extern void InitializeHelp(void);
extern void UpdateHelp(void);
extern void ExitHelpScreen(void);

// g_GameModeStackContext.dwModeState in the Help screen.
typedef enum {
    HelpScreenStateFadeIn = 1,
    HelpScreenStateBrowse = 2,
    HelpScreenStateFadeOut = 3,
    HelpScreenStateLoadPage = 4,  // the pending page, else the parent page, else frees the screen
    HelpScreenStateExit = 5,      // pushes dwExitMode
} HelpScreenMode;

// Help screen scripts (help_pages.c). The engine reads a page as a stream of
// 32-bit words: the low byte of each command word is the opcode and the upper bytes its
// parameters; commands that take operands are followed by that many words. A page ends with
// HELP_END. Pointer operands are the addresses of other pages.
typedef enum {
    HelpPageText = 0,  // reads as a text page
    HelpPageMenu = 1,  // a list of entries linking to pages
} HelpPageKind;

typedef enum {
    HelpOpEnd = 0,
    HelpOpHeader = 1,
    HelpOpMenuLink = 2,
    HelpOpMenuLinkIf = 3,
    HelpOpSelectEntry = 4,    // selected entry in byte 1; unused in the data
    HelpOpText = 5,
    HelpOpTitle = 6,
    HelpOpPageNumber = 7,
    HelpOpSprite = 8,
    HelpOpNop = 9,            // unused in the data
    HelpOpSetTextTileCursor = 10,  // dwTextTileCursor in bytes 2-3; unused in the data
    HelpOpNextPage = 11,
    HelpOpPrevPage = 12,
} HelpOp;

#define HELP_OP(op, b1, b2, b3) ((u32)(op) | (u32)(b1) << 8 | (u32)(b2) << 16 | (u32)(b3) << 24)

// Ends the page.
#define HELP_END                          HelpOpEnd
// Page kind: HelpPageText, or HelpPageMenu (records the page and spawns the menu cursor).
#define HELP_HEADER(kind)                 HELP_OP(HelpOpHeader, kind, 0, 0)
// Menu entry: label text id and the page it opens. LINK_IF adds a predicate on the entry
// (IsHelpTopicUnlocked) that decides whether the page can be opened.
#define HELP_MENU_LINK(textId, page)      HelpOpMenuLink, (textId), (u32)(page)
#define HELP_MENU_LINK_IF(textId, page, isAvailable) \
    HelpOpMenuLinkIf, (textId), (u32)(page), (u32)(isAvailable)
// Text box at (x, y) of the given size.
#define HELP_TEXT(x, y, w, h, textId)     HELP_OP(HelpOpText, x, y, 0), (w) | (u32)(h) << 8, (textId)
// One-line title box at (0x10, 0x20).
#define HELP_TITLE(textId)                HelpOpTitle, (textId)
// "current/total" (text 0x8EF) at the bottom of the page.
#define HELP_PAGE_NUMBER(current, total)  HELP_OP(HelpOpPageNumber, current, total, 0)
// Page-turn arrow sprite: index into g_aHelpSpriteAssets, then screen position.
#define HELP_SPRITE(assetIndex, x, y)     HELP_OP(HelpOpSprite, assetIndex, x, y)
// Pages reached with Right and Left.
#define HELP_NEXT_PAGE(page)              HelpOpNextPage, (u32)(page)
#define HELP_PREV_PAGE(page)              HelpOpPrevPage, (u32)(page)

// Whether the minigame or Owl Care Kit topic in a menu entry is unlocked; pTextId is the
// entry's label text id (the minigame names, 0xA4A-0xA4E, or "Owl Care Kit").
extern s32 IsHelpTopicUnlocked(const u32 *pTextId);

extern const u32 g_aHelpMenuMain[];
extern const u32 g_aHelpMenuFolios[];
extern const u32 g_aHelpMenuCollectorCards[];
extern const u32 g_aHelpMenuItems[];
extern const u32 g_aHelpMenuMiniGames[];
extern const u32 g_aHelpFolioUniversitas[];
extern const u32 g_aHelpFolioBruti[];
extern const u32 g_aHelpTradeCards[];
extern const u32 g_aHelpMagicalEncounters[];
extern const u32 g_aHelpEquipItems[];
extern const u32 g_aHelpUsingItems[];
extern const u32 g_aHelpWizardCrackerPopIt[];
extern const u32 g_aHelpBuckbeakMinigame[];
extern const u32 g_aHelpBoggart[];
extern const u32 g_aHelpTeaLeafDivination[];
extern const u32 g_aHelpDementors[];
extern const u32 g_aHelpCardComboGlossary[];
extern const u32 g_aHelpPotionsGlossary[];
extern const u32 g_aHelpItemsGlossary[];
extern const u32 g_aHelpSpecialMovesGlossary[];
extern const u32 g_aHelpOwlCareKit[];

// Help screen sprites, drawn by SpawnHelpPageSprite with the palette of the same index.
extern const ActorAssetRecord g_aHelpSpriteAssets[22];
extern const void *const g_apHelpSpritePalettes[22];

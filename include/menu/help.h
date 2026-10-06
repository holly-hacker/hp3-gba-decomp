#pragma once

#include "types.h"
#include "game/game_modes.h"
#include "graphics/object.h"

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
    Object *pTitleObject;                // 0x00
    s32 dwPaletteEffect;                 // 0x04; palette effect handle, -1 when none
    HelpPageFrame aPageStack[12];        // 0x08
    u8 bPageDepth;                       // 0x68; pages opened from menus, 0 on the root menu
    u8 bPageKind;                        // 0x69; HelpPageKind of the page on screen
    u8 abPad_6A[2];
    const u32 *pPendingPage;             // 0x6C; page to load on the next frame, or NULL
    Object *pCursor;                     // 0x70; the menu cursor, NULL on text pages
    u32 dwEntryCount;                    // 0x74
    HelpMenuEntry aEntries[14];          // 0x78
    u8 bSelectedEntry;                   // 0x120
    u8 abPad_121[3];
    u32 dwTextLines;                     // 0x124; DrawTextLines state of the page's text
    Object *apSprites[8];                // 0x128; the page's arrow sprites
    u32 dwSpriteCount;                   // 0x148
    const u32 *pNextPage;                // 0x14C; HELP_NEXT_PAGE
    const u32 *pPrevPage;                // 0x150; HELP_PREV_PAGE
    GameMode dwExitMode;                 // 0x154; the mode pushed when the screen is dismissed
    u32 dwExitArg1;                      // 0x158
    u32 dwExitArg2;                      // 0x15C
    u32 dwExitArg3;                      // 0x160
    u32 bTopicScreen;                    // 0x164; set when entered as HelpTopicScreen
} HelpState;
extern HelpState g_HelpState;

// Builds the screen from a page table. A nonzero second argument is the
// HelpTopicScreen variant, which dims the backdrop instead of fading the pause menu.
extern void StartHelpScreen(const u32 *pPageTable, s32 bTopicScreen);

// Stores the PushGameMode_3 arguments used when the screen is dismissed.
extern void SetHelpExitMode(GameMode mode, s32 arg1, s32 arg2, s32 arg3);

// Pushes the stored mode and starts the screen transition out.
extern void LeaveHelpScreen(void);

// Frees the screen's objects and particles.
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

extern void UpdateHelp(void);

// Help screen scripts (src/gamemode/modes/help/help_pages.c). The engine reads a page as a stream of
// 32-bit words: the low byte of each command word is the opcode and the upper bytes its
// parameters; commands that take operands are followed by that many words. A page ends with
// HELP_END. Pointer operands are the addresses of other pages.
typedef enum {
    HelpPageText = 0,  // reads as a text page
    HelpPageMenu = 1,  // a list of entries linking to pages
} HelpPageKind;

#define HELP_OP(op, b1, b2, b3) ((u32)(op) | (u32)(b1) << 8 | (u32)(b2) << 16 | (u32)(b3) << 24)

#define HELP_END                          0
#define HELP_HEADER(kind)                 HELP_OP(1, kind, 0, 0)
// Menu entry: label text id and the page it opens. LINK_IF adds a predicate on the entry
// (IsHelpTopicUnlocked) that decides whether the page can be opened.
#define HELP_MENU_LINK(textId, page)      2, (textId), (u32)(page)
#define HELP_MENU_LINK_IF(textId, page, isAvailable) 3, (textId), (u32)(page), (u32)(isAvailable)
// Text box at (x, y) of the given size.
#define HELP_TEXT(x, y, w, h, textId)     HELP_OP(5, x, y, 0), (w) | (u32)(h) << 8, (textId)
#define HELP_TITLE(textId)                6, (textId)
#define HELP_PAGE_NUMBER(current, total)  HELP_OP(7, current, total, 0)
// Page-turn arrow sprite: index into g_aHelpSpriteAssets, then screen position.
#define HELP_SPRITE(assetIndex, x, y)     HELP_OP(8, assetIndex, x, y)
#define HELP_NEXT_PAGE(page)              11, (u32)(page)
#define HELP_PREV_PAGE(page)              12, (u32)(page)

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
extern const u32 g_aHelpHippogriffGlide[];
extern const u32 g_aHelpRiddikulus[];
extern const u32 g_aHelpTeaLeafDivination[];
extern const u32 g_aHelpDementors[];
extern const u32 g_aHelpCardComboGlossary[];
extern const u32 g_aHelpPotionsGlossary[];
extern const u32 g_aHelpItemsGlossary[];
extern const u32 g_aHelpSpecialMovesGlossary[];
extern const u32 g_aHelpOwlCareKit[];

#pragma once

#include "types.h"
#include "actor.h"
#include "char_block.h"
#include "math.h"
#include "palette.h"

// Serve Pumpkin Juice, game mode 0x24 (UnusedServePumpkinJuiceMinigame). No
// screen pushes this mode, but its handlers are present in the dispatch table.
// The bartender pours goblets of pumpkin juice down three bar lanes towards
// customers walking in from the left, and catches the empty goblets they slide
// back. A full goblet reaching the left end, an empty one passing the bartender or a
// customer reaching the bar loses the game.

#define SERVE_PUMPKIN_JUICE_LANE_COUNT 3
#define SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT 9

// The mode's screen state at 0x03005238, driven by g_GameModeStackContext.dwModeState.
typedef struct {
    u32 dwScoreChanged;   // 0x00; nonzero redraws the score next frame
    u32 dwScore;          // 0x04
    u32 dwLane;           // 0x08; the bartender's lane, moved with up/down
    u32 dwRound;          // 0x0C; starts at 1
    u32 dwMenuSelection;  // 0x10; row of the pause menu
    u32 dwTextTileBase;   // 0x14; first text tile; the score is drawn from it
    u32 dwMenuTileBase;   // 0x18; text tile after the score; the menu is drawn from it
    u32 dwTileCursor;     // 0x1C; text tile cursor after the last string
    s32 adwCustomerCount[SERVE_PUMPKIN_JUICE_LANE_COUNT];  // 0x20
    IntPoint aLanePos[SERVE_PUMPKIN_JUICE_LANE_COUNT];     // 0x2C; the bartender's spot per lane
    u32 dwCustomerTypesInUse;  // 0x44; g_adwServePumpkinJuiceCustomerTypeBits of the customers
    // 0x48; per lane, whether the tap is pouring and whether BG1 shows it pouring
    u8 aabTapPouring[SERVE_PUMPKIN_JUICE_LANE_COUNT][2];
    IntPoint pourOffset;  // 0x50; anchor 0 of the bartender's pouring frame
    const u16 *pBg1Tilemap;// 0x58; LoadBgGraphic's result for BG1
} ServePumpkinJuiceState;

extern ServePumpkinJuiceState g_ServePumpkinJuice;  // 0x03005238

// Actor.bKind of the minigame's actors, read by the touch handlers.
typedef enum {
    ServePumpkinJuiceActorBartender = 1,
    ServePumpkinJuiceActorFullGoblet = 2,
    ServePumpkinJuiceActorCustomer = 4,
    ServePumpkinJuiceActorEmptyGoblet = 8,
    ServePumpkinJuiceActorPuff = 16,
} ServePumpkinJuiceActorKind;

// Rows of g_aabServePumpkinJuiceGobletAnims.
typedef enum {
    ServePumpkinJuiceGobletAnimEmpty = 0,
    ServePumpkinJuiceGobletAnimFull = 1,
    ServePumpkinJuiceGobletAnimEmptyFalling = 2,
    ServePumpkinJuiceGobletAnimEmptySmash = 3,
    ServePumpkinJuiceGobletAnimFullFalling = 4,
    ServePumpkinJuiceGobletAnimFullSmash = 5,
} ServePumpkinJuiceGobletAnim;

// Rows of g_aabServePumpkinJuiceBartenderAnims.
typedef enum {
    ServePumpkinJuiceBartenderAnimFill = 0,
    ServePumpkinJuiceBartenderAnimServe = 1,
    ServePumpkinJuiceBartenderAnimRun = 2,
    ServePumpkinJuiceBartenderAnimDrop = 3,
} ServePumpkinJuiceBartenderAnim;

// Rows of g_aabServePumpkinJuiceCustomerAnims. Type 6 walks with
// ...AnimWalkVariant + wActionVariant and drinks with ...AnimDrinkVariant.
typedef enum {
    ServePumpkinJuiceCustomerAnimWalk = 0,
    ServePumpkinJuiceCustomerAnimDrink = 1,
    ServePumpkinJuiceCustomerAnimWalkVariant = 2,
    ServePumpkinJuiceCustomerAnimDrinkVariant = 4,
} ServePumpkinJuiceCustomerAnim;

// BG control words, graphics, animations and strings.
extern const u8 g_aabServePumpkinJuiceGobletAnims[6][10];      // 0x08069038
extern const u8 g_aabServePumpkinJuiceBartenderAnims[4][28];   // 0x08069074
extern const u8 g_aabServePumpkinJuiceBartenderArmAnims[3][12];  // 0x080690E4
extern const u8 g_aabServePumpkinJuiceCustomerAnims[5][10];    // 0x08069108
extern const u8 g_abServePumpkinJuicePuffAnim[14];             // 0x0806913A
extern const u32 g_adwServePumpkinJuiceCustomerTypeBits[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT];  // 0x08069148
extern const IntPoint g_aServePumpkinJuiceTapCells[SERVE_PUMPKIN_JUICE_LANE_COUNT];  // 0x0806916C
extern const u32 g_dwServePumpkinJuiceBg0Control;  // 0x08069184
extern const u32 g_dwServePumpkinJuiceBg1Control;  // 0x08069188
extern const u32 g_dwServePumpkinJuiceBg2Control;  // 0x0806918C
extern const u32 g_dwServePumpkinJuiceBg3Control;  // 0x08069190
extern const ActorGfxRecord g_ServePumpkinJuiceGobletSprite;      // 0x08069194
extern const ActorGfxRecord g_ServePumpkinJuiceBartenderSprite;   // 0x0806919C
extern const ActorGfxRecord g_ServePumpkinJuiceBartenderArmSprite;  // 0x080691A4
extern const ActorGfxRecord g_ServePumpkinJuicePuffSprite;        // 0x080691AC
extern const ActorGfxRecord
    g_aaServePumpkinJuiceCustomerSprites[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT][2];  // 0x080691B4
// Per type, how many body palettes follow the part palette in the row below.
extern const u8 g_abServePumpkinJuiceCustomerPaletteCounts[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT];  // 0x08069244
// Per type, the part's palette, then the body palettes picked from at random.
extern const ObjPalette *const
    g_aapServePumpkinJuiceCustomerPalettes[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT][4];  // 0x08069250
// Per type, the body and part sprites.
extern const ActorGfxRecord *const
    g_aapServePumpkinJuiceCustomerSpriteRows[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT][2];  // 0x080692E0
extern const BgTileAnimation16 g_ServePumpkinJuiceTable;  // 0x08069328
extern const u8 g_ServePumpkinJuicePauseText[];    // 0x080693B0
extern const u8 g_ServePumpkinJuiceResultsText[];  // 0x080693C0

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    ServePumpkinJuiceStatePlaying = 0,
    ServePumpkinJuiceStateWaitInput = 1,
    ServePumpkinJuiceStateNextRound = 2,
    ServePumpkinJuiceStatePauseMenu = 3,
    ServePumpkinJuiceStateResults = 4,
    ServePumpkinJuiceStateRoundOver = 5,
} ServePumpkinJuiceMode;

extern void InitializeUnusedServePumpkinJuiceMinigame(void);
extern void UpdateUnusedServePumpkinJuiceMinigame(void);
extern void ExitUnusedServePumpkinJuiceMinigame(void);
extern void TickServePumpkinJuiceFullGoblet(Actor *goblet);
extern void TickServePumpkinJuiceEmptyGoblet(Actor *goblet);
extern void TickServePumpkinJuiceDroppedGoblet(Actor *goblet);
extern void TickServePumpkinJuiceBartenderArm(Actor *arm);
extern void TickServePumpkinJuiceBartender(Actor *bartender);
extern void TickServePumpkinJuiceCustomer(Actor *customer);
extern void TickServePumpkinJuiceCustomerPart(Actor *part);
extern void SpawnServePumpkinJuiceBartender(void);
extern void SpawnServePumpkinJuiceFullGoblet(void);
extern void SpawnServePumpkinJuiceEmptyGoblet(u32 lane, s32 x);
extern void SpawnServePumpkinJuiceCustomer(s32 lane, u32 type, u32 queuePos);
extern void HandleServePumpkinJuiceCustomerTouch(Actor *customer, Actor *other);
extern void DrawServePumpkinJuiceTaps(void);
extern void SpawnServePumpkinJuiceCustomers(void);
extern void HandleServePumpkinJuiceGobletTouch(Actor *goblet, Actor *other);
extern void HandleServePumpkinJuiceBartenderTouch(Actor *bartender, Actor *other);
extern void DrawServePumpkinJuicePauseMenu(void);
extern void StartServePumpkinJuiceGame(void);
extern void DrawServePumpkinJuiceScore(void);
extern u32 PickServePumpkinJuiceCustomerType(void);
extern void SpawnServePumpkinJuicePuff(s32 x, s32 y);
extern void TickServePumpkinJuicePuff(Actor *puff);

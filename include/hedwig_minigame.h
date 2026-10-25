#pragma once

#include "types.h"
#include "actor.h"

void InitializeOwlCareKitScreen(void);
void HandleOwlCareKitScreenTick(void);
void HandleOwlCareKitScreenExit(void);
void DeserializeOwlCareKit(void);
void SerializeOwlCareKit(void);

// Per-tick Owl Care Kit clock, a no-op until the care screen has been visited.
// Counts down the Mail flight timer, otherwise advances the elapsed-tick counter;
// each time that passes 149 it resets and, if nGrowCounters is set, raises all
// six care counters by 1 (cap 250).
void ProcessOwlCareKitTick(s32 nGrowCounters);

#define OWL_CARE_KIT_MAX_DROPPINGS 50

// OwlCareKitScreenState.bPanel: what the bottom panel shows.
typedef enum {
    OwlCareKitPanelNone = 0,   // while the owl leaves with or returns from the mail
    OwlCareKitPanelMenu = 1,
    OwlCareKitPanelAway = 2,
    OwlCareKitPanelMail = 3,   // the delivered mail's reward
} OwlCareKitPanel;

// Owl Care Kit care screen, game mode 0x29 (OwlCareMinigame). The screen's live
// state is the 0xE8-byte block at g_OwlCareKitScreen, cleared by
// InitializeOwlCareKitScreen. The persistent care data lives in
// g_saveStateBlock.owlCareKit.
typedef struct {
    Actor *pOwl;                  // 0x00; the owl actor
    Actor *pCursor;               // 0x04; the menu cursor, released on exit
    Actor *pCleaner;              // 0x08; the Clean action's sparkle sweep while it runs
    Actor *apDroppings[OWL_CARE_KIT_MAX_DROPPINGS];  // 0x0C
    u8 abShownMeters[3];          // 0xD4; meter values drawn, all start at 250
    u8 abUnmapped_D7[1];
    s32 nUnused;                  // 0xD8; cleared on entry, never read
    u8 bUnused;                   // 0xDC; cleared on entry, never read
    u8 bMetersRedrawn;            // 0xDD; set when a meter bar is redrawn
    u8 bPanel;                    // 0xDE; OwlCareKitPanel
    u8 bDroppingCount;            // 0xDF; apDroppings in use
    u8 bShownSelection;           // 0xE0; menu entry whose label is drawn, starts at 5
    u8 abUnmapped_E1[3];
    u8 bBgFrameOnLayer3;          // 0xE4; which of BG2/BG3 the next background frame goes to
    s8 nBlendStep;                // 0xE5; +1 or -1, the direction of the background crossfade
    u8 bBgTimer;                  // 0xE6
    u8 bBgFrame;                  // 0xE7; g_aOwlCareBgFrames index
} OwlCareKitScreenState;          // 0xE8

extern OwlCareKitScreenState g_OwlCareKitScreen;  // 0x03003270

// The owl's Actor.bActionState, an index into g_aOwlAnims. States 21-23 are
// never entered.
typedef enum {
    OwlStateIdle = 0,
    OwlStateIdleAnim1 = 1,         // OwlStateIdleAnim1-5 play at random while idle
    OwlStateIdleAnim2 = 2,
    OwlStateIdleAnim3 = 3,
    OwlStateIdleAnim4 = 4,         // turns to face the middle of the cage
    OwlStateIdleAnim5 = 5,         // hops toward the middle of the cage
    OwlStateFed = 6,
    OwlStateCleaned = 7,
    OwlStatePetted = 8,
    OwlStateGroomed = 9,
    OwlStateFlap = 10,             // flies about, then glides down in OwlStateGlide
    OwlStateTaught = 11,
    OwlStateRefusePet = 12,        // continues with OwlStateIdleAnim3
    OwlStateRefuseGroom = 13,      // continues with OwlStateIdleAnim3
    OwlStateRefuse = 14,
    OwlStateNeedFeed = 15,         // the need states show a thought bubble
    OwlStateNeedClean = 16,
    OwlStateNeedPet = 17,
    OwlStateNeedGroom = 18,
    OwlStateNeedExercise = 19,
    OwlStateNeedTeach = 20,
    OwlStateUnusedA = 21,          // OwlStateUnusedA-C are never set; each has its own animation
    OwlStateUnusedB = 22,
    OwlStateUnusedC = 23,
    OwlStateMailDepart = 24,
    OwlStateMailReturn = 25,
    OwlStateLand = 26,
    OwlStateGlide = 27,
    OwlStateTakeOff = 28,          // Exercise: takes off into OwlStateFlap
    OwlStateAway = 29,
    OwlStateMailDelivered = 30,
} OwlState;

#define OWL_STATE_COUNT 31

// One g_aOwlAnims entry: SetActorAnimData's sprite and stream.
typedef struct {
    const ActorGfxRecord *pSprite;
    const u8 *pAnim;
} OwlAnim;

// The owl states of one care action, by menu entry (Feed, Clean, Pet, Groom,
// Exercise, Teach).
typedef struct {
    u8 bCareState;     // the action was accepted
    u8 bRefuseState;   // its care counter was above OWL_CARE_NEED_THRESHOLD
    u8 bNeedState;     // the owl asks for it, OwlStateNeedFeed-OwlStateNeedTeach
} OwlCareActionStates;

// A care counter above this makes the owl refuse that action and Mail.
#define OWL_CARE_NEED_THRESHOLD 186

// Top-left tile of one 30x20 background frame in the BG3 tilemap.
typedef struct {
    u8 bX;
    u8 bY;
} OwlCareBgFrame;

extern const ActorGfxRecord g_aOwlCareSprites[16];
extern const u32 g_dwOwlCareBg3Control;
extern const u32 g_dwOwlCareBg2Control;
extern const u32 g_dwOwlCareBg1Control;
extern const u32 g_dwOwlCareBg0Control;
extern const OwlCareBgFrame g_aOwlCareBgFrames[4];
extern const OwlCareActionStates g_aOwlCareActionStates[6];
extern const OwlAnim g_aOwlAnims[OWL_STATE_COUNT];
// By need state - OwlStateNeedFeed.
extern const ActorAssetRecord g_aOwlThoughtBubbleSprites[OwlStateNeedTeach - OwlStateNeedFeed + 1];
extern const ActorAssetRecord g_OwlCareCleanerSparkles;
extern const u8 g_abOwlThoughtBubbleAnim[28];
extern const ActorAssetRecord g_OwlCageDoorSprite;
// The cage door's animations: shut, opening, open, closing.
extern const u8 *const g_apOwlCageDoorAnims[4];

// Owl animation streams, see g_aOwlAnims.
extern const u8 g_abOwlCareAnim00[4];
extern const u8 g_abOwlCareAnim01[8];
extern const u8 g_abOwlCareAnim02[28];
extern const u8 g_abOwlCareAnim03[28];
extern const u8 g_abOwlCareAnim04[16];
extern const u8 g_abOwlCareAnim05[20];
extern const u8 g_abOwlCareAnim06[44];
extern const u8 g_abOwlCareAnim07[44];
extern const u8 g_abOwlCareAnim08[72];
extern const u8 g_abOwlCareAnim09[44];
extern const u8 g_abOwlCareAnim10[16];
extern const u8 g_abOwlCareAnim11[44];
extern const u8 g_abOwlCareAnim12[36];
extern const u8 g_abOwlCareAnim13[32];
extern const u8 g_abOwlCareAnim14[56];
extern const u8 g_abOwlCareAnim21[16];
extern const u8 g_abOwlCareAnim22[20];
extern const u8 g_abOwlCareAnim23[16];
extern const u8 g_abOwlCareAnim24[48];
extern const u8 g_abOwlCareAnim25[52];
extern const u8 g_abOwlCareAnim26[20];
extern const u8 g_abOwlCareAnim27[12];
extern const u8 g_abOwlCareAnim28[16];
// Cage door animation streams, see g_apOwlCageDoorAnims.
extern const u8 g_abOwlCageDoorAnim0[4];
extern const u8 g_abOwlCageDoorAnim1[12];
extern const u8 g_abOwlCageDoorAnim2[4];
extern const u8 g_abOwlCageDoorAnim3[12];

// Care counter weights of each stat meter.
extern const u8 g_aabOwlStatMeterWeights[3][6];
// The owl's palette, by OwlCareKitState.bTypeIndex.
extern const void *const g_apOwlTypePalettes[3];

extern void UpdateOwlCareKitPanel(void);
extern void ProcessOwlMailReward(void);
extern u32 ConfirmOwlCareKitAction(void);  // A button: nonzero if the selected action was accepted
extern u32 ProcessOwlCareAction(u32 action);
extern void UpdateOwlStatMeters(s32 snap);
extern void TickOwlCareKitBackground(void);
extern void SpawnOwlCareKitActors(void);
extern void TickOwlActor(Actor *pOwl);
extern void UpdateOwlDroppings(void);
extern u32 StartOwlCleaning(void);
extern void TickOwlCleaner(Actor *pCleaner);
extern void AttachOwlCleanerEmitter(Actor *pCleaner, u8 spawnPeriod, u8 lifetimeBase, u8 spread,
                                    u8 spawnsPerPeriod, u8 pool, u8 entry);
extern Actor *InitializeOwlActorSprite(void);
extern void SetOwlPaletteRow(u32 row);
extern void HandleOwlCareKitCancel(void);
extern void StepOwlCareKitSelection(void);
extern void DrawOwlCareKitTextPanel(void);
extern void DrawOwlAwayMessage(void);
extern void DrawOwlName(void);
extern void DrawOwlCareKitMenuLabel(void);
extern void DrawOwlCareKitMenuIcon(u32 entry, u32 highlighted);
extern void UpdateOwlStatMeterBars(void);
extern void DrawOwlStatMeterBar(u32 meter, u32 value);
extern void ResetOwlCareKit(void);  // first visit: sets the visited flag and resets the care counters
extern s32 FindOwlNeediestCare(void);
extern u32 SelectOwlMailRewardItem(s32 budget);
extern void SetOwlCageDoorAnim(u32 anim);
extern void TickOwlCageDoor(Actor *pDoor);
extern void TickOwlCareKitCursor(Actor *pCursor);
extern void SetOwlState(u32 state);
extern void SpawnOwlThoughtBubble(u32 state);
extern void TickOwlThoughtBubble(Actor *pBubble);
extern void DestroyOwlCleaner(Actor *pCleaner);

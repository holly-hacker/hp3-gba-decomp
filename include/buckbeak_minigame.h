#pragma once

#include "types.h"
#include "actor.h"
#include "math.h"
#include "graphics/display.h"
#include "graphics/floor_effect.h"
#include "graphics/scanline_effects.h"
#include "menu/minigame_menu.h"
#include "gen/graphics/minigames/buckbeak.h"

extern u32 g_dwBuckbeakMinigameForceOverworldExit;  // 0x03002084; set by StartMinigame

// Buckbeak's Hippogriff Glide, game mode 0x2B (BuckbeakMinigame). Buckbeak
// glides over a perspective floor and steers through rings before the time
// runs out; each ring adds a point and extra time.

// A 16.16 value whose whole part is also read on its own, as a signed angle
// (256 per turn, an index into g_anSineTable) or a height in pixels.
typedef union {
    s32 dwValue;
    struct {
        u16 wFraction;
        s16 wWhole;
    } parts;
} BuckbeakMinigameFixed;

// A position on the ground plane plus a height, all 16.16.
typedef struct {
    FixedPoint ground;
    s32 dwHeight;
} BuckbeakMinigameWorldPos;

typedef struct {
    FixedPoint xy;      // pixels, 16.16
    s32 dwDepth;        // distance ahead of the camera
} BuckbeakMinigameScreenPos;

// A world position and where ProjectBuckbeakMinigamePoint puts it on screen.
typedef struct {
    BuckbeakMinigameWorldPos world;      // 0x00
    BuckbeakMinigameScreenPos screen;    // 0x0C
    s32 dwScale;                         // 0x18; larger when closer
} BuckbeakMinigameProjection;

// A ring Buckbeak flies through, drawn as three orbiting actors.
typedef struct {
    u8 bActive;                          // 0x00
    u8 bVisible;                         // 0x01; the point projected onto the screen
    u8 bTargeted;                        // 0x02; drawn with the highlighted palette
    u8 bSpawnParam;                      // 0x03; SpawnBuckbeakMinigameRing's last argument, 0 for every ring; never read
    BuckbeakMinigameProjection point;    // 0x04
    Actor *apParts[3];                   // 0x20
} BuckbeakMinigameRing;                  // 0x2C

#define BUCKBEAK_MINIGAME_RING_COUNT 9

// Allocated by InitializeBuckbeakMinigame, freed by ExitBuckbeakMinigame.
typedef struct {
    u32 dwMenuSelection;                 // 0x00; 0 resume, 1 replay, 2 exit
    u32 dwScore;                         // 0x04; rings flown through
    s32 dwTimeLeft;                      // 0x08; 8.8 seconds
    s32 dwTimeBonus;                     // 0x0C; added per ring, shrinks by a fifth each time
    Actor *pCursor;                      // 0x10; the results menu cursor
    FixedPoint camera;                   // 0x14; ground position
    BuckbeakMinigameFixed dwCameraHeight;  // 0x1C
    s32 nHorizonOffset;                         // 0x20
    s32 dwSpeed;                         // 0x24; forward speed, lower while climbing
    s32 dwCameraDistance;                // 0x28; how far behind Buckbeak the camera trails
    BuckbeakMinigameFixed dwHeading;     // 0x2C
    BuckbeakMinigameFixed dwCameraHeading;  // 0x30; follows dwHeading with a lag
    BuckbeakMinigameProjection player;   // 0x34
    Actor *pBuckbeak;                    // 0x50
    s32 dwClimbRate;                     // 0x54
    s32 dwTurnRate;                      // 0x58
    u32 dwBankState;                     // 0x5C; 0 level, 1 banking right, 2 banking left
    u8 bNextRing;                        // 0x60; index of the ring to fly through
    u8 bDifficulty;                      // 0x61
    u8 bResultsDelay;                    // 0x62; frames until the results menu opens
    u8 bWarningDelay;                    // 0x63; frames between low-time beeps
    BuckbeakMinigameRing aRings[BUCKBEAK_MINIGAME_RING_COUNT];  // 0x64
} BuckbeakMinigameState;  // 0x1F0

extern BuckbeakMinigameState *g_pBuckbeakMinigame;  // 0x03002088

// Slots of g_apTextActors this minigame fills.
typedef enum {
    BuckbeakMinigameTextResume = 0,
    BuckbeakMinigameTextReplay = 1,
    BuckbeakMinigameTextExit = 2,
    BuckbeakMinigameTextScore = 3,
    BuckbeakMinigameTextTime = 4,
} BuckbeakMinigameText;

// BG control words.
extern const u32 g_dwBuckbeakMinigameBg2Control;        // US 0x0804C284
extern const u32 g_dwBuckbeakMinigameBg1Control;        // US 0x0804C288
extern const u32 g_dwBuckbeakMinigameBg0Control;        // US 0x0804C28C
extern const u32 g_dwBuckbeakMinigameBg2GroundControl;  // US 0x0804C290

// Sprite resources: Buckbeak level, banking right and banking left (the same
// sprite flipped), then the ring.
extern const ActorAssetRecord g_aBuckbeakMinigameBuckbeakAssets[3];  // US 0x0804C294
extern const u8 g_abBuckbeakMinigameFlyAnimData[32];                 // US 0x0804C2C4
extern const ActorAssetRecord g_BuckbeakMinigameRingAsset;           // US 0x0804C2E4
// Per difficulty: the BG1 and BG0 graphics.
extern const void *const g_aapBuckbeakMinigameBgGraphics[3][2];      // US 0x0804C2F4
extern const u8 g_abBuckbeakMinigameRingAnimData[28];                // US 0x0804C30C
extern const ScanlineEffectEntry g_aBuckbeakMinigameScanlineEffects[2];  // US 0x0804C328
// Start positions of the nine rings.
extern const BuckbeakMinigameWorldPos g_aBuckbeakMinigameRingPositions[BUCKBEAK_MINIGAME_RING_COUNT];  // US 0x0804C348
extern const BgTileAnimation16 g_BuckbeakMinigameWaterAnimation;    // US 0x0804C3B4

// Starting time per difficulty, 8.8 seconds.
extern const s32 g_aBuckbeakMinigameStartTimes[3];  // US 0x08FAA824

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    BuckbeakMinigameStateFlying = 0,   // Start opens the results menu
    BuckbeakMinigameStateResults = 1,
    BuckbeakMinigameStateExitSelect = 2,
    BuckbeakMinigameStateFinished = 3, // records the high score, reopens the results menu
} BuckbeakMinigameMode;

extern void SetUpBuckbeakMinigameScene(void);
extern void ResetBuckbeakMinigame(void);
extern void ProcessBuckbeakMinigameFrame(void);
extern void InitializeBuckbeakMinigameResultsMenu(void);
extern void CloseBuckbeakMinigameResultsMenu(void);
extern void HandleBuckbeakMinigameResultsMenuSelect(void);
extern void DrawBuckbeakMinigameTime(void);
extern u32 SpawnBuckbeakMinigameRing(u32 index, BuckbeakMinigameWorldPos position, u32 param);
extern void UpdateBuckbeakMinigameRing(u32 index);
extern u8 ProjectBuckbeakMinigamePoint(BuckbeakMinigameProjection *pPoint);
extern void BeginBuckbeakMinigameGroundScanline(u32 *pPayload0, u32 *pPayload1);
extern void EndBuckbeakMinigameGroundScanline(u32 *pPayload0, u32 *pPayload1);
extern void SetBuckbeakMinigameSkyScroll(u8 heading);
extern void PlaceBuckbeakMinigameBuckbeak(void);
extern void DrawBuckbeakMinigameScore(void);
extern void MoveBuckbeakMinigameMenuCursor(Actor *pCursor);
extern void ClearBuckbeakMinigameRings(void);
extern s32 FindFreeBuckbeakMinigameRing(void);
extern u32 HasBuckbeakMinigameRingBeenReached(u32 index);
extern void RotateBuckbeakMinigameOffset(FixedPoint offset, s32 angle, FixedPoint *pOut);
extern s32 GetBuckbeakMinigameRingFrameRow(BuckbeakMinigameRing *pRing);
extern void ReleaseBuckbeakMinigameActor(Actor **ppActor);
extern void HandleBuckbeakMinigameExitSelect(void);

#pragma once

#include "types.h"
#include "actor.h"
#include "video.h"

extern void InitializeLupinPotionCutscene(void);
extern void UpdateLupinPotionCutscene(void);
extern void ExitLupinPotionCutscene(void);

// The cast's and the camera's scripts are tables of LupinPotionScriptCommand. A command
// runs when it is loaded and lasts until the mode's frame counter
// (g_GameModeStackContext.dwCurrentGameModeArg2) reaches its wEndFrame; a command whose
// wEndFrame has already passed stops the script instead.
typedef enum {
    LupinPotionOpMove = 1,         // cast: velocity (nArg0, nArg1)
    LupinPotionOpFace = 2,         // cast: bFacing = nArg0
    LupinPotionOpPose = 4,         // cast: bActionSubState = nArg0; nArg1 picks pose 4's sprite
    LupinPotionOpStop = 5,         // cast: zero velocity; camera: slow the pan to a stop
    LupinPotionOpDialog = 6,       // cast: show dialog page nArg0 and pause the scripts
    LupinPotionOpPanX = 7,         // camera: pan by nArg0 per frame
    LupinPotionOpPanY = 8,         // camera: move by nArg0 per frame vertically
    LupinPotionOpSetParallax = 9,  // camera: bParallaxScroll = nArg0
    LupinPotionOpEnd = 10,         // stops the script; the camera's ends the cutscene
} LupinPotionScriptOp;

typedef struct {
    u32 dwOp;       // 0x00, LupinPotionScriptOp
    s32 nArg0;      // 0x04
    s32 nArg1;      // 0x08
    u16 wEndFrame;  // 0x0C
} LupinPotionScriptCommand;

typedef struct {
    u32 dwOp;     // 0x00, op of the running command
    s32 nArg;     // 0x04, cast: its nArg1; camera: its nArg0
    u16 wTimer;   // 0x08, frames until the next command loads
    u16 wIndex;   // 0x0A, running command; 0xFFFF before the first
    u32 bActive;  // 0x0C
} LupinPotionScriptRunner;

#define LUPIN_POTION_CAST_COUNT 6
#define LUPIN_POTION_SCRIPT_LENGTH 14
#define LUPIN_POTION_PANEL_PIECES 8  // apPanelActor[8] is the speaker's portrait

// The mode's screen state at 0x03003A84.
typedef struct {
    Actor *apCast[LUPIN_POTION_CAST_COUNT];                            // 0x00
    LupinPotionScriptRunner aCastScripts[LUPIN_POTION_CAST_COUNT];    // 0x18
    LupinPotionScriptRunner cameraScript;                              // 0x78
    u32 bParallaxScroll;  // 0x88: nonzero scrolls BGs 1-3 at different speeds, otherwise only the camera y
    Actor *apPanelActor[LUPIN_POTION_PANEL_PIECES + 1];  // 0x8C: pieces one per 32 pixels of width
    u16 wDialogPage;      // 0xB0
    u16 wDialogLine;      // 0xB2: next line of the page
    s32 nPanelOffset;     // 0xB4: panel's y offset from its resting position (0 = raised, 0x28 = lowered)
} LupinPotionCutsceneState;

// One line of a dialog page; a zero dwTextId ends the page.
typedef struct {
    u32 dwTextId;
    u32 dwSpeaker;  // g_aLupinPotionPanelAssets index of the portrait
} LupinPotionDialogLine;

#define LUPIN_POTION_DIALOG_PAGE_LINES 12

extern LupinPotionCutsceneState g_LupinPotionCutscene;  // 0x03003A84
extern s32 g_aLupinPotionBg2Scroll[2];                  // 0x03003B3C

extern const ScanlineEffectEntry g_aLupinPotionScanlineTable[2];
extern const u32 g_dwLupinPotionBg3Control;
extern const u32 g_dwLupinPotionBg1Control;
extern const u32 g_dwLupinPotionTextBgControl;  // BG2
extern const u32 g_dwLupinPotionBg0Control;
extern const ActorGfxRecord g_LupinPotionShadowGfx;
extern const LupinPotionDialogLine g_aLupinPotionDialog[2][LUPIN_POTION_DIALOG_PAGE_LINES];
extern const IntPoint g_aLupinPotionCastPositions[LUPIN_POTION_CAST_COUNT];
extern const ActorAssetRecord g_aLupinPotionCastAssets[LUPIN_POTION_CAST_COUNT];
extern const ActorAssetRecord g_aLupinPotionPose4Assets[5];  // by the pose command's nArg1
// Poses 0-2 of the first three cast members; the others use g_aLupinPotionCastAssets.
extern const ActorAssetRecord g_aLupinPotionPoseAssets[3][3];
extern const ActorAssetRecord g_aLupinPotionPanelAssets[6];  // 0: panel piece, else portraits
extern const ActorAssetRecord g_aLupinPotionEffectAssets[2];
extern const u8 g_abLupinPotionStandFrames[4];  // by facing
extern const u8 g_aLupinPotionWalkAnims[4][24];      // by facing
extern const u8 g_aLupinPotionPose4Anims[5][62];     // by the pose command's nArg1
extern const u8 g_aLupinPotionPose1Anims[3][36];
extern const u8 g_aLupinPotionPose2WalkAnims[3][24];
extern const u8 g_aLupinPotionPose2StandAnims[3][24];
extern const u8 g_aLupinPotionWalkBackAnims[4][24];  // by facing, moving against it
extern const u8 g_aLupinPotionEffectAnims[2][62];
extern const LupinPotionScriptCommand
    g_aLupinPotionCastScripts[LUPIN_POTION_CAST_COUNT][LUPIN_POTION_SCRIPT_LENGTH];
extern const LupinPotionScriptCommand g_aLupinPotionCameraScript[LUPIN_POTION_SCRIPT_LENGTH];

// Scanline callback that shows the panel on BG2 (see nPanelOffset).
extern void LupinPotionPanelScanlineCallback(u32 *pPayload0, u32 *pPayload1);

extern void LoadLupinPotionCutsceneBgs(void);
extern Actor *SpawnLupinPotionCastActor(s32 index);
extern void TickLupinPotionCastActor(Actor *pActor);
extern void ResetLupinPotionScripts(void);
extern void RunLupinPotionCastScripts(void);
extern void RunLupinPotionCameraScript(void);
extern u32 ShowNextLupinPotionDialogLine(void);
extern void CloseLupinPotionDialogPanel(void);
extern Actor *SpawnLupinPotionPanelActor(s32 kind);
extern Actor *SpawnLupinPotionEffectActor(s32 kind, FixedPoint pos);
extern void SpawnLupinPotionCast(void);
extern void TickLupinPotionShadowActor(Actor *pActor);
extern void TickLupinPotionEffectActor(Actor *pActor);

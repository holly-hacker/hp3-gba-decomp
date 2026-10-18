#pragma once

#include "types.h"
#include "pause_menu.h"
#include "actor.h"

// The mode's text ids live in g_JoybusLinkState (gamecube.h).

// One text of a link status table, with how long it stays.
typedef struct {
    u16 wTextId;
    u16 wFrames;
} GameCubeLinkText;

typedef struct {
    u16 wX;
    u16 wY;
} GameCubeLinkIconPosition;

// Command 0x82's reply: the Owl Care Kit's owl (see OwlCareKitState).
typedef struct {
    u8 bFlags;
    u8 bNameIndex;
    u8 bTypeIndex;
    u8 bUnknown3;
    u8 abStatMeters[3];
    u8 bZero;  // always 0
} GameCubeOwlPacket;

extern const ListMenuDefinition g_GameCubeLinkMenuDefinition;  // 0x08069A2C: title only, no rows
extern const ActorAssetRecord g_aGameCubeLinkIconAssets[3];            // 0x08069A50
extern const GameCubeLinkIconPosition g_aGameCubeLinkIconPositions[3];  // 0x08069A80
extern const GameCubeLinkText g_aGameCubeLinkResultTexts[7];   // 0x08069A8C: by JOYBUS_STATE_*; wFrames holds the text
extern const GameCubeLinkText g_aGameCubeLinkStatusTexts[4];   // 0x08069AA8: by bLinkProgress; wFrames clears the text

extern void InitializeGameCubeLink(void);
extern void UpdateGameCubeLink(void);
extern void ExitGameCubeLink(void);

extern u32 DispatchGameCubeLinkCommand(u32 command, u16 *pLength, u16 *pBuffer);

extern void UpdateGameCubeLinkStatusText(u32 linkEvent);
extern void ShowGameCubeLinkMessage(u32 stringId);
extern void SpawnGameCubeLinkIconActors(void);

// DispatchGameCubeLinkCommand's handlers. The buffer holds bytes.
extern void VerifyGameCubeHandshakeBytes(u16 *pLength, u16 *pBuffer);
extern void FlagGameCubeHeaderReceived(u16 *pLength, u16 *pBuffer);
extern void AcknowledgeGameCubeCommand(u16 *pLength, u16 *pBuffer);
extern void StageGameCubeTestPattern(u16 *pLength, u16 *pBuffer);
extern void StageGameCubeStatusByte(u16 *pLength, u16 *pBuffer);
extern void StageGameCubeStateBytes(u16 *pLength, u16 *pBuffer);

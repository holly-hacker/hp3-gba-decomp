#include "types.h"
#include "audio.h"
#include "battle.h"
#include "display.h"
#include "graphics.h"
#include "game_modes.h"
#include "input.h"
#include "overworld.h"
#include "room.h"
#include "vblank.h"

// The room being loaded, per dwCurrentGameModeArg2.
#define CURRENT_ROOM g_aRoomTable[g_GameModeStackContext.dwCurrentGameModeArg2]

// Overworld mode's pInitFn. Sets up video and the room's BG layers, spawns the
// player, restores or respawns the room's objects and picks the room's music.
// dwCurrentGameModeArg1 is how the mode was entered; Arg2 is the room id.
void InitializeOverworld(void)
{
    u32 prevRoomId;
    u32 bgCtrl3;
    u32 bgCtrl2;
    u32 bgCtrl1;
    u32 bgCtrl0;
    Object *pPlayer;
    const RoomTableEntry *pRoom;

    // Entry: block the pause menu briefly and drop a stale script run state.
    prevRoomId = g_bCurrentRoomId;
    g_dwPauseMenuCooldown = 4;
    StopScanlineEffects();

    if (g_dwRoomScriptRunState == 4)
        g_dwRoomScriptRunState = 0;

    // Resume after a room-script yield: keep the loaded room, at most resume the chain.
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 9)
    {
        if (g_dwRoomScriptRunState == 2
            && (g_bRoomScriptYieldOpcode == 5 || g_bRoomScriptYieldOpcode == 0x24
                || g_bRoomScriptYieldOpcode == 0x2b || g_bRoomScriptYieldOpcode == 0x4f
                || g_bRoomScriptYieldOpcode == 0x50 || g_bRoomScriptYieldOpcode == 0x51
                || g_bRoomScriptYieldOpcode == 0x54 || g_bRoomScriptYieldOpcode == 0x55
                || g_bRoomScriptYieldOpcode == 0x56))
            ResumeRoomSwitchStateChain_candidate();
    }
    else
    {
        // Video, VRAM and VBlank setup.
        sub_08001D90(1);
        sub_0800A914();
        ClearVram();
        ClearResourceCacheSlots();
        g_wKeysPressed = 0;
        g_dwGameModeFlags &= ~8;
        sub_0803094C(1);
        sub_0803094C(2);
        SetVBlankCallback(OverworldVBlankCallback);
        ResetDisplayState_candidate(0);
        SetDispcntFlag(0x1000);

        // BG control registers.
        bgCtrl3 = g_dwBg3Control;
        SetBgControl_candidate(3, bgCtrl3);
        bgCtrl2 = g_dwBg2Control;
        SetBgControl_candidate(2, bgCtrl2);
        bgCtrl1 = g_dwBg1Control;
        SetBgControl_candidate(1, bgCtrl1);
        bgCtrl0 = g_dwBg0Control;
        SetBgControl_candidate(0, bgCtrl0);
        DisableBg(0);

        // Make the requested room current.
        g_dwGameModeFlags &= ~0x2000000;
        g_dwScanlineBandActiveMask = 0;
        g_bCurrentRoomId = g_GameModeStackContext.dwCurrentGameModeArg2;
        InitObjTileAllocBitmaps(0);
        sub_0803DC44();

        // Load the room's BG layers, tilesets, palette and collision.
        LoadRoomBgTilemap0_candidate(CURRENT_ROOM.pBgTilemap0);
        LoadRoomBgTilemap1_candidate(CURRENT_ROOM.pBgTilemap1);
        LoadRoomBgTilemap2_candidate(CURRENT_ROOM.pBgTilemap2);
        LoadRoomBgTilemap3_candidate(CURRENT_ROOM.pBgTilemap3);
        pRoom = &CURRENT_ROOM;
        SetupRoomBgControlAndWindows_candidate(bgCtrl3, bgCtrl1, bgCtrl2, bgCtrl0,
                                               pRoom->aBgResources[0], pRoom->aBgResources[1]);
        LoadRoomSharedTileset_candidate(
            CURRENT_ROOM.pCollisionBehaviorTable,
            CURRENT_ROOM.pCollisionTilemap);
        sub_0802B20C();
        LoadRoomBgLayer0Extra_candidate(
            CURRENT_ROOM.pBgLayer0Extra,
            CURRENT_ROOM.dwUnused0_8,
            CURRENT_ROOM.dwUnused0_c);
        LoadRoomBgLayer1Extra_candidate(
            CURRENT_ROOM.pBgLayer1Extra,
            CURRENT_ROOM.dwUnused1_8,
            CURRENT_ROOM.dwUnused1_c);
        LoadRoomBgLayer2Extra_candidate(
            CURRENT_ROOM.pBgLayer2Extra,
            CURRENT_ROOM.dwUnused2_8,
            CURRENT_ROOM.dwUnused2_c);
        LoadRoomBgLayer3Extra_candidate(
            CURRENT_ROOM.pBgLayer3Extra,
            CURRENT_ROOM.dwUnused3_8,
            CURRENT_ROOM.dwUnused3_c);

        // Alpha blending.
        SetAlphaBlendTargets(0, 0x1f);
        SetAlphaBlendCoefficients(9, 10);

        // Room object blob, player, camera and scroll bounds.
        g_OverworldControlState.bSlotCount = 1;
        g_OverworldControlState.bSlotIndex = 0;
        ParseRoomResourceBlob_candidate(CURRENT_ROOM.pRoomResourceBlob);
        pPlayer = SpawnPlayerObject_candidate(g_bPartyCharId0);
        sub_080248E8();
        sub_0800A348(0, 0);
        SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset.nX, g_PlayerCameraFocusOffset.nY, 0);
        SetRoomScrollBounds(
            CURRENT_ROOM.wScrollBoundMinX,
            CURRENT_ROOM.wScrollBoundMinY,
            CURRENT_ROOM.wScrollBoundMaxX,
            CURRENT_ROOM.wScrollBoundMaxY);

        // Fresh entry: spawn the room's objects.
        if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
        {
            RespawnRoomObjectsInRow_candidate(0);
            WalkRoomSwitchStateChain_candidate(0, 0);
            if (g_wRoomResourceFlags_candidate & 1)
            {
                RespawnRoomObjectsInRow_candidate(1);
                WalkRoomSwitchStateChain_candidate(1, 0);
            }
        }

        // Restore saved object state and spawn wandering monsters.
        if (g_dwOverworldMonstersDisabled == 0
            && (g_GameModeStackContext.dwCurrentGameModeArg1 == 0
                || (g_GameModeStackContext.dwCurrentGameModeArg1 == 2
                    && g_GameModeStackContext.dwCurrentGameModeArg3 == 0xff)))
        {
            if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xff)
            {
                if (sub_08005DC0(g_abQuestEventState[0x12], CURRENT_ROOM.pRoomResourceBlob)
                    == sub_08005DC0(g_abQuestEventState[0], CURRENT_ROOM.pRoomResourceBlob))
                {
                    g_GameModeStackContext.dwCurrentGameModeArg3 = 0;
                    RestoreRoomObjectState();
                    sub_0800A348(0, 0);
                    SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset.nX, g_PlayerCameraFocusOffset.nY, 0);
                }
                else
                {
                    RestoreRoomObjectStateMinimal();
                    sub_0800A348(0, 0);
                    SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset.nX, g_PlayerCameraFocusOffset.nY, 0);
                    RespawnRoomObjectsInRow_candidate(0);
                    WalkRoomSwitchStateChain_candidate(0, 0);
                    if (g_wRoomResourceFlags_candidate & 1)
                    {
                        RespawnRoomObjectsInRow_candidate(1);
                        WalkRoomSwitchStateChain_candidate(1, 0);
                    }
                }
            }
            SpawnOverworldMonsterEncounters(
                CURRENT_ROOM.bEncounterCountA,
                CURRENT_ROOM.bEncounterCountB,
                CURRENT_ROOM.bEncounterCountC,
                CURRENT_ROOM.bEncounterVariant);
        }
        else if (g_GameModeStackContext.dwCurrentGameModeArg1 - 2 < 2)
        {
            if (sub_08005DC0(g_abQuestEventState[0x12], CURRENT_ROOM.pRoomResourceBlob)
                == sub_08005DC0(g_abQuestEventState[0], CURRENT_ROOM.pRoomResourceBlob))
            {
                RestoreRoomObjectState();
                sub_0800A348(0, 0);
                SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset.nX, g_PlayerCameraFocusOffset.nY, 0);
            }
            else
            {
                RestoreRoomObjectStateMinimal();
                sub_0800A348(0, 0);
                SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset.nX, g_PlayerCameraFocusOffset.nY, 0);
                RespawnRoomObjectsInRow_candidate(0);
                WalkRoomSwitchStateChain_candidate(0, 0);
                if (g_wRoomResourceFlags_candidate & 1)
                {
                    RespawnRoomObjectsInRow_candidate(1);
                    WalkRoomSwitchStateChain_candidate(1, 0);
                }
            }
        }

        // Music.
        if (g_dwGameModeFlags & 0x1000000)
            g_dwGameModeFlags &= ~0x1000000;
        else if (g_abQuestEventState[0x1a] != 0)
            PlayMusicModule(g_adwRoomQuestMusicOverride[g_GameModeStackContext.dwCurrentGameModeArg2]);
        else if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0xf && (u8)(g_abQuestEventState[0] - 2) < 2)
            PlayMusicModule(0x12);
        else
            PlayMusicModule(CURRENT_ROOM.bDefaultMusicModule);

        // Display flags and the room's BG control overrides.
        g_dwGameModeFlags &= ~0x400000;
        UpdateOverworldCamera_candidate(1);
        sub_0803DB68();
        if ((g_dwGameModeFlags & 0x100020) != 0x100020)
            TickCameraFocus_candidate(0);
        ApplyRoomBgControlOverride_candidate(CURRENT_ROOM.pBgControlOverrideA);
        ApplyRoomBgControlOverride_candidate(CURRENT_ROOM.pBgControlOverrideB);

        // Per-room BG layer enables and priorities; rooms 12 and the default add scanline bands.
        g_dwRoomBgFlag_candidate = 0;
        switch (g_GameModeStackContext.dwCurrentGameModeArg2)
        {
        case 1:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 0);
            SetBgPriority(2, 0);
            SetAlphaBlendTargets(4, 0x1f);
            break;
        case 0x14:
        case 0x29:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            SetAlphaBlendTargets(4, 0x1f);
            break;
        case 6:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(1, 0);
            SetBgPriority(2, 0);
            SetAlphaBlendTargets(4, 0x1f);
            break;
        case 0x16:
        case 0x2d:
            SetBgPriority(2, 0);
            break;
        case 0xc:
            SetupScanlineBands_candidate(&g_ScanlineBandsRoom12);
            break;
        case 0x13:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            break;
        case 4:
            SetBgPriority(2, 0);
            break;
        case 3:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case 0x1b:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case 0x20:
            g_dwRoomBgFlag_candidate = 1;
            DisableBg(1);
            break;
        case 0x18:
        case 0x1f:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 0);
            break;
        case 0x22:
        case 0x23:
            SetBgPriority(2, 0);
            break;
        case 7:
        case 0xb:
        case 0x1d:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            break;
        case 5:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case 0x2a:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case 0x1e:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
            {
                if (prevRoomId == 0x15)
                {
                    SetRoomSwitchState(1);
                    ApplyRoomSwitchEffect(1);
                }
                else
                {
                    SetRoomSwitchState(0);
                    ApplyRoomSwitchEffect(0);
                }
            }
            else
                ApplyRoomSwitchEffect(GetRoomSwitchState());
            break;
        case 0x10:
        case 0x17:
            g_dwRoomBgFlag_candidate = 1;
            SetBgPriority(2, 0);
            EnableBg(0);
            SetBgPriority(0, 1);
            break;
        case 0x11:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 0);
            SetAlphaBlendTargets(5, 0x1f);
            SetAlphaBlendCoefficients(0xd, 7);
            break;
        case 0x24:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 2);
            SetBgPriority(2, 2);
            break;
        case 0x26:
        case 0x27:
            SetBgPriority(2, 0);
            break;
        case 0x21:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case 2:
            SetBgPriority(1, 0);
            SetBgPriority(2, 1);
            break;
        case 0x25:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 3);
            SetBgPriority(2, 0);
            break;
        case 0x1c:
            SetBgPriority(1, 0);
            break;
        case 0x19:
        case 0x2c:
        case 0x2e:
        case 0x2f:
        case 0x30:
        case 0x31:
            break;
        default:
            SetupScanlineBands_candidate(&g_ScanlineBandsDefault);
            break;
        }

        // Finish: quest state, screen transition and map name popup.
        sub_0801FA9C();
        if (g_GameModeStackContext.dwCurrentGameModeArg1 == 3
            && g_GameModeStackContext.dwCurrentGameModeArg3 == 0xff)
            RespawnRoomObjectsInRow_candidate(g_bPendingRoomScriptRow);

        g_abQuestEventState[0x12] = g_abQuestEventState[0];
        if (g_bPendingQuestStateOverride_candidate != 0xff)
        {
            g_abQuestEventState[0] = g_bPendingQuestStateOverride_candidate;
            g_bPendingQuestStateOverride_candidate = 0xff;
        }

        PlayScreenTransitionInByIndex_candidate(0x3f, 2);
        if (g_bCurrentRoomId != 0x20)
            ShowMapNamePopup();

        g_dwGameModeFlags &= ~0x10;
        g_bControlSlotTicks_candidate = 0;
        g_dwPendingCameraFocusFlag = 0;
        if (g_GameModeStackContext.dwCurrentGameModeArg1 == 3
            && g_GameModeStackContext.dwCurrentGameModeArg3 == 0xff)
            WalkRoomSwitchStateChain_candidate(g_bPendingRoomScriptChain, 0);
    }

    // The entry kind is consumed.
    g_GameModeStackContext.dwCurrentGameModeArg1 = 0;
}

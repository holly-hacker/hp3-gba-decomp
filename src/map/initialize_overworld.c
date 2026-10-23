#include "types.h"
#include "area.h"
#include "background.h"
#include "char_block.h"
#include "color.h"
#include "sound.h"
#include "dialog.h"
#include "modes.h"
#include "input.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "interrupts.h"
#include "ram_clear.h"
#include "vram.h"
#include "hero.h"
#include "map.h"
#include "move.h"
#include "screen_transitions.h"
#include "scroll.h"
#include "video.h"
#include "combat.h"
#include "commands.h"
#include "overworld/room_script_bytecode.h"
#include "main.h"

// The room being loaded, per dwCurrentGameModeArg2.
#define CURRENT_ROOM g_aRoomTable[g_GameModeStackContext.dwCurrentGameModeArg2]

// Overworld mode's pInitFn. Sets up video and the room's BG layers, spawns the
// player, restores or respawns the room's actors and picks the room's music.
// dwCurrentGameModeArg1 is the OverworldEntryKind; Arg2 is the room id.
void InitializeOverworld(void)
{
    u32 prevRoomId;
    u32 bgCtrl3;
    u32 bgCtrl2;
    u32 bgCtrl1;
    u32 bgCtrl0;
    Actor *pPlayer;
    const RoomTableEntry *pRoom;

    // Entry: block the pause menu briefly and drop a stale script run state.
    prevRoomId = g_bCurrentRoomId;
    g_dwPauseMenuCooldown = 4;
    StopScanlineEffects();

    if (g_dwRoomScriptRunState == 4)
        g_dwRoomScriptRunState = 0;

    // Resume after a room-script yield: keep the loaded room, at most resume the chain.
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == OverworldEntryResumeScript)
    {
        if (g_dwRoomScriptRunState == 2
            && (g_bRoomScriptYieldOpcode == RSOP_ShowRoomDialog
                || g_bRoomScriptYieldOpcode == RSOP_ShowChooseCharacter
                || g_bRoomScriptYieldOpcode == RSOP_StartBattle
                || g_bRoomScriptYieldOpcode == RSOP_ShowRewardPickupMessage
                || g_bRoomScriptYieldOpcode == RSOP_ShowItemRemovedMessage
                || g_bRoomScriptYieldOpcode == RSOP_ShowSpellLearnedMessage
                || g_bRoomScriptYieldOpcode == RSOP_ShowFolioCategoryStatusMessage
                || g_bRoomScriptYieldOpcode == RSOP_ShowMinigameUnlockedMessage
                || g_bRoomScriptYieldOpcode == RSOP_ShowPartyLevelUpMessage))
            ResumeRoomScriptChain();
    }
    else
    {
        // Video, VRAM and VBlank setup.
        SetActorDepthSortEnabled(1);
        FreeBgTileAnimations();
        ClearVram();
        ClearObjPaletteSlots();
        g_wKeysPressed = 0;
        g_dwGameModeFlags &= ~GameModeFlagActorTickOnly;
        ReserveObjPaletteSlot(1);
        ReserveObjPaletteSlot(2);
        SetVBlankCallback(OverworldVBlankCallback);
        ResetDisplayState(0);
        SetDispcntFlag(0x1000);

        // BG control registers.
        bgCtrl3 = g_dwBg3Control;
        SetBgControl(3, bgCtrl3);
        bgCtrl2 = g_dwBg2Control;
        SetBgControl(2, bgCtrl2);
        bgCtrl1 = g_dwBg1Control;
        SetBgControl(1, bgCtrl1);
        bgCtrl0 = g_dwBg0Control;
        SetBgControl(0, bgCtrl0);
        DisableBg(0);

        // Make the requested room current.
        g_dwGameModeFlags &= ~GameModeFlagUnk2000000;
        g_dwColorCycleActiveMask = 0;
        g_bCurrentRoomId = g_GameModeStackContext.dwCurrentGameModeArg2;
        InitObjTileAllocBitmaps(0);
        FreeRoomBgBlockData();

        // Load the room's BG layers, tilesets, palette and collision.
        LoadRoomBgTilemap0(CURRENT_ROOM.pBgTilemap0);
        LoadRoomBgTilemap1(CURRENT_ROOM.pBgTilemap1);
        LoadRoomBgTilemap2(CURRENT_ROOM.pBgTilemap2);
        LoadRoomBgTilemap3(CURRENT_ROOM.pBgTilemap3);
        pRoom = &CURRENT_ROOM;
        SetupRoomBgControlAndTilesets(bgCtrl3, bgCtrl1, bgCtrl2, bgCtrl0,
                                               pRoom->aBgResources[0], pRoom->aBgResources[1]);
        LoadRoomSharedTileset_candidate(
            CURRENT_ROOM.pCollisionBehaviorTable,
            CURRENT_ROOM.pCollisionTilemap);
        NoopOverworldRoomLoad();
        LoadRoomBgBlockTiles0(
            CURRENT_ROOM.pBgLayer0Extra,
            CURRENT_ROOM.dwUnused0_8,
            CURRENT_ROOM.dwUnused0_c);
        LoadRoomBgBlockTiles1(
            CURRENT_ROOM.pBgLayer1Extra,
            CURRENT_ROOM.dwUnused1_8,
            CURRENT_ROOM.dwUnused1_c);
        LoadRoomBgBlockTiles2(
            CURRENT_ROOM.pBgLayer2Extra,
            CURRENT_ROOM.dwUnused2_8,
            CURRENT_ROOM.dwUnused2_c);
        LoadRoomBgBlockTiles3(
            CURRENT_ROOM.pBgLayer3Extra,
            CURRENT_ROOM.dwUnused3_8,
            CURRENT_ROOM.dwUnused3_c);

        // Alpha blending.
        SetAlphaBlendTargets(0, 0x1f);
        SetAlphaBlendCoefficients(9, 10);

        // Room actor blob, player, camera and scroll bounds.
        g_OverworldControlState.bSlotCount = 1;
        g_OverworldControlState.bSlotIndex = 0;
        ParseRoomResourceBlob(CURRENT_ROOM.pRoomResourceBlob);
        pPlayer = SpawnPlayerActor(g_bPartyCharId0);
        SpawnPartyFollowers();
        SetCameraFocusPinned(0, 0);
        SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset, 0);
        SetRoomScrollBounds(
            CURRENT_ROOM.wScrollBoundMinX,
            CURRENT_ROOM.wScrollBoundMinY,
            CURRENT_ROOM.wScrollBoundMaxX,
            CURRENT_ROOM.wScrollBoundMaxY);

        // Fresh entry: spawn the room's actors.
        if (g_GameModeStackContext.dwCurrentGameModeArg1 == OverworldEntryEnterRoom)
        {
            SpawnMissingRoomGroupActors(0);
            RunRoomScriptChain(0, 0);
            if (g_wRoomResourceFlags_candidate & 1)
            {
                SpawnMissingRoomGroupActors(1);
                RunRoomScriptChain(1, 0);
            }
        }

        // Restore saved actor state and spawn wandering monsters.
        if (g_dwOverworldMonstersDisabled == 0
            && (g_GameModeStackContext.dwCurrentGameModeArg1 == OverworldEntryEnterRoom
                || (g_GameModeStackContext.dwCurrentGameModeArg1 == OverworldEntryRestore
                    && g_GameModeStackContext.dwCurrentGameModeArg3 == 0xff)))
        {
            if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xff)
            {
                if (GetRoomBlobStageVariant(g_abQuestEventState[QUEST_PREV_STORY_STAGE], CURRENT_ROOM.pRoomResourceBlob)
                    == GetRoomBlobStageVariant(g_abQuestEventState[QUEST_STORY_STAGE], CURRENT_ROOM.pRoomResourceBlob))
                {
                    g_GameModeStackContext.dwCurrentGameModeArg3 = 0;
                    RestoreRoomActorState();
                    SetCameraFocusPinned(0, 0);
                    SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset, 0);
                }
                else
                {
                    RestoreRoomActorStateMinimal();
                    SetCameraFocusPinned(0, 0);
                    SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset, 0);
                    SpawnMissingRoomGroupActors(0);
                    RunRoomScriptChain(0, 0);
                    if (g_wRoomResourceFlags_candidate & 1)
                    {
                        SpawnMissingRoomGroupActors(1);
                        RunRoomScriptChain(1, 0);
                    }
                }
            }
            SpawnOverworldMonsterEncounters(
                CURRENT_ROOM.bEncounterCountA,
                CURRENT_ROOM.bEncounterCountB,
                CURRENT_ROOM.bEncounterCountC,
                CURRENT_ROOM.bEncounterVariant);
        }
        else if (g_GameModeStackContext.dwCurrentGameModeArg1 == OverworldEntryRestore
                 || g_GameModeStackContext.dwCurrentGameModeArg1 == OverworldEntryReturn)
        {
            if (GetRoomBlobStageVariant(g_abQuestEventState[QUEST_PREV_STORY_STAGE], CURRENT_ROOM.pRoomResourceBlob)
                == GetRoomBlobStageVariant(g_abQuestEventState[QUEST_STORY_STAGE], CURRENT_ROOM.pRoomResourceBlob))
            {
                RestoreRoomActorState();
                SetCameraFocusPinned(0, 0);
                SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset, 0);
            }
            else
            {
                RestoreRoomActorStateMinimal();
                SetCameraFocusPinned(0, 0);
                SetCameraFollowTarget_candidate(pPlayer, g_PlayerCameraFocusOffset, 0);
                SpawnMissingRoomGroupActors(0);
                RunRoomScriptChain(0, 0);
                if (g_wRoomResourceFlags_candidate & 1)
                {
                    SpawnMissingRoomGroupActors(1);
                    RunRoomScriptChain(1, 0);
                }
            }
        }

        // Music.
        if (g_dwGameModeFlags & GameModeFlagKeepScriptMusic)
            g_dwGameModeFlags &= ~GameModeFlagKeepScriptMusic;
        else if (g_abQuestEventState[QUEST_ALT_PRESENTATION] != 0)
            PlayMusicModule(g_adwRoomQuestMusicOverride[g_GameModeStackContext.dwCurrentGameModeArg2]);
        else if (g_GameModeStackContext.dwCurrentGameModeArg2 == RoomHogwartsGroundsWhompingWillow
                 && (u8)(g_abQuestEventState[QUEST_STORY_STAGE] - 2) < 2)
            PlayMusicModule(0x12);
        else
            PlayMusicModule(CURRENT_ROOM.bDefaultMusicModule);

        // Display flags and the room's BG control overrides.
        g_dwGameModeFlags &= ~GameModeFlagFreezeViewOnExit;
        UpdateOverworldCamera(1);
        ReloadRoomBgTiles();
        if ((g_dwGameModeFlags & (SerialSessionActive | GameModeFlagSerialSkipFocusInit)) != (SerialSessionActive | GameModeFlagSerialSkipFocusInit))
            TickCameraFocus_candidate(0);
        RegisterRoomBgTileAnimation(CURRENT_ROOM.pBgTileAnimationA);
        RegisterRoomBgTileAnimation(CURRENT_ROOM.pBgTileAnimationB);

        // Per-room BG layer enables and priorities; RoomHagridsGardenMaze and the default start
        // color cycles.
        g_dwRoomBgFlag_candidate = 0;
        switch (g_GameModeStackContext.dwCurrentGameModeArg2)
        {
        case RoomPotionsClassroom:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 0);
            SetBgPriority(2, 0);
            SetAlphaBlendTargets(4, 0x1f);
            break;
        case RoomThirdFloor:
        case RoomLeakyCauldronHarrysRoom:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            SetAlphaBlendTargets(4, 0x1f);
            break;
        case RoomHogwartsExpressPassengerCar:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(1, 0);
            SetBgPriority(2, 0);
            SetAlphaBlendTargets(4, 0x1f);
            break;
        case RoomFifthFloor:
        case RoomShriekingShackPath2:
            SetBgPriority(2, 0);
            break;
        case RoomHagridsGardenMaze:
            SetupColorCycles(&g_ColorCyclesRoom12);
            break;
        case RoomSecondFloor:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            break;
        case RoomTransfigurationClassroomMaze:
            SetBgPriority(2, 0);
            break;
        case RoomTransfigurationClassroom:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case RoomStaffRoom:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case RoomPortraitRoomPassage:
            g_dwRoomBgFlag_candidate = 1;
            DisableBg(1);
            break;
        case RoomSeventhFloor:
        case RoomPortraitRoom:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 0);
            break;
        case RoomLibrary:
        case RoomLibrary2:
            SetBgPriority(2, 0);
            break;
        case RoomHogwartsExpressBuffetCar:
        case RoomHagridsHut:
        case RoomGryffindorCommonRoom:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            break;
        case RoomHogwartsExpressBaggageCar:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case RoomLeakyCauldronMain:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case RoomGrandStaircase:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            if (g_GameModeStackContext.dwCurrentGameModeArg1 == OverworldEntryEnterRoom)
            {
                if (prevRoomId == RoomFourthFloor)
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
        case RoomEntranceHall:
        case RoomSixthFloor:
            g_dwRoomBgFlag_candidate = 1;
            SetBgPriority(2, 0);
            EnableBg(0);
            SetBgPriority(0, 1);
            break;
        case RoomGreatHall:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 0);
            SetAlphaBlendTargets(5, 0x1f);
            SetAlphaBlendCoefficients(0xd, 7);
            break;
        case RoomFredAndGeorgesShop:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 2);
            SetBgPriority(2, 2);
            break;
        case RoomLeakyCauldronCellar1:
        case RoomLeakyCauldronCellar2:
            SetBgPriority(2, 0);
            break;
        case RoomHospitalWing:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 1);
            SetBgPriority(2, 0);
            break;
        case RoomPotionsClassroomMaze:
            SetBgPriority(1, 0);
            SetBgPriority(2, 1);
            break;
        case RoomWizardCardCollectorsClub:
            g_dwRoomBgFlag_candidate = 1;
            EnableBg(0);
            SetBgPriority(0, 3);
            SetBgPriority(2, 0);
            break;
        case RoomGryffindorBoysDormitory:
            SetBgPriority(1, 0);
            break;
        case RoomRooftop:
        case RoomShriekingShackPath:
        case RoomShriekingShackPath3:
        case RoomShriekingShackPath4:
        case RoomShriekingShackPath5:
        case RoomShriekingShackPath6:
            break;
        default:
            SetupColorCycles(&g_ColorCyclesDefault);
            break;
        }

        // Finish: quest state, screen transition and map name popup.
        LoadDialogBoxGraphics();
        if (g_GameModeStackContext.dwCurrentGameModeArg1 == OverworldEntryReturn
            && g_GameModeStackContext.dwCurrentGameModeArg3 == 0xff)
            SpawnMissingRoomGroupActors(g_bPendingRoomScriptRow);

        g_abQuestEventState[QUEST_PREV_STORY_STAGE] = g_abQuestEventState[QUEST_STORY_STAGE];
        if (g_bPendingQuestStateOverride_candidate != 0xff)
        {
            g_abQuestEventState[QUEST_STORY_STAGE] = g_bPendingQuestStateOverride_candidate;
            g_bPendingQuestStateOverride_candidate = 0xff;
        }

        PlayScreenTransitionInByIndex(0x3f, 2);
        if (g_bCurrentRoomId != RoomPortraitRoomPassage)
            ShowMapNamePopup();

        g_dwGameModeFlags &= ~GameModeFlagSwitchingMode;
        g_bControlSlotTicks_candidate = 0;
        g_dwFieldSpellActive = 0;
        if (g_GameModeStackContext.dwCurrentGameModeArg1 == OverworldEntryReturn
            && g_GameModeStackContext.dwCurrentGameModeArg3 == 0xff)
            RunRoomScriptChain(g_bPendingRoomScriptChain, 0);
    }

    // The entry kind is consumed.
    g_GameModeStackContext.dwCurrentGameModeArg1 = OverworldEntryEnterRoom;
}

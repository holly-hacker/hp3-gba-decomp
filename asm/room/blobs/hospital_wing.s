    .include "asm/room_blob.inc"

Room33Blob:
    RoomBlob 3
    PlayerEntry 335, 360, 0, 4
    PlayerEntry 167, 476, 1, 0
    PlayerEntry 170, 260, 2, 4
    StageIndex 3
    StageToVariant 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1
    VariantEntry Room33V0
    VariantEntry Room33V1
    VariantEntry Room33V2

    SubBlock Room33V0, 1, Room33V0Routes, Room33V0Chains, Room33V0End
    OffsetTable Room33V0Groups, 1
    Offsets Room33V0Group0
    EndTable
    Group Room33V0Group0, 2
    Chest 347, 178, flag_id=30, reward_id=92
    Door 224, 528, half_width=37, half_height=10, destination_room=21, exit_param=3
    OffsetTable Room33V0Routes, 0
    EndTable
    OffsetTable Room33V0Chains, 1
    Offsets Room33V0Chain0
    EndTable
Room33V0Chain0:
    SetDefeatWarpSelector 2
    End
    EndSubBlock Room33V0End

    SubBlock Room33V1, 1, Room33V1Routes, Room33V1Chains, Room33V1End
    OffsetTable Room33V1Groups, 2, 1
    Offsets Room33V1Group0, Room33V1Group1
    EndTable
    Group Room33V1Group0, 3
    Npc 222, 256, sprite=97, facing=0, interact_cooldown=3, interact_mode=1, chain=Room33V1Chain9_id
    TriggerZone 220, 264, half_width=33, half_height=20, require_a_press=1, chain=Room33V1Chain7_id
    TriggerZone 225, 105, half_width=37, half_height=10, rearm_delay=3, trigger_kind=1, chain=Room33V1Chain8_id
    Group Room33V1Group1, 2
    Npc 120, 260, sprite=34, facing=2
    Npc 144, 144, sprite=24, facing=4
    OffsetTable Room33V1Routes, 2
    Offsets Room33V1Route0, Room33V1Route1
    EndTable
Room33V1Route0:
    Route 2
    Waypoint 144, 144
    Waypoint 144, 235, on_arrival_chain=Room33V1Chain2_id
Room33V1Route1:
    Route 2
    Waypoint 120, 259
    Waypoint 170, 259, on_arrival_chain=Room33V1Chain4_id
    OffsetTable Room33V1Chains, 10, 1
    Offsets Room33V1Chain0, Room33V1Chain1, Room33V1Chain2, Room33V1Chain3, Room33V1Chain4, Room33V1Chain5
    Offsets Room33V1Chain6, Room33V1Chain7, Room33V1Chain8, Room33V1Chain9
    EndTable
Room33V1Chain0:
    GotoIfStoryStageCompare 0, 24, Room33V1Chain3_id, 0, Room33V1Group1_id, 0
    End
Room33V1Chain1:
    @ "You look as if you're injured. Here, let me help you."
    ShowRoomDialog 647
    End
Room33V1Chain2:
    ArmChainYield 1
    StartTileObjectScript 170, 3, 1, 0, 255, 0, 0, 6, 255, 255, 255
    @ "What we need is more time."
    @ "Miss Granger, three turns should do it. Good luck."
    ShowRoomDialog 587
    DelayedRespawnRowAndRunChain 2, 0, 0
    PlayCutscene 10, 0, Room33V1Chain6_id
    End
Room33V1Chain3:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChain 3, 0, 0
    PlayCutscene 9, 0, Room33V1Chain5_id
    End
Room33V1Chain4:
    ArmChainYield 1
    RecruitPartyFollower 6
    DespawnTileObject Room33V1Group1_id, 0
    SetQuestState QUEST_OBJ_SECRET_PATH_TO_HAGRIDS_HUT, QUEST_OBJECTIVE_INDEX
    SetQuestState 1, QUEST_ALT_PRESENTATION
    SetStoryStage 25
    PlayCutscene 15, 0, 0
    End
Room33V1Chain5:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence Room33V1Group1_id, 1, 0, 0, Room33V1Route0_id, 0, 1, 0, 0, 0
    End
Room33V1Chain6:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "What are we supposed to do?"
    @ "We're going to use the Time-Turner to go back three hours, rescue Buckbeak and then release Sirius from the West Tower."
    ShowRoomDialog 588
    ArmChainYield 0
    StartObjectAnimSequence Room33V1Group1_id, 0, 0, 0, Room33V1Route1_id, 0, 1, 0, 0, 0
    End
Room33V1Chain7:
    GotoIfQuestStateCompare QUEST_SCRATCH_RESULT, 0, 1, Room33V1Chain1_id, 0, 0, 0
    FullHealParty
    End
Room33V1Chain8:
    @ "Locked."
    ShowRoomDialog 624
    End
Room33V1Chain9:
    @ "Hello! How are you feeling?"
    ShowRoomDialog 646
    End
    EndSubBlock Room33V1End

    SubBlock Room33V2, 1, Room33V2Routes, Room33V2Chains, Room33V2End
    OffsetTable Room33V2Groups, 1, 1
    Offsets Room33V2Group0
    EndTable
    Group Room33V2Group0, 1
    Npc 317, 349, sprite=97, facing=4
    OffsetTable Room33V2Routes, 0
    EndTable
    OffsetTable Room33V2Chains, 3, 1
    Offsets Room33V2Chain0, Room33V2Chain1, Room33V2Chain2
    EndTable
Room33V2Chain0:
    SetDefeatWarpSelector 2
    @ "Oh! You're awake. Someone found you unconscious and brought you in for care. You should be more careful."
    ShowRoomDialog 649
    FullHealParty
    GotoIfStoryStageCompare 3, 25, Room33V2Chain1_id, 0, 0, 0
    End
Room33V2Chain1:
    GotoIfQuestStateCompare 130, 0, 1, Room33V2Chain2_id, 0, 0, 0
    End
Room33V2Chain2:
    SetQuestState 2, 130
    End
    EndSubBlock Room33V2End

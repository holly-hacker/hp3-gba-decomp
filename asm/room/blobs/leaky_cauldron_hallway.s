    .include "asm/room_blob.inc"

Room40Blob:
    RoomBlob 4
    PlayerEntry 271, 423, 0, 2
    PlayerEntry 334, 219, 1, 4
    PlayerEntry 198, 218, 2, 0
    PlayerEntry 75, 151, 3, 4
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room40V0
    VariantEntry Room40V1

    SubBlock Room40V0, 1, Room40V0Routes, Room40V0Chains, Room40V0End
    OffsetTable Room40V0Groups, 1
    Offsets Room40V0Group0
    EndTable
    Group Room40V0Group0, 3
    Door 222, 445, half_width=6, half_height=21, destination_room=42, exit_param=2
    Door 334, 192, half_width=13, half_height=10, destination_room=41
    Chest 54, 217, flag_id=2, reward_id=114
    OffsetTable Room40V0Routes, 0
    EndTable
    OffsetTable Room40V0Chains, 1
    Offsets Room40V0Chain0
    EndTable
Room40V0Chain0:
    End
    EndSubBlock Room40V0End

    SubBlock Room40V1, 1, Room40V1Routes, Room40V1Chains, Room40V1End
    OffsetTable Room40V1Groups, 3, 1
    Offsets Room40V1Group0, Room40V1Group1, Room40V1Group2
    EndTable
    Group Room40V1Group0, 2
    TriggerZone 197, 193, half_width=16, half_height=11, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room40V1Chain7_id
    TriggerZone 63, 99, half_width=16, half_height=11, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room40V1Chain7_id
    Group Room40V1Group1, 2
    Npc 380, 210, sprite=1, facing=4
    TriggerZone 380, 209, half_width=39, half_height=39, chain=Room40V1Chain3_id
    Group Room40V1Group2, 3
    Npc 160, 213, sprite=13, facing=6
    TriggerZone 149, 213, half_width=58, half_height=28, chain=Room40V1Chain4_id
    Npc 136, 214, sprite=14, facing=6
    OffsetTable Room40V1Routes, 1
    Offsets Room40V1Route0
    EndTable
Room40V1Route0:
    Route 3
    Waypoint 360, 218
    Waypoint 333, 218
    Waypoint 333, 205, on_arrival_chain=Room40V1Chain8_id
    OffsetTable Room40V1Chains, 9, 1
    Offsets Room40V1Chain0, Room40V1Chain1, Room40V1Chain2, Room40V1Chain3, Room40V1Chain4, Room40V1Chain5
    Offsets Room40V1Chain6, Room40V1Chain7, Room40V1Chain8
    EndTable
Room40V1Chain0:
    DelayedRespawnRowAndRunChain 0, 0, Room40V1Chain2_id
    End
Room40V1Chain1:
    End
Room40V1Chain2:
    GotoIfStoryStageCompare 0, 1, 0, 0, Room40V1Group1_id, 0
    GotoIfStoryStageCompare 0, 8, 0, 0, Room40V1Group2_id, 0
    End
Room40V1Chain3:
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, QUEST_ALT_PRESENTATION
    SetQuestState 1, 231
    ArmChainYield 1
    StartTileObjectScript 366, 232, 0, 0, 255, 0, 0, 0, 255, 255, 255
    @ "Here, Harry. Take these collector's cards. They might help you during a magical encounter."
    @ "Thank you, Minister."
    ShowRoomDialog 5
    GrantRoomReward 123, 0
    GrantRoomReward 124, 0
    GrantRoomReward 125, 0
    @ "You've received the Dunbar Oglethorpe, Devlin Whitehorn, and Cyprian Youdle collector's cards."
    ShowRoomDialog 663
    @ "You've received some collector's cards! Collect all the cards to unlock secrets and items in the Wizard Card Collectors' Club in classroom 5B. Collecting certain groups of cards will allow Harry to use Card Combos during magical encounters. To view your card collection, choose Folios and then Folio Universitas."
    ShowRoomDialog 623
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room40V1Route0_id, 0, 1, 0, 0, 0
    End
Room40V1Chain4:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    @ "C'mon you lot! We need to leave for King's Cross station right away if we want to catch the Hogwarts Express!"
    ShowRoomDialog 77
    ClearQuestStateUpperHalf
    SetStoryStage 7
    ResetPartyLeaderSelection
    CancelObjectAnimSequence 0, 255
    SetQuestState QUEST_OBJ_FIND_YOUR_SEAT, QUEST_OBJECTIVE_INDEX
    SetOverworldMonstersDisabled
    DelayedRespawnRowAndRunChain 1, 0, 0
    PlayCutscene 0, 0, Room40V1Chain6_id
    End
Room40V1Chain5:
    RecruitPartyFollower 6
    End
Room40V1Chain6:
    CancelObjectAnimSequence 0, 255
    ReturnToOverworld 6, 0
    End
Room40V1Chain7:
    @ "Locked."
    ShowRoomDialog 624
    End
Room40V1Chain8:
    ArmChainYield 1
    ClearQuestStateUpperHalf
    ReturnToOverworld 41, 0
    End
    EndSubBlock Room40V1End

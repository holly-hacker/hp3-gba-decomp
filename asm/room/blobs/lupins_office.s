    .include "asm/room_blob.inc"

Room26Blob:
    RoomBlob 1
    PlayerEntry 498, 379, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room26V0
    VariantEntry Room26V1

    SubBlock Room26V0, 1, Room26V0Routes, Room26V0Chains, Room26V0End
    OffsetTable Room26V0Groups, 1
    Offsets Room26V0Group0
    EndTable
    Group Room26V0Group0, 2
    Door 526, 381, half_width=9, half_height=24, destination_room=20, exit_param=5
    Chest 421, 250, flag_id=107, reward_id=125
    OffsetTable Room26V0Routes, 0
    EndTable
    OffsetTable Room26V0Chains, 1
    Offsets Room26V0Chain0
    EndTable
Room26V0Chain0:
    End
    EndSubBlock Room26V0End

    SubBlock Room26V1, 1, Room26V1Routes, Room26V1Chains, Room26V1End
    OffsetTable Room26V1Groups, 3, 1
    Offsets Room26V1Group0, Room26V1Group1, Room26V1Group2
    EndTable
    Group Room26V1Group0, 0
    Group Room26V1Group1, 3
    Npc 265, 360, sprite=15, facing=2, interact_cooldown=3, interact_mode=1, chain=Room26V1Chain5_id
    TriggerZone 452, 379, half_width=10, half_height=65, chain=Room26V1Chain2_id
    Prop 324, 335, kind=75
    Group Room26V1Group2, 1
    Npc 380, 488, sprite=15, facing=0, interact_cooldown=3, interact_mode=1, chain=Room26V1Chain5_id
    OffsetTable Room26V1Routes, 2
    Offsets Room26V1Route0, Room26V1Route1
    EndTable
Room26V1Route0:
    Route 3
    Waypoint 423, 360
    Waypoint 370, 360
    Waypoint 347, 360, on_arrival_chain=Room26V1Chain3_id
Room26V1Route1:
    Route 2
    Waypoint 265, 360
    Waypoint 302, 360
    OffsetTable Room26V1Chains, 6, 1
    Offsets Room26V1Chain0, Room26V1Chain1, Room26V1Chain2, Room26V1Chain3, Room26V1Chain4, Room26V1Chain5
    EndTable
Room26V1Chain0:
    GotoIfStoryStageCompare 0, 17, Room26V1Chain1_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 18, 0, 0, Room26V1Group2_id, 0
    End
Room26V1Chain1:
    GotoIfQuestStateCompare 230, 0, 0, 0, 0, Room26V1Group1_id, Room26V1Group2_id
    End
Room26V1Chain2:
    ArmChainYield 1
    SetQuestState 1, 230
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room26V1Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room26V1Group1_id, 0, 0, 0, Room26V1Route1_id, 0, 1, 0, 0, 0
    End
Room26V1Chain3:
    ArmChainYield 1
    @ "Glad you came, Harry. Are you ready for the lesson?"
    @ "Yes, Professor."
    @ "So... The spell I am going to try and teach you is highly advanced magic, Harry. It is called the Patronus Charm."
    @ "How does it work?"
    @ "It conjures up a Patronus, which is a kind of Anti-Dementor - a guardian which acts as a shield between you and the Dementor."
    @ "What does a Patronus look like?"
    @ "Each one is unique to the wizard who conjures it."
    @ "And how do you conjure it?"
    @ "With the incantation - expecto patronum! There is a Boggart in this chest. When you're ready, Harry - begin!"
    @ "Expecto patronum!"
    ShowRoomDialog 484
    UnlockMinigame 4
    StartMinigame 4, 1, 1, 0, Room26V1Chain4_id
    End
Room26V1Chain4:
    ArmChainYield 1
    GrantPartyExperience 10, 65535
    @ "Excellent! Excellent, Harry! That was definitely a start!"
    @ "Thank you very much, Professor."
    @ "Professor Lupin? If you knew my dad, you must've known Sirius Black as well."
    @ "I thought I did, Harry. You'd better get off to your common room. It's getting late."
    @ "Bye, Professor."
    ShowRoomDialog 494
    DespawnTileObject Room26V1Group1_id, 1
    SetQuestState 1, 230
    SetQuestState 36, 25
    SetStoryStage 18
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room26V1Chain5:
    @ "I'd advise you to go to your common room."
    ShowRoomDialog 353
    End
    EndSubBlock Room26V1End

    .include "asm/room_blob.inc"

Room00Blob:
    RoomBlob 1
    PlayerEntry 500, 392, 0, 6
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room00V0
    VariantEntry Room00V1

    SubBlock Room00V0, 1, Room00V0Routes, Room00V0Chains, Room00V0End
    OffsetTable Room00V0Groups, 1
    Offsets Room00V0Group0
    EndTable
    Group Room00V0Group0, 2
    Door 570, 380, half_width=9, half_height=27, destination_room=20, exit_param=2
    Chest 133, 259, flag_id=29, reward_id=86
    OffsetTable Room00V0Routes, 0
    EndTable
    OffsetTable Room00V0Chains, 1
    Offsets Room00V0Chain0
    EndTable
Room00V0Chain0:
    End
    EndSubBlock Room00V0End

    SubBlock Room00V1, 1, Room00V1Routes, Room00V1Chains, Room00V1End
    OffsetTable Room00V1Groups, 11, 1
    Offsets Room00V1Group0, Room00V1Group1, Room00V1Group2, Room00V1Group3, Room00V1Group4, Room00V1Group5
    Offsets Room00V1Group6, Room00V1Group7, Room00V1Group8, Room00V1Group9, Room00V1Group10
    EndTable
    Group Room00V1Group0, 1
    TriggerZone 89, 256, half_width=11, half_height=32, rearm_delay=2, trigger_kind=1, require_a_press=1, chain=Room00V1Chain21_id
    Group Room00V1Group1, 1
    Npc 222, 250, sprite=20, facing=2
    Group Room00V1Group2, 1
    Npc 436, 295, sprite=32, facing=4
    Group Room00V1Group3, 1
    Npc 350, 320, sprite=34, facing=4
    Group Room00V1Group4, 6
    Npc 330, 235, sprite=55, facing=4
    Npc 330, 325, sprite=47, facing=4
    Npc 330, 345, sprite=39, facing=4
    Npc 443, 250, sprite=43, facing=4
    Npc 443, 275, sprite=63, facing=4
    Npc 443, 320, sprite=51, facing=4
    Group Room00V1Group5, 1
    TriggerZone 438, 410, half_width=25, half_height=89, chain=Room00V1Chain1_id
    Group Room00V1Group6, 6
    Npc 326, 221, sprite=55, facing=6
    Npc 415, 219, sprite=43, facing=6
    Npc 414, 249, sprite=63, facing=6
    Npc 325, 326, sprite=47, facing=6
    Npc 325, 352, sprite=39, facing=6
    Npc 412, 329, sprite=51, facing=6
    Group Room00V1Group7, 1
    TriggerZone 448, 412, half_width=15, half_height=67, chain=Room00V1Chain12_id
    Group Room00V1Group8, 1
    Npc 450, 400, sprite=34, facing=6
    Group Room00V1Group9, 1
    Npc 117, 365, sprite=20, facing=2, arg_0f=0
    Group Room00V1Group10, 1
    Npc 320, 390, sprite=32, facing=6
    OffsetTable Room00V1Routes, 20
    Offsets Room00V1Route0, Room00V1Route1, Room00V1Route2, Room00V1Route3, Room00V1Route4, Room00V1Route5
    Offsets Room00V1Route6, Room00V1Route7, Room00V1Route8, Room00V1Route9, Room00V1Route10, Room00V1Route11
    Offsets Room00V1Route12, Room00V1Route13, Room00V1Route14, Room00V1Route15, Room00V1Route16, Room00V1Route17
    Offsets Room00V1Route18, Room00V1Route19
    EndTable
Room00V1Route0:
    Route 5
    Waypoint 443, 250
    Waypoint 443, 275
    Waypoint 443, 320
    Waypoint 443, 383
    Waypoint 550, 383
Room00V1Route1:
    Route 5
    Waypoint 330, 235
    Waypoint 330, 325
    Waypoint 330, 345
    Waypoint 330, 410
    Waypoint 550, 410
Room00V1Route2:
    Route 2
    Waypoint 422, 290
    Waypoint 422, 375, on_arrival_chain=Room00V1Chain4_id
Room00V1Route3:
    Route 2
    Waypoint 436, 295
    Waypoint 436, 395, on_arrival_chain=Room00V1Chain5_id
Room00V1Route4:
    Route 3
    Waypoint 350, 320
    Waypoint 350, 395
    Waypoint 408, 395, on_arrival_chain=Room00V1Chain3_id
Room00V1Route5:
    Route 2
    Waypoint 222, 250
    Waypoint 222, 205, on_arrival_chain=Room00V1Chain8_id
Room00V1Route6:
    Route 3
    Waypoint 335, 290
    Waypoint 335, 405
    Waypoint 550, 405, on_arrival_chain=Room00V1Chain7_id
Room00V1Route7:
    Route 3
    Waypoint 222, 205
    Waypoint 222, 225
    Waypoint 237, 225, on_arrival_chain=Room00V1Chain9_id
Room00V1Route8:
    Route 3
    Waypoint 210, 250
    Waypoint 210, 370
    Waypoint 220, 370, on_arrival_chain=Room00V1Chain13_id
Room00V1Route9:
    Route 3
    Waypoint 450, 400
    Waypoint 225, 400
    Waypoint 225, 390, on_arrival_chain=Room00V1Chain19_id
Room00V1Route10:
    Route 2
    Waypoint 410, 390
    Waypoint 300, 390
Room00V1Route11:
    Route 2
    Waypoint 300, 390
    Waypoint 303, 390, on_arrival_chain=Room00V1Chain18_id
Room00V1Route12:
    Route 2
    Waypoint 225, 395
    Waypoint 230, 395, on_arrival_chain=Room00V1Chain16_id
Room00V1Route13:
    Route 3
    Waypoint 230, 400
    Waypoint 305, 400, on_arrival_chain=Room00V1Chain22_id
    Waypoint 470, 400, on_arrival_chain=Room00V1Chain17_id
Room00V1Route14:
    Route 2
    Waypoint 250, 405
    Waypoint 305, 405
Room00V1Route15:
    Route 2
    Waypoint 303, 390
    Waypoint 297, 390, on_arrival_chain=Room00V1Chain14_id
Room00V1Route16:
    Route 2
    Waypoint 297, 390
    Waypoint 290, 390
Room00V1Route17:
    Route 2
    Waypoint 220, 370
    Waypoint 150, 370, on_arrival_chain=Room00V1Chain20_id
Room00V1Route18:
    Route 3
    Waypoint 290, 390
    Waypoint 310, 390
    Waypoint 250, 390, on_arrival_chain=Room00V1Chain15_id
Room00V1Route19:
    Route 2
    Waypoint 445, 397
    Waypoint 445, 290, on_arrival_chain=Room00V1Chain23_id
    OffsetTable Room00V1Chains, 24, 1
    Offsets Room00V1Chain0, Room00V1Chain1, Room00V1Chain2, Room00V1Chain3, Room00V1Chain4, Room00V1Chain5
    Offsets Room00V1Chain6, Room00V1Chain7, Room00V1Chain8, Room00V1Chain9, Room00V1Chain10, Room00V1Chain11
    Offsets Room00V1Chain12, Room00V1Chain13, Room00V1Chain14, Room00V1Chain15, Room00V1Chain16, Room00V1Chain17
    Offsets Room00V1Chain18, Room00V1Chain19, Room00V1Chain20, Room00V1Chain21, Room00V1Chain22, Room00V1Chain23
    EndTable
Room00V1Chain0:
    GotoIfStoryStageCompare 0, 7, Room00V1Chain10_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 9, Room00V1Chain11_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 14, 0, 0, Room00V1Group9_id, 0
    End
Room00V1Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnTileObject Room00V1Group5_id, 0
    @ "Sorry we're late - oh, Professor Snape!"
    ShowRoomDialog 409
    ArmChainYield 0
    StartObjectAnimSequence Room00V1Group1_id, 0, 0, 0, Room00V1Route5_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room00V1Group1_id, 0, 0, 0, 2200, 0
    End
Room00V1Chain2:
    ArmChainYield 0
    StartObjectAnimSequence Room00V1Group4_id, 0, 0, 0, Room00V1Route6_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room00V1Group4_id, 1, 0, 0, Room00V1Route1_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room00V1Group4_id, 2, 0, 0, Room00V1Route1_id, 2, 1, 0, 0, 0
    StartObjectAnimSequence Room00V1Group3_id, 0, 0, 0, Room00V1Route4_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room00V1Route2_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room00V1Group2_id, 0, 0, 0, Room00V1Route3_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room00V1Group4_id, 3, 0, 0, Room00V1Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room00V1Group4_id, 4, 0, 0, Room00V1Route0_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room00V1Group4_id, 5, 0, 0, Room00V1Route0_id, 2, 1, 0, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 400, 0
    End
Room00V1Chain3:
    SetTileObjectFacing Room00V1Group3_id, 0, 2
    End
Room00V1Chain4:
    SetTileObjectFacing 0, 255, 4
    End
Room00V1Chain5:
    SetTileObjectFacing Room00V1Group2_id, 0, 6
    End
Room00V1Chain6:
    DespawnTileObject Room00V1Group4_id, 0
    DespawnTileObject Room00V1Group4_id, 4
    DespawnTileObject Room00V1Group4_id, 3
    DespawnTileObject Room00V1Group4_id, 1
    DespawnTileObject Room00V1Group4_id, 2
    DespawnTileObject Room00V1Group4_id, 5
    End
Room00V1Chain7:
    DespawnRoomRowObjects Room00V1Group4_id
    ArmChainYield 1
    @ "I've already read a great deal about werewolves... I even know how to imitate a werewolf's howl."
    @ "Well, good for you, Hermione. I'm sure that'll come in really useful one day."
    @ "Let's get going."
    ShowRoomDialog 412
    StartTileObjectScript 422, 139, 1, 0, 255, 0, 0, 4, 255, 255, 255
    StartTileObjectScript 422, 139, 1, Room00V1Group2_id, 0, 0, 0, 2, 255, 255, 255
    DespawnTileObject Room00V1Group2_id, 0
    RecruitPartyFollower 7
    StartTileObjectScript 422, 139, 1, Room00V1Group3_id, 0, 0, 0, 2, 255, 255, 255
    DespawnTileObject Room00V1Group3_id, 0
    RecruitPartyFollower 6
    SetStoryStage 8
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room00V1Chain8:
    ArmChainYield 1
    SetTileObjectFacing Room00V1Group1_id, 0, 4
    RespawnRowAndRunChain Room00V1Group3_id, 0
    RespawnRowAndRunChain Room00V1Group2_id, 0
    RemovePartyFollower 6
    RemovePartyFollower 7
    @ "This lesson began ten minutes ago, Potter. Sit down."
    ShowRoomDialog 410
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room00V1Route19_id, 0, 1, 0, 0, 0
    End
Room00V1Chain9:
    ArmChainYield 1
    SetTileObjectFacing Room00V1Group1_id, 0, 2
    @ "Professor Lupin says he's feeling too ill to teach today."
    @ "I would like you all to go to the library and research the subject of - werewolves. Now, run along."
    ShowRoomDialog 411
    SetQuestState 27, 25
    DespawnRoomRowObjects Room00V1Group6_id
    DelayedRespawnRowAndRunChain 0, Room00V1Group4_id, 0
    InvokeChainIfEnabled 0, Room00V1Chain2_id
    End
Room00V1Chain10:
    SetOverworldMonstersDisabled
    RespawnRowAndRunChain Room00V1Group5_id, 0
    RespawnRowAndRunChain Room00V1Group1_id, 0
    RespawnRowAndRunChain Room00V1Group6_id, 0
    End
Room00V1Chain11:
    SetOverworldMonstersDisabled
    RespawnRowAndRunChain Room00V1Group1_id, 0
    RespawnRowAndRunChain Room00V1Group7_id, 0
    End
Room00V1Chain12:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ResetPartyLeaderSelection
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room00V1Route10_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room00V1Group1_id, 0, 0, 0, Room00V1Route8_id, 0, 1, 0, 0, 0
    End
Room00V1Chain13:
    ArmChainYield 1
    @ "Potter, Weasley... where is your research?"
    ShowRoomDialog 423
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room00V1Route11_id, 0, 1, 0, 0, 0
    End
Room00V1Chain14:
    ArmChainYield 1
    RespawnRowAndRunChain Room00V1Group8_id, 0
    @ "Here it is, Professor!"
    ShowRoomDialog 424
    SetTileObjectFacing 0, 255, 2
    QueueTileObjectMove Room00V1Group8_id, 0, 0, 0, 1600, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    RemovePartyFollower 7
    RespawnRowAndRunChain Room00V1Group10_id, 0
    Unk02 Room00V1Group8_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence Room00V1Group8_id, 0, 0, 0, Room00V1Route9_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room00V1Route16_id, 0, 1, 0, 0, 0
    End
Room00V1Chain15:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetTileObjectFacing Room00V1Group1_id, 0, 2
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "This is... acceptable."
    ShowRoomDialog 425
    SetTileObjectFacing 0, 255, 6
    GrantPartyExperience 10, 65535
    PlayRoomSoundEffect 24
    DelayedRespawnRowAndRunChain 1, 0, 0
    RemovePartyFollower 6
    QueueTileObjectMove 0, 255, 0, 0, 1800, 0
    SetTileObjectFacing 0, 255, 6
    ArmChainYield 0
    StartObjectAnimSequence Room00V1Group8_id, 0, 0, 0, Room00V1Route12_id, 0, 1, 0, 0, 0
    End
Room00V1Chain16:
    ArmChainYield 1
    SetTileObjectFacing Room00V1Group8_id, 0, 2
    @ "Hermione, how did you write that up so quickly?"
    @ "Umm... like I said, I'd read the book before. See you later..."
    ShowRoomDialog 426
    ArmChainYield 0
    StartObjectAnimSequence Room00V1Group8_id, 0, 0, 0, Room00V1Route13_id, 0, 1, 0, 0, 0
    End
Room00V1Chain17:
    ArmChainYield 1
    DespawnRoomRowObjects Room00V1Group8_id
    @ "Ever get the feeling there's something funny going on with her?"
    @ "More and more... C'mon, let's get back to the common room."
    ShowRoomDialog 427
    ClearQuestStateUpperHalf
    SetQuestState 30, 25
    SetStoryStage 14
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room00V1Chain18:
    ArmChainYield 1
    @ "Uhhh..."
    ShowRoomDialog 428
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room00V1Route15_id, 0, 1, 0, 0, 0
    End
Room00V1Chain19:
    ArmChainYield 1
    QueueTileObjectMove Room00V1Group1_id, 0, 0, 0, 500, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence Room00V1Group1_id, 0, 0, 0, Room00V1Route17_id, 0, 1, 0, 0, 0
    End
Room00V1Chain20:
    ArmChainYield 1
    DespawnRoomRowObjects Room00V1Group10_id
    SetTileObjectFacing Room00V1Group8_id, 0, 6
    RecruitPartyFollower 7
    RecruitPartyFollower 6
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room00V1Route18_id, 0, 1, 0, 0, 0
    End
Room00V1Chain21:
    @ "Locked."
    ShowRoomDialog 624
    End
Room00V1Chain22:
    StartObjectAnimSequence 0, 255, 0, 0, Room00V1Route14_id, 0, 1, 0, 0, 0
    End
Room00V1Chain23:
    StartObjectAnimSequence Room00V1Group1_id, 0, 0, 0, Room00V1Route7_id, 0, 1, 0, 0, 0
    End
    EndSubBlock Room00V1End

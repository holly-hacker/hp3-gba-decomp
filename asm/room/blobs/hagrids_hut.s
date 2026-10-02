    .include "asm/room_blob.inc"

Room11Blob:
    RoomBlob 1
    PlayerEntry 248, 377, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room11V0
    VariantEntry Room11V1

    SubBlock Room11V0, 1, Room11V0Routes, Room11V0Chains, Room11V0End
    OffsetTable Room11V0Groups, 1
    Offsets Room11V0Group0
    EndTable
    Group Room11V0Group0, 1
    Door 248, 409, half_width=43, half_height=11, destination_room=15, exit_param=5
    OffsetTable Room11V0Routes, 0
    EndTable
    OffsetTable Room11V0Chains, 1
    Offsets Room11V0Chain0
    EndTable
Room11V0Chain0:
    End
    EndSubBlock Room11V0End

    SubBlock Room11V1, 1, Room11V1Routes, Room11V1Chains, Room11V1End
    OffsetTable Room11V1Groups, 14, 1
    Offsets Room11V1Group0, Room11V1Group1, Room11V1Group2, Room11V1Group3, Room11V1Group4, Room11V1Group5
    Offsets Room11V1Group6, Room11V1Group7, Room11V1Group8, Room11V1Group9, Room11V1Group10, Room11V1Group11
    Offsets Room11V1Group12, Room11V1Group13
    EndTable
    Group Room11V1Group0, 0
    Group Room11V1Group1, 2
    Npc 225, 378, sprite=32, facing=0
    Npc 272, 377, sprite=34, facing=0
    Group Room11V1Group2, 1
    Npc 250, 215, sprite=31, facing=0
    Group Room11V1Group3, 1
    Npc 250, 300, sprite=34, facing=0
    Group Room11V1Group4, 1
    Npc 250, 300, sprite=32, facing=0
    Group Room11V1Group5, 1
    Npc 265, 195, sprite=35, facing=0
    Group Room11V1Group6, 1
    TriggerZone 247, 348, half_width=104, half_height=9, chain=Room11V1Chain2_id
    Group Room11V1Group7, 2
    TriggerZone 248, 345, half_width=111, half_height=10, chain=Room11V1Chain12_id
    Npc 250, 188, sprite=35, facing=0, interact_cooldown=3, interact_mode=1, chain=Room11V1Chain18_id
    Group Room11V1Group8, 2
    Npc 248, 255, sprite=32, facing=0
    Npc 248, 275, sprite=34, facing=0
    Group Room11V1Group9, 1
    Npc 310, 320, sprite=4, facing=0
    Group Room11V1Group10, 1
    Npc 232, 184, sprite=35, facing=4, interact_cooldown=3, interact_mode=1, chain=Room11V1Chain18_id
    Group Room11V1Group11, 1
    Prop 249, 247, kind=67
    Group Room11V1Group12, 1
    Npc 235, 185, sprite=35, facing=0
    Group Room11V1Group13, 2
    Npc 290, 190, sprite=35, facing=0, interact_cooldown=3, interact_mode=1, chain=Room11V1Chain24_id, arg_0f=0
    Npc 262, 215, sprite=34, facing=0, interact_cooldown=3, interact_mode=1, chain=Room11V1Chain23_id, arg_0f=0
    OffsetTable Room11V1Routes, 21
    Offsets Room11V1Route0, Room11V1Route1, Room11V1Route2, Room11V1Route3, Room11V1Route4, Room11V1Route5
    Offsets Room11V1Route6, Room11V1Route7, Room11V1Route8, Room11V1Route9, Room11V1Route10, Room11V1Route11
    Offsets Room11V1Route12, Room11V1Route13, Room11V1Route14, Room11V1Route15, Room11V1Route16, Room11V1Route17
    Offsets Room11V1Route18, Room11V1Route19, Room11V1Route20
    EndTable
Room11V1Route0:
    Route 2
    Waypoint 250, 330
    Waypoint 250, 258, on_arrival_chain=Room11V1Chain3_id
Room11V1Route1:
    Route 3
    Waypoint 250, 310
    Waypoint 230, 310
    Waypoint 230, 265, on_arrival_chain=Room11V1Chain4_id
Room11V1Route2:
    Route 3
    Waypoint 250, 300
    Waypoint 270, 300
    Waypoint 270, 260
Room11V1Route3:
    Route 3
    Waypoint 205, 200
    Waypoint 255, 200
    Waypoint 255, 185, on_arrival_chain=Room11V1Chain5_id
Room11V1Route4:
    Route 3
    Waypoint 265, 195
    Waypoint 205, 195
    Waypoint 205, 200
Room11V1Route5:
    Route 2
    Waypoint 250, 258
    Waypoint 250, 215
Room11V1Route6:
    Route 2
    Waypoint 230, 265
    Waypoint 230, 213
Room11V1Route7:
    Route 2
    Waypoint 270, 260
    Waypoint 270, 212
Room11V1Route8:
    Route 2
    Waypoint 230, 215
    Waypoint 230, 387
Room11V1Route9:
    Route 2
    Waypoint 270, 215
    Waypoint 250, 215, on_arrival_chain=Room11V1Chain9_id
Room11V1Route10:
    Route 2
    Waypoint 250, 215
    Waypoint 250, 389, on_arrival_chain=Room11V1Chain7_id
Room11V1Route11:
    Route 2
    Waypoint 250, 215
    Waypoint 250, 385, on_arrival_chain=Room11V1Chain10_id
Room11V1Route12:
    Route 2
    Waypoint 290, 190
    Waypoint 200, 190
Room11V1Route13:
    Route 3
    Waypoint 248, 340
    Waypoint 248, 243, on_arrival_chain=Room11V1Chain13_id
    Waypoint 248, 225
Room11V1Route14:
    Route 2
    Waypoint 250, 188
    Waypoint 250, 205, on_arrival_chain=Room11V1Chain14_id
Room11V1Route15:
    Route 4
    Waypoint 248, 255
    Waypoint 225, 255
    Waypoint 225, 215
    Waypoint 230, 215
Room11V1Route16:
    Route 4
    Waypoint 248, 275
    Waypoint 270, 275
    Waypoint 270, 210
    Waypoint 265, 210, on_arrival_chain=Room11V1Chain15_id
Room11V1Route17:
    Route 3
    Waypoint 310, 320
    Waypoint 310, 215
    Waypoint 235, 215, on_arrival_chain=Room11V1Chain16_id
Room11V1Route18:
    Route 3
    Waypoint 230, 215
    Waypoint 248, 215
    Waypoint 248, 225
Room11V1Route19:
    Route 3
    Waypoint 265, 210
    Waypoint 248, 210
    Waypoint 248, 225, on_arrival_chain=Room11V1Chain17_id
Room11V1Route20:
    Route 2
    Waypoint 248, 225
    Waypoint 248, 315, on_arrival_chain=Room11V1Chain19_id
    OffsetTable Room11V1Chains, 26, 1
    Offsets Room11V1Chain0, Room11V1Chain1, Room11V1Chain2, Room11V1Chain3, Room11V1Chain4, Room11V1Chain5
    Offsets Room11V1Chain6, Room11V1Chain7, Room11V1Chain8, Room11V1Chain9, Room11V1Chain10, Room11V1Chain11
    Offsets Room11V1Chain12, Room11V1Chain13, Room11V1Chain14, Room11V1Chain15, Room11V1Chain16, Room11V1Chain17
    Offsets Room11V1Chain18, Room11V1Chain19, Room11V1Chain20, Room11V1Chain21, Room11V1Chain22, Room11V1Chain23
    Offsets Room11V1Chain24, Room11V1Chain25
    EndTable
Room11V1Chain0:
    GotoIfStoryStageCompare 0, 15, Room11V1Chain1_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 21, Room11V1Chain11_id, 0, Room11V1Group7_id, 0
    GotoIfStoryStageCompare 0, 22, Room11V1Chain20_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 25, Room11V1Chain21_id, 0, 0, 0
    End
Room11V1Chain1:
    ResetPartyLeaderSelection
    GotoIfQuestStateCompare 224, 0, 0, 0, Room11V1Chain22_id, Room11V1Group6_id, Room11V1Group13_id
    End
Room11V1Chain2:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ResetPartyLeaderSelection
    RespawnRowAndRunChain Room11V1Group5_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room11V1Route0_id, 0, 1, 0, 0, 0
    End
Room11V1Chain3:
    ArmChainYield 1
    RespawnRowAndRunChain Room11V1Group11_id, 0
    @ "Hagrid! Look at my new Firebolt!"
    ShowRoomDialog 436
    DespawnRoomRowObjects Room11V1Group6_id
    RemovePartyFollower 6
    RespawnRowAndRunChain Room11V1Group3_id, 0
    RemovePartyFollower 7
    RespawnRowAndRunChain Room11V1Group4_id, 0
    ArmChainYield 0
    StartObjectAnimSequence Room11V1Group5_id, 0, 0, 0, Room11V1Route4_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room11V1Group3_id, 0, 0, 0, Room11V1Route2_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room11V1Group4_id, 0, 0, 0, Room11V1Route1_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room11V1Group5_id, 0, 0, 0, 1000, 0
    End
Room11V1Chain4:
    ArmChainYield 1
    @ "Yeh've heard!"
    @ "Hagrid, what is it?"
    ShowRoomDialog 437
    DespawnRoomRowObjects Room11V1Group11_id
    ArmChainYield 0
    StartObjectAnimSequence Room11V1Group5_id, 0, 0, 0, Room11V1Route3_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room11V1Route5_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room11V1Group4_id, 0, 0, 0, Room11V1Route6_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room11V1Group3_id, 0, 0, 0, Room11V1Route7_id, 0, 1, 0, 0, 0
    End
Room11V1Chain5:
    ArmChainYield 1
    SetTileObjectFacing Room11V1Group3_id, 0, 0
    DelayedRespawnRowAndRunChainFrames 15, 0, 0
    @ "They're going ter put poor Buckbeak on trial fer attackin' Malfoy..."
    @ "Listen, you can't give up. You just need a good defense. You can call us as witnesses."
    @ "I'm sure I've read about a case of Hippogriff-baiting¸"
    @ "We can look it up for you in the library. Coming, Hermione?"
    @ "No. I want a quick word with Professor McGonagall."
    @ "Don't worry, we'll work out a defense for Buckbeak. Let's go to the library, Ron."
    ShowRoomDialog 438
    DelayedRespawnRowAndRunChainFrames 15, 0, 0
    SetTileObjectFacing Room11V1Group3_id, 0, 4
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    Unk02 Room11V1Group4_id, 0, 2
    InvokeChainIfEnabled 0, Room11V1Chain6_id
    End
Room11V1Chain6:
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room11V1Route10_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room11V1Group4_id, 0, 0, 0, Room11V1Route8_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room11V1Group5_id, 0, 0, 0, Room11V1Route12_id, 0, 0, 0, 0, 0
    End
Room11V1Chain7:
    ArmChainYield 1
    SetQuestState 0, 230
    SetQuestState 1, 224
    SetQuestState QUEST_OBJ_GO_TO_LIBRARY_FOR_HERMIONE, QUEST_OBJECTIVE_INDEX
    RecruitPartyFollower 7
    DespawnRoomRowObjects Room11V1Group4_id
    SetTileObjectAnimStateWithSpeed 0, 255
    ReturnToOverworld 15, 5
    End
Room11V1Chain8:
    ArmChainYield 0
    StartObjectAnimSequence Room11V1Group3_id, 0, 0, 0, Room11V1Route9_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room11V1Group5_id, 0, 0, 0, Room11V1Route12_id, 0, 0, 0, 0, 0
    End
Room11V1Chain9:
    ArmChainYield 1
    Unk2A 6, 255, 255, 255
    RespawnRowAndRunChain Room11V1Group2_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room11V1Route11_id, 0, 1, 0, 0, 0
    End
Room11V1Chain10:
    ReturnToOverworld 15, 5
    End
Room11V1Chain11:
    GotoIfQuestStateCompare 233, 0, 1, 0, 0, Room11V1Group7_id, 0
    End
Room11V1Chain12:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room11V1Route13_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room11V1Group7_id, 1, 0, 0, 700, 0
    End
Room11V1Chain13:
    StartObjectAnimSequence Room11V1Group7_id, 1, 0, 0, Room11V1Route14_id, 0, 1, 0, 0, 0
    End
Room11V1Chain14:
    ArmChainYield 1
    @ "Isn't there anything anyone can do, Hagrid?"
    @ "Dumbledore's tried. He's got no power ter overrule the Committee. I expect Lucius Malfoy's threatened 'em."
    @ "We'll stay with you, Hagrid¸"
    ShowRoomDialog 546
    RespawnRowAndRunChain Room11V1Group8_id, 0
    RemovePartyFollower 7
    RemovePartyFollower 6
    ArmChainYield 0
    StartObjectAnimSequence Room11V1Group8_id, 0, 0, 0, Room11V1Route15_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room11V1Group8_id, 1, 0, 0, Room11V1Route16_id, 0, 1, 0, 0, 0
    End
Room11V1Chain15:
    ArmChainYield 1
    RespawnRowAndRunChain Room11V1Group9_id, 0
    Unk02 Room11V1Group9_id, 0, 3
    ArmChainYield 0
    StartObjectAnimSequence Room11V1Group9_id, 0, 0, 0, Room11V1Route17_id, 0, 1, 0, 0, 0
    End
Room11V1Chain16:
    ArmChainYield 1
    QueueTileObjectMove Room11V1Group8_id, 0, 0, 0, 1000, 0
    @ "Squeak!"
    @ "It's Scabbers! Scabbers, what are you doing here?"
    ShowRoomDialog 547
    DespawnRoomRowObjects Room11V1Group9_id
    @ "They're comin' - Macnair, the executioner, and Fudge. Yeh'd best leave now."
    @ "We'll be back, Hagrid..."
    ShowRoomDialog 548
    ArmChainYield 0
    QueueTileObjectMove 0, 255, 0, 0, 1000, 0
    StartObjectAnimSequence Room11V1Group8_id, 0, 0, 0, Room11V1Route18_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room11V1Group8_id, 1, 0, 0, Room11V1Route19_id, 0, 1, 0, 0, 0
    End
Room11V1Chain17:
    ArmChainYield 1
    RecruitPartyFollower 7
    RecruitPartyFollower 6
    DespawnRoomRowObjects Room11V1Group8_id
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room11V1Route20_id, 0, 1, 0, 0, 0
    End
Room11V1Chain18:
    @ "They're comin' - Macnair, the executioner, and Fudge. Yeh'd best leave now."
    ShowRoomDialog 550
    End
Room11V1Chain19:
    ArmChainYield 1
    DespawnTileObject Room11V1Group7_id, 0
    SetQuestState QUEST_OBJ_GO_TO_WHOMPING_WILLOW, QUEST_OBJECTIVE_INDEX
    SetQuestState 2, 233
    SetStoryStage 22
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room11V1Chain20:
    GotoIfQuestStateCompare 129, 0, 0, 0, 0, Room11V1Group10_id, Room11V1Group12_id
    End
Room11V1Chain21:
    SetStoryStage 26
    End
Room11V1Chain22:
    ArmChainYield 1
    DelayedRespawnRowAndRunChainFrames 5, 0, 0
    GotoIfQuestStateCompare 230, 0, 1, Room11V1Chain25_id, 0, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence Room11V1Group13_id, 0, 0, 0, Room11V1Route12_id, 0, 0, 0, 0, 0
    End
Room11V1Chain23:
    @ "Harry. Hurry up!"
    ShowRoomDialog 457
    End
Room11V1Chain24:
    @ "I really appreciate all yeh've done."
    ShowRoomDialog 458
    End
Room11V1Chain25:
    DespawnTileObject Room11V1Group13_id, 1
    End
    EndSubBlock Room11V1End

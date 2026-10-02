    .include "asm/room_blob.inc"

Room13Blob:
    RoomBlob 3
    PlayerEntry 23, 285, 0, 0
    PlayerEntry 25, 629, 1, 0
    PlayerEntry 108, 358, 2, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room13V0
    VariantEntry Room13V1

    SubBlock Room13V0, 1, Room13V0Routes, Room13V0Chains, Room13V0End
    OffsetTable Room13V0Groups, 1
    Offsets Room13V0Group0
    EndTable
    Group Room13V0Group0, 3
    Door 3, 606, half_width=8, half_height=58, destination_room=15, exit_param=2
    Door 2, 277, half_width=8, half_height=40, destination_room=15, exit_param=3
    Chest 550, 545, flag_id=117, reward_id=25
    OffsetTable Room13V0Routes, 0
    EndTable
    OffsetTable Room13V0Chains, 1
    Offsets Room13V0Chain0
    EndTable
Room13V0Chain0:
    End
    EndSubBlock Room13V0End

    SubBlock Room13V1, 1, Room13V1Routes, Room13V1Chains, Room13V1End
    OffsetTable Room13V1Groups, 13, 1
    Offsets Room13V1Group0, Room13V1Group1, Room13V1Group2, Room13V1Group3, Room13V1Group4, Room13V1Group5
    Offsets Room13V1Group6, Room13V1Group7, Room13V1Group8, Room13V1Group9, Room13V1Group10, Room13V1Group11
    Offsets Room13V1Group12
    EndTable
    Group Room13V1Group0, 0
    Group Room13V1Group1, 2
    TriggerZone 78, 281, half_width=47, half_height=9, chain=Room13V1Chain1_id
    TriggerZone 23, 328, half_width=7, half_height=90, chain=Room13V1Chain1_id
    Group Room13V1Group2, 1
    Npc 15, 215, sprite=12, facing=4
    Group Room13V1Group3, 1
    Npc 175, 355, sprite=12, facing=6
    Group Room13V1Group4, 1
    Npc 135, 418, sprite=12, facing=0
    Group Room13V1Group5, 1
    Npc 4, 350, sprite=12, facing=2
    Group Room13V1Group6, 0
    Group Room13V1Group7, 3
    Npc 5, 333, sprite=98, facing=2
    Npc 108, 329, sprite=31, facing=6
    Npc 125, 340, sprite=34, facing=6
    Group Room13V1Group8, 2
    Npc 250, 727, sprite=36, facing=0
    Npc 225, 720, sprite=34, facing=0
    Group Room13V1Group9, 4
    Npc 77, 260, sprite=12, facing=4
    Npc 160, 345, sprite=12, facing=6
    Npc 85, 395, sprite=12, facing=0
    Npc 5, 340, sprite=12, facing=2
    Group Room13V1Group10, 2
    Npc 87, 335, sprite=16, facing=0
    Npc 71, 341, sprite=34, facing=6
    Group Room13V1Group11, 1
    Npc 82, 334, sprite=34, facing=4
    Group Room13V1Group12, 1
    Npc 83, 390, sprite=109, facing=0
    OffsetTable Room13V1Routes, 20
    Offsets Room13V1Route0, Room13V1Route1, Room13V1Route2, Room13V1Route3, Room13V1Route4, Room13V1Route5
    Offsets Room13V1Route6, Room13V1Route7, Room13V1Route8, Room13V1Route9, Room13V1Route10, Room13V1Route11
    Offsets Room13V1Route12, Room13V1Route13, Room13V1Route14, Room13V1Route15, Room13V1Route16, Room13V1Route17
    Offsets Room13V1Route18, Room13V1Route19
    EndTable
Room13V1Route0:
    Route 5
    Waypoint 35, 280
    Waypoint 91, 331, on_arrival_chain=Room13V1Chain4_id
    Waypoint 120, 350
    Waypoint 123, 382
    Waypoint 100, 387, on_arrival_chain=Room13V1Chain6_id
Room13V1Route1:
    Route 2
    Waypoint 15, 215
    Waypoint 15, 275, on_arrival_chain=Room13V1Chain3_id
Room13V1Route2:
    Route 2
    Waypoint 175, 355
    Waypoint 147, 354
Room13V1Route3:
    Route 2
    Waypoint 135, 418
    Waypoint 135, 380
Room13V1Route4:
    Route 2
    Waypoint 4, 350
    Waypoint 40, 350
Room13V1Route5:
    Route 6
    Waypoint 88, 383
    Waypoint 59, 369, on_arrival_chain=Room13V1Chain7_id
    Waypoint 54, 331
    Waypoint 72, 324
    Waypoint 107, 337
    Waypoint 107, 345
Room13V1Route6:
    Route 2
    Waypoint 4, 325
    Waypoint 35, 325
Room13V1Route7:
    Route 3
    Waypoint 15, 275
    Waypoint 70, 275
    Waypoint 69, 295
Room13V1Route8:
    Route 2
    Waypoint 135, 380
    Waypoint 90, 380, on_arrival_chain=Room13V1Chain8_id
Room13V1Route9:
    Route 4
    Waypoint 25, 629
    Waypoint 170, 725
    Waypoint 250, 727
    Waypoint 250, 721, on_arrival_chain=Room13V1Chain11_id
Room13V1Route10:
    Route 2
    Waypoint 5, 333
    Waypoint 75, 333, on_arrival_chain=Room13V1Chain12_id
Room13V1Route11:
    Route 2
    Waypoint 72, 333
    Waypoint 10, 333, on_arrival_chain=Room13V1Chain18_id
Room13V1Route12:
    Route 2
    Waypoint 195, 700
    Waypoint 195, 690, on_arrival_chain=Room13V1Chain14_id
Room13V1Route13:
    Route 2
    Waypoint 77, 260
    Waypoint 77, 306, on_arrival_chain=Room13V1Chain15_id
Room13V1Route14:
    Route 2
    Waypoint 160, 345
    Waypoint 115, 345
Room13V1Route15:
    Route 2
    Waypoint 85, 398
    Waypoint 85, 353
Room13V1Route16:
    Route 2
    Waypoint 5, 340
    Waypoint 50, 340
Room13V1Route17:
    Route 3
    Waypoint 108, 358
    Waypoint 55, 358
    Waypoint 60, 358, on_arrival_chain=Room13V1Chain17_id
Room13V1Route18:
    Route 5
    Waypoint 108, 358
    Waypoint 80, 358
    Waypoint 90, 340
    Waypoint 115, 340
    Waypoint 115, 345
Room13V1Route19:
    Route 4
    Waypoint 250, 723
    Waypoint 250, 729
    Waypoint 198, 705
    Waypoint 198, 700, on_arrival_chain=Room13V1Chain13_id
    OffsetTable Room13V1Chains, 22, 1
    Offsets Room13V1Chain0, Room13V1Chain1, Room13V1Chain2, Room13V1Chain3, Room13V1Chain4, Room13V1Chain5
    Offsets Room13V1Chain6, Room13V1Chain7, Room13V1Chain8, Room13V1Chain9, Room13V1Chain10, Room13V1Chain11
    Offsets Room13V1Chain12, Room13V1Chain13, Room13V1Chain14, Room13V1Chain15, Room13V1Chain16, Room13V1Chain17
    Offsets Room13V1Chain18, Room13V1Chain19, Room13V1Chain20, Room13V1Chain21
    EndTable
Room13V1Chain0:
    GotoIfStoryStageCompare 0, 24, Room13V1Chain2_id, 0, Room13V1Group1_id, 0
    GotoIfStoryStageCompare 0, 26, Room13V1Chain21_id, 0, Room13V1Group7_id, 0
    End
Room13V1Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    PlayMusicModuleAndFlagIfChain1 9
    RespawnRowAndRunChain Room13V1Group2_id, 0
    ArmChainYield 0
    StartObjectAnimSequence Room13V1Group2_id, 0, 0, 0, Room13V1Route1_id, 0, 1, 0, 0, 0
    DespawnRoomRowObjects Room13V1Group1_id
    End
Room13V1Chain2:
    SetOverworldMonstersDisabled
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room13V1Group12_id, 0
    SetQuestState 48, 25
    RecruitPartyFollower 6
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room13V1Route17_id, 0, 1, 0, 0, 0
    End
Room13V1Chain3:
    ArmChainYield 1
    RespawnRowAndRunChain Room13V1Group3_id, 0
    RespawnRowAndRunChain Room13V1Group4_id, 0
    RespawnRowAndRunChain Room13V1Group5_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room13V1Route0_id, 0, 1, 0, 0, 0
    End
Room13V1Chain4:
    StartObjectAnimSequence Room13V1Group3_id, 0, 0, 0, Room13V1Route2_id, 0, 1, 0, 0, 0
    End
Room13V1Chain5:
    StartObjectAnimSequence Room13V1Group4_id, 0, 0, 0, Room13V1Route3_id, 0, 1, 0, 0, 0
    End
Room13V1Chain6:
    ArmChainYield 1
    StartTileObjectScript 88, 127, 1, 0, 255, 0, 0, 6, 255, 255, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room13V1Route5_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room13V1Group5_id, 0, 0, 0, Room13V1Route4_id, 0, 1, 0, 0, 0
    End
Room13V1Chain7:
    StartObjectAnimSequence Room13V1Group2_id, 0, 0, 0, Room13V1Route7_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room13V1Group4_id, 0, 0, 0, Room13V1Route8_id, 0, 1, 0, 0, 0
    End
Room13V1Chain8:
    ArmChainYield 1
    @ "Expecto... Expecto patro... No - no - he's innocent¸"
    ShowRoomDialog 585
    RespawnRowAndRunChain Room13V1Group11_id, 0
    RemovePartyFollower 6
    PlaySoundById 161
    ClearQuestStateUpperHalf
    UnlockMinigame 4
    StartMinigame 4, 2, 1, 0, Room13V1Chain9_id
    End
Room13V1Chain9:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "Dad?"
    ShowRoomDialog 586
    SetQuestState 50, 25
    ReturnToOverworld 33, 2
    End
Room13V1Chain10:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 130
    SetQuestState 2, 129
    RespawnRowAndRunChain Room13V1Group12_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room13V1Route9_id, 0, 1, 0, 0, 0
    End
Room13V1Chain11:
    ArmChainYield 1
    @ "Look, it's us... and Lupin's closing in!"
    ShowRoomDialog 595
    QueueTileObjectMove Room13V1Group7_id, 1, 0, 0, 2000, 0
    ArmChainYield 0
    StartObjectAnimSequence Room13V1Group7_id, 0, 0, 0, Room13V1Route10_id, 0, 1, 0, 0, 0
    End
Room13V1Chain12:
    ArmChainYield 1
    @ "I know what to do! Arrrrrooooooooh!"
    ShowRoomDialog 599
    PlaySoundById 54
    StartTileObjectScript 72, 77, 1, Room13V1Group7_id, 0, 0, 0, 0, 255, 255, 255
    @ "Well done, Hermione!"
    ShowRoomDialog 596
    DelayedRespawnRowAndRunChain 1, 0, 0
    Unk02 Room13V1Group7_id, 0, 2
    @ "Here comes Lupin! Help, Buckbeak!"
    ShowRoomDialog 597
    ArmChainYield 0
    QueueTileObjectMove 0, 255, 0, 0, 1000, 0
    StartObjectAnimSequence Room13V1Group7_id, 0, 0, 0, Room13V1Route11_id, 0, 1, 0, 0, 0
    End
Room13V1Chain13:
    ArmChainYield 1
    SetQuestState 53, 25
    SetQuestState 0, 129
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "The Dementors almost have Sirius! Where are you, Dad? Wait a minute, it wasn't Dad, it was¸ me."
    @ "Harry. Hurry up!"
    @ "Wait here, Hermione¸"
    ShowRoomDialog 602
    DespawnRoomRowObjects Room13V1Group7_id
    RespawnRowAndRunChain Room13V1Group9_id, 0
    RespawnRowAndRunChain Room13V1Group10_id, 0
    QueueTileObjectMove Room13V1Group10_id, 1, 0, 0, 2000, 0
    RemovePartyFollower 8
    RemovePartyFollower 6
    RespawnRowAndRunChain Room13V1Group8_id, 0
    ArmChainYield 0
    StartObjectAnimSequence Room13V1Group9_id, 0, 0, 0, Room13V1Route13_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room13V1Group9_id, 1, 0, 0, Room13V1Route14_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room13V1Group9_id, 2, 0, 0, Room13V1Route15_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room13V1Group9_id, 3, 0, 0, Room13V1Route16_id, 0, 1, 0, 0, 0
    End
Room13V1Chain14:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 2, 0, 0
    PlaySoundById 88
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "EXPECTO PATRONUM!"
    ShowRoomDialog 603
    PlayCutscene 14, 0, Room13V1Chain16_id
    End
Room13V1Chain15:
    StartObjectAnimSequence 0, 255, 0, 0, Room13V1Route12_id, 0, 1, 0, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 2000, 0
    End
Room13V1Chain16:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "What did you do?"
    @ "I just saved our lives! Listen, I'll fly Buckbeak up to the West Tower's window... You go there on foot. Maybe one of us will get there in time to rescue Sirius."
    @ "And whoever gets there first can set Sirius free! Let's go!"
    @ "Come on, Buckbeak, we have to get to Sirius!"
    ShowRoomDialog 604
    RecruitPartyFollower 6
    SetQuestState 0, 130
    UnlockMinigame 1
    StartMinigame 1, 2, 0, 0, 0
    End
Room13V1Chain17:
    ArmChainYield 1
    @ "Hermione, Pettigrew's gone, he transformed!"
    @ "Do something, Harry! Please!"
    ShowRoomDialog 584
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room13V1Chain18:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    StartBattle 3, 0, Room13V1Chain19_id
    End
Room13V1Chain19:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChainFrames 5, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room13V1Route19_id, 0, 1, 0, 0, 0
    End
Room13V1Chain20:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 270, 215, 2, 0, 255, 0, 0, 0, 255, 255, 255
    SetTileObjectFacing 0, 255, 0
    @ "Here comes Lupin! Help, Buckbeak!"
    ShowRoomDialog 597
    InvokeChainIfEnabled 0, Room13V1Chain18_id
    End
Room13V1Chain21:
    SetOverworldMonstersDisabled
    GotoIfQuestStateCompare 129, 0, 2, Room13V1Chain20_id, Room13V1Chain10_id, 0, 0
    End
    EndSubBlock Room13V1End

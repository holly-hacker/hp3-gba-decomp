    .include "asm/room_blob.inc"

Room17Blob:
    RoomBlob 2
    PlayerEntry 125, 132, 0, 4
    PlayerEntry 269, 785, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room17V0
    VariantEntry Room17V1

    SubBlock Room17V0, 1, Room17V0Routes, Room17V0Chains, Room17V0End
    OffsetTable Room17V0Groups, 1
    Offsets Room17V0Group0
    EndTable
    Group Room17V0Group0, 4
    Door 267, 810, half_width=48, half_height=10, destination_room=16, exit_param=6
    Door 117, 106, half_width=15, half_height=13, destination_room=31, exit_param=8
    Chest 431, 133, flag_id=17, reward_id=120
    Chest 107, 655, flag_id=18, reward_id=59
    OffsetTable Room17V0Routes, 0
    EndTable
    OffsetTable Room17V0Chains, 1
    Offsets Room17V0Chain0
    EndTable
Room17V0Chain0:
    SetQuestState 1, QUEST_CASTLE_AREA
    SetDefeatWarpSelector 2
    End
    EndSubBlock Room17V0End

    SubBlock Room17V1, 1, Room17V1Routes, Room17V1Chains, Room17V1End
    OffsetTable Room17V1Groups, 7, 1
    Offsets Room17V1Group0, Room17V1Group1, Room17V1Group2, Room17V1Group3, Room17V1Group4, Room17V1Group5
    Offsets Room17V1Group6
    EndTable
    Group Room17V1Group0, 0
    Group Room17V1Group1, 19
    Npc 371, 408, sprite=30, facing=6, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain25_id, arg_0f=0
    Npc 182, 584, sprite=50, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain19_id, arg_0f=0
    Npc 233, 555, sprite=58, facing=6, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain14_id, arg_0f=0
    Npc 371, 455, sprite=47, facing=6, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain15_id, arg_0f=0
    Npc 321, 579, sprite=41, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain16_id, arg_0f=0
    Npc 182, 543, sprite=46, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain18_id, arg_0f=0
    Npc 374, 527, sprite=61, facing=6, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain23_id, arg_0f=0
    Npc 179, 434, sprite=44, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain21_id, arg_0f=0
    Npc 120, 391, sprite=60, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain12_id, arg_0f=0
    Npc 184, 382, sprite=22, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain20_id, arg_0f=0
    Npc 232, 443, sprite=28, facing=6, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain17_id, arg_0f=0
    Npc 320, 532, sprite=45, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain13_id, arg_0f=0
    Npc 260, 125, sprite=24, facing=4, arg_0f=0
    Npc 110, 297, sprite=20, facing=4, interact_cooldown=3, interact_mode=1, arg_0f=0
    Npc 378, 294, sprite=17, facing=4, arg_0f=0
    Npc 404, 295, sprite=15, facing=4, arg_0f=0
    TriggerZone 266, 728, half_width=100, half_height=34, chain=Room17V1Chain1_id
    TriggerZone 125, 168, half_width=40, half_height=10, chain=Room17V1Chain4_id
    TriggerZone 185, 147, half_width=8, half_height=36, chain=Room17V1Chain3_id
    Group Room17V1Group2, 1
    Prop 313, 409, kind=67
    Group Room17V1Group3, 1
    Npc 318, 459, sprite=32, facing=0
    Group Room17V1Group4, 1
    Npc 277, 312, sprite=34, facing=4
    Group Room17V1Group5, 2
    Npc 319, 444, sprite=32, facing=2
    Npc 319, 465, sprite=34, facing=2
    Group Room17V1Group6, 10
    Npc 119, 388, sprite=60, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain12_id, arg_0f=0
    Npc 183, 380, sprite=22, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain20_id, arg_0f=0
    Npc 181, 433, sprite=44, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain21_id, arg_0f=0
    Npc 232, 442, sprite=28, facing=6, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain17_id, arg_0f=0
    Npc 320, 532, sprite=45, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain13_id, arg_0f=0
    Npc 321, 578, sprite=41, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain16_id, arg_0f=0
    Npc 371, 408, sprite=30, facing=6, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain25_id, arg_0f=0
    Npc 371, 456, sprite=47, facing=6, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain15_id, arg_0f=0
    Npc 181, 584, sprite=50, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain19_id, arg_0f=0
    Npc 182, 543, sprite=46, facing=2, interact_cooldown=3, interact_mode=1, chain=Room17V1Chain18_id, arg_0f=0
    OffsetTable Room17V1Routes, 7
    Offsets Room17V1Route0, Room17V1Route1, Room17V1Route2, Room17V1Route3, Room17V1Route4, Room17V1Route5
    Offsets Room17V1Route6
    EndTable
Room17V1Route0:
    Route 7
    Waypoint 174, 156
    Waypoint 125, 155
    Waypoint 125, 182
    Waypoint 125, 290
    Waypoint 305, 290
    Waypoint 305, 430
    Waypoint 318, 430, on_arrival_chain=Room17V1Chain5_id
Room17V1Route1:
    Route 3
    Waypoint 305, 690
    Waypoint 305, 430
    Waypoint 318, 430, on_arrival_chain=Room17V1Chain5_id
Room17V1Route2:
    Route 3
    Waypoint 377, 292
    Waypoint 300, 292
    Waypoint 300, 298, on_arrival_chain=Room17V1Chain11_id
Room17V1Route3:
    Route 3
    Waypoint 318, 430
    Waypoint 313, 430
    Waypoint 313, 420
Room17V1Route4:
    Route 4
    Waypoint 404, 295
    Waypoint 404, 312
    Waypoint 300, 312
    Waypoint 300, 410, on_arrival_chain=Room17V1Chain8_id
Room17V1Route5:
    Route 2
    Waypoint 296, 410
    Waypoint 296, 541, on_arrival_chain=Room17V1Chain9_id
Room17V1Route6:
    Route 2
    Waypoint 300, 298
    Waypoint 300, 401, on_arrival_chain=Room17V1Chain6_id
    OffsetTable Room17V1Chains, 27, 1
    Offsets Room17V1Chain0, Room17V1Chain1, Room17V1Chain2, Room17V1Chain3, Room17V1Chain4, Room17V1Chain5
    Offsets Room17V1Chain6, Room17V1Chain7, Room17V1Chain8, Room17V1Chain9, Room17V1Chain10, Room17V1Chain11
    Offsets Room17V1Chain12, Room17V1Chain13, Room17V1Chain14, Room17V1Chain15, Room17V1Chain16, Room17V1Chain17
    Offsets Room17V1Chain18, Room17V1Chain19, Room17V1Chain20, Room17V1Chain21, Room17V1Chain22, Room17V1Chain23
    Offsets Room17V1Chain24, Room17V1Chain25, Room17V1Chain26
    EndTable
Room17V1Chain0:
    GotoIfStoryStageCompare 0, 16, Room17V1Chain2_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 17, Room17V1Chain10_id, 0, Room17V1Group6_id, 0
    End
Room17V1Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room17V1Route1_id, 0, 1, 0, 0, 0
    End
Room17V1Chain2:
    SetOverworldMonstersDisabled
    GotoIfQuestStateCompare 244, 0, 0, Room17V1Chain10_id, 0, Room17V1Group1_id, 0
    End
Room17V1Chain3:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room17V1Route0_id, 0, 1, 0, 0, 0
    End
Room17V1Chain4:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room17V1Route0_id, 2, 1, 0, 0, 0
    End
Room17V1Chain5:
    ArmChainYield 1
    QueueTileObjectMove Room17V1Group1_id, 14, 0, 0, 1600, 0
    RemovePartyFollower 7
    RespawnRowAndRunChain Room17V1Group3_id, 0
    RespawnRowAndRunChain Room17V1Group2_id, 0
    ArmChainYield 0
    StartObjectAnimSequence Room17V1Group1_id, 14, 0, 0, Room17V1Route2_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room17V1Route3_id, 0, 1, 0, 0, 0
    End
Room17V1Chain6:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "May I see it? Hmm. And there was no note at all, Potter?"
    @ "No."
    @ "I see. Well, I'm afraid I will have to take this, Potter."
    @ "W-what? Why?"
    @ "It will need to be checked for jinxes. It shouldn't take more than a few weeks."
    @ "You will have it back if we are sure it is jinx-free. I shall keep you informed."
    ShowRoomDialog 461
    ConsumeRoomItem 67
    @ "I don't believe it!"
    @ "There's nothing wrong with it!"
    ShowRoomDialog 462
    RespawnRowAndRunChain Room17V1Group4_id, 0
    QueueTileObjectMove Room17V1Group4_id, 0, 0, 0, 2000, 0
    @ "Hermione! What did you go running to McGonagall for?"
    @ "Because I thought - and Professor McGonagall agrees with me - that that broom was probably sent to Harry by Sirius Black!"
    ShowRoomDialog 463
    QueueTileObjectMove Room17V1Group1_id, 12, 0, 0, 1800, 0
    @ "Merry Christmas! Sit down, sit down! And now - crackers! Or, to be precise, Wizard Cracker Pop-it! A new game I've just invented!"
    ShowRoomDialog 464
    DespawnRoomRowObjects Room17V1Group3_id
    DespawnRoomRowObjects Room17V1Group4_id
    DespawnRoomRowObjects Room17V1Group2_id
    DespawnTileObject Room17V1Group1_id, 14
    RespawnRowAndRunChain Room17V1Group5_id, 0
    UnlockMinigame 0
    StartMinigame 0, 0, 1, 0, Room17V1Chain7_id
    End
Room17V1Chain7:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    @ "That was a lot of fun."
    @ "Yes, it was!"
    @ "Wizard Cracker Pop-it can now be accessed from the Mini-Games menu found on the Title Screen."
    @ "Let's go to the common room and try and take our minds off losing the Firebolt¸"
    ShowRoomDialog 465
    QueueTileObjectMove Room17V1Group1_id, 15, 0, 0, 2000, 0
    ArmChainYield 0
    StartObjectAnimSequence Room17V1Group1_id, 15, 0, 0, Room17V1Route4_id, 0, 1, 0, 0, 0
    End
Room17V1Chain8:
    ArmChainYield 1
    @ "I was wondering, Harry, if you'd like to begin the Anti-Dementor lessons I promised you?"
    @ "Of course, Professor."
    @ "Very well, then. Meet me in my office on the third floor."
    ShowRoomDialog 483
    QueueTileObjectMove 0, 255, 0, 0, 1000, 0
    ArmChainYield 0
    StartObjectAnimSequence Room17V1Group1_id, 15, 0, 0, Room17V1Route5_id, 0, 1, 0, 0, 0
    End
Room17V1Chain9:
    ArmChainYield 1
    DespawnTileObject Room17V1Group1_id, 15
    DespawnTileObject Room17V1Group1_id, 16
    DespawnTileObject Room17V1Group1_id, 17
    DespawnTileObject Room17V1Group1_id, 18
    DespawnTileObject Room17V1Group1_id, 6
    DespawnTileObject Room17V1Group1_id, 2
    DespawnTileObject Room17V1Group1_id, 13
    SetQuestState QUEST_OBJ_GO_TO_LUPINS_OFFICE, QUEST_OBJECTIVE_INDEX
    SetQuestState 0, 230
    SetStoryStage 17
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room17V1Chain10:
    SetOverworldMonstersDisabled
    End
Room17V1Chain11:
    ArmChainYield 1
    @ "Miss Granger has recently informed me that you have been sent a broomstick, Potter."
    ShowRoomDialog 460
    ArmChainYield 0
    StartObjectAnimSequence Room17V1Group1_id, 14, 0, 0, Room17V1Route6_id, 0, 1, 0, 0, 0
    End
Room17V1Chain12:
    @ "I love the Christmas feast!"
    ShowRoomDialog 466
    End
Room17V1Chain13:
    @ "I'm going to eat so much at the Christmas Feast they'll have to send me to Madam Pomfrey!"
    ShowRoomDialog 467
    End
Room17V1Chain14:
    @ "I hope there are crackers at the Christmas feast."
    ShowRoomDialog 468
    End
Room17V1Chain15:
    @ "Great! It's time for the Christmas feast!"
    ShowRoomDialog 469
    End
Room17V1Chain16:
    @ "We need more holidays - and more feasts!"
    ShowRoomDialog 470
    End
Room17V1Chain17:
    @ "Shove off, Potter!"
    ShowRoomDialog 475
    End
Room17V1Chain18:
    @ "Anyone got any Toothflossing Stringmints for after the Christmas feast?"
    ShowRoomDialog 472
    End
Room17V1Chain19:
    @ "Christmas or Halloween... I don't know which feast I like best."
    ShowRoomDialog 474
    End
Room17V1Chain20:
    @ "We don't speak to Gryffindors."
    ShowRoomDialog 476
    End
Room17V1Chain21:
    @ "I don't speak to Gryffindors."
    ShowRoomDialog 477
    End
Room17V1Chain22:
    @ "Hello."
    ShowRoomDialog 478
    End
Room17V1Chain23:
    @ "I wish I was still in bed."
    ShowRoomDialog 479
    End
Room17V1Chain24:
    @ "Zonko's is definitely the best shop in Hogsmeade."
    ShowRoomDialog 480
    End
Room17V1Chain25:
    @ "Really good to see you."
    ShowRoomDialog 481
    End
Room17V1Chain26:
    @ "Good evening, Sirius. How I hoped I would be the one to catch you¸"
    ShowRoomDialog 482
    End
    EndSubBlock Room17V1End

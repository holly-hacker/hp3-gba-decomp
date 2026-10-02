    .include "asm/room_blob.inc"

Room19Blob:
    RoomBlob 4
    PlayerEntry 623, 211, 0, 4
    PlayerEntry 340, 390, 1, 6
    PlayerEntry 1017, 512, 2, 0
    PlayerEntry 987, 202, 3, 6
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room19V0
    VariantEntry Room19V1

    SubBlock Room19V0, 1, Room19V0Routes, Room19V0Chains, Room19V0End
    OffsetTable Room19V0Groups, 1
    Offsets Room19V0Group0
    EndTable
    Group Room19V0Group0, 6
    Door 1067, 517, half_width=11, half_height=42, destination_room=34, exit_param=1
    Door 1009, 219, half_width=9, half_height=43, destination_room=34
    Chest 682, 616, flag_id=43, reward_id=131
    Chest 487, 201, flag_id=44, reward_id=80
    Door 411, 399, half_width=13, half_height=19, destination_room=30, exit_param=4
    DoorAlt 621, 165, half_width=20, half_height=19, destination_room=31, exit_param=2
    OffsetTable Room19V0Routes, 0
    EndTable
    OffsetTable Room19V0Chains, 1
    Offsets Room19V0Chain0
    EndTable
Room19V0Chain0:
    SetQuestState 2, QUEST_CASTLE_AREA
    SetDefeatWarpSelector 2 @ Hospital Wing
    End
    EndSubBlock Room19V0End

    SubBlock Room19V1, 1, Room19V1Routes, Room19V1Chains, Room19V1End
    OffsetTable Room19V1Groups, 19, 1
    Offsets Room19V1Group0, Room19V1Group1, Room19V1Group2, Room19V1Group3, Room19V1Group4, Room19V1Group5
    Offsets Room19V1Group6, Room19V1Group7, Room19V1Group8, Room19V1Group9, Room19V1Group10, Room19V1Group11
    Offsets Room19V1Group12, Room19V1Group13, Room19V1Group14, Room19V1Group15, Room19V1Group16, Room19V1Group17
    Offsets Room19V1Group18
    EndTable
    Group Room19V1Group0, 0
    Group Room19V1Group1, 7
    TriggerZone 840, 501, half_width=11, half_height=107, chain=Room19V1Chain1_id
    TriggerZone 410, 572, half_width=10, half_height=42, chain=Room19V1Chain4_id
    TriggerZone 813, 579, half_width=11, half_height=102, chain=Room19V1Chain1_id
    Prop 384, 473, kind=88
    Prop 767, 343, kind=89
    TriggerZone 417, 516, half_width=0, half_height=0
    TriggerZone 795, 387, half_width=0, half_height=0
    Group Room19V1Group2, 2
    Npc 324, 479, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain9_id
    Npc 915, 237, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain10_id
    Group Room19V1Group3, 2
    Npc 326, 239, sprite=51, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain11_id
    Npc 915, 521, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain12_id
    Group Room19V1Group4, 2
    Npc 325, 457, sprite=56, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain13_id
    Npc 916, 245, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain14_id
    Group Room19V1Group5, 2
    Npc 325, 299, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain15_id
    Npc 916, 520, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain16_id
    Group Room19V1Group6, 2
    Npc 300, 225, sprite=46, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain17_id
    Npc 760, 450, sprite=60, facing=0, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain18_id
    Group Room19V1Group7, 2
    Npc 760, 503, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain7_id
    Npc 415, 225, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain8_id
    Group Room19V1Group8, 3
    TriggerZone 603, 224, half_width=67, half_height=54, chain=Room19V1Chain21_id
    TriggerZone 460, 582, half_width=10, half_height=55, chain=Room19V1Chain22_id
    TriggerZone 340, 389, half_width=10, half_height=55, chain=Room19V1Chain41_id
    Group Room19V1Group9, 1
    Npc 265, 390, sprite=34, facing=2
    Group Room19V1Group10, 2
    Npc 325, 239, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain24_id
    Npc 920, 487, sprite=49, facing=2, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain25_id
    Group Room19V1Group11, 2
    Prop 490, 480, kind=84
    TriggerZone 512, 530, half_width=45, half_height=29, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room19V1Chain40_id
    Group Room19V1Group12, 2
    Npc 325, 242, sprite=45, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain27_id
    Npc 917, 531, sprite=50, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain28_id
    Group Room19V1Group13, 2
    Npc 325, 289, sprite=58, facing=6, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain29_id
    Npc 916, 399, sprite=50, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain28_id
    Group Room19V1Group14, 1
    Npc 325, 495, sprite=41, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain31_id
    Group Room19V1Group15, 2
    Npc 326, 298, sprite=59, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain32_id
    Npc 916, 235, sprite=46, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain33_id
    Group Room19V1Group16, 2
    Npc 325, 288, sprite=45, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain34_id
    Npc 916, 409, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain35_id
    Group Room19V1Group17, 2
    Npc 242, 483, sprite=33, facing=4
    Npc 242, 507, sprite=33, facing=4
    Group Room19V1Group18, 1
    Npc 890, 298, sprite=45, facing=0, interact_cooldown=3, interact_mode=1, chain=Room19V1Chain43_id
    OffsetTable Room19V1Routes, 9
    Offsets Room19V1Route0, Room19V1Route1, Room19V1Route2, Room19V1Route3, Room19V1Route4, Room19V1Route5
    Offsets Room19V1Route6, Room19V1Route7, Room19V1Route8
    EndTable
Room19V1Route0:
    Route 2
    Waypoint 792, 380
    Waypoint 805, 380, on_arrival_chain=Room19V1Chain2_id
Room19V1Route1:
    Route 2
    Waypoint 418, 510
    Waypoint 405, 510, on_arrival_chain=Room19V1Chain5_id
Room19V1Route2:
    Route 3
    Waypoint 780, 570
    Waypoint 520, 570
    Waypoint 520, 557, on_arrival_chain=Room19V1Chain3_id
Room19V1Route3:
    Route 3
    Waypoint 430, 570
    Waypoint 520, 570
    Waypoint 520, 557, on_arrival_chain=Room19V1Chain3_id
Room19V1Route4:
    Route 6
    Waypoint 325, 228
    Waypoint 325, 555
    Waypoint 760, 555
    Waypoint 760, 450
    Waypoint 890, 450
    Waypoint 890, 228
Room19V1Route5:
    Route 4
    Waypoint 300, 225
    Waypoint 915, 225
    Waypoint 915, 565
    Waypoint 300, 565
Room19V1Route6:
    Route 4
    Waypoint 550, 225
    Waypoint 310, 225
    Waypoint 310, 390
    Waypoint 290, 390, on_arrival_chain=Room19V1Chain23_id
Room19V1Route7:
    Route 4
    Waypoint 415, 575
    Waypoint 310, 575
    Waypoint 310, 390
    Waypoint 290, 390, on_arrival_chain=Room19V1Chain23_id
Room19V1Route8:
    Route 2
    Waypoint 331, 388
    Waypoint 290, 389, on_arrival_chain=Room19V1Chain23_id
    OffsetTable Room19V1Chains, 56, 1
    Offsets Room19V1Chain0, Room19V1Chain1, Room19V1Chain2, Room19V1Chain3, Room19V1Chain4, Room19V1Chain5
    Offsets Room19V1Chain6, Room19V1Chain7, Room19V1Chain8, Room19V1Chain9, Room19V1Chain10, Room19V1Chain11
    Offsets Room19V1Chain12, Room19V1Chain13, Room19V1Chain14, Room19V1Chain15, Room19V1Chain16, Room19V1Chain17
    Offsets Room19V1Chain18, Room19V1Chain19, Room19V1Chain20, Room19V1Chain21, Room19V1Chain22, Room19V1Chain23
    Offsets Room19V1Chain24, Room19V1Chain25, Room19V1Chain26, Room19V1Chain27, Room19V1Chain28, Room19V1Chain29
    Offsets Room19V1Chain30, Room19V1Chain31, Room19V1Chain32, Room19V1Chain33, Room19V1Chain34, Room19V1Chain35
    Offsets Room19V1Chain36, Room19V1Chain37, Room19V1Chain38, Room19V1Chain39, Room19V1Chain40, Room19V1Chain41
    Offsets Room19V1Chain42, Room19V1Chain43, Room19V1Chain44, Room19V1Chain45, Room19V1Chain46, Room19V1Chain47
    Offsets Room19V1Chain48, Room19V1Chain49, Room19V1Chain50, Room19V1Chain51, Room19V1Chain52, Room19V1Chain53
    Offsets Room19V1Chain54, Room19V1Chain55
    EndTable
Room19V1Chain0:
    GotoIfStoryStageCompare 0, 0, Room19V1Chain44_id, 0, Room19V1Group7_id, 0
    GotoIfStoryStageCompare 0, 1, Room19V1Chain45_id, 0, Room19V1Group2_id, 0
    GotoIfStoryStageCompare 0, 2, Room19V1Chain46_id, 0, Room19V1Group3_id, 0
    GotoIfStoryStageCompare 0, 4, Room19V1Chain47_id, 0, Room19V1Group4_id, 0
    GotoIfStoryStageCompare 0, 5, Room19V1Chain48_id, 0, Room19V1Group5_id, 0
    GotoIfStoryStageCompare 0, 6, Room19V1Chain6_id, 0, Room19V1Group18_id, 0
    GotoIfStoryStageCompare 0, 7, Room19V1Chain26_id, 0, Room19V1Group10_id, 0
    GotoIfStoryStageCompare 0, 8, Room19V1Chain19_id, 0, Room19V1Group6_id, 0
    GotoIfStoryStageCompare 0, 15, Room19V1Chain20_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 15, Room19V1Chain50_id, 0, Room19V1Group12_id, 0
    GotoIfStoryStageCompare 0, 16, Room19V1Chain51_id, 0, Room19V1Group13_id, 0
    GotoIfStoryStageCompare 0, 17, Room19V1Chain52_id, 0, Room19V1Group14_id, 0
    GotoIfStoryStageCompare 0, 18, Room19V1Chain52_id, 0, Room19V1Group14_id, 0
    GotoIfStoryStageCompare 0, 20, Room19V1Chain53_id, 0, Room19V1Group15_id, 0
    GotoIfStoryStageCompare 0, 21, Room19V1Chain54_id, 0, Room19V1Group16_id, 0
    End
Room19V1Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnTileObject Room19V1Group1_id, 0
    DespawnTileObject Room19V1Group1_id, 2
    DespawnTileObject Room19V1Group1_id, 1
    QueueTileObjectMove Room19V1Group1_id, 6, 0, 0, 1200, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "The lady is found!"
    ShowRoomDialog 390
    DelayedRespawnRowAndRunChain 1, 0, 0
    InvokeChainIfEnabled 0, Room19V1Chain2_id
    End
Room19V1Chain2:
    ArmChainYield 1
    QueueTileObjectMove 0, 255, 0, 0, 1800, 0
    DespawnRoomRowObjects Room19V1Group1_id
    Unk02 0, 255, 2
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room19V1Route2_id, 0, 1, 0, 0, 0
    End
Room19V1Chain3:
    ArmChainYield 1
    @ "Hello, are you all right?"
    @ "Oh, it was horrible... horrible!"
    @ "What happened?"
    @ "He's got a dreadful temper!"
    @ "Who? Who has?"
    @ "Sirius Black!"
    @ "We have to warn Harry!"
    @ "Come on, then - back to the common room!"
    ShowRoomDialog 391
    SetQuestState 2, 249
    Unk02 0, 255, 1
    SetQuestState QUEST_OBJ_GO_TO_COMMON_ROOM_AFTER_POTIONS, QUEST_OBJECTIVE_INDEX
    SetQuestState 2, 245
    SetTileObjectFacing 0, 255, 0
    GrantPartyExperience 10, 65535
    DelayedRespawnRowAndRunChain 2, 0, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room19V1Chain4:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnTileObject Room19V1Group1_id, 0
    DespawnTileObject Room19V1Group1_id, 2
    DespawnTileObject Room19V1Group1_id, 1
    QueueTileObjectMove Room19V1Group1_id, 5, 0, 0, 1200, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "The lady is found!"
    ShowRoomDialog 390
    DelayedRespawnRowAndRunChain 1, 0, 0
    InvokeChainIfEnabled 0, Room19V1Chain5_id
    End
Room19V1Chain5:
    ArmChainYield 1
    QueueTileObjectMove 0, 255, 0, 0, 1800, 0
    DespawnRoomRowObjects Room19V1Group1_id
    Unk02 0, 255, 2
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room19V1Route3_id, 0, 1, 0, 0, 0
    End
Room19V1Chain6:
    GotoIfQuestStateCompare 249, 3, 1, Room19V1Chain42_id, Room19V1Chain55_id, Room19V1Group11_id, 0
    End
Room19V1Chain7:
    @ "The Gryffindor common room is on the seventh floor. Just like last year."
    ShowRoomDialog 187
    End
Room19V1Chain8:
    @ "I wonder who the new Defense Against the Dark Arts teacher will be this year¸"
    ShowRoomDialog 191
    End
Room19V1Chain9:
    @ "Transfiguration class is held on the first floor."
    ShowRoomDialog 212
    End
Room19V1Chain10:
    @ "I can't find the Transfiguration classroom. I heard it was on the first floor¸"
    ShowRoomDialog 213
    End
Room19V1Chain11:
    @ "This would be a nice day to have a class outside."
    ShowRoomDialog 237
    End
Room19V1Chain12:
    @ "Hagrid's a natural to teach Care of Magical Creatures - don't you think?"
    ShowRoomDialog 239
    End
Room19V1Chain13:
    @ "I much prefer Potions to Transfiguration."
    ShowRoomDialog 325
    End
Room19V1Chain14:
    @ "Shouldn't you be on your way to the Potions classroom? It's in the dungeons - off the Entrance Hall."
    ShowRoomDialog 326
    End
Room19V1Chain15:
    @ "The staff room's next to the Entrance Hall. I don't think we are allowed in there though¸"
    ShowRoomDialog 329
    End
Room19V1Chain16:
    @ "Why do you want to go to the staff room? Isn't it for teachers only?"
    ShowRoomDialog 330
    End
Room19V1Chain17:
    @ "I hope I can get to Madam Pince before everyone else does. She's on the second floor."
    ShowRoomDialog 632
    End
Room19V1Chain18:
    @ "The library's quite large - and it's got upper and lower levels..."
    ShowRoomDialog 631
    End
Room19V1Chain19:
    StartObjectAnimSequence Room19V1Group6_id, 0, 0, 0, Room19V1Route5_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group6_id, 1, 0, 0, Room19V1Route4_id, 3, 0, 0, 0, 0
    End
Room19V1Chain20:
    GotoIfQuestStateCompare 230, 0, 1, 0, 0, Room19V1Group8_id, 0
    End
Room19V1Chain21:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room19V1Group9_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room19V1Route6_id, 0, 1, 0, 0, 0
    End
Room19V1Chain22:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room19V1Group9_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room19V1Route7_id, 0, 1, 0, 0, 0
    End
Room19V1Chain23:
    ArmChainYield 1
    DespawnRoomRowObjects Room19V1Group8_id
    @ "Did you find out anything?"
    @ "Nothing very positive, I'm afraid."
    @ "Oh, poor Hagrid - and poor Buckbeak. Let's go back to the common room."
    ShowRoomDialog 445
    @ "We should be on our way to the Christmas feast in the Great Hall."
    @ "Absolutely, Harry! I'm starving!"
    @ "I'll see you there. I have - something important to do..."
    ShowRoomDialog 459
    SetQuestState 2, 230
    SetQuestState QUEST_OBJ_GO_TO_GREAT_HALL, QUEST_OBJECTIVE_INDEX
    SetStoryStage 16
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room19V1Chain24:
    @ "The Defense Against the Dark Arts class is on the third floor."
    ShowRoomDialog 327
    End
Room19V1Chain25:
    @ "The Defense Against the Dark Arts classroom's on the third floor."
    ShowRoomDialog 333
    End
Room19V1Chain26:
    StartObjectAnimSequence Room19V1Group10_id, 0, 0, 0, Room19V1Route4_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group10_id, 1, 0, 0, Room19V1Route5_id, 2, 0, 0, 0, 0
    End
Room19V1Chain27:
    @ "I heard somebody got a Firebolt for Christmas!"
    ShowRoomDialog 448
    End
Room19V1Chain28:
    @ "I'd really like to see a Firebolt close up."
    ShowRoomDialog 449
    End
Room19V1Chain29:
    @ "I hope there are crackers at the Christmas feast."
    ShowRoomDialog 468
    End
Room19V1Chain30:
    @ "Great! It's time for the Christmas feast!"
    ShowRoomDialog 469
    End
Room19V1Chain31:
    @ "Zonko's is definitely the best shop in Hogsmeade."
    ShowRoomDialog 514
    End
Room19V1Chain32:
    @ "I'm really glad Gryffindor beat Slytherin."
    ShowRoomDialog 512
    End
Room19V1Chain33:
    @ "I heard that Sirius Black was seen in Gryffindor Tower!"
    ShowRoomDialog 516
    End
Room19V1Chain34:
    @ "Is it true about Buckbeak?"
    ShowRoomDialog 535
    End
Room19V1Chain35:
    @ "Poor Hagrid! He loves that Hippogriff."
    ShowRoomDialog 536
    End
Room19V1Chain36:
    @ "Locked."
    ShowRoomDialog 624
    End
Room19V1Chain37:
    @ "Madam Pomfrey's the Hogwarts nurse. She's on the fourth floor if you ever feel ill¸"
    ShowRoomDialog 634
    End
Room19V1Chain38:
    @ "Fred and George sell all sorts of useful items in their shop on the seventh floor."
    ShowRoomDialog 628
    End
Room19V1Chain39:
    @ "I hate having to walk up and down the stairs all the time. I just use the portrait shortcuts to get me around Hogwarts."
    ShowRoomDialog 641
    End
Room19V1Chain40:
    @ "I think you should return to your common room - it's not safe."
    ShowRoomDialog 392
    End
Room19V1Chain41:
    RespawnRowAndRunChain Room19V1Group9_id, 0
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room19V1Route8_id, 0, 1, 0, 0, 0
    End
Room19V1Chain42:
    GotoIfQuestStateCompare 249, 0, 1, Room19V1Chain49_id, 0, Room19V1Group1_id, 0
    End
Room19V1Chain43:
    @ "It's come to something when even a portrait's not safe around here..."
    ShowRoomDialog 372
    End
Room19V1Chain44:
    StartObjectAnimSequence Room19V1Group7_id, 0, 0, 0, Room19V1Route4_id, 3, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group7_id, 1, 0, 0, Room19V1Route5_id, 1, 0, 0, 0, 0
    End
Room19V1Chain45:
    StartObjectAnimSequence Room19V1Group2_id, 0, 0, 0, Room19V1Route4_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group2_id, 1, 0, 0, Room19V1Route5_id, 2, 0, 0, 0, 0
    End
Room19V1Chain46:
    StartObjectAnimSequence Room19V1Group3_id, 0, 0, 0, Room19V1Route4_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group3_id, 1, 0, 0, Room19V1Route5_id, 2, 0, 0, 0, 0
    End
Room19V1Chain47:
    StartObjectAnimSequence Room19V1Group4_id, 0, 0, 0, Room19V1Route4_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group4_id, 1, 0, 0, Room19V1Route5_id, 2, 0, 0, 0, 0
    End
Room19V1Chain48:
    StartObjectAnimSequence Room19V1Group5_id, 0, 0, 0, Room19V1Route4_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group5_id, 1, 0, 0, Room19V1Route5_id, 2, 0, 0, 0, 0
    End
Room19V1Chain49:
    StartObjectAnimSequence Room19V1Group18_id, 0, 0, 0, Room19V1Route4_id, 5, 0, 0, 0, 0
    End
Room19V1Chain50:
    StartObjectAnimSequence Room19V1Group12_id, 0, 0, 0, Room19V1Route4_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group12_id, 1, 0, 0, Room19V1Route5_id, 2, 0, 0, 0, 0
    End
Room19V1Chain51:
    StartObjectAnimSequence Room19V1Group13_id, 0, 0, 0, Room19V1Route4_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group13_id, 1, 0, 0, Room19V1Route5_id, 2, 0, 0, 0, 0
    End
Room19V1Chain52:
    StartObjectAnimSequence Room19V1Group14_id, 0, 0, 0, Room19V1Route4_id, 1, 0, 0, 0, 0
    End
Room19V1Chain53:
    StartObjectAnimSequence Room19V1Group15_id, 0, 0, 0, Room19V1Route4_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group15_id, 1, 0, 0, Room19V1Route5_id, 2, 0, 0, 0, 0
    End
Room19V1Chain54:
    StartObjectAnimSequence Room19V1Group16_id, 0, 0, 0, Room19V1Route4_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room19V1Group16_id, 1, 0, 0, Room19V1Route5_id, 2, 0, 0, 0, 0
    End
Room19V1Chain55:
    DespawnRoomRowObjects Room19V1Group18_id
    End
    EndSubBlock Room19V1End

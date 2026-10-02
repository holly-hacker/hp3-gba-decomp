    .include "asm/room_blob.inc"

Room16Blob:
    RoomBlob 7
    PlayerEntry 321, 749, 0, 0
    PlayerEntry 565, 183, 1, 0
    PlayerEntry 177, 324, 2, 0
    PlayerEntry 80, 182, 3, 0
    PlayerEntry 119, 397, 4, 0
    PlayerEntry 521, 398, 5, 0
    PlayerEntry 528, 614, 6, 0
    StageIndex 3
    StageToVariantAll 1
    VariantEntry Room16V0
    VariantEntry Room16V1
    VariantEntry Room16V2

    SubBlock Room16V0, 1, Room16V0Routes, Room16V0Chains, Room16V0End
    OffsetTable Room16V0Groups, 1
    Offsets Room16V0Group0
    EndTable
    Group Room16V0Group0, 9
    Door 319, 816, half_width=68, half_height=11, destination_room=8
    TriggerZone 256, 114, half_width=0, half_height=0
    Door 585, 170, half_width=12, half_height=40, destination_room=30
    Door 51, 173, half_width=10, half_height=38, destination_room=3
    Door 82, 399, half_width=13, half_height=24, destination_room=27
    Door 178, 290, half_width=25, half_height=9, destination_room=18, exit_param=1
    Door 549, 395, half_width=10, half_height=28, destination_room=31, exit_param=1
    Door 558, 619, half_width=11, half_height=44, destination_room=17, exit_param=1
    Chest 515, 326, flag_id=14, reward_id=118
    OffsetTable Room16V0Routes, 0
    EndTable
    OffsetTable Room16V0Chains, 1
    Offsets Room16V0Chain0
    EndTable
Room16V0Chain0:
    SetQuestState 1, QUEST_CASTLE_AREA
    SetBattleDefeatState 2
    End
    EndSubBlock Room16V0End

    SubBlock Room16V1, 1, Room16V1Routes, Room16V1Chains, Room16V1End
    OffsetTable Room16V1Groups, 17, 1
    Offsets Room16V1Group0, Room16V1Group1, Room16V1Group2, Room16V1Group3, Room16V1Group4, Room16V1Group5
    Offsets Room16V1Group6, Room16V1Group7, Room16V1Group8, Room16V1Group9, Room16V1Group10, Room16V1Group11
    Offsets Room16V1Group12, Room16V1Group13, Room16V1Group14, Room16V1Group15, Room16V1Group16
    EndTable
    Group Room16V1Group0, 2
    TriggerZone 456, 286, half_width=23, half_height=9, rearm_delay=2, trigger_kind=1, require_a_press=1, chain=Room16V1Chain73_id
    TriggerZone 79, 607, half_width=14, half_height=28, rearm_delay=2, trigger_kind=1, require_a_press=1, chain=Room16V1Chain73_id
    Group Room16V1Group1, 5
    Npc 193, 590, sprite=28, facing=2
    Npc 184, 603, sprite=22, facing=2, interact_mode=1
    Npc 183, 572, sprite=23, facing=2, interact_mode=1
    TriggerZone 215, 692, half_width=127, half_height=10, chain=Room16V1Chain1_id
    TriggerZone 430, 670, half_width=126, half_height=10, chain=Room16V1Chain1_id
    Group Room16V1Group2, 6
    Npc 262, 817, sprite=39, facing=0
    Npc 331, 817, sprite=43, facing=0
    Npc 375, 817, sprite=47, facing=0
    Npc 288, 818, sprite=51, facing=0
    Npc 400, 817, sprite=55, facing=0
    Npc 420, 817, sprite=59, facing=0
    Group Room16V1Group3, 4
    Npc 387, 483, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain8_id, arg_0f=0
    Npc 372, 152, sprite=55, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain9_id, arg_0f=0
    Npc 290, 452, sprite=62, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain58_id
    Npc 320, 217, sprite=29, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain53_id, arg_0f=0
    Group Room16V1Group4, 2
    Npc 340, 340, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain10_id
    Npc 300, 580, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain11_id
    Group Room16V1Group5, 3
    Npc 340, 360, sprite=51, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain12_id
    Npc 300, 580, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain13_id
    TriggerZone 320, 810, half_width=77, half_height=16, chain=Room16V1Chain88_id
    Group Room16V1Group6, 4
    Npc 340, 340, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain14_id
    Npc 300, 500, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain15_id
    Npc 280, 280, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain16_id
    Npc 440, 582, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain17_id
    Group Room16V1Group7, 4
    Npc 340, 370, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain18_id
    Npc 300, 470, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain19_id
    Npc 280, 250, sprite=57, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain20_id
    Npc 460, 582, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain21_id
    Group Room16V1Group8, 4
    Npc 340, 180, sprite=39, facing=2, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain23_id
    Npc 280, 190, sprite=57, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain24_id
    Npc 356, 582, sprite=60, facing=0, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain25_id
    Npc 300, 580, sprite=46, facing=2, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain26_id
    Group Room16V1Group9, 4
    Npc 280, 189, sprite=58, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain59_id
    Npc 340, 180, sprite=39, facing=2, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain28_id
    Npc 301, 581, sprite=39, facing=2, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain60_id
    Npc 355, 582, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain29_id
    Group Room16V1Group10, 5
    Npc 340, 470, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain47_id
    Npc 300, 470, sprite=61, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain48_id
    Npc 280, 300, sprite=58, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain49_id
    Npc 480, 582, sprite=43, facing=2, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain50_id
    TriggerZone 320, 810, half_width=71, half_height=16, chain=Room16V1Chain74_id
    Group Room16V1Group11, 3
    Npc 340, 240, sprite=47, facing=2, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain35_id
    Npc 300, 410, sprite=46, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain36_id
    Npc 475, 582, sprite=50, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain38_id
    Group Room16V1Group12, 4
    Npc 340, 280, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain39_id
    Npc 300, 450, sprite=55, facing=0, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain40_id
    Npc 280, 370, sprite=41, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain41_id
    Npc 460, 582, sprite=50, facing=6, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain42_id
    Group Room16V1Group13, 2
    Npc 340, 380, sprite=59, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain43_id
    Npc 280, 230, sprite=49, facing=2, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain45_id
    Group Room16V1Group14, 4
    Npc 340, 385, sprite=59, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain31_id
    Npc 300, 525, sprite=45, facing=6, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain32_id
    Npc 280, 240, sprite=50, facing=4, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain33_id
    Npc 419, 582, sprite=52, facing=2, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain34_id
    Group Room16V1Group15, 2
    Npc 320, 625, sprite=32, facing=0, arg_0f=0
    Npc 320, 663, sprite=34, facing=0, arg_0f=0
    Group Room16V1Group16, 2
    Npc 300, 300, sprite=55, facing=0, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain77_id
    Npc 340, 430, sprite=45, facing=0, interact_cooldown=3, interact_mode=1, chain=Room16V1Chain76_id
    OffsetTable Room16V1Routes, 17
    Offsets Room16V1Route0, Room16V1Route1, Room16V1Route2, Room16V1Route3, Room16V1Route4, Room16V1Route5
    Offsets Room16V1Route6, Room16V1Route7, Room16V1Route8, Room16V1Route9, Room16V1Route10, Room16V1Route11
    Offsets Room16V1Route12, Room16V1Route13, Room16V1Route14, Room16V1Route15, Room16V1Route16
    EndTable
Room16V1Route0:
    Route 5
    Waypoint 275, 817
    Waypoint 275, 575
    Waypoint 275, 145
    Waypoint 645, 145
    Waypoint 640, 817
Room16V1Route1:
    Route 4
    Waypoint 360, 817
    Waypoint 360, 147
    Waypoint 648, 147
    Waypoint 648, 817
Room16V1Route2:
    Route 5
    Waypoint 344, 817
    Waypoint 344, 740
    Waypoint 344, 145
    Waypoint 650, 145
    Waypoint 650, 817
Room16V1Route3:
    Route 3
    Waypoint 294, 590
    Waypoint 180, 590
    Waypoint 180, 296, on_arrival_chain=Room16V1Chain2_id
Room16V1Route4:
    Route 3
    Waypoint 284, 572
    Waypoint 190, 570
    Waypoint 190, 296, on_arrival_chain=Room16V1Chain4_id
Room16V1Route5:
    Route 3
    Waypoint 282, 603
    Waypoint 170, 603
    Waypoint 170, 296, on_arrival_chain=Room16V1Chain3_id
Room16V1Route6:
    Route 2
    Waypoint 193, 590
    Waypoint 294, 589
Room16V1Route7:
    Route 2
    Waypoint 183, 572
    Waypoint 284, 572, on_arrival_chain=Room16V1Chain5_id
Room16V1Route8:
    Route 2
    Waypoint 184, 603
    Waypoint 283, 603
Room16V1Route9:
    Route 2
    Waypoint 320, 668, on_arrival_chain=Room16V1Chain64_id
    Waypoint 320, 590, on_arrival_chain=Room16V1Chain6_id
Room16V1Route10:
    Route 8
    Waypoint 340, 147
    Waypoint 660, 147
    Waypoint 660, 138
    Waypoint -20, 138
    Waypoint -20, 150
    Waypoint 280, 150
    Waypoint 280, 850
    Waypoint 340, 850
Room16V1Route11:
    Route 8
    Waypoint 355, 145
    Waypoint 665, 145
    Waypoint 665, 140
    Waypoint 300, 140
    Waypoint 300, 586
    Waypoint 650, 586
    Waypoint 650, 584
    Waypoint 355, 584
Room16V1Route12:
    Route 2
    Waypoint 320, 615
    Waypoint 320, 564, on_arrival_chain=Room16V1Chain61_id
Room16V1Route13:
    Route 1
    Waypoint 320, 615
Room16V1Route14:
    Route 1
    Waypoint 320, 590
Room16V1Route15:
    Route 1
    Waypoint 320, 590, on_arrival_chain=Room16V1Chain62_id
Room16V1Route16:
    Route 2
    Waypoint 320, 590
    Waypoint 320, 530, on_arrival_chain=Room16V1Chain72_id
    OffsetTable Room16V1Chains, 90, 1
    Offsets Room16V1Chain0, Room16V1Chain1, Room16V1Chain2, Room16V1Chain3, Room16V1Chain4, Room16V1Chain5
    Offsets Room16V1Chain6, Room16V1Chain7, Room16V1Chain8, Room16V1Chain9, Room16V1Chain10, Room16V1Chain11
    Offsets Room16V1Chain12, Room16V1Chain13, Room16V1Chain14, Room16V1Chain15, Room16V1Chain16, Room16V1Chain17
    Offsets Room16V1Chain18, Room16V1Chain19, Room16V1Chain20, Room16V1Chain21, Room16V1Chain22, Room16V1Chain23
    Offsets Room16V1Chain24, Room16V1Chain25, Room16V1Chain26, Room16V1Chain27, Room16V1Chain28, Room16V1Chain29
    Offsets Room16V1Chain30, Room16V1Chain31, Room16V1Chain32, Room16V1Chain33, Room16V1Chain34, Room16V1Chain35
    Offsets Room16V1Chain36, Room16V1Chain37, Room16V1Chain38, Room16V1Chain39, Room16V1Chain40, Room16V1Chain41
    Offsets Room16V1Chain42, Room16V1Chain43, Room16V1Chain44, Room16V1Chain45, Room16V1Chain46, Room16V1Chain47
    Offsets Room16V1Chain48, Room16V1Chain49, Room16V1Chain50, Room16V1Chain51, Room16V1Chain52, Room16V1Chain53
    Offsets Room16V1Chain54, Room16V1Chain55, Room16V1Chain56, Room16V1Chain57, Room16V1Chain58, Room16V1Chain59
    Offsets Room16V1Chain60, Room16V1Chain61, Room16V1Chain62, Room16V1Chain63, Room16V1Chain64, Room16V1Chain65
    Offsets Room16V1Chain66, Room16V1Chain67, Room16V1Chain68, Room16V1Chain69, Room16V1Chain70, Room16V1Chain71
    Offsets Room16V1Chain72, Room16V1Chain73, Room16V1Chain74, Room16V1Chain75, Room16V1Chain76, Room16V1Chain77
    Offsets Room16V1Chain78, Room16V1Chain79, Room16V1Chain80, Room16V1Chain81, Room16V1Chain82, Room16V1Chain83
    Offsets Room16V1Chain84, Room16V1Chain85, Room16V1Chain86, Room16V1Chain87, Room16V1Chain88, Room16V1Chain89
    EndTable
Room16V1Chain0:
    GotoIfStoryStageCompare 0, 0, Room16V1Chain22_id, 0, Room16V1Group3_id, 0
    GotoIfStoryStageCompare 0, 1, Room16V1Chain78_id, 0, Room16V1Group4_id, 0
    GotoIfStoryStageCompare 0, 2, Room16V1Chain79_id, 0, Room16V1Group5_id, 0
    GotoIfStoryStageCompare 0, 4, Room16V1Chain80_id, 0, Room16V1Group6_id, 0
    GotoIfStoryStageCompare 0, 5, Room16V1Chain81_id, 0, Room16V1Group7_id, 0
    GotoIfStoryStageCompare 0, 6, Room16V1Chain74_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 6, Room16V1Chain89_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room16V1Chain30_id, 0, Room16V1Group9_id, 0
    GotoIfStoryStageCompare 0, 8, Room16V1Chain27_id, 0, Room16V1Group8_id, 0
    GotoIfStoryStageCompare 0, 15, Room16V1Chain83_id, 0, Room16V1Group14_id, 0
    GotoIfStoryStageCompare 0, 16, Room16V1Chain84_id, 0, Room16V1Group11_id, 0
    GotoIfStoryStageCompare 0, 17, Room16V1Chain74_id, 0, Room16V1Group12_id, 0
    GotoIfStoryStageCompare 0, 18, Room16V1Chain74_id, 0, Room16V1Group12_id, 0
    GotoIfStoryStageCompare 0, 20, Room16V1Chain86_id, 0, Room16V1Group13_id, 0
    GotoIfStoryStageCompare 0, 21, Room16V1Chain87_id, 0, Room16V1Group10_id, 0
    GotoIfStoryStageCompare 3, 24, Room16V1Chain75_id, 0, 0, 0
    End
Room16V1Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ResetPartyLeaderSelection
    SetQuestState 2, 224
    DespawnTileObject Room16V1Group1_id, 3
    DespawnTileObject Room16V1Group1_id, 4
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room16V1Route9_id, 0, 1, 0, 0, 0
    End
Room16V1Chain2:
    DespawnTileObject Room16V1Group1_id, 0
    End
Room16V1Chain3:
    DespawnTileObject Room16V1Group1_id, 1
    End
Room16V1Chain4:
    DespawnTileObject Room16V1Group1_id, 2
    End
Room16V1Chain5:
    ArmChainYield 1
    RespawnRowAndRunChain Room16V1Group15_id, 0
    RemovePartyFollower 7
    RemovePartyFollower 6
    ArmChainYield 0
    StartObjectAnimSequence Room16V1Group15_id, 1, 0, 0, Room16V1Route13_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room16V1Group15_id, 0, 0, 0, Room16V1Route12_id, 0, 1, 0, 0, 0
    End
Room16V1Chain6:
    SetTileObjectFacing 0, 255, 6
    End
Room16V1Chain7:
    Unk2A 5, 255, 255, 255
    SetQuestState 1, 224
    RecruitPartyFollower 7
    RecruitPartyFollower 6
    SetQuestState QUEST_OBJ_FIND_COMMON_ROOM, QUEST_OBJECTIVE_INDEX
    End
Room16V1Chain8:
    @ "The Gryffindor common room is on the seventh floor. Just like last year."
    ShowRoomDialog 187
    End
Room16V1Chain9:
    @ "I just got sorted into Gryffindor. I think the common room is on the seventh floor¸"
    ShowRoomDialog 194
    End
Room16V1Chain10:
    @ "Transfiguration class is held on the first floor."
    ShowRoomDialog 212
    End
Room16V1Chain11:
    @ "I can't find the Transfiguration classroom. I heard it was on the first floor¸"
    ShowRoomDialog 213
    End
Room16V1Chain12:
    @ "This would be a nice day to have a class outside."
    ShowRoomDialog 237
    End
Room16V1Chain13:
    @ "What's going on in Hagrid's garden?"
    ShowRoomDialog 257
    End
Room16V1Chain14:
    @ "Potions class is in the dungeons off the Entrance Hall."
    ShowRoomDialog 321
    End
Room16V1Chain15:
    @ "I hate having to go into the dungeons to get to Potions."
    ShowRoomDialog 322
    End
Room16V1Chain16:
    @ "It's Potions next - down in the dungeons."
    ShowRoomDialog 323
    End
Room16V1Chain17:
    @ "Potions? It's held down in the dungeons."
    ShowRoomDialog 324
    End
Room16V1Chain18:
    @ "Defense Against the Dark Arts class is on the third floor. I heard it might be taking place in the staff room today, though."
    ShowRoomDialog 328
    End
Room16V1Chain19:
    @ "The staff room's next to the Entrance Hall. I don't think we are allowed in there though¸"
    ShowRoomDialog 329
    End
Room16V1Chain20:
    @ "The staff room's next to the Entrance Hall."
    ShowRoomDialog 331
    End
Room16V1Chain21:
    @ "Why do you want to go to the staff room? Isn't it for teachers only?"
    ShowRoomDialog 330
    End
Room16V1Chain22:
    GotoIfQuestStateCompare 224, 5, 1, Room16V1Chain63_id, 0, Room16V1Group1_id, 0
    End
Room16V1Chain23:
    @ "The library? You'll need to go to the second floor."
    ShowRoomDialog 626
    End
Room16V1Chain24:
    @ "Madam Pince's desk is in the library."
    ShowRoomDialog 627
    End
Room16V1Chain25:
    @ "The library's quite large - and it's got upper and lower levels..."
    ShowRoomDialog 631
    End
Room16V1Chain26:
    @ "I hope I can get to Madam Pince before everyone else does. She's on the second floor."
    ShowRoomDialog 632
    End
Room16V1Chain27:
    StartObjectAnimSequence Room16V1Group8_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group8_id, 1, 0, 0, Room16V1Route10_id, 5, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group8_id, 2, 0, 0, Room16V1Route11_id, 7, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group8_id, 3, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    End
Room16V1Chain28:
    @ "The Defense Against the Dark Arts class is on the third floor."
    ShowRoomDialog 327
    End
Room16V1Chain29:
    @ "The Defense Against the Dark Arts classroom's on the third floor."
    ShowRoomDialog 333
    End
Room16V1Chain30:
    StartObjectAnimSequence Room16V1Group9_id, 0, 0, 0, Room16V1Route10_id, 5, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group9_id, 1, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group9_id, 2, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group9_id, 3, 0, 0, Room16V1Route11_id, 7, 0, 0, 0, 0
    End
Room16V1Chain31:
    @ "Is it true about the Firebolt?"
    ShowRoomDialog 447
    End
Room16V1Chain32:
    @ "I heard somebody got a Firebolt for Christmas!"
    ShowRoomDialog 448
    End
Room16V1Chain33:
    @ "I'd really like to see a Firebolt close up."
    ShowRoomDialog 449
    End
Room16V1Chain34:
    @ "I'd love a new broom for Christmas. I still have my sister's old one!"
    ShowRoomDialog 450
    End
Room16V1Chain35:
    @ "I've heard we'll be playing a game at this year's Christmas feast."
    ShowRoomDialog 471
    End
Room16V1Chain36:
    @ "Anyone got any Toothflossing Stringmints for after the Christmas feast?"
    ShowRoomDialog 472
    End
Room16V1Chain37:
    @ "I don't want to be late for the Christmas feast!"
    ShowRoomDialog 473
    End
Room16V1Chain38:
    @ "Christmas or Halloween... I don't know which feast I like best."
    ShowRoomDialog 474
    End
Room16V1Chain39:
    @ "I'm still stuffed from the Christmas feast!"
    ShowRoomDialog 511
    End
Room16V1Chain40:
    @ "When's the next feast going to be, anyway?"
    ShowRoomDialog 515
    End
Room16V1Chain41:
    @ "We need more holidays - and more feasts!"
    ShowRoomDialog 470
    End
Room16V1Chain42:
    @ "Christmas or Halloween... I don't know which feast I like best."
    ShowRoomDialog 474
    End
Room16V1Chain43:
    @ "I'm really glad Gryffindor beat Slytherin."
    ShowRoomDialog 512
    End
Room16V1Chain44:
    @ "I heard that Sirius Black was seen in Gryffindor Tower!"
    ShowRoomDialog 516
    End
Room16V1Chain45:
    @ "Is it true Sirius Black tried to stab Ron Weasley?"
    ShowRoomDialog 517
    End
Room16V1Chain46:
    @ "Security's really been stepped up, hasn't it?"
    ShowRoomDialog 518
    End
Room16V1Chain47:
    @ "I've heard they're going to execute Buckbeak!"
    ShowRoomDialog 534
    End
Room16V1Chain48:
    @ "Personally, I'm against the execution of magical creatures."
    ShowRoomDialog 538
    End
Room16V1Chain49:
    @ "It's a real shame about Buckbeak."
    ShowRoomDialog 539
    End
Room16V1Chain50:
    @ "It's all Malfoy's fault!"
    ShowRoomDialog 541
    End
Room16V1Chain51:
    @ "Locked."
    ShowRoomDialog 624
    End
Room16V1Chain52:
    @ "Did you know that Fred and George sell items that you usually can't get in Hogwarts? Their shop's on the seventh floor."
    ShowRoomDialog 629
    End
Room16V1Chain53:
    @ "Did you know that you can visit our shop on the seventh floor? You can buy items from George and me at very reasonable prices..."
    ShowRoomDialog 638
    End
Room16V1Chain54:
    @ "Have you visited Madam Pomfrey in the hospital wing on the fourth floor?"
    ShowRoomDialog 636
    End
Room16V1Chain55:
    @ "The hospital wing is on the fourth floor."
    ShowRoomDialog 637
    End
Room16V1Chain56:
    @ "There are portraits on the different floors that will help you get around Hogwarts more quickly."
    ShowRoomDialog 643
    End
Room16V1Chain57:
    @ "When I'm running late for class, I use the portrait shortcuts to get where I'm going faster."
    ShowRoomDialog 644
    End
Room16V1Chain58:
    @ "The Grand Staircase is up those stairs and to your right..."
    ShowRoomDialog 193
    End
Room16V1Chain59:
    @ "I know the hospital wing's on the fourth floor - I just can't remember the name of the nurse..."
    ShowRoomDialog 635
    End
Room16V1Chain60:
    @ "I heard a rumor that Fred and George Weasley have a shop on the seventh floor."
    ShowRoomDialog 625
    End
Room16V1Chain61:
    ArmChainYield 1
    SetTileObjectFacing Room16V1Group15_id, 0, 6
    SetTileObjectFacing Room16V1Group15_id, 1, 6
    @ "Hey, Potter, better watch out, the Dementors are coming!"
    @ "Shove off, Malfoy."
    @ "Leave him, Ron, he's not worth it. Let's get to the Gryffindor common room."
    ShowRoomDialog 183
    ArmChainYield 0
    StartObjectAnimSequence Room16V1Group15_id, 0, 0, 0, Room16V1Route15_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room16V1Group15_id, 1, 0, 0, Room16V1Route14_id, 0, 1, 0, 0, 0
    End
Room16V1Chain62:
    ArmChainYield 1
    DespawnRoomRowObjects Room16V1Group15_id
    RecruitPartyFollower 6
    RecruitPartyFollower 7
    SetQuestState 2, 224
    RespawnRowAndRunChain Room16V1Group2_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room16V1Route16_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room16V1Group1_id, 0, 0, 0, Room16V1Route3_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room16V1Group1_id, 2, 0, 0, Room16V1Route4_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room16V1Group1_id, 1, 0, 0, Room16V1Route5_id, 0, 1, 0, 0, 0
    End
Room16V1Chain63:
    GotoIfQuestStateCompare 224, 0, 0, Room16V1Chain7_id, 0, 0, 0
    End
Room16V1Chain64:
    ArmChainYield 1
    ArmChainYield 0
    StartObjectAnimSequence Room16V1Group1_id, 0, 0, 0, Room16V1Route6_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room16V1Group1_id, 2, 0, 0, Room16V1Route7_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room16V1Group1_id, 1, 0, 0, Room16V1Route8_id, 0, 1, 0, 0, 0
    End
Room16V1Chain65:
    StartObjectAnimSequence Room16V1Group2_id, 0, 0, 0, Room16V1Route0_id, 0, 0, 0, 0, 0
    End
Room16V1Chain66:
    StartObjectAnimSequence Room16V1Group2_id, 1, 0, 0, Room16V1Route2_id, 0, 0, 0, 0, 0
    End
Room16V1Chain67:
    StartObjectAnimSequence Room16V1Group2_id, 2, 0, 0, Room16V1Route1_id, 0, 0, 0, 0, 0
    End
Room16V1Chain68:
    ArmChainYield 1
    RespawnRowAndRunChain 0, Room16V1Chain65_id
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 5, 0, 0
    RespawnRowAndRunChain 0, Room16V1Chain66_id
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 7, 0, 0
    RespawnRowAndRunChain 0, Room16V1Chain67_id
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 6, 0, 0
    RespawnRowAndRunChain 0, Room16V1Chain69_id
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 7, 0, 0
    RespawnRowAndRunChain 0, Room16V1Chain70_id
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 6, 0, 0
    RespawnRowAndRunChain 0, Room16V1Chain71_id
    End
Room16V1Chain69:
    StartObjectAnimSequence Room16V1Group2_id, 3, 0, 0, Room16V1Route0_id, 0, 0, 0, 0, 0
    End
Room16V1Chain70:
    StartObjectAnimSequence Room16V1Group2_id, 4, 0, 0, Room16V1Route2_id, 0, 0, 0, 0, 0
    End
Room16V1Chain71:
    StartObjectAnimSequence Room16V1Group2_id, 5, 0, 0, Room16V1Route1_id, 0, 0, 0, 0, 0
    End
Room16V1Chain72:
    ArmChainYield 1
    ClearOverworldMonstersDisabled
    SetTileObjectAnimStateWithSpeed 0, 255
    InvokeChainIfEnabled 0, Room16V1Chain68_id
    End
Room16V1Chain73:
    @ "Locked."
    ShowRoomDialog 624
    End
Room16V1Chain74:
    ClearOverworldMonstersDisabled
    GotoIfStoryStageCompare 0, 17, Room16V1Chain85_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 18, Room16V1Chain85_id, 0, 0, 0
    End
Room16V1Chain75:
    SetQuestState 1, QUEST_ALT_PRESENTATION
    End
Room16V1Chain76:
    @ "I wonder why the portraits are so nervous?"
    ShowRoomDialog 368
    End
Room16V1Chain77:
    @ "The eyes of the portraits are following us more than usual..."
    ShowRoomDialog 371
    End
Room16V1Chain78:
    StartObjectAnimSequence Room16V1Group4_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group4_id, 1, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    End
Room16V1Chain79:
    StartObjectAnimSequence Room16V1Group5_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group5_id, 1, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    End
Room16V1Chain80:
    StartObjectAnimSequence Room16V1Group6_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group6_id, 1, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group6_id, 2, 0, 0, Room16V1Route10_id, 6, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group6_id, 3, 0, 0, Room16V1Route11_id, 7, 0, 0, 0, 0
    End
Room16V1Chain81:
    StartObjectAnimSequence Room16V1Group7_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group7_id, 1, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group7_id, 2, 0, 0, Room16V1Route10_id, 6, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group7_id, 3, 0, 0, Room16V1Route11_id, 7, 0, 0, 0, 0
    End
Room16V1Chain82:
    StartObjectAnimSequence Room16V1Group16_id, 1, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group16_id, 0, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    End
Room16V1Chain83:
    StartObjectAnimSequence Room16V1Group14_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group14_id, 1, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group14_id, 2, 0, 0, Room16V1Route10_id, 6, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group14_id, 3, 0, 0, Room16V1Route11_id, 7, 0, 0, 0, 0
    End
Room16V1Chain84:
    StartObjectAnimSequence Room16V1Group11_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group11_id, 1, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group11_id, 2, 0, 0, Room16V1Route11_id, 7, 0, 0, 0, 0
    End
Room16V1Chain85:
    StartObjectAnimSequence Room16V1Group12_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group12_id, 1, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group12_id, 2, 0, 0, Room16V1Route10_id, 6, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group12_id, 3, 0, 0, Room16V1Route11_id, 7, 0, 0, 0, 0
    End
Room16V1Chain86:
    StartObjectAnimSequence Room16V1Group13_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group13_id, 1, 0, 0, Room16V1Route10_id, 6, 0, 0, 0, 0
    End
Room16V1Chain87:
    StartObjectAnimSequence Room16V1Group10_id, 0, 0, 0, Room16V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group10_id, 1, 0, 0, Room16V1Route11_id, 4, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group10_id, 2, 0, 0, Room16V1Route10_id, 6, 0, 0, 0, 0
    StartObjectAnimSequence Room16V1Group10_id, 3, 0, 0, Room16V1Route11_id, 7, 0, 0, 0, 0
    End
Room16V1Chain88:
    SetOverworldMonstersDisabled
    End
Room16V1Chain89:
    GotoIfQuestStateCompare 249, 0, 1, Room16V1Chain82_id, 0, Room16V1Group16_id, 0
    End
    EndSubBlock Room16V1End

    SubBlock Room16V2, 1, Room16V2Routes, Room16V2Chains, Room16V2End
    OffsetTable Room16V2Groups, 1, 1
    Offsets Room16V2Group0
    EndTable
    Group Room16V2Group0, 0
    OffsetTable Room16V2Routes, 0
    EndTable
    OffsetTable Room16V2Chains, 1, 1
    Offsets Room16V2Chain0
    EndTable
Room16V2Chain0:
    End
    EndSubBlock Room16V2End

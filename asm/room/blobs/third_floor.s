    .include "asm/room_blob.inc"

Room20Blob:
    RoomBlob 6
    PlayerEntry 526, 584, 0, 0
    PlayerEntry 701, 244, 1, 0
    PlayerEntry 184, 215, 2, 0
    PlayerEntry 891, 216, 4, 0
    PlayerEntry 194, 413, 5, 0
    PlayerEntry 439, 218, 6, 4
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room20V0
    VariantEntry Room20V1

    SubBlock Room20V0, 1, Room20V0Routes, Room20V0Chains, Room20V0End
    OffsetTable Room20V0Groups, 1
    Offsets Room20V0Group0
    EndTable
    Group Room20V0Group0, 6
    Door 705, 286, half_width=40, half_height=12, destination_room=30, exit_param=3
    DoorAlt 437, 174, half_width=21, half_height=5, destination_room=31, exit_param=3
    Door 936, 212, half_width=9, half_height=37, destination_room=35, exit_param=1
    Chest 1070, 511, flag_id=45, reward_id=90
    Chest 540, 172, flag_id=46, reward_id=59
    Door 163, 415, half_width=10, half_height=44, destination_room=26
    OffsetTable Room20V0Routes, 0
    EndTable
    OffsetTable Room20V0Chains, 1
    Offsets Room20V0Chain0
    EndTable
Room20V0Chain0:
    SetQuestState 3, QUEST_CASTLE_AREA
    SetDefeatWarpSelector 2 @ Hospital Wing
    End
    EndSubBlock Room20V0End

    SubBlock Room20V1, 1, Room20V1Routes, Room20V1Chains, Room20V1End
    OffsetTable Room20V1Groups, 16, 1
    Offsets Room20V1Group0, Room20V1Group1, Room20V1Group2, Room20V1Group3, Room20V1Group4, Room20V1Group5
    Offsets Room20V1Group6, Room20V1Group7, Room20V1Group8, Room20V1Group9, Room20V1Group10, Room20V1Group11
    Offsets Room20V1Group12, Room20V1Group13, Room20V1Group14, Room20V1Group15
    EndTable
    Group Room20V1Group0, 1
    TriggerZone 538, 155, half_width=23, half_height=7, rearm_delay=2, trigger_kind=1, require_a_press=1, chain=Room20V1Chain35_id
    Group Room20V1Group1, 2
    Npc 831, 435, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain6_id
    Npc 812, 565, sprite=39, facing=0, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain7_id
    Group Room20V1Group2, 2
    Npc 830, 254, sprite=51, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain8_id
    Npc 736, 564, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain9_id
    Group Room20V1Group3, 2
    Npc 831, 433, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain10_id
    Npc 369, 565, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain11_id
    Group Room20V1Group4, 2
    Npc 830, 237, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain12_id
    Npc 623, 565, sprite=39, facing=0, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain13_id
    Group Room20V1Group5, 5
    TriggerZone 629, 183, half_width=27, half_height=31, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room20V1Chain2_id
    TriggerZone 704, 443, half_width=30, half_height=29, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room20V1Chain3_id
    TriggerZone 453, 540, half_width=33, half_height=30, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room20V1Chain33_id
    Npc 830, 449, sprite=43, facing=0, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain36_id
    Npc 814, 565, sprite=47, facing=0, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain37_id
    Group Room20V1Group6, 2
    Npc 733, 564, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain15_id
    Npc 830, 254, sprite=57, facing=2, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain14_id
    Group Room20V1Group7, 2
    Npc 830, 371, sprite=46, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain4_id
    Npc 324, 566, sprite=49, facing=2, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain5_id
    Group Room20V1Group8, 2
    Npc 701, 565, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain18_id
    Npc 830, 240, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain17_id
    Group Room20V1Group9, 2
    Npc 831, 389, sprite=52, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain20_id
    Npc 329, 566, sprite=61, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain21_id
    Group Room20V1Group10, 2
    Npc 829, 253, sprite=41, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain22_id
    Npc 579, 566, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain23_id
    Group Room20V1Group11, 1
    Npc 830, 412, sprite=41, facing=6, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain24_id
    Group Room20V1Group12, 2
    Npc 830, 413, sprite=54, facing=6, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain25_id
    Npc 270, 565, sprite=40, facing=6, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain26_id
    Group Room20V1Group13, 2
    Npc 831, 267, sprite=61, facing=2, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain27_id
    Npc 766, 565, sprite=58, facing=2, interact_cooldown=3, interact_mode=1, chain=Room20V1Chain28_id
    Group Room20V1Group14, 1
    TriggerZone 104, 202, half_width=65, half_height=63, rearm_delay=2, trigger_kind=1, require_a_press=1, chain=Room20V1Chain35_id
    Group Room20V1Group15, 1
    Door 151, 221, half_width=12, half_height=45, destination_room=0
    OffsetTable Room20V1Routes, 2
    Offsets Room20V1Route0, Room20V1Route1
    EndTable
Room20V1Route0:
    Route 6
    Waypoint 830, 225
    Waypoint 830, 480
    Waypoint 675, 480
    Waypoint 675, 555
    Waypoint 255, 555
    Waypoint 255, 225
Room20V1Route1:
    Route 4
    Waypoint 230, 222
    Waypoint 230, 565
    Waypoint 860, 565
    Waypoint 860, 222
    OffsetTable Room20V1Chains, 49, 1
    Offsets Room20V1Chain0, Room20V1Chain1, Room20V1Chain2, Room20V1Chain3, Room20V1Chain4, Room20V1Chain5
    Offsets Room20V1Chain6, Room20V1Chain7, Room20V1Chain8, Room20V1Chain9, Room20V1Chain10, Room20V1Chain11
    Offsets Room20V1Chain12, Room20V1Chain13, Room20V1Chain14, Room20V1Chain15, Room20V1Chain16, Room20V1Chain17
    Offsets Room20V1Chain18, Room20V1Chain19, Room20V1Chain20, Room20V1Chain21, Room20V1Chain22, Room20V1Chain23
    Offsets Room20V1Chain24, Room20V1Chain25, Room20V1Chain26, Room20V1Chain27, Room20V1Chain28, Room20V1Chain29
    Offsets Room20V1Chain30, Room20V1Chain31, Room20V1Chain32, Room20V1Chain33, Room20V1Chain34, Room20V1Chain35
    Offsets Room20V1Chain36, Room20V1Chain37, Room20V1Chain38, Room20V1Chain39, Room20V1Chain40, Room20V1Chain41
    Offsets Room20V1Chain42, Room20V1Chain43, Room20V1Chain44, Room20V1Chain45, Room20V1Chain46, Room20V1Chain47
    Offsets Room20V1Chain48
    EndTable
Room20V1Chain0:
    GotoIfStoryStageCompare 0, 0, Room20V1Chain38_id, 0, Room20V1Group7_id, 0
    GotoIfStoryStageCompare 0, 1, Room20V1Chain39_id, 0, Room20V1Group1_id, 0
    GotoIfStoryStageCompare 0, 2, Room20V1Chain40_id, 0, Room20V1Group2_id, 0
    GotoIfStoryStageCompare 0, 4, Room20V1Chain41_id, 0, Room20V1Group3_id, 0
    GotoIfStoryStageCompare 0, 5, Room20V1Chain42_id, 0, Room20V1Group4_id, 0
    GotoIfStoryStageCompare 0, 6, Room20V1Chain34_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room20V1Chain19_id, 0, Room20V1Group8_id, 0
    GotoIfStoryStageCompare 0, 8, Room20V1Chain16_id, 0, Room20V1Group6_id, 0
    GotoIfStoryStageCompare 0, 9, 0, 0, 0, 0
    GotoIfStoryStageCompare 0, 15, Room20V1Chain44_id, 0, Room20V1Group9_id, 0
    GotoIfStoryStageCompare 0, 16, Room20V1Chain45_id, 0, Room20V1Group10_id, 0
    GotoIfStoryStageCompare 0, 17, Room20V1Chain46_id, 0, Room20V1Group11_id, 0
    GotoIfStoryStageCompare 0, 18, Room20V1Chain46_id, 0, Room20V1Group11_id, 0
    GotoIfStoryStageCompare 0, 20, Room20V1Chain47_id, 0, Room20V1Group12_id, 0
    GotoIfStoryStageCompare 0, 21, Room20V1Chain48_id, 0, Room20V1Group13_id, 0
    GotoIfStoryStageCompare 5, 22, 0, 0, Room20V1Group15_id, 0
    GotoIfStoryStageCompare 3, 23, 0, 0, Room20V1Group14_id, 0
    End
Room20V1Chain1:
    @ "Has Sir Cadogan come this way?"
    @ "That daft knight? No, I'm afraid not."
    ShowRoomDialog 385
    End
Room20V1Chain2:
    @ "Has Sir Cadogan come this way?"
    @ "Ah, yes. I believe he's down on the lower levels."
    ShowRoomDialog 386
    End
Room20V1Chain3:
    @ "Has Sir Cadogan come this way?"
    @ "Yes. Took a dive into the portrait room."
    ShowRoomDialog 387
    End
Room20V1Chain4:
    @ "I can't find the common room for my house! Do you know where it is?"
    ShowRoomDialog 188
    End
Room20V1Chain5:
    @ "I heard that the Gryffindor common room is on the seventh floor."
    ShowRoomDialog 189
    End
Room20V1Chain6:
    @ "Transfiguration class is held on the first floor."
    ShowRoomDialog 212
    End
Room20V1Chain7:
    @ "I can't find the Transfiguration classroom. I heard it was on the first floor¸"
    ShowRoomDialog 213
    End
Room20V1Chain8:
    @ "This would be a nice day to have a class outside."
    ShowRoomDialog 237
    End
Room20V1Chain9:
    @ "Hagrid's a natural to teach Care of Magical Creatures - don't you think?"
    ShowRoomDialog 239
    End
Room20V1Chain10:
    @ "It's Potions next - down in the dungeons."
    ShowRoomDialog 323
    End
Room20V1Chain11:
    @ "Potions? It's held down in the dungeons."
    ShowRoomDialog 324
    End
Room20V1Chain12:
    @ "The staff room's next to the Entrance Hall. I don't think we are allowed in there though¸"
    ShowRoomDialog 329
    End
Room20V1Chain13:
    @ "Defense Against the Dark Arts class is on the third floor. I heard it might be taking place in the staff room today, though."
    ShowRoomDialog 328
    End
Room20V1Chain14:
    @ "Madam Pince's desk is in the library."
    ShowRoomDialog 627
    End
Room20V1Chain15:
    @ "The library? You'll need to go to the second floor."
    ShowRoomDialog 626
    End
Room20V1Chain16:
    StartObjectAnimSequence Room20V1Group6_id, 1, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group6_id, 0, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain17:
    @ "The Defense Against the Dark Arts class is on the third floor."
    ShowRoomDialog 327
    End
Room20V1Chain18:
    @ "The Defense Against the Dark Arts classroom's on the third floor."
    ShowRoomDialog 333
    End
Room20V1Chain19:
    StartObjectAnimSequence Room20V1Group8_id, 1, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group8_id, 0, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain20:
    @ "I'd love a new broom for Christmas. I still have my sister's old one!"
    ShowRoomDialog 450
    End
Room20V1Chain21:
    @ "I dream about Firebolts!"
    ShowRoomDialog 451
    End
Room20V1Chain22:
    @ "We need more holidays - and more feasts!"
    ShowRoomDialog 470
    End
Room20V1Chain23:
    @ "I've heard we'll be playing a game at this year's Christmas feast."
    ShowRoomDialog 471
    End
Room20V1Chain24:
    @ "Zonko's is definitely the best shop in Hogsmeade."
    ShowRoomDialog 514
    End
Room20V1Chain25:
    @ "I'm still stuffed from the Christmas feast!"
    ShowRoomDialog 511
    End
Room20V1Chain26:
    @ "Security's really been stepped up, hasn't it?"
    ShowRoomDialog 518
    End
Room20V1Chain27:
    @ "Personally, I'm against the execution of magical creatures."
    ShowRoomDialog 538
    End
Room20V1Chain28:
    @ "It's a real shame about Buckbeak."
    ShowRoomDialog 539
    End
Room20V1Chain29:
    @ "Locked."
    ShowRoomDialog 624
    End
Room20V1Chain30:
    @ "Did you know that Fred and George sell items that you usually can't get in Hogwarts? Their shop's on the seventh floor."
    ShowRoomDialog 629
    End
Room20V1Chain31:
    @ "I know the hospital wing's on the fourth floor - I just can't remember the name of the nurse..."
    ShowRoomDialog 635
    End
Room20V1Chain32:
    @ "Portraits are a convenient way to get around Hogwarts - once you figure out which portrait takes you to which floor."
    ShowRoomDialog 642
    End
Room20V1Chain33:
    @ "Has Sir Cadogan come this way?"
    @ "Indeed. Saw him dash into the Grand Staircase."
    ShowRoomDialog 388
    End
Room20V1Chain34:
    GotoIfQuestStateCompare 249, 0, 1, Room20V1Chain43_id, 0, Room20V1Group5_id, 0
    End
Room20V1Chain35:
    @ "Locked."
    ShowRoomDialog 624
    End
Room20V1Chain36:
    @ "There's something going on just outside the Gryffindor common room!"
    ShowRoomDialog 364
    End
Room20V1Chain37:
    @ "What's happened to the Fat Lady?"
    ShowRoomDialog 366
    End
Room20V1Chain38:
    StartObjectAnimSequence Room20V1Group7_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group7_id, 1, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain39:
    StartObjectAnimSequence Room20V1Group1_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group1_id, 1, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain40:
    StartObjectAnimSequence Room20V1Group2_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group2_id, 1, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain41:
    StartObjectAnimSequence Room20V1Group3_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group3_id, 1, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain42:
    StartObjectAnimSequence Room20V1Group4_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group4_id, 1, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain43:
    StartObjectAnimSequence Room20V1Group5_id, 3, 0, 0, Room20V1Route0_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group5_id, 4, 0, 0, Room20V1Route1_id, 0, 0, 0, 0, 0
    End
Room20V1Chain44:
    StartObjectAnimSequence Room20V1Group9_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group9_id, 1, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain45:
    StartObjectAnimSequence Room20V1Group10_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group10_id, 1, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain46:
    StartObjectAnimSequence Room20V1Group11_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    End
Room20V1Chain47:
    StartObjectAnimSequence Room20V1Group12_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group12_id, 1, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
Room20V1Chain48:
    StartObjectAnimSequence Room20V1Group13_id, 0, 0, 0, Room20V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room20V1Group13_id, 1, 0, 0, Room20V1Route1_id, 2, 0, 0, 0, 0
    End
    EndSubBlock Room20V1End

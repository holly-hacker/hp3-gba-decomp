    .include "asm/room_blob.inc"

Room18Blob:
    RoomBlob 5
    PlayerEntry 394, 167, 0, 0
    PlayerEntry 395, 903, 1, 0
    PlayerEntry 107, 672, 2, 0
    PlayerEntry 549, 612, 3, 0
    PlayerEntry 496, 235, 4, 4
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room18V0
    VariantEntry Room18V1

    SubBlock Room18V0, 1, Room18V0Routes, Room18V0Chains, Room18V0End
    OffsetTable Room18V0Groups, 1
    Offsets Room18V0Group0
    EndTable
    Group Room18V0Group0, 4
    Door 78, 679, half_width=8, half_height=22, destination_room=1
    Door 395, 943, half_width=31, half_height=11, destination_room=16, exit_param=2
    DoorAlt 497, 187, half_width=26, half_height=13, destination_room=31
    Chest 555, 415, flag_id=42, reward_id=82
    OffsetTable Room18V0Routes, 0
    EndTable
    OffsetTable Room18V0Chains, 1
    Offsets Room18V0Chain0
    EndTable
Room18V0Chain0:
    SetQuestState 0, QUEST_CASTLE_AREA
    SetDefeatWarpSelector 2
    End
    EndSubBlock Room18V0End

    SubBlock Room18V1, 1, Room18V1Routes, Room18V1Chains, Room18V1End
    OffsetTable Room18V1Groups, 14, 1
    Offsets Room18V1Group0, Room18V1Group1, Room18V1Group2, Room18V1Group3, Room18V1Group4, Room18V1Group5
    Offsets Room18V1Group6, Room18V1Group7, Room18V1Group8, Room18V1Group9, Room18V1Group10, Room18V1Group11
    Offsets Room18V1Group12, Room18V1Group13
    EndTable
    Group Room18V1Group0, 1
    TriggerZone 395, 121, half_width=15, half_height=9, rearm_delay=3, trigger_kind=1, chain=Room18V1Chain30_id
    Group Room18V1Group1, 2
    Npc 379, 331, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain3_id
    Npc 230, 739, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain4_id
    Group Room18V1Group2, 2
    Npc 188, 502, sprite=51, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain5_id
    Npc 230, 710, sprite=49, facing=2, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain6_id
    Group Room18V1Group3, 2
    Npc 380, 356, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain28_id
    Npc 230, 597, sprite=39, facing=6, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain8_id
    Group Room18V1Group4, 2
    Npc 190, 609, sprite=39, facing=2, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain9_id
    Npc 421, 291, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain10_id
    Group Room18V1Group5, 2
    Npc 380, 230, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain11_id
    Npc 230, 790, sprite=39, facing=0, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain12_id
    Group Room18V1Group6, 2
    Npc 318, 420, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain1_id
    Npc 230, 729, sprite=44, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain2_id
    Group Room18V1Group7, 2
    Npc 380, 232, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain14_id
    Npc 230, 794, sprite=49, facing=0, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain15_id
    Group Room18V1Group8, 2
    Npc 380, 372, sprite=59, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain17_id
    Npc 230, 728, sprite=49, facing=6, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain18_id
    Group Room18V1Group9, 2
    Npc 380, 287, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain19_id
    Npc 230, 607, sprite=45, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain20_id
    Group Room18V1Group10, 1
    Npc 266, 421, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain21_id
    Group Room18V1Group11, 1
    Npc 190, 577, sprite=40, facing=2, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain23_id
    Group Room18V1Group12, 2
    Npc 380, 311, sprite=40, facing=2, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain24_id
    Npc 231, 608, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain25_id
    Group Room18V1Group13, 1
    Npc 230, 610, sprite=39, facing=0, interact_cooldown=3, interact_mode=1, chain=Room18V1Chain31_id
    OffsetTable Room18V1Routes, 1
    Offsets Room18V1Route0
    EndTable
Room18V1Route0:
    Route 8
    Waypoint 380, 230
    Waypoint 380, 420
    Waypoint 190, 420
    Waypoint 190, 770
    Waypoint 230, 770
    Waypoint 230, 435
    Waypoint 420, 435
    Waypoint 420, 230
    OffsetTable Room18V1Chains, 44, 1
    Offsets Room18V1Chain0, Room18V1Chain1, Room18V1Chain2, Room18V1Chain3, Room18V1Chain4, Room18V1Chain5
    Offsets Room18V1Chain6, Room18V1Chain7, Room18V1Chain8, Room18V1Chain9, Room18V1Chain10, Room18V1Chain11
    Offsets Room18V1Chain12, Room18V1Chain13, Room18V1Chain14, Room18V1Chain15, Room18V1Chain16, Room18V1Chain17
    Offsets Room18V1Chain18, Room18V1Chain19, Room18V1Chain20, Room18V1Chain21, Room18V1Chain22, Room18V1Chain23
    Offsets Room18V1Chain24, Room18V1Chain25, Room18V1Chain26, Room18V1Chain27, Room18V1Chain28, Room18V1Chain29
    Offsets Room18V1Chain30, Room18V1Chain31, Room18V1Chain32, Room18V1Chain33, Room18V1Chain34, Room18V1Chain35
    Offsets Room18V1Chain36, Room18V1Chain37, Room18V1Chain38, Room18V1Chain39, Room18V1Chain40, Room18V1Chain41
    Offsets Room18V1Chain42, Room18V1Chain43
    EndTable
Room18V1Chain0:
    GotoIfStoryStageCompare 0, 0, Room18V1Chain32_id, 0, Room18V1Group6_id, 0
    GotoIfStoryStageCompare 0, 1, Room18V1Chain33_id, 0, Room18V1Group1_id, 0
    GotoIfStoryStageCompare 0, 2, Room18V1Chain34_id, 0, Room18V1Group2_id, 0
    GotoIfStoryStageCompare 0, 3, Room18V1Chain34_id, 0, Room18V1Group2_id, 0
    GotoIfStoryStageCompare 0, 4, Room18V1Chain35_id, 0, Room18V1Group3_id, 0
    GotoIfStoryStageCompare 0, 5, Room18V1Chain36_id, 0, Room18V1Group4_id, 0
    GotoIfStoryStageCompare 0, 6, Room18V1Chain43_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room18V1Chain16_id, 0, Room18V1Group7_id, 0
    GotoIfStoryStageCompare 0, 8, Room18V1Chain13_id, 0, Room18V1Group5_id, 0
    GotoIfStoryStageCompare 0, 15, Room18V1Chain38_id, 0, Room18V1Group8_id, 0
    GotoIfStoryStageCompare 0, 16, Room18V1Chain39_id, 0, Room18V1Group9_id, 0
    GotoIfStoryStageCompare 0, 17, Room18V1Chain40_id, 0, Room18V1Group10_id, 0
    GotoIfStoryStageCompare 0, 18, Room18V1Chain40_id, 0, Room18V1Group10_id, 0
    GotoIfStoryStageCompare 0, 20, Room18V1Chain41_id, 0, Room18V1Group11_id, 0
    GotoIfStoryStageCompare 0, 21, Room18V1Chain42_id, 0, Room18V1Group12_id, 0
    End
Room18V1Chain1:
    @ "I'm so excited! A brand new year at Hogwarts!"
    ShowRoomDialog 190
    End
Room18V1Chain2:
    @ "I don't speak to Gryffindors."
    ShowRoomDialog 196
    End
Room18V1Chain3:
    @ "Transfiguration class is held on the first floor."
    ShowRoomDialog 212
    End
Room18V1Chain4:
    @ "I can't find the Transfiguration classroom. I heard it was on the first floor¸"
    ShowRoomDialog 213
    End
Room18V1Chain5:
    @ "This would be a nice day to have a class outside."
    ShowRoomDialog 237
    End
Room18V1Chain6:
    @ "Hagrid's a natural to teach Care of Magical Creatures - don't you think?"
    ShowRoomDialog 239
    End
Room18V1Chain7:
    @ "Potions class is in the dungeons off the Entrance Hall."
    ShowRoomDialog 321
    End
Room18V1Chain8:
    @ "I hate having to go into the dungeons to get to Potions."
    ShowRoomDialog 322
    End
Room18V1Chain9:
    @ "Defense Against the Dark Arts class is on the third floor. I heard it might be taking place in the staff room today, though."
    ShowRoomDialog 328
    End
Room18V1Chain10:
    @ "The staff room's next to the Entrance Hall. I don't think we are allowed in there though¸"
    ShowRoomDialog 329
    End
Room18V1Chain11:
    @ "The library's quite large - and it's got upper and lower levels..."
    ShowRoomDialog 631
    End
Room18V1Chain12:
    @ "The library? You'll need to go to the second floor."
    ShowRoomDialog 626
    End
Room18V1Chain13:
    StartObjectAnimSequence Room18V1Group5_id, 0, 0, 0, Room18V1Route0_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group5_id, 1, 0, 0, Room18V1Route0_id, 4, 0, 0, 0, 0
    End
Room18V1Chain14:
    @ "The Defense Against the Dark Arts class is on the third floor."
    ShowRoomDialog 327
    End
Room18V1Chain15:
    @ "The Defense Against the Dark Arts classroom's on the third floor."
    ShowRoomDialog 333
    End
Room18V1Chain16:
    StartObjectAnimSequence Room18V1Group7_id, 0, 0, 0, Room18V1Route0_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group7_id, 1, 0, 0, Room18V1Route0_id, 4, 0, 0, 0, 0
    End
Room18V1Chain17:
    @ "Is it true about the Firebolt?"
    ShowRoomDialog 447
    End
Room18V1Chain18:
    @ "If our Quidditch team all had Firebolts, they'd make mincemeat of everyone!"
    ShowRoomDialog 454
    End
Room18V1Chain19:
    @ "I love the Christmas feast!"
    ShowRoomDialog 466
    End
Room18V1Chain20:
    @ "I'm going to eat so much at the Christmas Feast they'll have to send me to Madam Pomfrey!"
    ShowRoomDialog 467
    End
Room18V1Chain21:
    @ "I'm still stuffed from the Christmas feast!"
    ShowRoomDialog 511
    End
Room18V1Chain22:
    @ "Is it true Sirius Black tried to stab Ron Weasley?"
    ShowRoomDialog 517
    End
Room18V1Chain23:
    @ "Security's really been stepped up, hasn't it?"
    ShowRoomDialog 518
    End
Room18V1Chain24:
    @ "I wonder how they'll execute Buckbeak?"
    ShowRoomDialog 537
    End
Room18V1Chain25:
    @ "I've heard they're going to execute Buckbeak!"
    ShowRoomDialog 534
    End
Room18V1Chain26:
    @ "Locked."
    ShowRoomDialog 624
    End
Room18V1Chain27:
    @ "I heard a rumor that Fred and George Weasley have a shop on the seventh floor."
    ShowRoomDialog 625
    End
Room18V1Chain28:
    @ "If you're unwell, go and see Madam Pomfrey whenever you like. She's in the hospital wing on the fourth floor."
    ShowRoomDialog 633
    End
Room18V1Chain29:
    @ "I heard there are portrait shortcuts on every floor of Hogwarts..."
    ShowRoomDialog 640
    End
Room18V1Chain30:
    @ "Locked."
    ShowRoomDialog 624
    End
Room18V1Chain31:
    @ "Heard about the portrait of the Fat Lady?"
    ShowRoomDialog 363
    End
Room18V1Chain32:
    StartObjectAnimSequence Room18V1Group6_id, 0, 0, 0, Room18V1Route0_id, 2, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group6_id, 1, 0, 0, Room18V1Route0_id, 5, 0, 0, 0, 0
    End
Room18V1Chain33:
    StartObjectAnimSequence Room18V1Group1_id, 0, 0, 0, Room18V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group1_id, 1, 0, 0, Room18V1Route0_id, 5, 0, 0, 0, 0
    End
Room18V1Chain34:
    StartObjectAnimSequence Room18V1Group2_id, 0, 0, 0, Room18V1Route0_id, 3, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group2_id, 1, 0, 0, Room18V1Route0_id, 5, 0, 0, 0, 0
    End
Room18V1Chain35:
    StartObjectAnimSequence Room18V1Group3_id, 0, 0, 0, Room18V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group3_id, 1, 0, 0, Room18V1Route0_id, 5, 0, 0, 0, 0
    End
Room18V1Chain36:
    StartObjectAnimSequence Room18V1Group4_id, 0, 0, 0, Room18V1Route0_id, 3, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group4_id, 1, 0, 0, Room18V1Route0_id, 7, 0, 0, 0, 0
    End
Room18V1Chain37:
    StartObjectAnimSequence Room18V1Group13_id, 0, 0, 0, Room18V1Route0_id, 5, 0, 0, 0, 0
    End
Room18V1Chain38:
    StartObjectAnimSequence Room18V1Group8_id, 0, 0, 0, Room18V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group8_id, 1, 0, 0, Room18V1Route0_id, 5, 0, 0, 0, 0
    End
Room18V1Chain39:
    StartObjectAnimSequence Room18V1Group9_id, 0, 0, 0, Room18V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group9_id, 1, 0, 0, Room18V1Route0_id, 5, 0, 0, 0, 0
    End
Room18V1Chain40:
    StartObjectAnimSequence Room18V1Group10_id, 0, 0, 0, Room18V1Route0_id, 2, 0, 0, 0, 0
    End
Room18V1Chain41:
    StartObjectAnimSequence Room18V1Group11_id, 0, 0, 0, Room18V1Route0_id, 3, 0, 0, 0, 0
    End
Room18V1Chain42:
    StartObjectAnimSequence Room18V1Group12_id, 0, 0, 0, Room18V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room18V1Group12_id, 1, 0, 0, Room18V1Route0_id, 5, 0, 0, 0, 0
    End
Room18V1Chain43:
    GotoIfQuestStateCompare 249, 0, 1, Room18V1Chain37_id, 0, Room18V1Group13_id, 0
    End
    EndSubBlock Room18V1End

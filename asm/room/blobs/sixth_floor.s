    .include "asm/room_blob.inc"

Room23Blob:
    RoomBlob 2
    PlayerEntry 268, 149, 0, 4
    PlayerEntry 354, 201, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room23V0
    VariantEntry Room23V1

    SubBlock Room23V0, 1, Room23V0Routes, Room23V0Chains, Room23V0End
    OffsetTable Room23V0Groups, 1
    Offsets Room23V0Group0
    EndTable
    Group Room23V0Group0, 4
    Door 355, 232, half_width=41, half_height=10, destination_room=30, exit_param=2
    DoorAlt 267, 109, half_width=17, half_height=7, destination_room=31, exit_param=6
    Chest 283, 465, flag_id=49, reward_id=123
    Chest 104, 146, flag_id=50, reward_id=57
    OffsetTable Room23V0Routes, 0
    EndTable
    OffsetTable Room23V0Chains, 1
    Offsets Room23V0Chain0
    EndTable
Room23V0Chain0:
    SetQuestState 6, 17
    SetBattleDefeatState 2
    End
    EndSubBlock Room23V0End

    SubBlock Room23V1, 1, Room23V1Routes, Room23V1Chains, Room23V1End
    OffsetTable Room23V1Groups, 14, 1
    Offsets Room23V1Group0, Room23V1Group1, Room23V1Group2, Room23V1Group3, Room23V1Group4, Room23V1Group5
    Offsets Room23V1Group6, Room23V1Group7, Room23V1Group8, Room23V1Group9, Room23V1Group10, Room23V1Group11
    Offsets Room23V1Group12, Room23V1Group13
    EndTable
    Group Room23V1Group0, 0
.ifdef VERSION_JP
    Group Room23V1Group1, 2
.else
    Group Room23V1Group1, 3
    TriggerZone 268, 108, half_width=42, half_height=39, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room23V1Chain1_id
.endif
    Npc 111, 219, sprite=55, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain32_id
    Npc 491, 175, sprite=39, facing=2, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain33_id
    Group Room23V1Group2, 2
    Npc 429, 176, sprite=39, facing=2, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain4_id
    Npc 111, 422, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain5_id
    Group Room23V1Group3, 2
    Npc 109, 360, sprite=51, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain6_id
    Npc 452, 175, sprite=53, facing=2, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain7_id
    Group Room23V1Group4, 2
    Npc 110, 197, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain8_id
    Npc 205, 174, sprite=60, facing=2, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain9_id
    Group Room23V1Group5, 2
    Npc 111, 413, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain10_id
    Npc 472, 175, sprite=54, facing=2, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain11_id
    Group Room23V1Group6, 2
    Npc 110, 165, sprite=57, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain12_id
    Npc 471, 370, sprite=46, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain13_id
    Group Room23V1Group7, 2
    Npc 110, 207, sprite=46, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain2_id
    Npc 145, 175, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain3_id
    Group Room23V1Group8, 2
    Npc 515, 174, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain15_id
    Npc 111, 491, sprite=49, facing=2, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain16_id
    Group Room23V1Group9, 2
    Npc 109, 211, sprite=39, facing=4, chain=Room23V1Chain18_id
    Npc 138, 176, sprite=44, facing=2, chain=Room23V1Chain19_id
    Group Room23V1Group10, 2
    Npc 108, 291, sprite=45, facing=4, chain=Room23V1Chain20_id
    Npc 500, 175, sprite=58, facing=2, chain=Room23V1Chain21_id
    Group Room23V1Group11, 1
    Npc 110, 434, sprite=41, facing=4, chain=Room23V1Chain22_id
    Group Room23V1Group12, 2
    Npc 110, 215, sprite=46, facing=4, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain23_id
    Npc 136, 175, sprite=49, facing=0, interact_cooldown=3, interact_mode=1, chain=Room23V1Chain24_id
    Group Room23V1Group13, 2
    Npc 475, 175, sprite=58, facing=2, chain=Room23V1Chain26_id
    Npc 110, 346, sprite=47, facing=4, chain=Room23V1Chain25_id
    OffsetTable Room23V1Routes, 2
    Offsets Room23V1Route0, Room23V1Route1
    EndTable
Room23V1Route0:
    Route 6
    Waypoint 110, 165
    Waypoint 110, 485
    Waypoint 545, 485
    Waypoint 545, 100
    Waypoint 350, 100
    Waypoint 350, 165
Room23V1Route1:
    Route 6
    Waypoint 125, 175
    Waypoint 515, 175
    Waypoint 515, 360
    Waypoint 470, 360
    Waypoint 470, 475
    Waypoint 125, 475
    OffsetTable Room23V1Chains, 45, 1
    Offsets Room23V1Chain0, Room23V1Chain1, Room23V1Chain2, Room23V1Chain3, Room23V1Chain4, Room23V1Chain5
    Offsets Room23V1Chain6, Room23V1Chain7, Room23V1Chain8, Room23V1Chain9, Room23V1Chain10, Room23V1Chain11
    Offsets Room23V1Chain12, Room23V1Chain13, Room23V1Chain14, Room23V1Chain15, Room23V1Chain16, Room23V1Chain17
    Offsets Room23V1Chain18, Room23V1Chain19, Room23V1Chain20, Room23V1Chain21, Room23V1Chain22, Room23V1Chain23
    Offsets Room23V1Chain24, Room23V1Chain25, Room23V1Chain26, Room23V1Chain27, Room23V1Chain28, Room23V1Chain29
    Offsets Room23V1Chain30, Room23V1Chain31, Room23V1Chain32, Room23V1Chain33, Room23V1Chain34, Room23V1Chain35
    Offsets Room23V1Chain36, Room23V1Chain37, Room23V1Chain38, Room23V1Chain39, Room23V1Chain40, Room23V1Chain41
    Offsets Room23V1Chain42, Room23V1Chain43, Room23V1Chain44
    EndTable
Room23V1Chain0:
    GotoIfStoryStageCompare 0, 0, Room23V1Chain34_id, 0, Room23V1Group7_id, 0
    GotoIfStoryStageCompare 0, 1, Room23V1Chain35_id, 0, Room23V1Group2_id, 0
    GotoIfStoryStageCompare 0, 2, Room23V1Chain36_id, 0, Room23V1Group3_id, 0
    GotoIfStoryStageCompare 0, 4, Room23V1Chain37_id, 0, Room23V1Group4_id, 0
    GotoIfStoryStageCompare 0, 5, Room23V1Chain38_id, 0, Room23V1Group5_id, 0
    GotoIfStoryStageCompare 0, 6, Room23V1Chain31_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room23V1Chain17_id, 0, Room23V1Group8_id, 0
    GotoIfStoryStageCompare 0, 8, Room23V1Chain14_id, 0, Room23V1Group6_id, 0
    GotoIfStoryStageCompare 0, 15, Room23V1Chain40_id, 0, Room23V1Group9_id, 0
    GotoIfStoryStageCompare 0, 16, Room23V1Chain41_id, 0, Room23V1Group10_id, 0
    GotoIfStoryStageCompare 0, 17, Room23V1Chain42_id, 0, Room23V1Group11_id, 0
    GotoIfStoryStageCompare 0, 18, Room23V1Chain42_id, 0, Room23V1Group11_id, 0
    GotoIfStoryStageCompare 0, 20, Room23V1Chain43_id, 0, Room23V1Group12_id, 0
    GotoIfStoryStageCompare 0, 21, Room23V1Chain44_id, 0, Room23V1Group13_id, 0
    End
Room23V1Chain1:
    @ "Has Sir Cadogan come this way?"
    @ "Don't know anyone by that name."
    ShowRoomDialog 382
    End
Room23V1Chain2:
    @ "I can't find the common room for my house! Do you know where it is?"
    ShowRoomDialog 188
    End
Room23V1Chain3:
    @ "I'm so excited! A brand new year at Hogwarts!"
    ShowRoomDialog 190
    End
Room23V1Chain4:
    @ "Transfiguration class is held on the first floor."
    ShowRoomDialog 212
    End
Room23V1Chain5:
    @ "I can't find the Transfiguration classroom. I heard it was on the first floor¸"
    ShowRoomDialog 213
    End
Room23V1Chain6:
    @ "This would be a nice day to have a class outside."
    ShowRoomDialog 237
    End
Room23V1Chain7:
    @ "Hagrid's a natural to teach Care of Magical Creatures - don't you think?"
    ShowRoomDialog 239
    End
Room23V1Chain8:
    @ "It's Potions next - down in the dungeons."
    ShowRoomDialog 323
    End
Room23V1Chain9:
    @ "Potions? It's held down in the dungeons."
    ShowRoomDialog 324
    End
Room23V1Chain10:
    @ "The staff room's next to the Entrance Hall. I don't think we are allowed in there though¸"
    ShowRoomDialog 329
    End
Room23V1Chain11:
    @ "Why do you want to go to the staff room? Isn't it for teachers only?"
    ShowRoomDialog 330
    End
Room23V1Chain12:
    @ "Madam Pince's desk is in the library."
    ShowRoomDialog 627
    End
Room23V1Chain13:
    @ "I hope I can get to Madam Pince before everyone else does. She's on the second floor."
    ShowRoomDialog 632
    End
Room23V1Chain14:
    StartObjectAnimSequence Room23V1Group6_id, 0, 0, 0, Room23V1Route0_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group6_id, 1, 0, 0, Room23V1Route1_id, 0, 0, 0, 0, 0
    End
Room23V1Chain15:
    @ "The Defense Against the Dark Arts class is on the third floor."
    ShowRoomDialog 327
    End
Room23V1Chain16:
    @ "The Defense Against the Dark Arts classroom's on the third floor."
    ShowRoomDialog 333
    End
Room23V1Chain17:
    StartObjectAnimSequence Room23V1Group8_id, 0, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group8_id, 1, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    End
Room23V1Chain18:
    @ "I've heard Firebolts are the fastest brooms ever."
    ShowRoomDialog 455
    End
Room23V1Chain19:
    @ "I touched a Firebolt once and I didn't wash my hands for two weeks!"
    ShowRoomDialog 456
    End
Room23V1Chain20:
    @ "I'm going to eat so much at the Christmas Feast they'll have to send me to Madam Pomfrey!"
    ShowRoomDialog 467
    End
Room23V1Chain21:
    @ "I hope there are crackers at the Christmas feast."
    ShowRoomDialog 468
    End
Room23V1Chain22:
    @ "Zonko's is definitely the best shop in Hogsmeade."
    ShowRoomDialog 514
    End
Room23V1Chain23:
    @ "I heard that Sirius Black was seen in Gryffindor Tower!"
    ShowRoomDialog 516
    End
Room23V1Chain24:
    @ "Is it true Sirius Black tried to stab Ron Weasley?"
    ShowRoomDialog 517
    End
Room23V1Chain25:
    @ "I've heard they're going to execute Buckbeak!"
    ShowRoomDialog 534
    End
Room23V1Chain26:
    @ "It's a real shame about Buckbeak."
    ShowRoomDialog 539
    End
Room23V1Chain27:
    @ "Locked."
    ShowRoomDialog 624
    End
Room23V1Chain28:
    @ "I heard a rumor that Fred and George Weasley have a shop on the seventh floor."
    ShowRoomDialog 625
    End
Room23V1Chain29:
    @ "If you're unwell, go and see Madam Pomfrey whenever you like. She's in the hospital wing on the fourth floor."
    ShowRoomDialog 633
    End
Room23V1Chain30:
    @ "When I'm running late for class, I use the portrait shortcuts to get where I'm going faster."
    ShowRoomDialog 645
    End
Room23V1Chain31:
    GotoIfQuestStateCompare 249, 0, 1, Room23V1Chain39_id, 0, Room23V1Group1_id, 0
    End
Room23V1Chain32:
    @ "The eyes of the portraits are following us more than usual..."
    ShowRoomDialog 371
    End
Room23V1Chain33:
    @ "Heard about the portrait of the Fat Lady?"
    ShowRoomDialog 363
    End
Room23V1Chain34:
    StartObjectAnimSequence Room23V1Group7_id, 0, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group7_id, 1, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    End
Room23V1Chain35:
    StartObjectAnimSequence Room23V1Group2_id, 1, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group2_id, 0, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    End
Room23V1Chain36:
    StartObjectAnimSequence Room23V1Group3_id, 0, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group3_id, 1, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    End
Room23V1Chain37:
    StartObjectAnimSequence Room23V1Group4_id, 0, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group4_id, 1, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    End
Room23V1Chain38:
    StartObjectAnimSequence Room23V1Group5_id, 0, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group5_id, 1, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    End
Room23V1Chain39:
.ifdef VERSION_JP
    StartObjectAnimSequence Room23V1Group1_id, 0, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group1_id, 1, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
.else
    StartObjectAnimSequence Room23V1Group1_id, 1, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group1_id, 2, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
.endif
    End
Room23V1Chain40:
    StartObjectAnimSequence Room23V1Group9_id, 0, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group9_id, 1, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    End
Room23V1Chain41:
    StartObjectAnimSequence Room23V1Group10_id, 0, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group10_id, 1, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    End
Room23V1Chain42:
    StartObjectAnimSequence Room23V1Group11_id, 0, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    End
Room23V1Chain43:
    StartObjectAnimSequence Room23V1Group12_id, 0, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group12_id, 1, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    End
Room23V1Chain44:
    StartObjectAnimSequence Room23V1Group13_id, 1, 0, 0, Room23V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room23V1Group13_id, 0, 0, 0, Room23V1Route1_id, 1, 0, 0, 0, 0
    End
    EndSubBlock Room23V1End

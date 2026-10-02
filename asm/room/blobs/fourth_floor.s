    .include "asm/room_blob.inc"

Room21Blob:
    RoomBlob 3
    PlayerEntry 455, 208, 0, 4
    PlayerEntry 349, 394, 1, 0
    PlayerEntry 788, 124, 3, 4
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room21V0
    VariantEntry Room21V1

    SubBlock Room21V0, 1, Room21V0Routes, Room21V0Chains, Room21V0End
    OffsetTable Room21V0Groups, 1
    Offsets Room21V0Group0
    EndTable
    Group Room21V0Group0, 5
    DoorAlt 454, 169, half_width=22, half_height=11, destination_room=31, exit_param=4
    Chest 804, 424, flag_id=47, reward_id=131
    Chest 886, 204, flag_id=48, reward_id=127
    Door 406, 401, half_width=11, half_height=32, destination_room=30, exit_param=5
    Door 787, 79, half_width=54, half_height=11, destination_room=33, exit_param=1
    OffsetTable Room21V0Routes, 0
    EndTable
    OffsetTable Room21V0Chains, 1
    Offsets Room21V0Chain0
    EndTable
Room21V0Chain0:
    SetQuestState 4, 17
    SetBattleDefeatState 2
    End
    EndSubBlock Room21V0End

    SubBlock Room21V1, 1, Room21V1Routes, Room21V1Chains, Room21V1End
    OffsetTable Room21V1Groups, 14, 1
    Offsets Room21V1Group0, Room21V1Group1, Room21V1Group2, Room21V1Group3, Room21V1Group4, Room21V1Group5
    Offsets Room21V1Group6, Room21V1Group7, Room21V1Group8, Room21V1Group9, Room21V1Group10, Room21V1Group11
    Offsets Room21V1Group12, Room21V1Group13
    EndTable
    Group Room21V1Group0, 0
    Group Room21V1Group1, 2
    Npc 279, 359, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain4_id
    Npc 890, 471, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain5_id
    Group Room21V1Group2, 2
    Npc 279, 498, sprite=51, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain6_id
    Npc 889, 508, sprite=53, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain7_id
    Group Room21V1Group3, 2
    Npc 280, 244, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain8_id
    Npc 891, 246, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain9_id
    Group Room21V1Group4, 2
    Npc 280, 282, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain10_id
    Npc 890, 506, sprite=57, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain11_id
    Group Room21V1Group5, 3
    TriggerZone 937, 181, half_width=39, half_height=36, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room21V1Chain2_id
    Npc 280, 260, sprite=52, facing=0, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain32_id
    Npc 890, 254, sprite=45, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain33_id
    Group Room21V1Group6, 2
    Npc 892, 554, sprite=39, facing=0, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain13_id
    Npc 280, 215, sprite=60, facing=0, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain12_id
    Group Room21V1Group7, 2
    Npc 280, 237, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain3_id
    Npc 890, 469, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain28_id
    Group Room21V1Group8, 2
    Npc 891, 554, sprite=49, facing=0, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain16_id
    Npc 281, 580, sprite=39, facing=2, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain15_id
    Group Room21V1Group9, 2
    Npc 280, 299, sprite=43, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain18_id
    Npc 891, 441, sprite=43, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain19_id
    Group Room21V1Group10, 2
    Npc 890, 484, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain21_id
    Npc 281, 470, sprite=46, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain20_id
    Group Room21V1Group11, 1
    Npc 281, 249, sprite=55, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain22_id
    Group Room21V1Group12, 1
    Npc 890, 390, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain23_id
    Group Room21V1Group13, 2
    Npc 280, 289, sprite=42, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain25_id
    Npc 890, 517, sprite=43, facing=4, interact_cooldown=3, interact_mode=1, chain=Room21V1Chain26_id
    OffsetTable Room21V1Routes, 2
    Offsets Room21V1Route0, Room21V1Route1
    EndTable
Room21V1Route0:
    Route 4
    Waypoint 280, 225
    Waypoint 280, 565
    Waypoint 915, 565
    Waypoint 915, 225
Room21V1Route1:
    Route 4
    Waypoint 305, 215
    Waypoint 890, 215
    Waypoint 890, 555
    Waypoint 305, 555
    OffsetTable Room21V1Chains, 45, 1
    Offsets Room21V1Chain0, Room21V1Chain1, Room21V1Chain2, Room21V1Chain3, Room21V1Chain4, Room21V1Chain5
    Offsets Room21V1Chain6, Room21V1Chain7, Room21V1Chain8, Room21V1Chain9, Room21V1Chain10, Room21V1Chain11
    Offsets Room21V1Chain12, Room21V1Chain13, Room21V1Chain14, Room21V1Chain15, Room21V1Chain16, Room21V1Chain17
    Offsets Room21V1Chain18, Room21V1Chain19, Room21V1Chain20, Room21V1Chain21, Room21V1Chain22, Room21V1Chain23
    Offsets Room21V1Chain24, Room21V1Chain25, Room21V1Chain26, Room21V1Chain27, Room21V1Chain28, Room21V1Chain29
    Offsets Room21V1Chain30, Room21V1Chain31, Room21V1Chain32, Room21V1Chain33, Room21V1Chain34, Room21V1Chain35
    Offsets Room21V1Chain36, Room21V1Chain37, Room21V1Chain38, Room21V1Chain39, Room21V1Chain40, Room21V1Chain41
    Offsets Room21V1Chain42, Room21V1Chain43, Room21V1Chain44
    EndTable
Room21V1Chain0:
    GotoIfStoryStageCompare 0, 0, Room21V1Chain34_id, 0, Room21V1Group7_id, 0
    GotoIfStoryStageCompare 0, 1, Room21V1Chain35_id, 0, Room21V1Group1_id, 0
    GotoIfStoryStageCompare 0, 2, Room21V1Chain36_id, 0, Room21V1Group2_id, 0
    GotoIfStoryStageCompare 0, 4, Room21V1Chain37_id, 0, Room21V1Group3_id, 0
    GotoIfStoryStageCompare 0, 5, Room21V1Chain38_id, 0, Room21V1Group4_id, 0
    GotoIfStoryStageCompare 0, 6, Room21V1Chain31_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room21V1Chain17_id, 0, Room21V1Group8_id, 0
    GotoIfStoryStageCompare 0, 8, Room21V1Chain14_id, 0, Room21V1Group6_id, 0
    GotoIfStoryStageCompare 0, 15, Room21V1Chain40_id, 0, Room21V1Group9_id, 0
    GotoIfStoryStageCompare 0, 16, Room21V1Chain41_id, 0, Room21V1Group10_id, 0
    GotoIfStoryStageCompare 0, 17, Room21V1Chain42_id, 0, Room21V1Group11_id, 0
    GotoIfStoryStageCompare 0, 18, Room21V1Chain42_id, 0, Room21V1Group11_id, 0
    GotoIfStoryStageCompare 0, 20, Room21V1Chain43_id, 0, Room21V1Group12_id, 0
    GotoIfStoryStageCompare 0, 21, Room21V1Chain44_id, 0, Room21V1Group13_id, 0
    End
Room21V1Chain1:
    @ "Has Sir Cadogan come this way?"
    @ "Don't know anyone by that name."
    ShowRoomDialog 382
    End
Room21V1Chain2:
    @ "Has Sir Cadogan come this way?"
    @ "He's on the second floor. And would you kindly ask him to stay there?"
    ShowRoomDialog 389
    End
Room21V1Chain3:
    @ "The Gryffindor common room is on the seventh floor. Just like last year."
    ShowRoomDialog 187
    End
Room21V1Chain4:
    @ "Transfiguration class is held on the first floor."
    ShowRoomDialog 212
    End
Room21V1Chain5:
    @ "I can't find the Transfiguration classroom. I heard it was on the first floor¸"
    ShowRoomDialog 213
    End
Room21V1Chain6:
    @ "This would be a nice day to have a class outside."
    ShowRoomDialog 237
    End
Room21V1Chain7:
    @ "Hagrid's a natural to teach Care of Magical Creatures - don't you think?"
    ShowRoomDialog 239
    End
Room21V1Chain8:
    @ "Potions class is in the dungeons off the Entrance Hall."
    ShowRoomDialog 321
    End
Room21V1Chain9:
    @ "I hate having to go into the dungeons to get to Potions."
    ShowRoomDialog 322
    End
Room21V1Chain10:
    @ "I wonder if the new Defense Against the Dark Arts teacher will be as good-looking as Professor Lockhart."
    ShowRoomDialog 334
    End
Room21V1Chain11:
    @ "The staff room's next to the Entrance Hall."
    ShowRoomDialog 331
    End
Room21V1Chain12:
    @ "The library's quite large - and it's got upper and lower levels..."
    ShowRoomDialog 631
    End
Room21V1Chain13:
    @ "The library? You'll need to go to the second floor."
    ShowRoomDialog 626
    End
Room21V1Chain14:
    StartObjectAnimSequence Room21V1Group6_id, 1, 0, 0, Room21V1Route0_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group6_id, 0, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain15:
    @ "The Defense Against the Dark Arts class is on the third floor."
    ShowRoomDialog 327
    End
Room21V1Chain16:
    @ "The Defense Against the Dark Arts classroom's on the third floor."
    ShowRoomDialog 333
    End
Room21V1Chain17:
    StartObjectAnimSequence Room21V1Group8_id, 1, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group8_id, 0, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain18:
    @ "Firebolts are the best racing brooms in the world!"
    ShowRoomDialog 452
    End
Room21V1Chain19:
    @ "I'd love to ride a Firebolt!"
    ShowRoomDialog 453
    End
Room21V1Chain20:
    @ "Anyone got any Toothflossing Stringmints for after the Christmas feast?"
    ShowRoomDialog 472
    End
Room21V1Chain21:
    @ "Great! It's time for the Christmas feast!"
    ShowRoomDialog 469
    End
Room21V1Chain22:
    @ "When's the next feast going to be, anyway?"
    ShowRoomDialog 515
    End
Room21V1Chain23:
    @ "Is it true Sirius Black tried to stab Ron Weasley?"
    ShowRoomDialog 517
    End
Room21V1Chain24:
    @ "I heard that Sirius Black was seen in Gryffindor Tower!"
    ShowRoomDialog 516
    End
Room21V1Chain25:
    @ "Poor Buckbeak..."
    ShowRoomDialog 540
    End
Room21V1Chain26:
    @ "It's all Malfoy's fault!"
    ShowRoomDialog 541
    End
Room21V1Chain27:
    @ "Locked."
    ShowRoomDialog 624
    End
Room21V1Chain28:
    @ "Looking for a new robe? Fred and George will sell you one - try their shop on the seventh floor."
    ShowRoomDialog 630
    End
Room21V1Chain29:
    @ "Have you visited Madam Pomfrey in the hospital wing on the fourth floor?"
    ShowRoomDialog 636
    End
Room21V1Chain30:
    @ "There are portraits on the different floors that will help you get around Hogwarts more quickly."
    ShowRoomDialog 643
    End
Room21V1Chain31:
    GotoIfQuestStateCompare 249, 0, 1, Room21V1Chain39_id, 0, Room21V1Group5_id, 0
    End
Room21V1Chain32:
    @ "All the portraits seem a little nervous..."
    ShowRoomDialog 367
    End
Room21V1Chain33:
    @ "I wonder why the portraits are so nervous?"
    ShowRoomDialog 368
    End
Room21V1Chain34:
    StartObjectAnimSequence Room21V1Group7_id, 0, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group7_id, 1, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain35:
    StartObjectAnimSequence Room21V1Group1_id, 0, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group1_id, 1, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain36:
    StartObjectAnimSequence Room21V1Group2_id, 0, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group2_id, 1, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain37:
    StartObjectAnimSequence Room21V1Group3_id, 0, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group3_id, 1, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain38:
    StartObjectAnimSequence Room21V1Group4_id, 0, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group4_id, 1, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain39:
    StartObjectAnimSequence Room21V1Group5_id, 1, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group5_id, 2, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain40:
    StartObjectAnimSequence Room21V1Group9_id, 0, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group9_id, 1, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain41:
    StartObjectAnimSequence Room21V1Group10_id, 1, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group10_id, 0, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain42:
    StartObjectAnimSequence Room21V1Group11_id, 0, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    End
Room21V1Chain43:
    StartObjectAnimSequence Room21V1Group12_id, 0, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
Room21V1Chain44:
    StartObjectAnimSequence Room21V1Group13_id, 0, 0, 0, Room21V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room21V1Group13_id, 1, 0, 0, Room21V1Route1_id, 2, 0, 0, 0, 0
    End
    EndSubBlock Room21V1End

    .include "asm/room_blob.inc"

Room22Blob:
    RoomBlob 3
    PlayerEntry 119, 153, 0, 4
    PlayerEntry 448, 170, 1, 0
    PlayerEntry 87, 370, 3, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room22V0
    VariantEntry Room22V1

    SubBlock Room22V0, 1, Room22V0Routes, Room22V0Chains, Room22V0End
    OffsetTable Room22V0Groups, 1
    Offsets Room22V0Group0
    EndTable
    Group Room22V0Group0, 5
    DoorAlt 116, 108, half_width=21, half_height=9, destination_room=31, exit_param=5
    Chest 316, 131, flag_id=71, reward_id=131
    Chest 595, 506, flag_id=72, reward_id=115
    Door 29, 368, half_width=13, half_height=40, destination_room=37
    Door 447, 219, half_width=38, half_height=20, destination_room=30, exit_param=6
    OffsetTable Room22V0Routes, 0
    EndTable
    OffsetTable Room22V0Chains, 1
    Offsets Room22V0Chain0
    EndTable
Room22V0Chain0:
    SetQuestState 5, QUEST_CASTLE_AREA
    SetDefeatWarpSelector 2 @ Hospital Wing
    End
    EndSubBlock Room22V0End

    SubBlock Room22V1, 1, Room22V1Routes, Room22V1Chains, Room22V1End
    OffsetTable Room22V1Groups, 14, 1
    Offsets Room22V1Group0, Room22V1Group1, Room22V1Group2, Room22V1Group3, Room22V1Group4, Room22V1Group5
    Offsets Room22V1Group6, Room22V1Group7, Room22V1Group8, Room22V1Group9, Room22V1Group10, Room22V1Group11
    Offsets Room22V1Group12, Room22V1Group13
    EndTable
    Group Room22V1Group0, 0
.ifdef VERSION_JP
    Group Room22V1Group1, 2
.else
    Group Room22V1Group1, 3
    TriggerZone 116, 122, half_width=29, half_height=29, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room22V1Chain1_id
.endif
    Npc 90, 224, sprite=40, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain32_id
    Npc 556, 440, sprite=62, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain33_id
    Group Room22V1Group2, 2
    Npc 86, 217, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain4_id
    Npc 559, 448, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain5_id
    Group Room22V1Group3, 2
    Npc 87, 196, sprite=51, facing=6, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain6_id
    Npc 558, 299, sprite=53, facing=6, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain7_id
    Group Room22V1Group4, 2
    Npc 86, 429, sprite=56, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain8_id
    Npc 558, 389, sprite=54, facing=2, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain9_id
    Group Room22V1Group5, 2
    Npc 85, 195, sprite=57, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain10_id
    Npc 560, 276, sprite=62, facing=6, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain11_id
    Group Room22V1Group6, 2
    Npc 85, 439, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain12_id
    Npc 560, 468, sprite=60, facing=0, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain13_id
    Group Room22V1Group7, 2
    Npc 86, 441, sprite=57, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain2_id
    Npc 560, 235, sprite=55, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain3_id
    Group Room22V1Group8, 2
    Npc 85, 325, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain15_id
    Npc 560, 288, sprite=49, facing=2, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain16_id
    Group Room22V1Group9, 2
    Npc 90, 460, sprite=43, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain18_id
    Npc 556, 444, sprite=53, facing=6, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain19_id
    Group Room22V1Group10, 2
    Npc 557, 289, sprite=60, facing=6, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain21_id
    Npc 91, 445, sprite=54, facing=6, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain20_id
    Group Room22V1Group11, 1
    Npc 91, 437, sprite=41, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain22_id
    Group Room22V1Group12, 2
    Npc 556, 239, sprite=59, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain24_id
    Npc 91, 178, sprite=40, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain23_id
    Group Room22V1Group13, 2
    Npc 89, 480, sprite=61, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain25_id
    Npc 556, 471, sprite=51, facing=4, interact_cooldown=3, interact_mode=1, chain=Room22V1Chain26_id
    OffsetTable Room22V1Routes, 1
    Offsets Room22V1Route0
    EndTable
Room22V1Route0:
    Route 12
    Waypoint 85, 155
    Waypoint 85, 530
    Waypoint 610, 530
    Waypoint 610, 185
    Waypoint 560, 185
    Waypoint 560, 515
    Waypoint 105, 515
    Waypoint 105, 160
    Waypoint 480, 160
    Waypoint 480, 130
    Waypoint 310, 130
    Waypoint 310, 155
    OffsetTable Room22V1Chains, 45, 1
    Offsets Room22V1Chain0, Room22V1Chain1, Room22V1Chain2, Room22V1Chain3, Room22V1Chain4, Room22V1Chain5
    Offsets Room22V1Chain6, Room22V1Chain7, Room22V1Chain8, Room22V1Chain9, Room22V1Chain10, Room22V1Chain11
    Offsets Room22V1Chain12, Room22V1Chain13, Room22V1Chain14, Room22V1Chain15, Room22V1Chain16, Room22V1Chain17
    Offsets Room22V1Chain18, Room22V1Chain19, Room22V1Chain20, Room22V1Chain21, Room22V1Chain22, Room22V1Chain23
    Offsets Room22V1Chain24, Room22V1Chain25, Room22V1Chain26, Room22V1Chain27, Room22V1Chain28, Room22V1Chain29
    Offsets Room22V1Chain30, Room22V1Chain31, Room22V1Chain32, Room22V1Chain33, Room22V1Chain34, Room22V1Chain35
    Offsets Room22V1Chain36, Room22V1Chain37, Room22V1Chain38, Room22V1Chain39, Room22V1Chain40, Room22V1Chain41
    Offsets Room22V1Chain42, Room22V1Chain43, Room22V1Chain44
    EndTable
Room22V1Chain0:
    GotoIfStoryStageCompare 0, 0, Room22V1Chain34_id, 0, Room22V1Group7_id, 0
    GotoIfStoryStageCompare 0, 1, Room22V1Chain35_id, 0, Room22V1Group2_id, 0
    GotoIfStoryStageCompare 0, 2, Room22V1Chain36_id, 0, Room22V1Group3_id, 0
    GotoIfStoryStageCompare 0, 4, Room22V1Chain37_id, 0, Room22V1Group4_id, 0
    GotoIfStoryStageCompare 0, 5, Room22V1Chain38_id, 0, Room22V1Group5_id, 0
    GotoIfStoryStageCompare 0, 6, Room22V1Chain31_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room22V1Chain17_id, 0, Room22V1Group8_id, 0
    GotoIfStoryStageCompare 0, 8, Room22V1Chain14_id, 0, Room22V1Group6_id, 0
    GotoIfStoryStageCompare 0, 15, Room22V1Chain40_id, 0, Room22V1Group9_id, 0
    GotoIfStoryStageCompare 0, 16, Room22V1Chain41_id, 0, Room22V1Group10_id, 0
    GotoIfStoryStageCompare 0, 17, Room22V1Chain42_id, 0, Room22V1Group11_id, 0
    GotoIfStoryStageCompare 0, 18, Room22V1Chain42_id, 0, Room22V1Group11_id, 0
    GotoIfStoryStageCompare 0, 20, Room22V1Chain43_id, 0, Room22V1Group12_id, 0
    GotoIfStoryStageCompare 0, 21, Room22V1Chain44_id, 0, Room22V1Group13_id, 0
    End
Room22V1Chain1:
    @ "Has Sir Cadogan come this way?"
    @ "No, I'm afraid he hasn't."
    ShowRoomDialog 380
    End
Room22V1Chain2:
    @ "Hi, Harry! Welcome back!"
    ShowRoomDialog 192
    End
Room22V1Chain3:
    @ "I just got sorted into Gryffindor. I think the common room is on the seventh floor¸"
    ShowRoomDialog 194
    End
Room22V1Chain4:
    @ "Transfiguration class is held on the first floor."
    ShowRoomDialog 212
    End
Room22V1Chain5:
    @ "I can't find the Transfiguration classroom. I heard it was on the first floor¸"
    ShowRoomDialog 213
    End
Room22V1Chain6:
    @ "This would be a nice day to have a class outside."
    ShowRoomDialog 237
    End
Room22V1Chain7:
    @ "Hagrid's a natural to teach Care of Magical Creatures - don't you think?"
    ShowRoomDialog 239
    End
Room22V1Chain8:
    @ "I much prefer Potions to Transfiguration."
    ShowRoomDialog 325
    End
Room22V1Chain9:
    @ "Shouldn't you be on your way to the Potions classroom? It's in the dungeons - off the Entrance Hall."
    ShowRoomDialog 326
    End
Room22V1Chain10:
    @ "The staff room's next to the Entrance Hall."
    ShowRoomDialog 331
    End
Room22V1Chain11:
    @ "The staff room? Didn't Professor Binns fall asleep in there once?"
    ShowRoomDialog 332
    End
Room22V1Chain12:
    @ "The library? You'll need to go to the second floor."
    ShowRoomDialog 626
    End
Room22V1Chain13:
    @ "The library's quite large - and it's got upper and lower levels..."
    ShowRoomDialog 631
    End
Room22V1Chain14:
    StartObjectAnimSequence Room22V1Group6_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group6_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain15:
    @ "The Defense Against the Dark Arts class is on the third floor."
    ShowRoomDialog 327
    End
Room22V1Chain16:
    @ "The Defense Against the Dark Arts classroom's on the third floor."
    ShowRoomDialog 333
    End
Room22V1Chain17:
    StartObjectAnimSequence Room22V1Group8_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group8_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain18:
    @ "I'd love to ride a Firebolt!"
    ShowRoomDialog 453
    End
Room22V1Chain19:
    @ "If our Quidditch team all had Firebolts, they'd make mincemeat of everyone!"
    ShowRoomDialog 454
    End
Room22V1Chain20:
    @ "Christmas or Halloween... I don't know which feast I like best."
    ShowRoomDialog 474
    End
Room22V1Chain21:
    @ "I love the Christmas feast!"
    ShowRoomDialog 466
    End
Room22V1Chain22:
    @ "Zonko's is definitely the best shop in Hogsmeade."
    ShowRoomDialog 514
    End
Room22V1Chain23:
    @ "Security's really been stepped up, hasn't it?"
    ShowRoomDialog 518
    End
Room22V1Chain24:
    @ "I'm really glad Gryffindor beat Slytherin."
    ShowRoomDialog 512
    End
Room22V1Chain25:
    @ "Hippogriffs aren't dangerous unless you provoke them!"
    ShowRoomDialog 542
    End
Room22V1Chain26:
    @ "Malfoy provoked Buckbeak!"
    ShowRoomDialog 543
    End
Room22V1Chain27:
    @ "Locked."
    ShowRoomDialog 624
    End
Room22V1Chain28:
    @ "Did you know that you can visit our shop on the seventh floor? You can buy items from George and me at very reasonable prices..."
    ShowRoomDialog 638
    End
Room22V1Chain29:
    @ "The hospital wing is on the fourth floor."
    ShowRoomDialog 637
    End
Room22V1Chain30:
    @ "When I'm running late for class, I use the portrait shortcuts to get where I'm going faster."
    ShowRoomDialog 644
    End
Room22V1Chain31:
    GotoIfQuestStateCompare 249, 0, 1, Room22V1Chain39_id, 0, Room22V1Group1_id, 0
    End
Room22V1Chain32:
    @ "The portraits are looking rather shifty at the moment..."
    ShowRoomDialog 369
    End
Room22V1Chain33:
    @ "The portraits are making me nervous..."
    ShowRoomDialog 370
    End
Room22V1Chain34:
    StartObjectAnimSequence Room22V1Group7_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group7_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain35:
    StartObjectAnimSequence Room22V1Group2_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group2_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain36:
    StartObjectAnimSequence Room22V1Group3_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group3_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain37:
    StartObjectAnimSequence Room22V1Group4_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group4_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain38:
    StartObjectAnimSequence Room22V1Group5_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group5_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain39:
.ifdef VERSION_JP
    StartObjectAnimSequence Room22V1Group1_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group1_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
.else
    StartObjectAnimSequence Room22V1Group1_id, 1, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group1_id, 2, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
.endif
    End
Room22V1Chain40:
    StartObjectAnimSequence Room22V1Group9_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group9_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain41:
    StartObjectAnimSequence Room22V1Group10_id, 1, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group10_id, 0, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain42:
    StartObjectAnimSequence Room22V1Group11_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    End
Room22V1Chain43:
    StartObjectAnimSequence Room22V1Group12_id, 1, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group12_id, 0, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
Room22V1Chain44:
    StartObjectAnimSequence Room22V1Group13_id, 0, 0, 0, Room22V1Route0_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room22V1Group13_id, 1, 0, 0, Room22V1Route0_id, 5, 0, 0, 0, 0
    End
    EndSubBlock Room22V1End

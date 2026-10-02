    .include "asm/room_blob.inc"

Room30Blob:
    RoomBlob 7
    PlayerEntry 272, 836, 0, 0
    PlayerEntry 428, 227, 1, 3
    PlayerEntry 263, 242, 2, 0
    PlayerEntry 432, 613, 3, 0
    PlayerEntry 276, 617, 4, 0
    PlayerEntry 280, 585, 5, 0
    PlayerEntry 132, 406, 6, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room30V0
    VariantEntry Room30V1

    SubBlock Room30V0, 1, Room30V0Routes, Room30V0Chains, Room30V0End
    OffsetTable Room30V0Groups, 1
    Offsets Room30V0Group0
    EndTable
    Group Room30V0Group0, 6
    Door 271, 870, half_width=26, half_height=12, destination_room=16, exit_param=1
    Door 445, 197, half_width=17, half_height=8, destination_room=24, exit_param=1
    Door 245, 218, half_width=21, half_height=6, destination_room=23, exit_param=1
    Door 463, 600, half_width=14, half_height=11, destination_room=20, exit_param=1
    Door 94, 382, half_width=24, half_height=11, destination_room=22, exit_param=1
    Door 239, 603, half_width=20, half_height=16, destination_room=19, exit_param=1
    OffsetTable Room30V0Routes, 0
    EndTable
    OffsetTable Room30V0Chains, 1
    Offsets Room30V0Chain0
    EndTable
Room30V0Chain0:
    ShowBackgroundLayer 0, 255, 255, 255
    SetBackgroundBlendLayers 1, 0, 1, 0
    SetBackgroundPriority 0, 0, 255, 255
    End
    EndSubBlock Room30V0End

    SubBlock Room30V1, 1, Room30V1Routes, Room30V1Chains, Room30V1End
    OffsetTable Room30V1Groups, 14, 1
    Offsets Room30V1Group0, Room30V1Group1, Room30V1Group2, Room30V1Group3, Room30V1Group4, Room30V1Group5
    Offsets Room30V1Group6, Room30V1Group7, Room30V1Group8, Room30V1Group9, Room30V1Group10, Room30V1Group11
    Offsets Room30V1Group12, Room30V1Group13
    EndTable
    Group Room30V1Group0, 0
    Group Room30V1Group1, 2
    Npc 145, 395, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain13_id, arg_0f=0
    Npc 179, 709, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain14_id, arg_0f=0
    Group Room30V1Group2, 2
    Npc 259, 728, sprite=51, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain15_id, arg_0f=0
    Npc 254, 263, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain16_id, arg_0f=0
    Group Room30V1Group3, 3
    Npc 325, 741, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain17_id, arg_0f=0
    Npc 287, 246, sprite=56, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain18_id, arg_0f=0
    Npc 117, 424, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain19_id, arg_0f=0
    Group Room30V1Group4, 3
    Npc 148, 734, sprite=57, facing=2, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain20_id, arg_0f=0
    Npc 403, 609, sprite=62, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain21_id, arg_0f=0
    Npc 205, 287, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain23_id, arg_0f=0
    Group Room30V1Group5, 6
    TriggerZone 227, 275, half_width=19, half_height=20, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room30V1Chain10_id
    TriggerZone 148, 399, half_width=18, half_height=22, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room30V1Chain2_id
    TriggerZone 168, 352, half_width=18, half_height=16, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room30V1Chain4_id
    TriggerZone 200, 311, half_width=24, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room30V1Chain5_id
    TriggerZone 356, 225, half_width=25, half_height=15, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room30V1Chain7_id
    TriggerZone 318, 621, half_width=28, half_height=27, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room30V1Chain10_id
    Group Room30V1Group6, 2
    Npc 408, 603, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain11_id, arg_0f=0
    Npc 287, 244, sprite=53, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain12_id, arg_0f=0
    Group Room30V1Group7, 2
    Npc 420, 238, sprite=39, facing=6, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain24_id, arg_0f=0
    Npc 267, 716, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain26_id, arg_0f=0
    Group Room30V1Group8, 2
    Npc 158, 744, sprite=60, facing=2, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain27_id, arg_0f=0
    Npc 396, 219, sprite=57, facing=6, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain28_id, arg_0f=0
    Group Room30V1Group9, 2
    Npc 273, 754, sprite=61, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain29_id, arg_0f=0
    Npc 216, 273, sprite=44, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain30_id, arg_0f=0
    Group Room30V1Group10, 2
    Npc 399, 604, sprite=58, facing=2, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain31_id, arg_0f=0
    Npc 300, 241, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain32_id, arg_0f=0
    Group Room30V1Group11, 2
    Npc 157, 760, sprite=54, facing=2, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain33_id, arg_0f=0
    Npc 124, 423, sprite=55, facing=2, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain34_id, arg_0f=0
    Group Room30V1Group12, 2
    Npc 238, 735, sprite=46, facing=6, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain35_id, arg_0f=0
    Npc 148, 363, sprite=49, facing=2, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain36_id, arg_0f=0
    Group Room30V1Group13, 2
    Npc 214, 663, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain37_id, arg_0f=0
    Npc 388, 213, sprite=58, facing=4, interact_cooldown=3, interact_mode=1, chain=Room30V1Chain38_id, arg_0f=0
    OffsetTable Room30V1Routes, 0
    EndTable
    OffsetTable Room30V1Chains, 39, 1
    Offsets Room30V1Chain0, Room30V1Chain1, Room30V1Chain2, Room30V1Chain3, Room30V1Chain4, Room30V1Chain5
    Offsets Room30V1Chain6, Room30V1Chain7, Room30V1Chain8, Room30V1Chain9, Room30V1Chain10, Room30V1Chain11
    Offsets Room30V1Chain12, Room30V1Chain13, Room30V1Chain14, Room30V1Chain15, Room30V1Chain16, Room30V1Chain17
    Offsets Room30V1Chain18, Room30V1Chain19, Room30V1Chain20, Room30V1Chain21, Room30V1Chain22, Room30V1Chain23
    Offsets Room30V1Chain24, Room30V1Chain25, Room30V1Chain26, Room30V1Chain27, Room30V1Chain28, Room30V1Chain29
    Offsets Room30V1Chain30, Room30V1Chain31, Room30V1Chain32, Room30V1Chain33, Room30V1Chain34, Room30V1Chain35
    Offsets Room30V1Chain36, Room30V1Chain37, Room30V1Chain38
    EndTable
Room30V1Chain0:
    GotoIfStoryStageCompare 0, 0, 0, 0, Room30V1Group6_id, 0
    GotoIfStoryStageCompare 0, 1, 0, 0, Room30V1Group1_id, 0
    GotoIfStoryStageCompare 0, 2, 0, 0, Room30V1Group2_id, 0
    GotoIfStoryStageCompare 0, 4, 0, 0, Room30V1Group3_id, 0
    GotoIfStoryStageCompare 0, 5, 0, 0, Room30V1Group4_id, 0
    GotoIfStoryStageCompare 0, 6, Room30V1Chain25_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room30V1Chain25_id, 0, Room30V1Group7_id, 0
    GotoIfStoryStageCompare 0, 8, 0, 0, Room30V1Group8_id, 0
    GotoIfStoryStageCompare 0, 15, 0, 0, Room30V1Group9_id, 0
    GotoIfStoryStageCompare 0, 16, 0, 0, Room30V1Group10_id, 0
    GotoIfStoryStageCompare 0, 17, 0, 0, Room30V1Group11_id, 0
    GotoIfStoryStageCompare 0, 18, 0, 0, Room30V1Group11_id, 0
    GotoIfStoryStageCompare 0, 20, 0, 0, Room30V1Group12_id, 0
    GotoIfStoryStageCompare 0, 21, 0, 0, Room30V1Group13_id, 0
    End
Room30V1Chain1:
    @ "Has Sir Cadogan come this way?"
    @ "No, I'm afraid he hasn't."
    ShowRoomDialog 380
    End
Room30V1Chain2:
    @ "Has Sir Cadogan come this way?"
    @ "Sorry, no."
    ShowRoomDialog 381
    End
Room30V1Chain3:
    @ "Has Sir Cadogan come this way?"
    @ "Don't know anyone by that name."
    ShowRoomDialog 382
    End
Room30V1Chain4:
    @ "Has Sir Cadogan come this way?"
    @ "No, he hasn't."
    ShowRoomDialog 383
    End
Room30V1Chain5:
    @ "Has Sir Cadogan come this way?"
    @ "I'm afraid not."
    ShowRoomDialog 384
    End
Room30V1Chain6:
    @ "Has Sir Cadogan come this way?"
    @ "That daft knight? No, I'm afraid not."
    ShowRoomDialog 385
    End
Room30V1Chain7:
    @ "Has Sir Cadogan come this way?"
    @ "Ah, yes. I believe he's down on the lower levels."
    ShowRoomDialog 386
    End
Room30V1Chain8:
    @ "Has Sir Cadogan come this way?"
    @ "Yes. Took a dive into the portrait room."
    ShowRoomDialog 387
    End
Room30V1Chain9:
    @ "Has Sir Cadogan come this way?"
    @ "Indeed. Saw him dash into the Grand Staircase."
    ShowRoomDialog 388
    End
Room30V1Chain10:
    @ "Has Sir Cadogan come this way?"
    @ "He's on the second floor. And would you kindly ask him to stay there?"
    ShowRoomDialog 389
    End
Room30V1Chain11:
    @ "The Gryffindor common room is on the seventh floor. Just like last year."
    ShowRoomDialog 187
    End
Room30V1Chain12:
    @ "I heard that the Gryffindor common room is on the seventh floor."
    ShowRoomDialog 189
    End
Room30V1Chain13:
    @ "Transfiguration class is held on the first floor."
    ShowRoomDialog 212
    End
Room30V1Chain14:
    ShowRoomDialog 210
    End
Room30V1Chain15:
    @ "This would be a nice day to have a class outside."
    ShowRoomDialog 237
    End
Room30V1Chain16:
    @ "Hagrid's a natural to teach Care of Magical Creatures - don't you think?"
    ShowRoomDialog 239
    End
Room30V1Chain17:
    @ "Potions? It's held down in the dungeons."
    ShowRoomDialog 324
    End
Room30V1Chain18:
    @ "I much prefer Potions to Transfiguration."
    ShowRoomDialog 325
    End
Room30V1Chain19:
    @ "Shouldn't you be on your way to the Potions classroom? It's in the dungeons - off the Entrance Hall."
    ShowRoomDialog 326
    End
Room30V1Chain20:
    @ "The staff room's next to the Entrance Hall."
    ShowRoomDialog 331
    End
Room30V1Chain21:
    @ "The staff room? Didn't Professor Binns fall asleep in there once?"
    ShowRoomDialog 332
    End
Room30V1Chain22:
    End
Room30V1Chain23:
    @ "I wonder if the new Defense Against the Dark Arts teacher will be as good-looking as Professor Lockhart."
    ShowRoomDialog 334
    End
Room30V1Chain24:
    @ "The Defense Against the Dark Arts class is on the third floor."
    ShowRoomDialog 327
    End
Room30V1Chain25:
    GotoIfQuestStateCompare 249, 0, 1, 0, 0, Room30V1Group5_id, 0
    End
Room30V1Chain26:
    @ "The Defense Against the Dark Arts classroom's on the third floor."
    ShowRoomDialog 333
    End
Room30V1Chain27:
    @ "The library's quite large - and it's got upper and lower levels..."
    ShowRoomDialog 631
    End
Room30V1Chain28:
    @ "Madam Pince's desk is in the library."
    ShowRoomDialog 627
    End
Room30V1Chain29:
    @ "I dream about Firebolts!"
    ShowRoomDialog 451
    End
Room30V1Chain30:
    @ "I touched a Firebolt once and I didn't wash my hands for two weeks!"
    ShowRoomDialog 456
    End
Room30V1Chain31:
    @ "I hope there are crackers at the Christmas feast."
    ShowRoomDialog 468
    End
Room30V1Chain32:
    @ "I've heard we'll be playing a game at this year's Christmas feast."
    ShowRoomDialog 471
    End
Room30V1Chain33:
    @ "I'm still stuffed from the Christmas feast!"
    ShowRoomDialog 511
    End
Room30V1Chain34:
    @ "When's the next feast going to be, anyway?"
    ShowRoomDialog 515
    End
Room30V1Chain35:
    @ "I heard that Sirius Black was seen in Gryffindor Tower!"
    ShowRoomDialog 516
    End
Room30V1Chain36:
    @ "Is it true Sirius Black tried to stab Ron Weasley?"
    ShowRoomDialog 517
    End
Room30V1Chain37:
    @ "I've heard they're going to execute Buckbeak!"
    ShowRoomDialog 534
    End
Room30V1Chain38:
    @ "It's a real shame about Buckbeak."
    ShowRoomDialog 539
    End
    EndSubBlock Room30V1End

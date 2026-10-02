    .include "asm/room_blob.inc"

Room24Blob:
    RoomBlob 5
    PlayerEntry 628, 219, 0, 4
    PlayerEntry 882, 219, 1, 0
    PlayerEntry 1046, 283, 3, 6
    PlayerEntry 1035, 472, 4, 6
    PlayerEntry 245, 515, 5, 0
    StageIndex 4
    StageToVariant 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2
    VariantEntry Room24V0
    VariantEntry Room24V1
    VariantEntry Room24V2
    VariantEntry Room24V3

    SubBlock Room24V0, 1, Room24V0Routes, Room24V0Chains, Room24V0End
    OffsetTable Room24V0Groups, 1
    Offsets Room24V0Group0
    EndTable
    Group Room24V0Group0, 5
    Door 896, 271, half_width=52, half_height=13, destination_room=30, exit_param=1
    DoorAlt 628, 178, half_width=18, half_height=11, destination_room=31, exit_param=7
    Chest 415, 215, flag_id=51, reward_id=61
    Chest 908, 446, flag_id=52, reward_id=81
    Door 1089, 473, half_width=14, half_height=41, destination_room=36
    OffsetTable Room24V0Routes, 0
    EndTable
    OffsetTable Room24V0Chains, 1
    Offsets Room24V0Chain0
    EndTable
Room24V0Chain0:
    SetQuestState 7, 17
    SetBattleDefeatState 2
    End
    EndSubBlock Room24V0End

    SubBlock Room24V1, 1, Room24V1Routes, Room24V1Chains, Room24V1End
    OffsetTable Room24V1Groups, 25, 1
    Offsets Room24V1Group0, Room24V1Group1, Room24V1Group2, Room24V1Group3, Room24V1Group4, Room24V1Group5
    Offsets Room24V1Group6, Room24V1Group7, Room24V1Group8, Room24V1Group9, Room24V1Group10, Room24V1Group11
    Offsets Room24V1Group12, Room24V1Group13, Room24V1Group14, Room24V1Group15, Room24V1Group16, Room24V1Group17
    Offsets Room24V1Group18, Room24V1Group19, Room24V1Group20, Room24V1Group21, Room24V1Group22, Room24V1Group23
    Offsets Room24V1Group24
    EndTable
    Group Room24V1Group0, 2
    Door 240, 467, half_width=27, half_height=16, destination_room=29
    Prop 200, 447, kind=59
    Group Room24V1Group1, 10
    Npc 190, 507, sprite=39, facing=2, arg_0f=0
    Npc 197, 525, sprite=63, facing=2, arg_0f=0
    Npc 214, 554, sprite=47, facing=0, arg_0f=0
    Npc 231, 570, sprite=55, facing=0, arg_0f=0
    Npc 252, 564, sprite=51, facing=0, arg_0f=0
    Npc 295, 504, sprite=59, facing=6, arg_0f=0
    Npc 317, 512, sprite=26, facing=6, arg_0f=0
    TriggerZone 578, 225, half_width=104, half_height=48, chain=Room24V1Chain20_id
    TriggerZone 833, 572, half_width=127, half_height=67, chain=Room24V1Chain19_id
    Npc 378, 525, sprite=34, facing=6
    Group Room24V1Group2, 1
    Npc 302, 540, sprite=31, facing=2
    Group Room24V1Group3, 3
    TriggerZone 796, 223, half_width=13, half_height=37, chain=Room24V1Chain8_id
    TriggerZone 985, 397, half_width=56, half_height=13, chain=Room24V1Chain9_id
    Npc 1018, 218, sprite=33, facing=2
    Group Room24V1Group4, 2
    Npc 410, 225, sprite=4, facing=4
    Npc 650, 555, sprite=4, facing=6
    Group Room24V1Group5, 4
    TriggerZone 595, 220, half_width=16, half_height=48, chain=Room24V1Chain18_id
    TriggerZone 854, 575, half_width=15, half_height=59, chain=Room24V1Chain18_id
    TriggerZone 525, 574, half_width=23, half_height=55, chain=Room24V1Chain63_id
    TriggerZone 422, 351, half_width=52, half_height=19, chain=Room24V1Chain64_id
    Group Room24V1Group6, 1
    Npc 415, 545, sprite=32, facing=6
    Group Room24V1Group7, 1
    Npc 235, 487, sprite=33, facing=4
    Group Room24V1Group8, 2
    Npc 430, 277, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain25_id
    Npc 1001, 510, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain26_id
    Group Room24V1Group9, 2
    Npc 430, 342, sprite=51, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain29_id
    Npc 1001, 314, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain30_id
    Group Room24V1Group10, 2
    Npc 430, 502, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain31_id
    Npc 1002, 532, sprite=39, facing=0, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain32_id
    Group Room24V1Group11, 2
    Npc 430, 410, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain33_id
    Npc 1000, 282, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain34_id
    Group Room24V1Group12, 5
    TriggerZone 1041, 555, half_width=33, half_height=37, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room24V1Chain56_id
    TriggerZone 805, 534, half_width=31, half_height=31, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room24V1Chain57_id
    TriggerZone 688, 535, half_width=36, half_height=33, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room24V1Chain58_id
    TriggerZone 550, 532, half_width=30, half_height=36, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room24V1Chain59_id
    TriggerZone 243, 494, half_width=37, half_height=11, trigger_kind=1, chain=Room24V1Chain5_id
    Group Room24V1Group13, 3
    Npc 461, 233, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain37_id
    Npc 900, 519, sprite=39, facing=2, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain36_id
    Prop 205, 449, kind=85, arg_0e=0
    Group Room24V1Group14, 2
    Npc 430, 520, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain27_id
    Npc 1002, 528, sprite=49, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain55_id
    Group Room24V1Group15, 3
    Npc 430, 561, sprite=39, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain39_id
    Npc 1001, 580, sprite=49, facing=2, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain40_id
    Prop 205, 449, kind=85, arg_0e=0
    Group Room24V1Group16, 3
    Npc 430, 361, sprite=59, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain42_id
    Npc 997, 244, sprite=45, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain43_id
    Prop 205, 449, kind=85, arg_0e=0
    Group Room24V1Group17, 3
    Npc 430, 421, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain44_id
    Npc 1000, 309, sprite=41, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain45_id
    Prop 205, 449, kind=85, arg_0e=0
    Group Room24V1Group18, 3
    Npc 430, 264, sprite=54, facing=6, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain46_id
    Npc 1000, 509, sprite=55, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain47_id
    Prop 205, 449, kind=85, arg_0e=0
    Group Room24V1Group19, 1
    Npc 430, 247, sprite=59, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain48_id
    Group Room24V1Group20, 2
    Npc 430, 471, sprite=47, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain50_id
    Npc 1000, 528, sprite=54, facing=4, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain51_id
    Group Room24V1Group21, 2
    Prop 205, 449, kind=85, arg_0e=0
    TriggerZone 245, 495, half_width=0, half_height=0
    Group Room24V1Group22, 1
    Prop 205, 449, kind=85, arg_0e=0
    Group Room24V1Group23, 2
    Npc 429, 281, sprite=45, facing=0, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain66_id
    Npc 1001, 311, sprite=47, facing=0, interact_cooldown=3, interact_mode=1, chain=Room24V1Chain67_id
    Group Room24V1Group24, 1
    TriggerZone 342, 542, half_width=21, half_height=72, chain=Room24V1Chain79_id
    OffsetTable Room24V1Routes, 24
    Offsets Room24V1Route0, Room24V1Route1, Room24V1Route2, Room24V1Route3, Room24V1Route4, Room24V1Route5
    Offsets Room24V1Route6, Room24V1Route7, Room24V1Route8, Room24V1Route9, Room24V1Route10, Room24V1Route11
    Offsets Room24V1Route12, Room24V1Route13, Room24V1Route14, Room24V1Route15, Room24V1Route16, Room24V1Route17
    Offsets Room24V1Route18, Room24V1Route19, Room24V1Route20, Room24V1Route21, Room24V1Route22, Room24V1Route23
    EndTable
Room24V1Route0:
    Route 2
    Waypoint 390, 540
    Waypoint 285, 540
Room24V1Route1:
    Route 2
    Waypoint 378, 525
    Waypoint 290, 525
Room24V1Route2:
    Route 2
    Waypoint 377, 560
    Waypoint 273, 560, on_arrival_chain=Room24V1Chain23_id
Room24V1Route3:
    Route 2
    Waypoint 290, 525
    Waypoint 298, 525
Room24V1Route4:
    Route 2
    Waypoint 275, 560
    Waypoint 302, 560, on_arrival_chain=Room24V1Chain4_id
Room24V1Route5:
    Route 2
    Waypoint 245, 514
    Waypoint 245, 522, on_arrival_chain=Room24V1Chain6_id
Room24V1Route6:
    Route 2
    Waypoint 840, 233
    Waypoint 995, 233, on_arrival_chain=Room24V1Chain7_id
Room24V1Route7:
    Route 2
    Waypoint 1000, 350
    Waypoint 995, 233, on_arrival_chain=Room24V1Chain7_id
Room24V1Route8:
    Route 3
    Waypoint 1018, 218
    Waypoint 880, 218
    Waypoint 880, 110, on_arrival_chain=Room24V1Chain11_id
Room24V1Route9:
    Route 3
    Waypoint 995, 233
    Waypoint 890, 233
    Waypoint 890, 204, on_arrival_chain=Room24V1Chain12_id
Room24V1Route10:
    Route 3
    Waypoint 870, 110
    Waypoint 870, 203
    Waypoint 870, 260, on_arrival_chain=Room24V1Chain13_id
Room24V1Route11:
    Route 2
    Waypoint 890, 204
    Waypoint 890, 210, on_arrival_chain=Room24V1Chain14_id
Room24V1Route12:
    Route 2
    Waypoint 650, 565
    Waypoint 850, 565
Room24V1Route13:
    Route 2
    Waypoint 410, 225
    Waypoint 590, 225
Room24V1Route14:
    Route 4
    Waypoint 700, 570
    Waypoint 435, 570
    Waypoint 435, 540
    Waypoint 390, 540, on_arrival_chain=Room24V1Chain21_id
Room24V1Route15:
    Route 3
    Waypoint 415, 230
    Waypoint 415, 540
    Waypoint 390, 540, on_arrival_chain=Room24V1Chain21_id
Room24V1Route16:
    Route 3
    Waypoint 415, 545
    Waypoint 415, 560
    Waypoint 377, 560, on_arrival_chain=Room24V1Chain1_id
Room24V1Route17:
    Route 2
    Waypoint 234, 477
    Waypoint 256, 477, on_arrival_chain=Room24V1Chain3_id
Room24V1Route18:
    Route 6
    Waypoint 430, 232
    Waypoint 430, 560
    Waypoint 900, 560
    Waypoint 900, 465
    Waypoint 980, 465
    Waypoint 980, 232
Room24V1Route19:
    Route 4
    Waypoint 403, 233
    Waypoint 997, 233
    Waypoint 997, 570
    Waypoint 400, 570
Room24V1Route20:
    Route 1
    Waypoint 687, 571
Room24V1Route21:
    Route 3
    Waypoint 570, 570
    Waypoint 625, 570, on_arrival_chain=Room24V1Chain16_id
    Waypoint 851, 570, on_arrival_chain=Room24V1Chain18_id
Room24V1Route22:
    Route 4
    Waypoint 420, 295
    Waypoint 420, 255, on_arrival_chain=Room24V1Chain62_id
    Waypoint 420, 230
    Waypoint 590, 230, on_arrival_chain=Room24V1Chain18_id
Room24V1Route23:
    Route 3
    Waypoint 270, 520
    Waypoint 243, 520
    Waypoint 243, 492, on_arrival_chain=Room24V1Chain78_id
    OffsetTable Room24V1Chains, 81, 1
    Offsets Room24V1Chain0, Room24V1Chain1, Room24V1Chain2, Room24V1Chain3, Room24V1Chain4, Room24V1Chain5
    Offsets Room24V1Chain6, Room24V1Chain7, Room24V1Chain8, Room24V1Chain9, Room24V1Chain10, Room24V1Chain11
    Offsets Room24V1Chain12, Room24V1Chain13, Room24V1Chain14, Room24V1Chain15, Room24V1Chain16, Room24V1Chain17
    Offsets Room24V1Chain18, Room24V1Chain19, Room24V1Chain20, Room24V1Chain21, Room24V1Chain22, Room24V1Chain23
    Offsets Room24V1Chain24, Room24V1Chain25, Room24V1Chain26, Room24V1Chain27, Room24V1Chain28, Room24V1Chain29
    Offsets Room24V1Chain30, Room24V1Chain31, Room24V1Chain32, Room24V1Chain33, Room24V1Chain34, Room24V1Chain35
    Offsets Room24V1Chain36, Room24V1Chain37, Room24V1Chain38, Room24V1Chain39, Room24V1Chain40, Room24V1Chain41
    Offsets Room24V1Chain42, Room24V1Chain43, Room24V1Chain44, Room24V1Chain45, Room24V1Chain46, Room24V1Chain47
    Offsets Room24V1Chain48, Room24V1Chain49, Room24V1Chain50, Room24V1Chain51, Room24V1Chain52, Room24V1Chain53
    Offsets Room24V1Chain54, Room24V1Chain55, Room24V1Chain56, Room24V1Chain57, Room24V1Chain58, Room24V1Chain59
    Offsets Room24V1Chain60, Room24V1Chain61, Room24V1Chain62, Room24V1Chain63, Room24V1Chain64, Room24V1Chain65
    Offsets Room24V1Chain66, Room24V1Chain67, Room24V1Chain68, Room24V1Chain69, Room24V1Chain70, Room24V1Chain71
    Offsets Room24V1Chain72, Room24V1Chain73, Room24V1Chain74, Room24V1Chain75, Room24V1Chain76, Room24V1Chain77
    Offsets Room24V1Chain78, Room24V1Chain79, Room24V1Chain80
    EndTable
Room24V1Chain0:
    GotoIfStoryStageCompare 0, 0, Room24V1Chain68_id, 0, Room24V1Group14_id, 0
    GotoIfStoryStageCompare 0, 0, Room24V1Chain80_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 1, Room24V1Chain69_id, 0, Room24V1Group8_id, 0
    GotoIfStoryStageCompare 0, 2, Room24V1Chain70_id, 0, Room24V1Group9_id, 0
    GotoIfStoryStageCompare 0, 4, Room24V1Chain71_id, 0, Room24V1Group10_id, 0
    GotoIfStoryStageCompare 0, 5, Room24V1Chain72_id, 0, Room24V1Group11_id, 0
    GotoIfStoryStageCompare 0, 6, Room24V1Chain35_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room24V1Chain41_id, 0, Room24V1Group15_id, 0
    GotoIfStoryStageCompare 0, 8, Room24V1Chain38_id, 0, Room24V1Group13_id, 0
    GotoIfStoryStageCompare 0, 9, 0, 0, 0, 0
    GotoIfStoryStageCompare 0, 14, 0, 0, Room24V1Group22_id, 0
    GotoIfStoryStageCompare 0, 15, Room24V1Chain74_id, 0, Room24V1Group16_id, 0
    GotoIfStoryStageCompare 0, 16, Room24V1Chain75_id, 0, Room24V1Group17_id, 0
    GotoIfStoryStageCompare 0, 17, Room24V1Chain61_id, 0, Room24V1Group18_id, 0
    GotoIfStoryStageCompare 0, 18, Room24V1Chain61_id, 0, Room24V1Group18_id, 0
    GotoIfStoryStageCompare 0, 19, 0, 0, Room24V1Group21_id, 0
    GotoIfStoryStageCompare 0, 20, Room24V1Chain65_id, 0, Room24V1Group19_id, 0
    GotoIfStoryStageCompare 0, 21, Room24V1Chain77_id, 0, Room24V1Group20_id, 0
    End
Room24V1Chain1:
    ArmChainYield 1
    DespawnTileObject Room24V1Group1_id, 7
    DespawnTileObject Room24V1Group1_id, 8
    SetQuestState 1, 240
    SetQuestState 1, 241
    SetTileObjectFacing Room24V1Group1_id, 9, 4
    @ "Why isn't everyone going into the common room?"
    @ "Oh, my... haven't you heard, Harry?"
    @ "Heard what?"
    @ "Over here!"
    @ "Oh no..."
    @ "The Fat Lady's gone and we can't get into the common room..."
    ShowRoomDialog 373
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room24V1Group1_id, 9, 0, 0, Room24V1Route1_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room24V1Group6_id, 0, 0, 0, Room24V1Route2_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room24V1Group21_id, 1, 0, 0, 1200, 0
    End
Room24V1Chain2:
    ArmChainYield 1
    RespawnRowAndRunChain Room24V1Group21_id, 0
    GotoIfQuestStateCompare 240, 0, 0, 0, 0, Room24V1Group1_id, 0
    End
Room24V1Chain3:
    ArmChainYield 1
    DespawnRoomRowObjects Room24V1Group7_id
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    SetTileObjectFacing 0, 255, 7
    SetTileObjectFacing Room24V1Group6_id, 0, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "We need to find her! Come on, Ron. Harry, why don't you stay here in case she comes back?"
    ShowRoomDialog 374
    @ "OK."
    ShowRoomDialog 375
    ArmChainYield 0
    StartObjectAnimSequence Room24V1Group1_id, 9, 0, 0, Room24V1Route3_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room24V1Group6_id, 0, 0, 0, Room24V1Route4_id, 0, 1, 0, 0, 0
    End
Room24V1Chain4:
    ArmChainYield 1
    SetTileObjectFacing Room24V1Group1_id, 9, 4
    SetTileObjectFacing Room24V1Group6_id, 0, 0
    SetTileObjectFacing 0, 255, 2
    @ "How can we find Sir Cadogan?"
    @ "Let's ask the portraits. Maybe they saw him go by."
    ShowRoomDialog 377
    ArmChainYield 0
    StartTileObjectScript 302, 28, 2, Room24V1Group1_id, 9, 0, 0, 2, 255, 255, 255
    StartTileObjectScript 302, 28, 2, Room24V1Group6_id, 0, 0, 0, 2, 255, 255, 255
    StartTileObjectScript 302, 28, 2, 0, 255, 0, 0, 2, 255, 255, 255
    ArmChainYield 1
    Unk2A 6, 255, 255, 255
    DespawnTileObject Room24V1Group6_id, 0
    DespawnTileObject Room24V1Group1_id, 9
    RecruitPartyFollower 7
    RespawnRowAndRunChain Room24V1Group2_id, 0
    StartTileObjectScript 270, 28, 2, Room24V1Group2_id, 0, 0, 0, 0, 255, 255, 255
    SetQuestState 25, 25
    SetQuestState 1, 249
    RespawnRowAndRunChain Room24V1Group12_id, 0
    RespawnRowAndRunChain Room24V1Group23_id, Room24V1Chain73_id
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room24V1Chain5:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route5_id, 0, 1, 0, 0, 0
    End
Room24V1Chain6:
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room24V1Chain7:
    ArmChainYield 1
    SetTileObjectFacing Room24V1Group3_id, 2, 4
    @ "Have at thee, scurvy knave!"
    @ "The Fat Lady must be in another portrait..."
    @ "Why don't we ask Sir Cadogan? He's bonkers, but he knows all about this floor."
    @ "OK, we have to start somewhere."
    @ "Hello, Sir Cadogan."
    @ "I don't suppose you happened to see the Fat Lady go by here?"
    @ "That I did, fair maiden, and in great distress!"
    @ "Could you help us find her?"
    @ "That I shall, milady, and verily so!"
    ShowRoomDialog 376
    Unk02 0, 255, 3
    Unk02 Room24V1Group3_id, 2, 2
    ArmChainYield 0
    RespawnRowAndRunChain 0, Room24V1Chain10_id
    End
Room24V1Chain8:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route6_id, 0, 1, 0, 0, 0
    End
Room24V1Chain9:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 10, Room24V1Route7_id, 0, 1, 0, 0, 0
    End
Room24V1Chain10:
    StartObjectAnimSequence Room24V1Group3_id, 2, 0, 0, Room24V1Route8_id, 0, 1, 0, 0, 0
    End
Room24V1Chain11:
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route9_id, 0, 1, 0, 0, 0
    End
Room24V1Chain12:
    StartObjectAnimSequence Room24V1Group3_id, 2, 0, 0, Room24V1Route10_id, 0, 1, 0, 0, 0
    End
Room24V1Chain13:
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route11_id, 0, 1, 0, 0, 0
    End
Room24V1Chain14:
    ArmChainYield 1
    DespawnTileObject Room24V1Group3_id, 2
    DespawnTileObject Room24V1Group3_id, 0
    DespawnTileObject Room24V1Group3_id, 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room24V1Chain15:
    RespawnRowAndRunChain Room24V1Group5_id, 0
    RespawnRowAndRunChain Room24V1Group4_id, 0
    Unk02 Room24V1Group4_id, 1, 6
    Unk02 Room24V1Group4_id, 0, 6
    End
Room24V1Chain16:
    PlaySoundById 52
    StartObjectAnimSequence Room24V1Group4_id, 1, 0, 0, Room24V1Route12_id, 0, 1, 0, 0, 0
    End
Room24V1Chain17:
    DespawnRoomRowObjects Room24V1Group4_id
    End
Room24V1Chain18:
    ArmChainYield 1
    PlaySoundById 52
    DelayedRespawnRowAndRunChainFrames 15, 0, 0
    GrantPartyExperience 10, 65535
    PlayRoomSoundEffect 24
    @ "Scabbers! There you are!"
    @ "Let's get back to the common room."
    ShowRoomDialog 357
    DespawnRoomRowObjects Room24V1Group5_id
    DespawnRoomRowObjects Room24V1Group4_id
    DespawnTileObject Room24V1Group0_id, 1
    SetQuestState 2, 245
    SetTileObjectAnimStateWithSpeed 0, 255
    InvokeChainIfEnabled 0, Room24V1Chain2_id
    End
Room24V1Chain19:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route14_id, 0, 1, 0, 0, 0
    End
Room24V1Chain20:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route15_id, 0, 1, 0, 0, 0
    End
Room24V1Chain21:
    ArmChainYield 1
    RemovePartyFollower 7
    RespawnRowAndRunChain Room24V1Group6_id, 0
    ArmChainYield 0
    StartObjectAnimSequence Room24V1Group6_id, 0, 0, 0, Room24V1Route16_id, 0, 1, 0, 0, 0
    End
Room24V1Chain22:
    End
Room24V1Chain23:
    ArmChainYield 1
    @ "Have at thee, scurvy knave!"
    @ "The Fat Lady must be in another portrait..."
    @ "Why don't we ask Sir Cadogan? He's bonkers, but he knows all about this floor."
    @ "OK, we have to start somewhere."
    @ "Hello, Sir Cadogan."
    @ "I don't suppose you happened to see the Fat Lady go by here?"
    @ "That I did, fair maiden, and in great distress!"
    @ "Could you help us find her?"
    @ "That I shall, milady, and verily so!"
    ShowRoomDialog 376
    DelayedRespawnRowAndRunChain 1, 0, 0
    DespawnRoomRowObjects Room24V1Group21_id
    InvokeChainIfEnabled 0, Room24V1Chain3_id
    End
Room24V1Chain24:
    @ "Has Sir Cadogan come this way?"
    @ "Indeed. Saw him dash into the Grand Staircase."
    ShowRoomDialog 388
    End
Room24V1Chain25:
    @ "Transfiguration class is held on the first floor."
    ShowRoomDialog 212
    End
Room24V1Chain26:
    @ "I can't find the Transfiguration classroom. I heard it was on the first floor¸"
    ShowRoomDialog 213
    End
Room24V1Chain27:
    @ "I wonder who the new Defense Against the Dark Arts teacher will be this year¸"
    ShowRoomDialog 191
    End
Room24V1Chain28:
    @ "Hi, Harry! Welcome back!"
    ShowRoomDialog 192
    End
Room24V1Chain29:
    @ "This would be a nice day to have a class outside."
    ShowRoomDialog 237
    End
Room24V1Chain30:
    @ "Hagrid's a natural to teach Care of Magical Creatures - don't you think?"
    ShowRoomDialog 239
    End
Room24V1Chain31:
    @ "Potions class is in the dungeons off the Entrance Hall."
    ShowRoomDialog 321
    End
Room24V1Chain32:
    @ "I hate having to go into the dungeons to get to Potions."
    ShowRoomDialog 322
    End
Room24V1Chain33:
    @ "Why do you want to go to the staff room? Isn't it for teachers only?"
    ShowRoomDialog 330
    End
Room24V1Chain34:
    @ "Defense Against the Dark Arts class is on the third floor. I heard it might be taking place in the staff room today, though."
    ShowRoomDialog 328
    End
Room24V1Chain35:
    GotoIfQuestStateCompare 245, 0, 1, Room24V1Chain15_id, 0, 0, 0
    GotoIfQuestStateCompare 249, 0, 1, Room24V1Chain61_id, 0, Room24V1Group12_id, 0
    GotoIfQuestStateCompare 249, 0, 2, Room24V1Chain61_id, 0, Room24V1Group21_id, 0
    End
Room24V1Chain36:
    @ "The library? You'll need to go to the second floor."
    ShowRoomDialog 626
    End
Room24V1Chain37:
    @ "The library's quite large - and it's got upper and lower levels..."
    ShowRoomDialog 631
    End
Room24V1Chain38:
    StartObjectAnimSequence Room24V1Group13_id, 1, 0, 0, Room24V1Route18_id, 3, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group13_id, 0, 0, 0, Room24V1Route19_id, 0, 0, 0, 0, 0
    End
Room24V1Chain39:
    @ "The Defense Against the Dark Arts class is on the third floor."
    ShowRoomDialog 327
    End
Room24V1Chain40:
    @ "The Defense Against the Dark Arts classroom's on the third floor."
    ShowRoomDialog 333
    End
Room24V1Chain41:
    StartObjectAnimSequence Room24V1Group15_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group15_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain42:
    @ "Is it true about the Firebolt?"
    ShowRoomDialog 447
    End
Room24V1Chain43:
    @ "I heard somebody got a Firebolt for Christmas!"
    ShowRoomDialog 448
    End
Room24V1Chain44:
    @ "Great! It's time for the Christmas feast!"
    ShowRoomDialog 469
    End
Room24V1Chain45:
    @ "We need more holidays - and more feasts!"
    ShowRoomDialog 470
    End
Room24V1Chain46:
    @ "I'm still stuffed from the Christmas feast!"
    ShowRoomDialog 511
    End
Room24V1Chain47:
    @ "When's the next feast going to be, anyway?"
    ShowRoomDialog 515
    End
Room24V1Chain48:
    @ "I'm really glad Gryffindor beat Slytherin."
    ShowRoomDialog 512
    End
Room24V1Chain49:
    @ "Is it true Sirius Black tried to stab Ron Weasley?"
    ShowRoomDialog 517
    End
Room24V1Chain50:
    @ "Malfoy provoked Buckbeak!"
    ShowRoomDialog 543
    End
Room24V1Chain51:
    @ "Poor Hagrid! He loves that Hippogriff."
    ShowRoomDialog 536
    End
Room24V1Chain52:
    @ "Locked."
    ShowRoomDialog 624
    End
Room24V1Chain53:
    @ "Fred and George sell all sorts of useful items in their shop on the seventh floor."
    ShowRoomDialog 628
    End
Room24V1Chain54:
    @ "Madam Pomfrey's the Hogwarts nurse. She's on the fourth floor if you ever feel ill¸"
    ShowRoomDialog 634
    End
Room24V1Chain55:
    @ "I heard there are portrait shortcuts on every floor of Hogwarts..."
    ShowRoomDialog 640
    End
Room24V1Chain56:
    @ "Has Sir Cadogan come this way?"
    @ "Sorry, no."
    ShowRoomDialog 381
    End
Room24V1Chain57:
    @ "Has Sir Cadogan come this way?"
    @ "I'm afraid not."
    ShowRoomDialog 384
    End
Room24V1Chain58:
    @ "Has Sir Cadogan come this way?"
    @ "No, he hasn't."
    ShowRoomDialog 383
    End
Room24V1Chain59:
    @ "Has Sir Cadogan come this way?"
    @ "Don't know anyone by that name."
    ShowRoomDialog 382
    End
Room24V1Chain60:
    @ "Has Sir Cadogan come this way?"
    @ "That daft knight? No, I'm afraid not."
    ShowRoomDialog 385
    End
Room24V1Chain61:
    DespawnTileObject Room24V1Group0_id, 1
    GotoIfStoryStageCompare 0, 17, Room24V1Chain76_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 18, Room24V1Chain76_id, 0, 0, 0
    End
Room24V1Chain62:
    PlaySoundById 52
    StartObjectAnimSequence Room24V1Group4_id, 0, 0, 0, Room24V1Route13_id, 0, 1, 0, 0, 0
    End
Room24V1Chain63:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route21_id, 0, 1, 0, 0, 0
    End
Room24V1Chain64:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route22_id, 0, 1, 0, 0, 0
    End
Room24V1Chain65:
    StartObjectAnimSequence Room24V1Group19_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    End
Room24V1Chain66:
    @ "It's come to something when even a portrait's not safe around here..."
    ShowRoomDialog 372
    End
Room24V1Chain67:
    @ "What's happened to the Fat Lady?"
    ShowRoomDialog 366
    End
Room24V1Chain68:
    StartObjectAnimSequence Room24V1Group14_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group14_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain69:
    StartObjectAnimSequence Room24V1Group8_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group8_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain70:
    StartObjectAnimSequence Room24V1Group9_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group9_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain71:
    StartObjectAnimSequence Room24V1Group10_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group10_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain72:
    StartObjectAnimSequence Room24V1Group11_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group11_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain73:
    StartObjectAnimSequence Room24V1Group23_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group23_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain74:
    StartObjectAnimSequence Room24V1Group16_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group16_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain75:
    StartObjectAnimSequence Room24V1Group17_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group17_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain76:
    StartObjectAnimSequence Room24V1Group18_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group18_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain77:
    StartObjectAnimSequence Room24V1Group20_id, 0, 0, 0, Room24V1Route18_id, 1, 0, 0, 0, 0
    StartObjectAnimSequence Room24V1Group20_id, 1, 0, 0, Room24V1Route19_id, 2, 0, 0, 0, 0
    End
Room24V1Chain78:
    ReturnToOverworld 29, 0
    End
Room24V1Chain79:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 129
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room24V1Route23_id, 0, 1, 0, 0, 0
    End
Room24V1Chain80:
    GotoIfQuestStateCompare 129, 0, 0, 0, 0, Room24V1Group24_id, 0
    End
    EndSubBlock Room24V1End

    SubBlock Room24V2, 1, Room24V2Routes, Room24V2Chains, Room24V2End
    OffsetTable Room24V2Groups, 1, 1
    Offsets Room24V2Group0
    EndTable
    Group Room24V2Group0, 3
    Door 238, 467, half_width=27, half_height=16, destination_room=29
    Prop 206, 448, kind=59
    Prop 206, 448, kind=59
    OffsetTable Room24V2Routes, 7
    Offsets Room24V2Route0, Room24V2Route1, Room24V2Route2, Room24V2Route3, Room24V2Route4, Room24V2Route5
    Offsets Room24V2Route6
    EndTable
Room24V2Route0:
    Route 4
    Waypoint 486, 549
    Waypoint 486, 593
    Waypoint 669, 594
    Waypoint 669, 549
Room24V2Route1:
    Route 4
    Waypoint 180, 505
    Waypoint 385, 505
    Waypoint 385, 535
    Waypoint 180, 535
Room24V2Route2:
    Route 4
    Waypoint 165, 525
    Waypoint 370, 525
    Waypoint 370, 555
    Waypoint 165, 555
Room24V2Route3:
    Route 8
    Waypoint 397, 379
    Waypoint 396, 329
    Waypoint 441, 328
    Waypoint 442, 392
    Waypoint 396, 393
    Waypoint 396, 440
    Waypoint 443, 440
    Waypoint 441, 379
Room24V2Route4:
    Route 4
    Waypoint 395, 221
    Waypoint 395, 309
    Waypoint 441, 309
    Waypoint 442, 221
Room24V2Route5:
    Route 4
    Waypoint 1023, 216
    Waypoint 974, 217
    Waypoint 975, 295
    Waypoint 1025, 295
Room24V2Route6:
    Route 13
    Waypoint 1011, 443
    Waypoint 975, 443
    Waypoint 899, 443
    Waypoint 900, 485
    Waypoint 949, 486
    Waypoint 950, 545
    Waypoint 791, 546
    Waypoint 792, 598
    Waypoint 845, 598
    Waypoint 842, 553
    Waypoint 813, 555
    Waypoint 813, 575
    Waypoint 1012, 577
    OffsetTable Room24V2Chains, 1, 1
    Offsets Room24V2Chain0
    EndTable
Room24V2Chain0:
    DelayedRespawnRowAndRunChain 0, 0, 0
    End
    EndSubBlock Room24V2End

    SubBlock Room24V3, 1, Room24V3Routes, Room24V3Chains, Room24V3End
    OffsetTable Room24V3Groups, 1, 1
    Offsets Room24V3Group0
    EndTable
    Group Room24V3Group0, 2
    Door 238, 469, half_width=27, half_height=16, destination_room=29
    Prop 206, 448, kind=59
    OffsetTable Room24V3Routes, 0
    EndTable
    OffsetTable Room24V3Chains, 1, 1
    Offsets Room24V3Chain0
    EndTable
Room24V3Chain0:
    End
    EndSubBlock Room24V3End

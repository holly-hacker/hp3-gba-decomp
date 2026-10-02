    .include "asm/room_blob.inc"

Room15Blob:
    RoomBlob 11
    PlayerEntry 383, 896, 8, 3
    PlayerEntry 1125, 592, 1, 0
    PlayerEntry 1124, 921, 3, 0
    PlayerEntry 326, 870, 4, 0
    PlayerEntry 458, 831, 5, 0
    PlayerEntry 943, 1066, 0, 0
    PlayerEntry 1127, 1276, 2, 0
    PlayerEntry 326, 870, 4, 0
    PlayerEntry 486, 27, 7, 3
    PlayerEntry 970, 1065, 6, 2
    PlayerEntry 272, 540, 9, 2
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room15V0
    VariantEntry Room15V1

    SubBlock Room15V0, 1, Room15V0Routes, Room15V0Chains, Room15V0End
    OffsetTable Room15V0Groups, 1
    Offsets Room15V0Group0
    EndTable
    Group Room15V0Group0, 4
    Door 1147, 585, half_width=10, half_height=33, destination_room=8, exit_param=1
    Door 1149, 1313, half_width=8, half_height=62, destination_room=13, exit_param=1
    Door 524, 5, half_width=36, half_height=9, destination_room=10
    TileAnimation 912, 1017, anim_id=30
    OffsetTable Room15V0Routes, 0
    EndTable
    OffsetTable Room15V0Chains, 1
    Offsets Room15V0Chain0
    EndTable
Room15V0Chain0:
    SetBattleDefeatState 2
    End
    EndSubBlock Room15V0End

    SubBlock Room15V1, 1, Room15V1Routes, Room15V1Chains, Room15V1End
    OffsetTable Room15V1Groups, 32, 1
    Offsets Room15V1Group0, Room15V1Group1, Room15V1Group2, Room15V1Group3, Room15V1Group4, Room15V1Group5
    Offsets Room15V1Group6, Room15V1Group7, Room15V1Group8, Room15V1Group9, Room15V1Group10, Room15V1Group11
    Offsets Room15V1Group12, Room15V1Group13, Room15V1Group14, Room15V1Group15, Room15V1Group16, Room15V1Group17
    Offsets Room15V1Group18, Room15V1Group19, Room15V1Group20, Room15V1Group21, Room15V1Group22, Room15V1Group23
    Offsets Room15V1Group24, Room15V1Group25, Room15V1Group26, Room15V1Group27, Room15V1Group28, Room15V1Group29
    Offsets Room15V1Group30, Room15V1Group31
    EndTable
    Group Room15V1Group0, 0
    Group Room15V1Group1, 3
    Npc 505, 848, sprite=35, facing=4, arg_0f=0
    Npc 530, 920, sprite=56, facing=0, arg_0f=0
    Npc 490, 924, sprite=51, facing=0, arg_0f=0
    Group Room15V1Group2, 3
    Npc 595, 683, sprite=23, facing=6, arg_0f=0
    Npc 630, 687, sprite=22, facing=6, arg_0f=0
    Npc 610, 685, sprite=28, facing=6, arg_0f=0
    Group Room15V1Group3, 2
    Npc 581, 895, sprite=34, facing=6
    Npc 607, 895, sprite=32, facing=6
    Group Room15V1Group4, 0
    Group Room15V1Group5, 1
    TriggerZone 422, 876, half_width=22, half_height=23, chain=Room15V1Chain11_id
    Group Room15V1Group6, 2
    TriggerZone 431, 869, half_width=26, half_height=26, chain=Room15V1Chain10_id
    Door 298, 874, half_width=10, half_height=35, destination_room=12
    Group Room15V1Group7, 3
    Npc 385, 444, sprite=56, facing=6
    Npc 346, 432, sprite=51, facing=4
    Npc 290, 440, sprite=35, facing=4
    Group Room15V1Group8, 4
    TriggerZone 512, 623, half_width=124, half_height=12, rearm_delay=1, chain=Room15V1Chain2_id
    TriggerZone 741, 714, half_width=20, half_height=71, chain=Room15V1Chain2_id
    TriggerZone 743, 920, half_width=10, half_height=127, chain=Room15V1Chain2_id
    TriggerZone 719, 1026, half_width=13, half_height=84, chain=Room15V1Chain2_id
    Group Room15V1Group9, 3
    Npc 302, 413, sprite=22, facing=4
    Npc 333, 425, sprite=28, facing=6
    Npc 315, 428, sprite=23, facing=4
    Group Room15V1Group10, 2
    TriggerZone 515, 632, half_width=127, half_height=17, chain=Room15V1Chain23_id
    TriggerZone 624, 490, half_width=10, half_height=84, chain=Room15V1Chain23_id
    Group Room15V1Group11, 2
    Npc 365, 475, sprite=34, facing=6
    Npc 365, 495, sprite=32, facing=6
    Group Room15V1Group12, 1
    Npc 230, 425, sprite=36, facing=4
    Group Room15V1Group13, 1
    Npc 345, 375, sprite=35, facing=0
    Group Room15V1Group14, 6
    Npc 431, 869, sprite=35, facing=4
    Npc 485, 903, sprite=51, facing=0, interact_cooldown=4, interact_mode=1, chain=Room15V1Chain14_id, arg_0f=0
    Npc 535, 905, sprite=56, facing=0, interact_cooldown=4, interact_mode=1, chain=Room15V1Chain13_id, arg_0f=0
    Npc 585, 855, sprite=22, facing=6, interact_cooldown=4, interact_mode=1, chain=Room15V1Chain17_id, arg_0f=0
    Npc 570, 840, sprite=28, facing=6, interact_cooldown=4, interact_mode=1, chain=Room15V1Chain16_id, arg_0f=0
    Npc 550, 825, sprite=23, facing=6, interact_cooldown=4, interact_mode=1, chain=Room15V1Chain18_id, arg_0f=0
    Group Room15V1Group15, 2
    Npc 618, 942, sprite=99, facing=2
    Npc 618, 942, sprite=32, facing=4
    Group Room15V1Group16, 4
    Npc 1004, 1095, sprite=32, facing=0, arg_0f=0
    Npc 985, 1095, sprite=34, facing=0, arg_0f=0
    Npc 1015, 1050, sprite=15, facing=6, arg_0f=0
    Npc 1015, 1075, sprite=100, facing=6, arg_0f=0
    Group Room15V1Group17, 1
    Npc 965, 970, sprite=20, facing=4, arg_0f=0
    Group Room15V1Group18, 2
    Npc 470, 907, sprite=5, facing=2, arg_0f=0
    Npc 542, 902, sprite=4, facing=0, arg_0f=0
    Group Room15V1Group19, 1
    Npc 458, 831, sprite=32, facing=2, arg_0f=0
    Group Room15V1Group20, 1
    Npc 475, 900, sprite=99, facing=2, arg_0f=0
    Group Room15V1Group21, 1
    Npc 525, 891, sprite=34, facing=2
    Group Room15V1Group22, 5
    Npc 467, 550, sprite=35, facing=6
    Npc 428, 545, sprite=36, facing=2
    TriggerZone 1134, 943, half_width=30, half_height=127, chain=Room15V1Chain54_id
    TriggerZone 1135, 1238, half_width=18, half_height=127, chain=Room15V1Chain54_id
    TriggerZone 444, 814, half_width=23, half_height=10, rearm_delay=3, trigger_kind=1, chain=Room15V1Chain63_id
    Group Room15V1Group23, 1
    Npc 330, 485, sprite=28, facing=0
    Group Room15V1Group24, 1
    Door 1145, 931, half_width=9, half_height=114, destination_room=13
    Group Room15V1Group25, 3
    TriggerZone 1134, 938, half_width=30, half_height=127, chain=Room15V1Chain61_id
    TriggerZone 1136, 1230, half_width=18, half_height=127, chain=Room15V1Chain61_id
    TriggerZone 444, 814, half_width=23, half_height=10, rearm_delay=5, trigger_kind=1, chain=Room15V1Chain62_id
    Group Room15V1Group26, 2
    Door 1146, 926, half_width=9, half_height=127, destination_room=13
    Door 440, 798, half_width=15, half_height=23, destination_room=11
    Group Room15V1Group27, 1
    TriggerZone 928, 1044, half_width=46, half_height=45, chain=Room15V1Chain45_id
    Group Room15V1Group28, 2
    Npc 1010, 1065, sprite=99, facing=6, arg_0f=0
    Npc 1010, 1065, sprite=32, facing=0, arg_0f=0
    Group Room15V1Group29, 1
    Npc 1005, 1020, sprite=101, facing=0, arg_0f=0
    Group Room15V1Group30, 1
    Npc 1000, 1065, sprite=101, facing=6, arg_0f=0
    Group Room15V1Group31, 1
    TriggerZone 297, 875, half_width=16, half_height=22, rearm_delay=3, trigger_kind=1, chain=Room15V1Chain73_id
    OffsetTable Room15V1Routes, 68
    Offsets Room15V1Route0, Room15V1Route1, Room15V1Route2, Room15V1Route3, Room15V1Route4, Room15V1Route5
    Offsets Room15V1Route6, Room15V1Route7, Room15V1Route8, Room15V1Route9, Room15V1Route10, Room15V1Route11
    Offsets Room15V1Route12, Room15V1Route13, Room15V1Route14, Room15V1Route15, Room15V1Route16, Room15V1Route17
    Offsets Room15V1Route18, Room15V1Route19, Room15V1Route20, Room15V1Route21, Room15V1Route22, Room15V1Route23
    Offsets Room15V1Route24, Room15V1Route25, Room15V1Route26, Room15V1Route27, Room15V1Route28, Room15V1Route29
    Offsets Room15V1Route30, Room15V1Route31, Room15V1Route32, Room15V1Route33, Room15V1Route34, Room15V1Route35
    Offsets Room15V1Route36, Room15V1Route37, Room15V1Route38, Room15V1Route39, Room15V1Route40, Room15V1Route41
    Offsets Room15V1Route42, Room15V1Route43, Room15V1Route44, Room15V1Route45, Room15V1Route46, Room15V1Route47
    Offsets Room15V1Route48, Room15V1Route49, Room15V1Route50, Room15V1Route51, Room15V1Route52, Room15V1Route53
    Offsets Room15V1Route54, Room15V1Route55, Room15V1Route56, Room15V1Route57, Room15V1Route58, Room15V1Route59
    Offsets Room15V1Route60, Room15V1Route61, Room15V1Route62, Room15V1Route63, Room15V1Route64, Room15V1Route65
    Offsets Room15V1Route66, Room15V1Route67
    EndTable
Room15V1Route0:
    Route 2
    Waypoint 610, 840
    Waypoint 570, 840
Room15V1Route1:
    Route 4
    Waypoint 712, 780
    Waypoint 625, 895, on_arrival_chain=Room15V1Chain3_id
    Waypoint 515, 900
    Waypoint 515, 890, on_arrival_chain=Room15V1Chain3_id
Room15V1Route2:
    Route 2
    Waypoint 630, 855
    Waypoint 580, 855, on_arrival_chain=Room15V1Chain4_id
Room15V1Route3:
    Route 2
    Waypoint 595, 827
    Waypoint 555, 827
Room15V1Route4:
    Route 3
    Waypoint 581, 895
    Waypoint 581, 883
    Waypoint 560, 883
Room15V1Route5:
    Route 3
    Waypoint 607, 895
    Waypoint 607, 877
    Waypoint 580, 877, on_arrival_chain=Room15V1Chain5_id
Room15V1Route6:
    Route 2
    Waypoint 515, 893
    Waypoint 515, 890
Room15V1Route7:
    Route 3
    Waypoint 505, 848
    Waypoint 505, 865
    Waypoint 515, 865, on_arrival_chain=Room15V1Chain6_id
Room15V1Route8:
    Route 3
    Waypoint 510, 891
    Waypoint 440, 891
    Waypoint 440, 885
Room15V1Route9:
    Route 3
    Waypoint 515, 865
    Waypoint 430, 865
    Waypoint 430, 869, on_arrival_chain=Room15V1Chain7_id
Room15V1Route10:
    Route 2
    Waypoint 440, 885
    Waypoint 315, 885, on_arrival_chain=Room15V1Chain8_id
Room15V1Route11:
    Route 2
    Waypoint 530, 920
    Waypoint 530, 905
Room15V1Route12:
    Route 2
    Waypoint 510, 925
    Waypoint 510, 908
Room15V1Route13:
    Route 2
    Waypoint 490, 923
    Waypoint 490, 903, on_arrival_chain=Room15V1Chain5_id
Room15V1Route14:
    Route 3
    Waypoint 430, 877
    Waypoint 540, 877
    Waypoint 538, 877
Room15V1Route15:
    Route 2
    Waypoint 430, 869
    Waypoint 505, 869, on_arrival_chain=Room15V1Chain19_id
Room15V1Route16:
    Route 3
    Waypoint 560, 883
    Waypoint 540, 883
    Waypoint 540, 877
Room15V1Route17:
    Route 2
    Waypoint 580, 877
    Waypoint 540, 877
Room15V1Route18:
    Route 1
    Waypoint 505, 760
Room15V1Route19:
    Route 5
    Waypoint 230, 425
    Waypoint 245, 425
    Waypoint 245, 490
    Waypoint 300, 490
    Waypoint 300, 480, on_arrival_chain=Room15V1Chain26_id
Room15V1Route20:
    Route 1
    Waypoint 530, 760
Room15V1Route21:
    Route 1
    Waypoint 550, 760
Room15V1Route22:
    Route 1
    Waypoint 515, 760, on_arrival_chain=Room15V1Chain57_id
Room15V1Route23:
    Route 5
    Waypoint 483, 543
    Waypoint 455, 505
    Waypoint 365, 505
    Waypoint 365, 450
    Waypoint 360, 450, on_arrival_chain=Room15V1Chain38_id
Room15V1Route24:
    Route 2
    Waypoint 333, 425
    Waypoint 333, 445, on_arrival_chain=Room15V1Chain25_id
Room15V1Route25:
    Route 2
    Waypoint 346, 432
    Waypoint 346, 440
Room15V1Route26:
    Route 2
    Waypoint 385, 444
    Waypoint 375, 444
Room15V1Route27:
    Route 2
    Waypoint 333, 445
    Waypoint 333, 475, on_arrival_chain=Room15V1Chain27_id
Room15V1Route28:
    Route 2
    Waypoint 300, 480
    Waypoint 303, 480
Room15V1Route29:
    Route 2
    Waypoint 315, 480
    Waypoint 325, 480, on_arrival_chain=Room15V1Chain28_id
Room15V1Route30:
    Route 2
    Waypoint 333, 475
    Waypoint 337, 475, on_arrival_chain=Room15V1Chain56_id
Room15V1Route31:
    Route 3
    Waypoint 290, 460
    Waypoint 360, 460
    Waypoint 360, 470, on_arrival_chain=Room15V1Chain29_id
Room15V1Route32:
    Route 6
    Waypoint 360, 460
    Waypoint 360, 445
    Waypoint 345, 445, on_arrival_chain=Room15V1Chain32_id
    Waypoint 345, 379
    Waypoint 328, 379
    Waypoint 328, 330
Room15V1Route33:
    Route 5
    Waypoint 335, 475
    Waypoint 335, 455, on_arrival_chain=Room15V1Chain30_id
    Waypoint 325, 455
    Waypoint 325, 371
    Waypoint 325, 330
Room15V1Route34:
    Route 4
    Waypoint 385, 444
    Waypoint 385, 395
    Waypoint 330, 395
    Waypoint 330, 330, on_arrival_chain=Room15V1Chain33_id
Room15V1Route35:
    Route 3
    Waypoint 346, 400
    Waypoint 315, 400
    Waypoint 315, 330
Room15V1Route36:
    Route 4
    Waypoint 276, 410
    Waypoint 295, 410
    Waypoint 302, 410
    Waypoint 302, 330
Room15V1Route37:
    Route 2
    Waypoint 360, 450
    Waypoint 345, 465, on_arrival_chain=Room15V1Chain34_id
Room15V1Route38:
    Route 3
    Waypoint 345, 465
    Waypoint 325, 465
    Waypoint 320, 465, on_arrival_chain=Room15V1Chain35_id
Room15V1Route39:
    Route 2
    Waypoint 345, 375
    Waypoint 345, 440, on_arrival_chain=Room15V1Chain39_id
Room15V1Route40:
    Route 2
    Waypoint 365, 495
    Waypoint 363, 495
Room15V1Route41:
    Route 2
    Waypoint 365, 475
    Waypoint 361, 475, on_arrival_chain=Room15V1Chain24_id
Room15V1Route42:
    Route 2
    Waypoint 361, 475
    Waypoint 350, 475, on_arrival_chain=Room15V1Chain36_id
Room15V1Route43:
    Route 2
    Waypoint 363, 495
    Waypoint 357, 495
Room15V1Route44:
    Route 2
    Waypoint 325, 470
    Waypoint 330, 470, on_arrival_chain=Room15V1Chain40_id
Room15V1Route45:
    Route 2
    Waypoint 330, 470
    Waypoint 350, 470
Room15V1Route46:
    Route 2
    Waypoint 350, 475
    Waypoint 350, 470
Room15V1Route47:
    Route 2
    Waypoint 350, 495
    Waypoint 350, 470
Room15V1Route48:
    Route 3
    Waypoint 345, 440
    Waypoint 400, 440
    Waypoint 400, 595
Room15V1Route49:
    Route 2
    Waypoint 542, 904
    Waypoint 740, 904
Room15V1Route50:
    Route 2
    Waypoint 965, 970
    Waypoint 965, 1020, on_arrival_chain=Room15V1Chain58_id
Room15V1Route51:
    Route 3
    Waypoint 458, 831
    Waypoint 491, 852
    Waypoint 558, 893, on_arrival_chain=Room15V1Chain65_id
Room15V1Route52:
    Route 2
    Waypoint 558, 893
    Waypoint 610, 920
Room15V1Route53:
    Route 2
    Waypoint 540, 900
    Waypoint 800, 900, on_arrival_chain=Room15V1Chain70_id
Room15V1Route54:
    Route 3
    Waypoint 610, 920
    Waypoint 784, 1105
    Waypoint 875, 1105, on_arrival_chain=Room15V1Chain71_id
Room15V1Route55:
    Route 2
    Waypoint 272, 540
    Waypoint 291, 540, on_arrival_chain=Room15V1Chain49_id
Room15V1Route56:
    Route 3
    Waypoint 467, 560
    Waypoint 467, 715, on_arrival_chain=Room15V1Chain52_id
    Waypoint 467, 750, on_arrival_chain=Room15V1Chain52_id
Room15V1Route57:
    Route 2
    Waypoint 293, 540
    Waypoint 407, 540
Room15V1Route58:
    Route 3
    Waypoint 407, 540
    Waypoint 473, 540
    Waypoint 452, 542, on_arrival_chain=Room15V1Chain53_id
Room15V1Route59:
    Route 2
    Waypoint 330, 475
    Waypoint 330, 490, on_arrival_chain=Room15V1Chain28_id
Room15V1Route60:
    Route 2
    Waypoint 467, 550
    Waypoint 467, 560, on_arrival_chain=Room15V1Chain51_id
Room15V1Route61:
    Route 3
    Waypoint 1000, 1070
    Waypoint 1015, 1070
    Waypoint 1015, 960, on_arrival_chain=Room15V1Chain59_id
Room15V1Route62:
    Route 4
    Waypoint 325, 480
    Waypoint 325, 520
    Waypoint 392, 520
    Waypoint 392, 585, on_arrival_chain=Room15V1Chain41_id
Room15V1Route63:
    Route 3
    Waypoint 458, 831
    Waypoint 478, 860
    Waypoint 504, 879
Room15V1Route64:
    Route 2
    Waypoint 504, 879
    Waypoint 540, 900, on_arrival_chain=Room15V1Chain66_id
Room15V1Route65:
    Route 3
    Waypoint 470, 907
    Waypoint 525, 907, on_arrival_chain=Room15V1Chain67_id
    Waypoint 740, 907, on_arrival_chain=Room15V1Chain68_id
Room15V1Route66:
    Route 2
    Waypoint 1010, 1065
    Waypoint 945, 1065, on_arrival_chain=Room15V1Chain72_id
Room15V1Route67:
    Route 2
    Waypoint 1005, 1065
    Waypoint 1005, 1020, on_arrival_chain=Room15V1Chain60_id
    OffsetTable Room15V1Chains, 75, 1
    Offsets Room15V1Chain0, Room15V1Chain1, Room15V1Chain2, Room15V1Chain3, Room15V1Chain4, Room15V1Chain5
    Offsets Room15V1Chain6, Room15V1Chain7, Room15V1Chain8, Room15V1Chain9, Room15V1Chain10, Room15V1Chain11
    Offsets Room15V1Chain12, Room15V1Chain13, Room15V1Chain14, Room15V1Chain15, Room15V1Chain16, Room15V1Chain17
    Offsets Room15V1Chain18, Room15V1Chain19, Room15V1Chain20, Room15V1Chain21, Room15V1Chain22, Room15V1Chain23
    Offsets Room15V1Chain24, Room15V1Chain25, Room15V1Chain26, Room15V1Chain27, Room15V1Chain28, Room15V1Chain29
    Offsets Room15V1Chain30, Room15V1Chain31, Room15V1Chain32, Room15V1Chain33, Room15V1Chain34, Room15V1Chain35
    Offsets Room15V1Chain36, Room15V1Chain37, Room15V1Chain38, Room15V1Chain39, Room15V1Chain40, Room15V1Chain41
    Offsets Room15V1Chain42, Room15V1Chain43, Room15V1Chain44, Room15V1Chain45, Room15V1Chain46, Room15V1Chain47
    Offsets Room15V1Chain48, Room15V1Chain49, Room15V1Chain50, Room15V1Chain51, Room15V1Chain52, Room15V1Chain53
    Offsets Room15V1Chain54, Room15V1Chain55, Room15V1Chain56, Room15V1Chain57, Room15V1Chain58, Room15V1Chain59
    Offsets Room15V1Chain60, Room15V1Chain61, Room15V1Chain62, Room15V1Chain63, Room15V1Chain64, Room15V1Chain65
    Offsets Room15V1Chain66, Room15V1Chain67, Room15V1Chain68, Room15V1Chain69, Room15V1Chain70, Room15V1Chain71
    Offsets Room15V1Chain72, Room15V1Chain73, Room15V1Chain74
    EndTable
Room15V1Chain0:
    ArmChainYield 1
    GotoIfStoryStageCompare 5, 24, 0, 0, Room15V1Group26_id, 0
    GotoIfStoryStageCompare 0, 2, Room15V1Chain1_id, 0, Room15V1Group2_id, 0
    GotoIfStoryStageCompare 0, 2, Room15V1Chain43_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 3, Room15V1Chain43_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 3, 0, 0, Room15V1Group14_id, 0
    GotoIfStoryStageCompare 0, 3, Room15V1Chain42_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 22, Room15V1Chain55_id, 0, Room15V1Group27_id, 0
    GotoIfStoryStageCompare 0, 23, 0, 0, Room15V1Group30_id, 0
    GotoIfStoryStageCompare 0, 23, Room15V1Chain47_id, 0, Room15V1Group16_id, 0
    GotoIfStoryStageCompare 0, 25, Room15V1Chain50_id, 0, Room15V1Group22_id, 0
    GotoIfStoryStageCompare 0, 26, 0, 0, Room15V1Group25_id, 0
    GotoIfStoryStageCompare 2, 3, 0, 0, Room15V1Group31_id, 0
    End
Room15V1Chain1:
    GotoIfQuestStateCompare 248, 0, 0, 0, 0, Room15V1Group8_id, 0
    GotoIfQuestStateCompare 248, 0, 0, 0, 0, Room15V1Group2_id, 0
    End
Room15V1Chain2:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room15V1Group1_id, 0
    DespawnRoomRowObjects Room15V1Group8_id
    Unk02 Room15V1Group2_id, 1, 2
    Unk02 Room15V1Group2_id, 2, 2
    Unk02 Room15V1Group2_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route1_id, 0, 1, 0, 0, 0
    End
Room15V1Chain3:
    StartObjectAnimSequence Room15V1Group2_id, 1, 0, 0, Room15V1Route2_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group2_id, 2, 0, 0, Room15V1Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group2_id, 0, 0, 0, Room15V1Route3_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room15V1Group1_id, 0, 0, 0, 800, 0
    End
Room15V1Chain4:
    ArmChainYield 1
    SetQuestState 1, 248
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group1_id, 1, 0, 0, Room15V1Route11_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group1_id, 2, 0, 0, Room15V1Route13_id, 0, 1, 0, 0, 0
    End
Room15V1Chain5:
    ArmChainYield 1
    @ "Got a real treat for yeh today! Great lesson comin' up!"
    ShowRoomDialog 230
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group1_id, 0, 0, 0, Room15V1Route7_id, 0, 1, 0, 0, 0
    End
Room15V1Chain6:
    ArmChainYield 1
    @ "Firs' thing yeh'll want ter do is open yer books -"
    @ "How do we do that if we don't have a copy of 'The Monster Book of Monsters'? I'm afraid, Hagrid, that I've mislaid my copy - and so have Crabbe and Goyle."
    @ "Oh, er, well, I¸"
    @ "Oh, surely you have extra copies we could borrow?"
    @ "Harry, can I have a word?"
    ShowRoomDialog 231
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group1_id, 0, 0, 0, Room15V1Route9_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route8_id, 0, 1, 0, 0, 0
    End
Room15V1Chain7:
    ArmChainYield 1
    QueueTileObjectMove 0, 255, 0, 0, 500, 0
    @ "What's wrong, Hagrid?"
    @ "My extra copies o' 'The Monster Book of Monsters'... they escaped!"
    @ "I bet Malfoy had something to do with it."
    @ "Tha' may be, but I'd really appreciate it if yeh'd go and find 'em fer me. Five books in all - there'd be a reward in it fer yeh."
    @ "Of course we'll find them for you, Hagrid. We'd be glad to help, reward or not."
    @ "Thanks."
    ShowRoomDialog 232
    @ "These three spellbooks may help you to get through my garden."
    ShowRoomDialog 243
    GrantPartySpell 6
    GrantPartySpell 7
    GrantPartySpell 5
    @ "Harry receives Diffindo, Ron receives Spongify, and Hermione receives Glacius!"
    ShowRoomDialog 664
    ClearOverworldMonstersDisabled
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route10_id, 0, 1, 0, 0, 0
    End
Room15V1Chain8:
    ArmChainYield 1
    SetQuestState 1, 248
    SetQuestState QUEST_OBJ_FIND_ESCAPED_BOOKS, QUEST_OBJECTIVE_INDEX
    SetTileObjectAnimStateWithSpeed 0, 255
    ReturnToOverworld 12, 0
    End
Room15V1Chain9:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group14_id, 0, 0, 0, Room15V1Route15_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room15V1Group14_id, 0, 0, 0, 1000, 0
    End
Room15V1Chain10:
    @ "Oh, dear, that ain't all of 'em. Yeh'd best go back and look fer the rest."
    ShowRoomDialog 250
    End
Room15V1Chain11:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ConsumeRoomItem 78
    ConsumeRoomItem 78
    ConsumeRoomItem 78
    ConsumeRoomItem 78
    ConsumeRoomItem 78
    @ "Hagrid's copies of 'The Monster Book of Monsters' have been removed from your Inventory."
    ShowRoomDialog 662
    @ "Well done! 'Ave this as a reward fer returning the books!"
    ShowRoomDialog 251
    GrantPartyExperience 5, 65535
    GrantRoomReward 10, 0
    ShowRewardPickupMessage 10
    InvokeChainIfEnabled 0, Room15V1Chain9_id
    End
Room15V1Chain12:
    @ "What's going on in Hagrid's garden?"
    ShowRoomDialog 257
    End
Room15V1Chain13:
    @ "Can't someone find out what's going on in Hagrid's garden?"
    ShowRoomDialog 254
    End
Room15V1Chain14:
    @ "Is there some kind of trouble in Hagrid's garden?"
    ShowRoomDialog 256
    End
Room15V1Chain15:
    @ "There appears to be some kind of problem in Hagrid's garden..."
    ShowRoomDialog 253
    End
Room15V1Chain16:
    @ "Sounds like something's on a rampage in Hagrid's garden!"
    ShowRoomDialog 259
    End
Room15V1Chain17:
    @ "Something's definitely going on in Hagrid's garden."
    ShowRoomDialog 258
    End
Room15V1Chain18:
    @ "Sounds like animals fighting in Hagrid's garden."
    ShowRoomDialog 255
    End
Room15V1Chain19:
    ArmChainYield 1
    @ "Righ', then, so... so yeh've got yer books an'... an'... if you'd like to follow me to the paddock we can start the lesson."
    ShowRoomDialog 264
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route14_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group14_id, 0, 0, 0, Room15V1Route18_id, 0, 1, 0, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1000, 0
    StartObjectAnimSequence Room15V1Group14_id, 2, 0, 0, Room15V1Route20_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group14_id, 1, 0, 0, Room15V1Route22_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group14_id, 3, 0, 0, Room15V1Route21_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group14_id, 4, 0, 0, Room15V1Route21_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group14_id, 5, 0, 0, Room15V1Route21_id, 0, 1, 0, 0, 0
    End
Room15V1Chain20:
    ArmChainYield 1
    RespawnRowAndRunChain Room15V1Group10_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room15V1Chain21:
    End
Room15V1Chain22:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room15V1Group14_id
    SetQuestState 6, 229
    InvokeChainIfEnabled 0, Room15V1Chain20_id
    End
Room15V1Chain23:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room15V1Group9_id, 0
    RespawnRowAndRunChain Room15V1Group7_id, 0
    RespawnRowAndRunChain Room15V1Group12_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route23_id, 0, 1, 0, 0, 0
    End
Room15V1Chain24:
    ArmChainYield 1
    @ "Everyone gather round! That's it - make sure yeh can see."
    ShowRoomDialog 266
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group9_id, 1, 0, 0, Room15V1Route24_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group7_id, 0, 0, 0, Room15V1Route26_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group7_id, 1, 0, 0, Room15V1Route25_id, 0, 1, 0, 0, 0
    End
Room15V1Chain25:
    ArmChainYield 1
    @ "This place is going to the dogs. That oaf teaching classes, my father'll have a fit when I tell him-"
    @ "Shut up, Malfoy."
    @ "Careful, Potter, there's a Dementor behind you-"
    ShowRoomDialog 267
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group12_id, 0, 0, 0, Room15V1Route19_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room15V1Group12_id, 0, 0, 0, 700, 0
    End
Room15V1Chain26:
    ArmChainYield 1
    @ "A Hippogriff! Beau'iful, aren' they?"
    @ "Ooooooooh!"
    @ "Now, firs' thing yeh gotta know abou' Hippogriffs is they're proud. Don't never insult one, 'cause it might be the last thing yeh do. Right then - let's see how yeh get on with Buckbeak."
    ShowRoomDialog 268
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group12_id, 0, 0, 0, Room15V1Route28_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group9_id, 1, 0, 0, Room15V1Route27_id, 0, 1, 0, 0, 0
    End
Room15V1Chain27:
    ArmChainYield 1
    @ "This is very easy. I bet you're not dangerous at all, are you, you ugly great brute?"
    ShowRoomDialog 269
    PlaySoundById 57
    Unk02 Room15V1Group9_id, 1, 8
    SetTileObjectSpecialFlag Room15V1Group12_id, 0, 1
    SetTileObjectSpecialFlag Room15V1Group9_id, 1, 1
    ArmChainYield 0
    PlayTileObjectAnimation Room15V1Group12_id, 0, 20
    PlaySoundById 55
    DelayedRespawnRowAndRunChain 1, 0, 0
    PlaySoundById 58
    PlayTileObjectAnimation Room15V1Group9_id, 1, 15
    PlaySoundById 59
    PlayMusicModuleAndFlagIfChain1 16
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group9_id, 1, 0, 0, Room15V1Route30_id, 0, 1, 0, 0, 0
    End
Room15V1Chain28:
    ArmChainYield 1
    QueueTileObjectMove Room15V1Group7_id, 2, 0, 0, 1600, 0
    RespawnRowAndRunChain Room15V1Group23_id, 0
    DespawnTileObject Room15V1Group9_id, 1
    @ "I'm dying! Look at me! It's killed me!"
    @ "Yer not dyin'! Someone help me - gotta get him outta here, gotta get him to Madam Pomfrey..."
    ShowRoomDialog 270
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group7_id, 2, 0, 0, Room15V1Route31_id, 0, 1, 0, 0, 0
    End
Room15V1Chain29:
    QueueTileObjectMove 0, 255, 0, 0, 1000, 0
    StartObjectAnimSequence Room15V1Group23_id, 0, 0, 0, Room15V1Route33_id, 0, 1, 0, 0, 0
    End
Room15V1Chain30:
    StartObjectAnimSequence Room15V1Group7_id, 2, 0, 0, Room15V1Route32_id, 0, 1, 0, 0, 0
    End
Room15V1Chain31:
    @ "It was Malfoy's fault. He insulted Buckbeak even though he was warned not to!"
    @ "Buckbeak looks pretty calm now. I'll try and approach him the way Hagrid said."
    ShowRoomDialog 271
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route37_id, 0, 1, 0, 0, 0
    End
Room15V1Chain32:
    StartObjectAnimSequence Room15V1Group7_id, 0, 0, 0, Room15V1Route34_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group7_id, 1, 0, 0, Room15V1Route35_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group9_id, 2, 0, 0, Room15V1Route35_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group9_id, 0, 0, 0, Room15V1Route36_id, 2, 1, 0, 0, 0
    End
Room15V1Chain33:
    ArmChainYield 1
    DespawnRoomRowObjects Room15V1Group7_id
    DespawnRoomRowObjects Room15V1Group9_id
    DespawnRoomRowObjects Room15V1Group23_id
    InvokeChainIfEnabled 0, Room15V1Chain31_id
    End
Room15V1Chain34:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "Careful, Harry!"
    @ "We're friends now. You know, I bet I could ride him..."
    ShowRoomDialog 272
    PlaySoundById 57
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route38_id, 0, 1, 0, 0, 0
    End
Room15V1Chain35:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "That's it, Harry!"
    ShowRoomDialog 273
    PlaySoundById 56
    DelayedRespawnRowAndRunChain 1, 0, 0
    UnlockMinigame 1
    StartMinigame 1, 0, 1, 0, Room15V1Chain37_id
    End
Room15V1Chain36:
    ArmChainYield 1
    @ "Wow! That was great!"
    @ "Well done, Harry!"
    @ "Buckbeak's Hippogriff Glide can now be accessed from the Mini-Games menu found on the Title Screen."
    ShowRoomDialog 274
    RespawnRowAndRunChain Room15V1Group13_id, 0
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group13_id, 0, 0, 0, Room15V1Route39_id, 0, 1, 0, 0, 0
    End
Room15V1Chain37:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group11_id, 1, 0, 0, Room15V1Route43_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group11_id, 0, 0, 0, Room15V1Route42_id, 0, 1, 0, 0, 0
    End
Room15V1Chain38:
    ArmChainYield 1
    RespawnRowAndRunChain Room15V1Group11_id, 0
    RemovePartyFollower 6
    RemovePartyFollower 7
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group11_id, 1, 0, 0, Room15V1Route40_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group11_id, 0, 0, 0, Room15V1Route41_id, 0, 1, 0, 0, 0
    End
Room15V1Chain39:
    ArmChainYield 1
    @ "I really appreciate all yeh've done."
    ShowRoomDialog 275
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route44_id, 0, 1, 0, 0, 0
    End
Room15V1Chain40:
    ArmChainYield 1
    @ "It's Potions next..."
    @ "I don't know what you're groaning about, Harry, I'm really looking forward to it!"
    @ "What?!"
    @ "Just joking - I'm dreading it as much as you."
    @ "I've heard we're learning how to make a Shrinking Solution today. Let's go."
    ShowRoomDialog 286
    Unk02 Room15V1Group13_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route45_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group11_id, 0, 0, 0, Room15V1Route46_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group11_id, 1, 0, 0, Room15V1Route47_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group13_id, 0, 0, 0, Room15V1Route48_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group12_id, 0, 0, 0, Room15V1Route62_id, 0, 1, 0, 0, 0
    End
Room15V1Chain41:
    ArmChainYield 1
    Unk02 Room15V1Group13_id, 0, 1
    DespawnRoomRowObjects Room15V1Group13_id
    DespawnRoomRowObjects Room15V1Group12_id
    DespawnRoomRowObjects Room15V1Group10_id
    RecruitPartyFollower 6
    RecruitPartyFollower 7
    DespawnRoomRowObjects Room15V1Group11_id
    ClearQuestStateUpperHalf
    SetQuestState QUEST_OBJ_GO_TO_POTIONS, QUEST_OBJECTIVE_INDEX
    SetStoryStage 4
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room15V1Chain42:
    ArmChainYield 1
    ResetPartyLeaderSelection
    GotoIfQuestStateCompare 229, 4, 5, 0, 0, Room15V1Group6_id, 0
    GotoIfQuestStateCompare 229, 0, 5, Room15V1Chain64_id, 0, Room15V1Group5_id, 0
    GotoIfQuestStateCompare 229, 0, 6, Room15V1Chain22_id, 0, 0, 0
    End
Room15V1Chain43:
    SetOverworldMonstersDisabled
    End
Room15V1Chain44:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room15V1Group19_id, 0
    RemovePartyFollower 7
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route51_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group19_id, 0, 0, 0, Room15V1Route63_id, 0, 1, 0, 0, 0
    End
Room15V1Chain45:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartBattle 2, 0, Room15V1Chain46_id
    End
Room15V1Chain46:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "That took care of that - now let's get Ron!"
    ShowRoomDialog 559
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetQuestState QUEST_OBJ_FOLLOW_PATH_TO_SHRIEKING_SHACK, QUEST_OBJECTIVE_INDEX
    ClearQuestStateUpperHalf
    ReturnToOverworld 44, 0
    End
Room15V1Chain47:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, QUEST_ALT_PRESENTATION
    SetOverworldMonstersDisabled
    RemovePartyFollower 6
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "You're free, Sirius."
    @ "Yes, thank you all. Harry, your parents named me your godfather. Once my name's cleared... if you wanted a... a different home¸"
    @ "When can I move in?"
    ShowRoomDialog 577
    RespawnRowAndRunChain Room15V1Group17_id, 0
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group17_id, 0, 0, 0, Room15V1Route50_id, 0, 1, 0, 0, 0
    End
Room15V1Chain48:
    SetTileObjectAnimState Room15V0Group0_id, 3
    PlaySoundById 68
    End
Room15V1Chain49:
    ArmChainYield 1
    SetTileObjectFacing 0, 255, 2
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "There's Hagrid! Don't let him see us!"
    ShowRoomDialog 590
    ArmChainYield 0
    QueueTileObjectMove Room15V1Group22_id, 0, 0, 75, 400, 0
    End
Room15V1Chain50:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 130
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route55_id, 0, 1, 0, 0, 0
    End
Room15V1Chain51:
    ArmChainYield 1
    @ "Who's that at the door?"
    ShowRoomDialog 592
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "That must be us! We don't have much time before Macnair, the executioner, shows up."
    ShowRoomDialog 593
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group22_id, 0, 0, 0, Room15V1Route56_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route57_id, 0, 1, 0, 0, 0
    End
Room15V1Chain52:
    ArmChainYield 1
    RemovePartyFollower 6
    DespawnTileObject Room15V1Group22_id, 1
    ArmChainYield 0
.ifndef VERSION_JP
    PlaySoundById 46
.endif
    QueueTileObjectMove 0, 255, 0, 0, 1000, 0
    ArmChainYield 1
    RecruitPartyFollower 6
    RecruitPartyFollower 8
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route58_id, 0, 1, 0, 0, 0
    End
Room15V1Chain53:
    ArmChainYield 1
    DespawnTileObject Room15V1Group22_id, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "Hello, Buckbeak, remember me? We're going to take you for a walk."
    @ "Let's hurry on to the lake!"
    ShowRoomDialog 594
    SetQuestState QUEST_OBJ_GO_BACK_TO_LAKE, QUEST_OBJECTIVE_INDEX
    SetStoryStage 26
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room15V1Chain54:
    ArmChainYield 1
    DespawnTileObject Room15V1Group22_id, 2
    DespawnTileObject Room15V1Group22_id, 3
    SetQuestState 1, QUEST_ALT_PRESENTATION
    ReturnToOverworld 13, 1
    End
Room15V1Chain55:
    SetOverworldMonstersDisabled
    ArmChainYield 1
    GotoIfQuestStateCompare 129, 0, 0, Room15V1Chain44_id, 0, 0, 0
    End
Room15V1Chain56:
    ArmChainYield 1
    Unk02 Room15V1Group9_id, 1, 1
    PlayTileObjectAnimation Room15V1Group9_id, 1, 16
    DelayedRespawnRowAndRunChain 1, 0, 0
    InvokeChainIfEnabled 0, Room15V1Chain28_id
    End
Room15V1Chain57:
    ArmChainYield 1
    @ "Come on you two. I can't wait to see what Hagrid's going to show us!"
    @ "Me neither - let's go!"
    ShowRoomDialog 265
    InvokeChainIfEnabled 0, Room15V1Chain22_id
    End
Room15V1Chain58:
    ArmChainYield 1
    @ "Good evening, Sirius. How I hoped I would be the one to catch you¸"
    ShowRoomDialog 580
    PlayMusicModuleAndFlagIfChain1 16
    StartTileObjectScript 970, 39, 4, 0, 255, 0, 0, 0, 255, 255, 255
    SetTileObjectFacing 0, 255, 0
    DelayedRespawnRowAndRunChainFrames 10, 0, 0
    @ "Professor Snape! You're making a mistake. Sirius Black isn't here to kill me!"
    @ "SILENCE! Two more for Azkaban tonight..."
    ShowRoomDialog 578
    @ "Professor Snape - it - it wouldn't hurt to hear what they've got to say, w-would it?"
    @ "Professor Lupin could have killed me many times. If he was helping Black, why didn't he just finish me off?"
    @ "Get out of the way, Potter."
    ShowRoomDialog 579
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group30_id, 0, 0, 0, Room15V1Route67_id, 0, 1, 0, 0, 0
    StartTileObjectScript 1015, 242, 3, Room15V1Group16_id, 2, 0, 0, 0, 255, 255, 255
    StartTileObjectScript 1015, 6, 4, Room15V1Group16_id, 3, 0, 0, 0, 255, 255, 255
    StartTileObjectScript 1015, 31, 4, Room15V1Group16_id, 0, 0, 0, 0, 255, 255, 255
    StartTileObjectScript 1015, 61, 4, Room15V1Group16_id, 1, 0, 0, 0, 255, 255, 255
    StartTileObjectScript 1000, 41, 4, 0, 255, 0, 0, 0, 255, 255, 255
    StartTileObjectScript 970, 252, 3, Room15V1Group17_id, 0, 0, 0, 2, 255, 255, 255
    End
Room15V1Chain59:
    ArmChainYield 1
    SetQuestState QUEST_OBJ_WALK_TO_LAKE, QUEST_OBJECTIVE_INDEX
    SetStoryStage 24
    PlayCutscene 12, 0, 0
    End
Room15V1Chain60:
    ArmChainYield 1
    SetTileObjectFacing Room15V1Group17_id, 0, 2
    SetTileObjectFacing Room15V1Group30_id, 0, 6
    DelayedRespawnRowAndRunChainFrames 2, 0, 0
    @ "Expelliarmus!"
    ShowRoomDialog 581
    PlaySoundById 74
    PlayTileObjectAnimation Room15V1Group30_id, 0, 26
    PlayTileObjectAnimation Room15V1Group17_id, 0, 24
    DelayedRespawnRowAndRunChain 1, 0, 0
    RespawnRowAndRunChain Room15V1Group29_id, 0
    DespawnRoomRowObjects Room15V1Group30_id
    DelayedRespawnRowAndRunChainFrames 10, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route61_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group16_id, 2, 0, 0, Room15V1Route61_id, 2, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group16_id, 1, 0, 0, Room15V1Route61_id, 2, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group16_id, 0, 0, 0, Room15V1Route61_id, 2, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group16_id, 3, 0, 0, Room15V1Route61_id, 2, 1, 0, 0, 0
    End
Room15V1Chain61:
    ArmChainYield 1
    DespawnRoomRowObjects Room15V1Group25_id
    SetQuestState 1, QUEST_ALT_PRESENTATION
    ReturnToOverworld 13, 1
    End
Room15V1Chain62:
    @ "Locked."
    ShowRoomDialog 624
    End
Room15V1Chain63:
    @ "Locked."
    ShowRoomDialog 624
    End
Room15V1Chain64:
    SetQuestState QUEST_OBJ_GO_TO_CARE_OF_MAGICAL_CREATURES, QUEST_OBJECTIVE_INDEX
    End
Room15V1Chain65:
    ArmChainYield 1
    DelayedRespawnRowAndRunChainFrames 15, 0, 0
    PlaySoundById 46
    DelayedRespawnRowAndRunChain 1, 0, 0
    PlayMusicModuleAndFlagIfChain1 16
    @ "What was that? It sounded like..."
    @ "Oh, no!"
    @ "They did it! I d-don't believe it - they executed Buckbeak!"
    ShowRoomDialog 549
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route52_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group19_id, 0, 0, 0, Room15V1Route64_id, 0, 1, 0, 0, 0
    End
Room15V1Chain66:
    ArmChainYield 1
    @ "How could they execute Buckbeak - how could they?"
    @ "Scabbers, keep still!"
    @ "Squeak!"
    @ "Ouch! Scabbers bit me!"
    ShowRoomDialog 551
    RespawnRowAndRunChain Room15V1Group18_id, 0
    Unk02 Room15V1Group18_id, 0, 5
    Unk02 Room15V1Group18_id, 1, 5
    @ "Yeowwl!"
    ShowRoomDialog 552
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group18_id, 0, 0, 0, Room15V1Route65_id, 0, 1, 0, 0, 0
    End
Room15V1Chain67:
    StartObjectAnimSequence Room15V1Group18_id, 1, 0, 0, Room15V1Route49_id, 0, 1, 0, 0, 0
    End
Room15V1Chain68:
    ArmChainYield 1
    @ "Crookshanks, no! Come back!"
    ShowRoomDialog 553
    SetTileObjectFacing Room15V1Group19_id, 0, 2
    PlayMusicModuleAndFlagIfChain1 12
    DespawnRoomRowObjects Room15V1Group18_id
    RespawnRowAndRunChain Room15V1Group20_id, 0
    StartTileObjectScript 540, 132, 3, Room15V1Group20_id, 0, 0, 0, 0, 255, 255, 255
    InvokeChainIfEnabled 0, Room15V1Chain69_id
    End
Room15V1Chain69:
    ArmChainYield 1
    Unk02 Room15V1Group19_id, 0, 4
    Unk02 Room15V1Group20_id, 0, 4
    SetTileObjectSpecialFlag Room15V1Group19_id, 0, 1
    PlaySoundById 48
    DelayedRespawnRowAndRunChainFrames 15, 0, 0
    ArmChainYield 0
    PlayTileObjectAnimation Room15V1Group19_id, 0, 22
    StartObjectAnimSequence Room15V1Group20_id, 0, 0, 0, Room15V1Route53_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group19_id, 0, 0, 0, Room15V1Route53_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room15V1Group19_id, 0, 0, 0, 800, 0
    End
Room15V1Chain70:
    ArmChainYield 1
    DespawnTileObject Room15V1Group20_id, 0
    DespawnTileObject Room15V1Group19_id, 0
    @ "Help!"
    ShowRoomDialog 555
    QueueTileObjectMove 0, 255, 0, 0, 1800, 0
    @ "The black dog! It's got Ron!"
    ShowRoomDialog 554
    RespawnRowAndRunChain Room15V1Group28_id, 0
    Unk02 0, 255, 3
    @ "It's dragging him towards the Whomping Willow! And where's Crookshanks?"
    ShowRoomDialog 556
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room15V1Route54_id, 0, 1, 0, 0, 0
    End
Room15V1Chain71:
    ArmChainYield 1
    Unk02 Room15V1Group28_id, 0, 3
    Unk02 Room15V1Group28_id, 1, 3
    @ "Help!"
    ShowRoomDialog 555
    SetTileObjectSpecialFlag Room15V1Group28_id, 1, 1
    ArmChainYield 0
    PlayTileObjectAnimation Room15V1Group28_id, 1, 22
    StartObjectAnimSequence Room15V1Group28_id, 0, 0, 0, Room15V1Route66_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room15V1Group28_id, 1, 0, 0, Room15V1Route66_id, 0, 1, 0, 0, 0
    SetTileObjectFacing 0, 255, 2
    End
Room15V1Chain72:
    ArmChainYield 1
    DespawnRoomRowObjects Room15V1Group28_id
    Unk02 0, 255, 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "The dog's dragged Ron under the Whomping Willow!"
    @ "If that dog can get in, we can!"
    ShowRoomDialog 557
    SetQuestState 1, 129
    SetQuestState QUEST_OBJ_FIND_PATH_BENEATH_WILLOW, QUEST_OBJECTIVE_INDEX
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room15V1Chain73:
    @ "Locked."
    ShowRoomDialog 624
    End
Room15V1Chain74:
    ArmChainYield 1
    @ "It's all righ', Beaky... It's all righ'..."
    ShowRoomDialog 591
    ArmChainYield 0
    StartObjectAnimSequence Room15V1Group22_id, 0, 0, 0, Room15V1Route60_id, 0, 1, 0, 0, 0
    End
    EndSubBlock Room15V1End

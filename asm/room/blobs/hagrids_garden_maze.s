    .include "asm/room_blob.inc"

Room12Blob:
    RoomBlob 1
    PlayerEntry 1495, 503, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room12V0
    VariantEntry Room12V1

    SubBlock Room12V0, 1, Room12V0Routes, Room12V0Chains, Room12V0End
    OffsetTable Room12V0Groups, 1
    Offsets Room12V0Group0
    EndTable
    Group Room12V0Group0, 5
    Chest 109, 668, flag_id=73, reward_id=100
    Chest 1031, 944, flag_id=74, reward_id=117
    Chest 397, 745, flag_id=75, reward_id=59
    Chest 785, 182, flag_id=76, reward_id=57
    TileAnimation 71, 527, anim_id=29
    OffsetTable Room12V0Routes, 0
    EndTable
    OffsetTable Room12V0Chains, 1
    Offsets Room12V0Chain0
    EndTable
Room12V0Chain0:
    ClearOverworldMonstersDisabled
    End
    EndSubBlock Room12V0End

    SubBlock Room12V1, 1, Room12V1Routes, Room12V1Chains, Room12V1End
    OffsetTable Room12V1Groups, 11, 1
    Offsets Room12V1Group0, Room12V1Group1, Room12V1Group2, Room12V1Group3, Room12V1Group4, Room12V1Group5
    Offsets Room12V1Group6, Room12V1Group7, Room12V1Group8, Room12V1Group9, Room12V1Group10
    EndTable
    Group Room12V1Group0, 47
    Prop 1033, 738, kind=49, arg_13=0
    Prop 919, 614, kind=49, arg_13=0
    Prop 1038, 752, kind=49, arg_13=0, chain=Room12V1Chain38_id
    Prop 1023, 721, kind=49, arg_13=0
    Prop 1117, 634, kind=49, arg_13=0
    Prop 1120, 649, kind=49, arg_13=0
    Prop 1120, 602, kind=49, arg_13=0
    Prop 910, 624, kind=49, arg_13=0
    Prop 929, 627, kind=49, arg_13=0
    Prop 910, 595, kind=49, arg_13=0
    MovePlayer 845, 317, target_x=786, target_y=310, variant=2, arg_0e=40
    MovePlayer 692, 496, target_x=587, target_y=489, variant=2
    Prop 1030, 252, kind=49, arg_13=0
    Prop 1045, 254, kind=49, arg_13=0
    Prop 1028, 272, kind=49, arg_13=0
    Prop 1044, 274, kind=49, arg_13=0
    Prop 562, 657, kind=49, arg_13=0
    Prop 570, 675, kind=49, arg_13=0
    Prop 563, 689, kind=49, arg_13=0
    Prop 969, 900, kind=51, chain=Room12V1Chain37_id
    Prop 380, 826, kind=51
    Prop 380, 803, kind=51
    Prop 380, 708, kind=51
    Prop 380, 691, kind=51
    Prop 308, 615, kind=51
    Prop 574, 703, kind=49, arg_13=0, chain=Room12V1Chain5_id
    TriggerZone 1029, 971, half_width=71, half_height=61, chain=Room12V1Chain1_id
    TriggerZone 580, 586, half_width=47, half_height=27, chain=Room12V1Chain5_id
    TriggerZone 398, 849, half_width=24, half_height=27, chain=Room12V1Chain9_id
    MovePlayer 106, 718, target_x=179, target_y=714, variant=2
    MovePlayer 179, 720, target_x=105, target_y=712, variant=2
    TriggerZone 104, 673, half_width=24, half_height=27, chain=Room12V1Chain17_id
    TriggerZone 1007, 252, half_width=24, half_height=45, chain=Room12V1Chain13_id
    TriggerZone 101, 258, half_width=19, half_height=12, chain=Room12V1Chain21_id
    Npc 1348, 805, sprite=95, facing=0
    TriggerZone 1352, 819, half_width=45, half_height=33, chain=Room12V1Chain36_id
    TriggerZone 1031, 793, half_width=79, half_height=8, chain=Room12V1Chain28_id
    TriggerZone 956, 919, half_width=25, half_height=9, chain=Room12V1Chain30_id
    TriggerZone 849, 311, half_width=41, half_height=10, chain=Room12V1Chain29_id
    TriggerZone 100, 512, half_width=24, half_height=14, chain=Room12V1Chain26_id
    TriggerZone 1514, 364, half_width=85, half_height=47, chain=Room12V1Chain35_id
    Prop 404, 826, kind=51
    Prop 404, 803, kind=51
    Prop 402, 691, kind=51
    Prop 402, 708, kind=51
    Prop 308, 638, kind=51
    TriggerZone 116, 563, half_width=0, half_height=0
    Group Room12V1Group1, 2
    Npc 392, 728, sprite=38, facing=0
    TriggerZone 393, 745, half_width=34, half_height=13, chain=Room12V1Chain11_id
    Group Room12V1Group2, 2
    Npc 1008, 858, sprite=38, facing=0
    TriggerZone 1001, 855, half_width=44, half_height=15, chain=Room12V1Chain3_id
    Group Room12V1Group3, 2
    Npc 658, 872, sprite=38, facing=0
    TriggerZone 657, 875, half_width=22, half_height=20, chain=Room12V1Chain7_id
    Group Room12V1Group4, 2
    Npc 785, 351, sprite=38, facing=0
    TriggerZone 785, 352, half_width=38, half_height=37, chain=Room12V1Chain15_id
    Group Room12V1Group5, 2
    Npc 101, 458, sprite=38, facing=0
    TriggerZone 102, 462, half_width=22, half_height=20, chain=Room12V1Chain19_id
    Group Room12V1Group6, 0
    Group Room12V1Group7, 2
    Npc 1343, 780, sprite=32, facing=4
    Npc 1363, 787, sprite=34, facing=4
    Group Room12V1Group8, 2
    Npc 101, 318, sprite=108, facing=0
    TriggerZone 100, 319, half_width=29, half_height=25, chain=Room12V1Chain25_id
    Group Room12V1Group9, 1
    TriggerZone 1354, 820, half_width=45, half_height=40, chain=Room12V1Chain22_id
    Group Room12V1Group10, 1
    Prop 139, 528, kind=57, arg_0f=1, chain=Room12V1Chain42_id
    OffsetTable Room12V1Routes, 10
    Offsets Room12V1Route0, Room12V1Route1, Room12V1Route2, Room12V1Route3, Room12V1Route4, Room12V1Route5
    Offsets Room12V1Route6, Room12V1Route7, Room12V1Route8, Room12V1Route9
    EndTable
Room12V1Route0:
    Route 6
    Waypoint 1349, 812
    Waypoint 1252, 842
    Waypoint 1197, 859
    Waypoint 1147, 877
    Waypoint 1091, 905
    Waypoint 1063, 928, on_arrival_chain=Room12V1Chain23_id
Room12V1Route1:
    Route 1
    Waypoint 1361, 819
Room12V1Route2:
    Route 6
    Waypoint 1349, 818
    Waypoint 1246, 838
    Waypoint 1191, 856
    Waypoint 1146, 873
    Waypoint 1104, 881
    Waypoint 1057, 898
Room12V1Route3:
    Route 0
Room12V1Route4:
    Route 2
    Waypoint 90, 311
    Waypoint 109, 311
Room12V1Route5:
    Route 2
    Waypoint 992, 852
    Waypoint 1017, 852
Room12V1Route6:
    Route 2
    Waypoint 771, 352
    Waypoint 794, 352
Room12V1Route7:
    Route 2
    Waypoint 646, 872
    Waypoint 670, 872
Room12V1Route8:
    Route 2
    Waypoint 378, 745
    Waypoint 406, 745
Room12V1Route9:
    Route 2
    Waypoint 88, 458
    Waypoint 109, 458
    OffsetTable Room12V1Chains, 45, 1
    Offsets Room12V1Chain0, Room12V1Chain1, Room12V1Chain2, Room12V1Chain3, Room12V1Chain4, Room12V1Chain5
    Offsets Room12V1Chain6, Room12V1Chain7, Room12V1Chain8, Room12V1Chain9, Room12V1Chain10, Room12V1Chain11
    Offsets Room12V1Chain12, Room12V1Chain13, Room12V1Chain14, Room12V1Chain15, Room12V1Chain16, Room12V1Chain17
    Offsets Room12V1Chain18, Room12V1Chain19, Room12V1Chain20, Room12V1Chain21, Room12V1Chain22, Room12V1Chain23
    Offsets Room12V1Chain24, Room12V1Chain25, Room12V1Chain26, Room12V1Chain27, Room12V1Chain28, Room12V1Chain29
    Offsets Room12V1Chain30, Room12V1Chain31, Room12V1Chain32, Room12V1Chain33, Room12V1Chain34, Room12V1Chain35
    Offsets Room12V1Chain36, Room12V1Chain37, Room12V1Chain38, Room12V1Chain39, Room12V1Chain40, Room12V1Chain41
    Offsets Room12V1Chain42, Room12V1Chain43, Room12V1Chain44
    EndTable
Room12V1Chain0:
    SetBattleDefeatState 5
    SetQuestState QUEST_OBJ_FIND_ESCAPED_BOOKS, QUEST_OBJECTIVE_INDEX
    GotoIfQuestStateCompare 233, 0, 23, Room12V1Chain40_id, 0, 0, Room12V1Group10_id
    GotoIfQuestStateCompare 245, 2, 0, Room12V1Chain1_id, 0, 0, 0
    End
Room12V1Chain1:
    GotoIfQuestStateCompare 224, 0, 0, Room12V1Chain2_id, 0, Room12V1Group2_id, 0
    End
Room12V1Chain2:
    StartObjectAnimSequence Room12V1Group2_id, 0, 0, 0, Room12V1Route5_id, 0, 0, 0, 0, 0
    End
Room12V1Chain3:
    ArmChainYield 1
    DespawnRoomRowObjects Room12V1Group2_id
    StartBattle 6, 0, Room12V1Chain4_id
    End
Room12V1Chain4:
    SetQuestState 1, 224
    AddQuestState 1, 229
    End
Room12V1Chain5:
    GotoIfQuestStateCompare 225, 0, 0, Room12V1Chain6_id, 0, Room12V1Group3_id, 0
    End
Room12V1Chain6:
    StartObjectAnimSequence Room12V1Group3_id, 0, 0, 0, Room12V1Route7_id, 0, 0, 0, 0, 0
    End
Room12V1Chain7:
    ArmChainYield 1
    DespawnTileObject Room12V1Group3_id, 0
    StartBattle 6, 0, Room12V1Chain8_id
    End
Room12V1Chain8:
    SetQuestState 1, 225
    AddQuestState 1, 229
    End
Room12V1Chain9:
    GotoIfQuestStateCompare 226, 0, 0, Room12V1Chain10_id, 0, Room12V1Group1_id, 0
    End
Room12V1Chain10:
    StartObjectAnimSequence Room12V1Group1_id, 0, 0, 0, Room12V1Route8_id, 0, 0, 0, 0, 0
    End
Room12V1Chain11:
    ArmChainYield 1
    DespawnTileObject Room12V1Group1_id, 0
    StartBattle 6, 0, Room12V1Chain12_id
    End
Room12V1Chain12:
    SetQuestState 1, 226
    AddQuestState 1, 229
    End
Room12V1Chain13:
    GotoIfQuestStateCompare 227, 0, 0, Room12V1Chain14_id, 0, Room12V1Group4_id, 0
    End
Room12V1Chain14:
    StartObjectAnimSequence Room12V1Group4_id, 0, 0, 0, Room12V1Route6_id, 0, 0, 0, 0, 0
    End
Room12V1Chain15:
    ArmChainYield 1
    DespawnTileObject Room12V1Group4_id, 0
    StartBattle 6, 0, Room12V1Chain16_id
    End
Room12V1Chain16:
    SetQuestState 1, 227
    AddQuestState 1, 229
    End
Room12V1Chain17:
    GotoIfQuestStateCompare 228, 0, 0, Room12V1Chain18_id, 0, Room12V1Group5_id, 0
    End
Room12V1Chain18:
    StartObjectAnimSequence Room12V1Group5_id, 0, 0, 0, Room12V1Route9_id, 0, 0, 0, 0, 0
    End
Room12V1Chain19:
    ArmChainYield 1
    DespawnTileObject Room12V1Group5_id, 0
    StartBattle 6, 0, Room12V1Chain20_id
    End
Room12V1Chain20:
    SetQuestState 1, 228
    AddQuestState 1, 229
    SetQuestState QUEST_OBJ_GO_TO_CARE_OF_MAGICAL_CREATURES, QUEST_OBJECTIVE_INDEX
    End
Room12V1Chain21:
    SetStoryStage 3
    ReturnToOverworld 15, 4
    End
Room12V1Chain22:
    ArmChainYield 1
    ClearTileObjectFlagBit 0, 255, 9
    ClearTileObjectFlagBit 0, 255, 4
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    RemovePartyFollower 6
    RemovePartyFollower 7
    ArmChainYield 1
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room12V1Route0_id, 0, 6, 0, 0, 0
    StartObjectAnimSequence Room12V1Group0_id, 34, 0, 0, Room12V1Route0_id, 0, 1, 0, 0, 0
    End
Room12V1Chain23:
    SetTileObjectAnimStateValue Room12V1Group0_id, 34, 5
    SetTileObjectAnimStateWithSpeed 0, 255
    SetTileObjectFlagBit 0, 255, 9
    RecruitPartyFollower 7
    RecruitPartyFollower 6
    SetPauseMenuLocked 0, 255, 255, 255
    End
Room12V1Chain24:
    SetTileObjectAnimState Room12V0Group0_id, 4
    DespawnTileObject Room12V1Group0_id, 46
    ArmChainYield 0
    RespawnRowAndRunChain 0, Room12V1Chain44_id
    End
Room12V1Chain25:
    DespawnTileObject Room12V1Group8_id, 0
    StartBattle 7, 0, Room12V1Chain34_id
    End
Room12V1Chain26:
    GotoIfQuestStateCompare 251, 0, 0, Room12V1Chain32_id, 0, Room12V1Group8_id, 0
    End
Room12V1Chain27:
    GrantPartyExperience 10, 65535
    End
Room12V1Chain28:
    @ "I bet I can sever this with my Diffindo Spell!"
    ShowRoomDialog 261
    End
Room12V1Chain29:
    @ "I can use Spongify to make these pads rubbery so we can bounce over this."
    ShowRoomDialog 262
    DespawnTileObject Room12V0Group0_id, 0
    DespawnTileObject Room12V0Group0_id, 0
    End
Room12V1Chain30:
    @ "I can cast Glacius to turn the water into ice so that we can cross this."
    ShowRoomDialog 263
    DespawnTileObject Room12V0Group0_id, 0
    End
Room12V1Chain31:
    ArmChainYield 1
    GotoIfQuestStateCompare 233, 0, 0, Room12V1Chain27_id, 0, 0, 0
    SetQuestState 23, 233
    DelayedRespawnRowAndRunChainFrames 7, 0, Room12V1Chain24_id
    End
Room12V1Chain32:
    StartObjectAnimSequence Room12V1Group8_id, 0, 0, 0, Room12V1Route4_id, 0, 0, 0, 0, 0
    End
Room12V1Chain33:
    GrantPartyExperience 10, 65535
    DespawnTileObject Room12V0Group0_id, 0
    End
Room12V1Chain34:
    SetQuestState 1, 251
    End
Room12V1Chain35:
    SetQuestState 5, 229
    End
Room12V1Chain36:
    SetPauseMenuLocked 1, 255, 255, 255
    DelayedRespawnRowAndRunChainFrames 1, Room12V1Group9_id, 0
    ArmChainYield 1
    ArmChainYield 0
    End
Room12V1Chain37:
    GotoIfQuestStateCompare 230, 0, 0, Room12V1Chain27_id, 0, 0, 0
    SetQuestState 1, 230
    End
Room12V1Chain38:
    GotoIfQuestStateCompare 231, 0, 0, Room12V1Chain27_id, 0, 0, 0
    SetQuestState 1, 231
    End
Room12V1Chain39:
    GotoIfQuestStateCompare 232, 0, 0, Room12V1Chain27_id, 0, 0, 0
    SetQuestState 1, 232
    End
Room12V1Chain40:
    DelayedRespawnRowAndRunChainFrames 3, 0, Room12V1Chain43_id
    End
Room12V1Chain41:
    RespawnRowAndRunChain 0, 0
    End
Room12V1Chain42:
    CancelObjectAnimSequence 0, 255
    SetPauseMenuLocked 1, 255, 255, 255
    ClearTileObjectFlagBit 0, 255, 2
    RespawnRowAndRunChain 0, Room12V1Chain31_id
    End
Room12V1Chain43:
    SetTileObjectAnimState Room12V0Group0_id, 4
    End
Room12V1Chain44:
    SetPauseMenuLocked 0, 255, 255, 255
    SetTileObjectFlagBit 0, 255, 2
    SetTileObjectAnimStateWithSpeed 0, 255
    End
    EndSubBlock Room12V1End

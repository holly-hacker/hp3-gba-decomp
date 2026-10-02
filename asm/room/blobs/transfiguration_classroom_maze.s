    .include "asm/room_blob.inc"

Room04Blob:
    RoomBlob 1
    PlayerEntry 649, 968, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room04V0
    VariantEntry Room04V1

    SubBlock Room04V0, 1, Room04V0Routes, Room04V0Chains, Room04V0End
    OffsetTable Room04V0Groups, 1
    Offsets Room04V0Group0
    EndTable
    Group Room04V0Group0, 4
    Chest 552, 625, flag_id=20, reward_id=108
    Chest 1301, 159, flag_id=21, reward_id=89
    Chest 258, 718, flag_id=22, reward_id=57, kind=2
    Chest 482, 722, flag_id=110, reward_id=57
    OffsetTable Room04V0Routes, 0
    EndTable
    OffsetTable Room04V0Chains, 1
    Offsets Room04V0Chain0
    EndTable
Room04V0Chain0:
    ClearOverworldMonstersDisabled
    End
    EndSubBlock Room04V0End

    SubBlock Room04V1, 1, Room04V1Routes, Room04V1Chains, Room04V1End
    OffsetTable Room04V1Groups, 10, 1
    Offsets Room04V1Group0, Room04V1Group1, Room04V1Group2, Room04V1Group3, Room04V1Group4, Room04V1Group5
    Offsets Room04V1Group6, Room04V1Group7, Room04V1Group8, Room04V1Group9
    EndTable
    Group Room04V1Group0, 12
    Switch 702, 696, variant=1, unk_08=8, on_deactivate_chain=Room04V1Chain2_id
    Switch 851, 697, variant=1, unk_08=8, on_deactivate_chain=Room04V1Chain2_id
    Prop 739, 709, kind=1, arg_0f=1
    Prop 808, 708, kind=1, arg_0f=1
    TileAnimation 722, 624, anim_id=22, flag=1
    Breakable 622, 750, variant=0, group0=Room04V1Group0_id, member0=2, group1=Room04V1Group0_id, member1=3
    Prop 763, 702, kind=5, arg_10=1
    Prop 786, 702, kind=5, arg_10=1
    TriggerZone 159, 482, half_width=36, half_height=24, chain=Room04V1Chain16_id
    Breakable 677, 749, variant=0, group0=Room04V1Group0_id, member0=2, group1=Room04V1Group0_id, member1=3
    TriggerZone 635, 444, half_width=37, half_height=18, respawn_group=Room04V1Group8_id
    TriggerZone 392, 598, half_width=37, half_height=18, respawn_group=Room04V1Group9_id
    Group Room04V1Group1, 3
    Npc 310, 528, sprite=22, facing=6
    Npc 309, 550, sprite=23, facing=6
    TriggerZone 309, 536, half_width=47, half_height=32, chain=Room04V1Chain7_id
    Group Room04V1Group2, 5
    Npc 309, 761, sprite=18, facing=0
    TriggerZone 352, 775, half_width=20, half_height=19, chain=Room04V1Chain11_id
    TriggerZone 407, 815, half_width=20, half_height=10, chain=Room04V1Chain13_id
    Breakable 438, 678, variant=0, group0=Room04V1Group9_id, member0=0, group1=Room04V1Group9_id, member1=1, group2=Room04V1Group9_id, member2=2
    Switch 330, 846, variant=0, unk_08=10, on_activate_respawn_group=Room04V1Group4_id, on_activate_chain=Room04V1Chain14_id
    Group Room04V1Group3, 1
    Npc 361, 812, sprite=17, facing=4
    Group Room04V1Group4, 0
    Group Room04V1Group5, 1
    TriggerZone 397, 879, half_width=31, half_height=25, chain=Room04V1Chain20_id
    Group Room04V1Group6, 1
    TriggerZone 159, 490, half_width=36, half_height=24, respawn_group=Room04V1Group1_id
    Group Room04V1Group7, 1
    Switch 330, 846, variant=0, unk_08=10, initial_frame=1, on_activate_chain=0
    Group Room04V1Group8, 13
    Prop 410, 300, kind=24, arg_13=0
    Prop 242, 308, kind=24, arg_13=0
    Prop 445, 365, kind=24, arg_13=0
    Prop 491, 400, kind=24, arg_13=0
    TileAnimation 235, 207, anim_id=23, flag=1
    Switch 238, 340, variant=1, unk_08=8, on_activate_chain=Room04V1Chain4_id, on_deactivate_chain=Room04V1Chain5_id
    Switch 405, 317, variant=1, unk_08=8, on_activate_chain=Room04V1Chain4_id, on_deactivate_chain=Room04V1Chain5_id
    Switch 368, 403, variant=1, unk_08=8, on_activate_chain=Room04V1Chain4_id, on_deactivate_chain=Room04V1Chain5_id
    Prop 285, 400, kind=1, arg_0f=1
    Prop 260, 400, kind=1, arg_0f=1
    Prop 310, 400, kind=1, arg_0f=1
    Breakable 496, 296, variant=0, group0=Room04V1Group8_id, member0=8, group1=Room04V1Group8_id, member1=9, group2=Room04V1Group8_id, member2=10
    Breakable 425, 236, variant=0, group0=Room04V1Group8_id, member0=8, group1=Room04V1Group8_id, member1=9, group2=Room04V1Group8_id, member2=10
    Group Room04V1Group9, 17
    Prop 330, 728, kind=1, arg_0f=1
    Prop 405, 784, kind=1, arg_0f=1
    Prop 354, 850, kind=1, arg_0f=1
    Prop 457, 722, kind=24, arg_13=0
    Prop 364, 745, kind=24, arg_13=0
    Prop 326, 761, kind=24, arg_13=0
    Prop 348, 797, kind=24, arg_13=0
    Prop 379, 815, kind=24, arg_13=0
    Prop 443, 815, kind=24, arg_13=0
    Prop 448, 774, kind=24, arg_13=0
    Prop 481, 851, kind=24
    Prop 392, 746, kind=24, arg_13=0
    Prop 424, 748, kind=24, arg_13=0
    Prop 400, 695, kind=24, arg_13=0
    Prop 488, 790, kind=24, arg_13=0
    Prop 357, 881, kind=24, arg_13=0
    TriggerZone 392, 616, half_width=36, half_height=24, chain=Room04V1Chain17_id
    OffsetTable Room04V1Routes, 6
    Offsets Room04V1Route0, Room04V1Route1, Room04V1Route2, Room04V1Route3, Room04V1Route4, Room04V1Route5
    EndTable
Room04V1Route0:
    Route 3
    Waypoint 275, 528
    Waypoint 170, 528
    Waypoint 170, 420, on_arrival_chain=Room04V1Chain10_id
Room04V1Route1:
    Route 3
    Waypoint 275, 550
    Waypoint 160, 550
    Waypoint 160, 420
Room04V1Route2:
    Route 1
    Waypoint 310, 791
Room04V1Route3:
    Route 2
    Waypoint 312, 812
    Waypoint 361, 812
Room04V1Route4:
    Route 3
    Waypoint 361, 847
    Waypoint 390, 847
    Waypoint 390, 872, on_arrival_chain=Room04V1Chain15_id
Room04V1Route5:
    Route 0
    OffsetTable Room04V1Chains, 26, 1
    Offsets Room04V1Chain0, Room04V1Chain1, Room04V1Chain2, Room04V1Chain3, Room04V1Chain4, Room04V1Chain5
    Offsets Room04V1Chain6, Room04V1Chain7, Room04V1Chain8, Room04V1Chain9, Room04V1Chain10, Room04V1Chain11
    Offsets Room04V1Chain12, Room04V1Chain13, Room04V1Chain14, Room04V1Chain15, Room04V1Chain16, Room04V1Chain17
    Offsets Room04V1Chain18, Room04V1Chain19, Room04V1Chain20, Room04V1Chain21, Room04V1Chain22, Room04V1Chain23
    Offsets Room04V1Chain24, Room04V1Chain25
    EndTable
Room04V1Chain0:
    SetBattleDefeatState 3
    SetQuestState 0, 128
    SetQuestState 0, 226
    GotoIfQuestStateCompare 5, 1, 23, Room04V1Chain18_id, 0, 0, 0
    GotoIfQuestStateCompare 4, 1, 23, Room04V1Chain19_id, 0, 0, 0
    ClearOverworldMonstersDisabled
    SetQuestState 0, 225
    SetQuestState 0, 229
    End
Room04V1Chain1:
    AddQuestState 1, 128
    GotoIfQuestStateCompare 128, 0, 2, Room04V1Chain3_id, 0, 0, 0
    End
Room04V1Chain2:
    GotoIfQuestStateCompare 225, 1, 73, Room04V1Chain25_id, 0, 0, 0
    End
Room04V1Chain3:
    PlaySoundById 22
    CancelObjectAnimSequence 0, 255
    SetTileObjectAnimState Room04V1Group0_id, 4
    DelayedRespawnRowAndRunChainFrames 3, 0, Room04V1Chain12_id
    GotoIfQuestStateCompare 225, 1, 73, Room04V1Chain21_id, 0, 0, 0
    End
Room04V1Chain4:
    AddQuestState 1, 226
    GotoIfQuestStateCompare 226, 0, 3, Room04V1Chain6_id, 0, 0, 0
    End
Room04V1Chain5:
    GotoIfQuestStateCompare 229, 1, 19, Room04V1Chain24_id, 0, 0, 0
    End
Room04V1Chain6:
    PlaySoundById 22
    CancelObjectAnimSequence 0, 255
    SetTileObjectAnimState Room04V1Group8_id, 4
    DelayedRespawnRowAndRunChainFrames 3, 0, Room04V1Chain12_id
    GotoIfQuestStateCompare 229, 1, 19, Room04V1Chain22_id, 0, 0, 0
    End
Room04V1Chain7:
    StartBattle 4, 0, Room04V1Chain8_id
    End
Room04V1Chain8:
    CancelObjectAnimSequence 0, 255
    Unk02 Room04V1Group1_id, 1, 3
    Unk02 Room04V1Group1_id, 0, 3
    StartObjectAnimSequence Room04V1Group1_id, 0, 0, 0, Room04V1Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room04V1Group1_id, 1, 0, 0, Room04V1Route1_id, 0, 1, 0, 0, 0
    SetQuestState 23, 5
    GrantPartyExperience 10, 65535
    DelayedRespawnRowAndRunChainFrames 5, 0, Room04V1Chain23_id
    End
Room04V1Chain9:
    GotoIfQuestStateCompare 5, 1, 23, 0, 0, Room04V1Group1_id, 0
    End
Room04V1Chain10:
    DespawnRoomRowObjects Room04V1Group1_id
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room04V1Chain11:
    StartObjectAnimSequence Room04V1Group2_id, 0, 0, 0, Room04V1Route2_id, 0, 1, 0, 0, 0
    End
Room04V1Chain12:
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room04V1Chain13:
    StartObjectAnimSequence Room04V1Group2_id, 0, 0, 0, Room04V1Route3_id, 0, 1, 0, 0, 0
    End
Room04V1Chain14:
    GrantPartyExperience 10, 65535
    CancelObjectAnimSequence 0, 255
    PlayTileObjectAnimation Room04V1Group2_id, 0, 10
    DespawnRoomRowObjects Room04V1Group2_id
    DelayedRespawnRowAndRunChainFrames 0, Room04V1Group3_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room04V1Group7_id, 0
    StartObjectAnimSequence Room04V1Group3_id, 0, 0, 0, Room04V1Route4_id, 0, 1, 0, 0, 0
    SetTileObjectFacing 0, 255, 6
    SetTileObjectAnimStateValue Room04V1Group9_id, 0, 5
    SetTileObjectAnimStateValue Room04V1Group9_id, 1, 5
    SetTileObjectAnimStateValue Room04V1Group9_id, 2, 5
    End
Room04V1Chain15:
    ArmChainYield 1
    DespawnTileObject Room04V1Group3_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room04V1Group5_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    SetQuestState 23, 4
    End
Room04V1Chain16:
    GotoIfQuestStateCompare 5, 1, 23, 0, 0, Room04V1Group6_id, 0
    End
Room04V1Chain17:
    GotoIfQuestStateCompare 4, 0, 0, 0, 0, Room04V1Group2_id, Room04V1Group5_id
    GotoIfQuestStateCompare 4, 0, 0, 0, 0, 0, Room04V1Group7_id
    End
Room04V1Chain18:
    SetQuestState 0, 5
    End
Room04V1Chain19:
    SetQuestState 0, 4
    End
Room04V1Chain20:
    ClearQuestStateUpperHalf
    SetQuestState 0, 4
    SetQuestState 0, 5
    SetQuestState 1, 223
    ReturnToOverworld 3, 1
    End
Room04V1Chain21:
    GrantPartyExperience 5, 65535
    SetQuestState 73, 225
    SetTileObjectAnimStateValue Room04V1Group0_id, 2, 5
    SetTileObjectAnimStateValue Room04V1Group0_id, 3, 5
    DespawnTileObject Room04V1Group0_id, 9
    DespawnTileObject Room04V1Group0_id, 5
    End
Room04V1Chain22:
    GrantPartyExperience 5, 65535
    SetQuestState 19, 229
    SetTileObjectAnimStateValue Room04V1Group8_id, 9, 5
    SetTileObjectAnimStateValue Room04V1Group8_id, 10, 5
    SetTileObjectAnimStateValue Room04V1Group8_id, 8, 5
    DespawnTileObject Room04V1Group8_id, 11
    DespawnTileObject Room04V1Group8_id, 12
    End
Room04V1Chain23:
    CancelObjectAnimSequence 0, 255
    End
Room04V1Chain24:
    SubtractQuestState 1, 226
    GotoIfQuestStateCompare 226, 0, 2, Room04V1Chain6_id, 0, 0, 0
    End
Room04V1Chain25:
    SubtractQuestState 1, 128
    GotoIfQuestStateCompare 128, 0, 1, Room04V1Chain3_id, 0, 0, 0
    End
    EndSubBlock Room04V1End

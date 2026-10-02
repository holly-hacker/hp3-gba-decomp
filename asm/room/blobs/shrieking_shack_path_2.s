    .include "asm/room_blob.inc"

Room45Blob:
    RoomBlob 7
    PlayerEntry 550, 81, 0, 4
    PlayerEntry 810, 411, 1, 4
    PlayerEntry 823, 683, 2, 0
    PlayerEntry 723, 798, 3, 4
    PlayerEntry 619, 967, 4, 0
    PlayerEntry 926, 798, 5, 0
    PlayerEntry 918, 880, 6, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room45V0
    VariantEntry Room45V1

    SubBlock Room45V0, 1, Room45V0Routes, Room45V0Chains, Room45V0End
    OffsetTable Room45V0Groups, 1
    Offsets Room45V0Group0
    EndTable
    Group Room45V0Group0, 9
    Door 967, 884, half_width=10, half_height=25, destination_room=43
    TileAnimation 140, 180, anim_id=36
    TileAnimation 975, 471, anim_id=38
    TileAnimation 623, 503, anim_id=39
    TileAnimation 592, 888, anim_id=40
    TileAnimation 690, 728, anim_id=41
    TileAnimation 978, 851, anim_id=43
    Door 541, 38, half_width=19, half_height=8, destination_room=44, exit_param=1
    Door 824, 628, half_width=20, half_height=25, destination_room=46, exit_param=1
    OffsetTable Room45V0Routes, 0
    EndTable
    OffsetTable Room45V0Chains, 1
    Offsets Room45V0Chain0
    EndTable
Room45V0Chain0:
    ClearOverworldMonstersDisabled
    SetBattleDefeatState 7
    End
    EndSubBlock Room45V0End

    SubBlock Room45V1, 1, Room45V1Routes, Room45V1Chains, Room45V1End
    OffsetTable Room45V1Groups, 26, 1
    Offsets Room45V1Group0, Room45V1Group1, Room45V1Group2, Room45V1Group3, Room45V1Group4, Room45V1Group5
    Offsets Room45V1Group6, Room45V1Group7, Room45V1Group8, Room45V1Group9, Room45V1Group10, Room45V1Group11
    Offsets Room45V1Group12, Room45V1Group13, Room45V1Group14, Room45V1Group15, Room45V1Group16, Room45V1Group17
    Offsets Room45V1Group18, Room45V1Group19, Room45V1Group20, Room45V1Group21, Room45V1Group22, Room45V1Group23
    Offsets Room45V1Group24, Room45V1Group25
    EndTable
    Group Room45V1Group0, 13
    TriggerZone 553, 120, half_width=43, half_height=19, chain=Room45V1Chain33_id
    Prop 483, 123, kind=51
    Switch 696, 675, variant=7, initial_frame=1, on_activate_chain=Room45V1Chain40_id
    Switch 591, 801, variant=7, initial_frame=1, on_activate_chain=Room45V1Chain41_id
    TriggerZone 554, 169, half_width=0, half_height=0
    Prop 452, 527, kind=51
    Prop 432, 527, kind=51
    Prop 432, 554, kind=51
    Prop 452, 555, kind=51
    Prop 432, 581, kind=51
    Prop 452, 581, kind=51
    TriggerZone 809, 372, half_width=12, half_height=8, rearm_delay=3, trigger_kind=1, chain=Room45V1Chain69_id
    TriggerZone 989, 500, half_width=7, half_height=15, rearm_delay=3, trigger_kind=1, chain=Room45V1Chain69_id
    Group Room45V1Group1, 11
    Prop 314, 317, kind=5, arg_0f=1
    Prop 486, 319, kind=5, arg_10=1, chain=Room45V1Chain11_id
    Prop 421, 270, kind=5, arg_10=1
    Prop 255, 209, kind=5, arg_10=1
    Prop 195, 108, kind=5, arg_10=1, chain=Room45V1Chain9_id
    Prop 325, 138, kind=5, arg_10=1
    Prop 401, 207, kind=5, arg_10=1
    Prop 196, 314, kind=5, arg_10=1, chain=Room45V1Chain14_id
    TriggerZone 137, 196, half_width=7, half_height=46, respawn_group=Room45V1Group2_id
    Prop 397, 144, kind=5, arg_10=1
    Prop 334, 317, kind=5, arg_10=1
    Group Room45V1Group2, 1
    TriggerZone 547, 545, half_width=15, half_height=62, chain=Room45V1Chain51_id
    Group Room45V1Group3, 1
    Switch 196, 313, variant=0, unk_08=10, on_activate_chain=Room45V1Chain74_id
    Group Room45V1Group4, 1
    Npc 695, 540, sprite=31, facing=6
    Group Room45V1Group5, 1
    Npc 404, 547, sprite=34, facing=2
    Group Room45V1Group6, 5
    Prop 868, 324, kind=77, chain=Room45V1Chain29_id
    Prop 905, 323, kind=77, chain=Room45V1Chain31_id
    Prop 944, 323, kind=77, chain=Room45V1Chain30_id
    TriggerZone 949, 394, half_width=75, half_height=24, chain=Room45V1Chain76_id
    TriggerZone 671, 547, half_width=11, half_height=30, chain=Room45V1Chain69_id
    Group Room45V1Group7, 1
    Prop 676, 878, kind=76
    Group Room45V1Group8, 2
    Prop 724, 878, kind=76
    Door 720, 763, half_width=17, half_height=12, destination_room=46
    Group Room45V1Group9, 2
    Prop 771, 878, kind=76
    Door 594, 924, half_width=15, half_height=26, destination_room=47
    Group Room45V1Group10, 2
    Prop 819, 878, kind=76
    Door 927, 764, half_width=19, half_height=11, destination_room=48
    Group Room45V1Group11, 1
    Prop 867, 878, kind=76, chain=Room45V1Chain50_id
    Group Room45V1Group12, 1
    Prop 720, 784, kind=62, arg_13=0
    Group Room45V1Group13, 1
    Prop 926, 785, kind=63, arg_13=0
    Group Room45V1Group14, 2
    Prop 582, 880, kind=66, arg_13=0
    Prop 582, 880, kind=64, arg_13=0
    Group Room45V1Group15, 4
    TileAnimation 718, 881, anim_id=46
    TileAnimation 751, 880, anim_id=47
    TileAnimation 814, 883, anim_id=48
    TileAnimation 850, 883, anim_id=49
    Group Room45V1Group16, 1
    Npc 195, 109, sprite=102, facing=4
    Group Room45V1Group17, 1
    Npc 485, 320, sprite=102, facing=4
    Group Room45V1Group18, 1
    Npc 811, 394, sprite=102, facing=4
    Group Room45V1Group19, 1
    Npc 970, 498, sprite=102, facing=6
    Group Room45V1Group20, 1
    Npc 551, 87, sprite=34, facing=4
    Group Room45V1Group21, 1
    Npc 553, 121, sprite=31, facing=4
    Group Room45V1Group22, 1
    Switch 591, 801, variant=9, initial_frame=1, on_activate_chain=0
    Group Room45V1Group23, 1
    Switch 697, 673, variant=9, initial_frame=1, on_activate_chain=0
    Group Room45V1Group24, 1
    TriggerZone 613, 547, half_width=26, half_height=67, chain=Room45V1Chain52_id
    Group Room45V1Group25, 0
    OffsetTable Room45V1Routes, 3
    Offsets Room45V1Route0, Room45V1Route1, Room45V1Route2
    EndTable
Room45V1Route0:
    Route 2
    Waypoint 669, 541
    Waypoint 613, 541
Room45V1Route1:
    Route 2
    Waypoint 497, 542
    Waypoint 583, 541
Room45V1Route2:
    Route 1
    Waypoint 553, 118
    OffsetTable Room45V1Chains, 79, 1
    Offsets Room45V1Chain0, Room45V1Chain1, Room45V1Chain2, Room45V1Chain3, Room45V1Chain4, Room45V1Chain5
    Offsets Room45V1Chain6, Room45V1Chain7, Room45V1Chain8, Room45V1Chain9, Room45V1Chain10, Room45V1Chain11
    Offsets Room45V1Chain12, Room45V1Chain13, Room45V1Chain14, Room45V1Chain15, Room45V1Chain16, Room45V1Chain17
    Offsets Room45V1Chain18, Room45V1Chain19, Room45V1Chain20, Room45V1Chain21, Room45V1Chain22, Room45V1Chain23
    Offsets Room45V1Chain24, Room45V1Chain25, Room45V1Chain26, Room45V1Chain27, Room45V1Chain28, Room45V1Chain29
    Offsets Room45V1Chain30, Room45V1Chain31, Room45V1Chain32, Room45V1Chain33, Room45V1Chain34, Room45V1Chain35
    Offsets Room45V1Chain36, Room45V1Chain37, Room45V1Chain38, Room45V1Chain39, Room45V1Chain40, Room45V1Chain41
    Offsets Room45V1Chain42, Room45V1Chain43, Room45V1Chain44, Room45V1Chain45, Room45V1Chain46, Room45V1Chain47
    Offsets Room45V1Chain48, Room45V1Chain49, Room45V1Chain50, Room45V1Chain51, Room45V1Chain52, Room45V1Chain53
    Offsets Room45V1Chain54, Room45V1Chain55, Room45V1Chain56, Room45V1Chain57, Room45V1Chain58, Room45V1Chain59
    Offsets Room45V1Chain60, Room45V1Chain61, Room45V1Chain62, Room45V1Chain63, Room45V1Chain64, Room45V1Chain65
    Offsets Room45V1Chain66, Room45V1Chain67, Room45V1Chain68, Room45V1Chain69, Room45V1Chain70, Room45V1Chain71
    Offsets Room45V1Chain72, Room45V1Chain73, Room45V1Chain74, Room45V1Chain75, Room45V1Chain76, Room45V1Chain77
    Offsets Room45V1Chain78
    EndTable
Room45V1Chain0:
    SetBattleDefeatState 10
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group6_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group1_id, 0
    DelayedRespawnRowAndRunChainFrames 0, 0, Room45V1Chain46_id
    GotoIfQuestStateCompare 225, 0, 1, Room45V1Chain39_id, 0, 0, 0
    GotoIfQuestStateCompare 226, 0, 1, Room45V1Chain41_id, 0, 0, 0
    GotoIfQuestStateCompare 226, 0, 1, Room45V1Chain56_id, 0, 0, 0
    GotoIfQuestStateCompare 227, 0, 1, Room45V1Chain40_id, 0, 0, 0
    GotoIfQuestStateCompare 227, 0, 1, Room45V1Chain57_id, 0, 0, 0
    GotoIfQuestStateCompare 228, 0, 1, Room45V1Chain42_id, 0, 0, 0
    GotoIfQuestStateCompare 229, 0, 1, Room45V1Chain43_id, 0, 0, 0
    GotoIfQuestStateCompare 231, 0, 0, Room45V1Chain72_id, Room45V1Chain61_id, 0, 0
    GotoIfQuestStateCompare 232, 0, 1, Room45V1Chain62_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 31, Room45V1Chain55_id, 0, 0, 0
    End
Room45V1Chain1:
    PlaySoundById 22
    SetTileObjectAnimState Room45V0Group0_id, 1
    End
Room45V1Chain2:
    PlaySoundById 22
    SetTileObjectAnimState Room45V0Group0_id, 0
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain3:
    PlaySoundById 22
    SetTileObjectAnimState Room45V0Group0_id, 2
    DespawnTileObject Room45V0Group0_id, 2
    End
Room45V1Chain4:
    SetTileObjectAnimState Room45V0Group0_id, 3
    DespawnTileObject Room45V0Group0_id, 3
    PlaySoundById 22
    End
Room45V1Chain5:
    SetTileObjectAnimState Room45V0Group0_id, 4
    DespawnTileObject Room45V0Group0_id, 4
    PlaySoundById 22
    End
Room45V1Chain6:
    SetTileObjectAnimState Room45V0Group0_id, 5
    DespawnTileObject Room45V0Group0_id, 5
    PlaySoundById 22
    End
Room45V1Chain7:
    SetTileObjectAnimState Room45V0Group0_id, 0
    DespawnTileObject Room45V0Group0_id, 0
    PlaySoundById 22
    End
Room45V1Chain8:
    SetTileObjectAnimState Room45V0Group0_id, 6
    DespawnTileObject Room45V0Group0_id, 6
    PlaySoundById 22
    End
Room45V1Chain9:
    DelayedRespawnRowAndRunChain 0, Room45V1Group16_id, 0
    ArmChainYield 1
    QueueTileObjectMove Room45V1Group16_id, 0, 0, 0, 1450, 0
    StartBattle 11, 0, Room45V1Chain44_id
    End
Room45V1Chain10:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    QueueTileObjectMove Room45V0Group0_id, 1, 0, 0, 1610, 0
    DelayedRespawnRowAndRunChainFrames 48, 0, 0
    DelayedRespawnRowAndRunChain 0, 0, Room45V1Chain1_id
    DelayedRespawnRowAndRunChain 11, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1800, 0
    GotoIfQuestStateCompare 236, 0, 0, Room45V1Chain68_id, 0, 0, 0
    SetQuestState 1, 232
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room45V1Chain11:
    DelayedRespawnRowAndRunChain 0, Room45V1Group17_id, 0
    ArmChainYield 1
    QueueTileObjectMove Room45V1Group17_id, 0, 0, 0, 1450, 0
    StartBattle 11, 0, Room45V1Chain44_id
    End
Room45V1Chain12:
    CancelObjectAnimSequence 0, 255
    SetQuestState 2, 231
    SetQuestState 2, 224
    DespawnRoomRowObjects Room45V1Group21_id
    DespawnRoomRowObjects Room45V1Group6_id
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group15_id, 0
    SetTileObjectAnimState Room45V0Group0_id, 3
    DelayedRespawnRowAndRunChain 0, 0, Room45V1Chain73_id
    End
Room45V1Chain13:
    CancelObjectAnimSequence 0, 255
    SetTileObjectAnimState Room45V1Group0_id, 8
    SetTileObjectAnimState Room45V1Group0_id, 7
    SetQuestState 2, 231
    SetQuestState 2, 224
    ArmChainYield 1
    StartTileObjectScript 611, 27, 2, 0, 255, 0, 0, 2, 255, 255, 255
    SetTileObjectFacing 0, 255, 6
    ArmChainYield 0
    DelayedRespawnRowAndRunChain 0, Room45V1Group5_id, 0
    ArmChainYield 1
    QueueTileObjectMove Room45V1Group5_id, 0, 0, 0, 1200, 0
    StartObjectAnimSequence Room45V1Group5_id, 0, 0, 33, Room45V1Route1_id, 0, 1, 0, 0, 0
    @ "Any luck?"
    @ "No. You?"
    @ "I'm afraid not. They must have gone this way."
    ShowRoomDialog 562
    StartTileObjectScript 611, 27, 2, Room45V1Group5_id, 0, 0, 0, 4, 255, 255, 255
    DespawnTileObject Room45V1Group20_id, 0
    DespawnTileObject Room45V1Group5_id, 0
    RecruitPartyFollower 6
    QueueTileObjectMove 0, 255, 0, 0, 1600, 0
    SetTileObjectFacing 0, 255, 4
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room45V1Chain14:
    RespawnRowAndRunChain Room45V1Group3_id, 0
    DespawnTileObject Room45V1Group1_id, 7
    End
Room45V1Chain15:
    DespawnRoomRowObjects Room45V1Group2_id
    End
Room45V1Chain16:
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain17:
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain18:
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain19:
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain20:
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain21:
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain22:
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain23:
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain24:
    DespawnTileObject Room45V0Group0_id, 0
    End
Room45V1Chain25:
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 224
    ArmChainYield 1
    StartTileObjectScript 567, 120, 0, 0, 255, 0, 0, 4, 255, 255, 255
    @ "We have to find Ron! Maybe we should split up¸"
    ShowRoomDialog 560
    SetTileObjectFacing 0, 255, 6
    DelayedRespawnRowAndRunChainFrames 28, 0, 0
    SetTileObjectFacing 0, 255, 2
    DelayedRespawnRowAndRunChainFrames 20, 0, 0
    SetTileObjectFacing 0, 255, 6
    DelayedRespawnRowAndRunChainFrames 16, 0, 0
    SetTileObjectFacing 0, 255, 2
    DelayedRespawnRowAndRunChainFrames 26, 0, 0
    SetTileObjectFacing 0, 255, 4
    DelayedRespawnRowAndRunChainFrames 4, 0, 0
    QueueTileObjectMove Room45V1Group0_id, 4, 0, 0, 1500, 0
    ShowLoadingScreenTransition 29, 30, 32, 255
    GotoIfStoryStageCompare 0, 29, Room45V1Chain26_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 30, Room45V1Chain27_id, 0, 0, 0
    End
Room45V1Chain26:
    QueueTileObjectMove 0, 255, 0, 0, 1500, 0
    RemovePartyFollower 6
    RespawnRowAndRunChain Room45V1Group20_id, 0
    DespawnTileObject Room45V1Group0_id, 4
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room45V1Chain27:
    RemovePartyFollower 5
    ArmChainYield 1
    QueueTileObjectMove 0, 255, 0, 0, 1500, 0
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group1_id, 0
    DespawnTileObject Room45V1Group0_id, 4
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group21_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room45V1Chain28:
    SetTileObjectFacing Room45V1Group4_id, 0, 6
    End
Room45V1Chain29:
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group18_id, 0
    DelayedRespawnRowAndRunChain 1, 0, Room45V1Chain65_id
    End
Room45V1Chain30:
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group19_id, 0
    DelayedRespawnRowAndRunChain 1, 0, Room45V1Chain66_id
    End
Room45V1Chain31:
    CancelObjectAnimSequence 0, 255
    QueueTileObjectMove Room45V0Group0_id, 3, 0, 60, 1500, 30
    End
Room45V1Chain32:
    SetTileObjectFacing Room45V1Group5_id, 0, 2
    End
Room45V1Chain33:
    GotoIfQuestStateCompare QUEST_STORY_STAGE, 0, 22, Room45V1Chain58_id, 0, 0, 0
    End
Room45V1Chain34:
    DespawnTileObject Room45V1Group7_id, 0
    End
Room45V1Chain35:
    DespawnTileObject Room45V1Group8_id, 0
    End
Room45V1Chain36:
    DespawnTileObject Room45V1Group9_id, 0
    End
Room45V1Chain37:
    DespawnTileObject Room45V1Group10_id, 0
    End
Room45V1Chain38:
    DespawnTileObject Room45V1Group11_id, 0
    End
Room45V1Chain39:
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group7_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group13_id, 0
    DelayedRespawnRowAndRunChainFrames 0, 0, 0
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group14_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group15_id, 0
    End
Room45V1Chain40:
    DespawnRoomRowObjects Room45V1Group14_id
    SetTileObjectAnimState Room45V1Group15_id, 1
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group9_id, 0
    GotoIfQuestStateCompare 227, 0, 0, Room45V1Chain53_id, 0, 0, 0
    SetQuestState 1, 227
    End
Room45V1Chain41:
    DespawnRoomRowObjects Room45V1Group12_id
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group8_id, 0
    SetTileObjectAnimState Room45V1Group15_id, 0
    GotoIfQuestStateCompare 226, 0, 0, Room45V1Chain53_id, 0, 0, 0
    SetQuestState 1, 226
    End
Room45V1Chain42:
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group10_id, 0
    SetTileObjectAnimState Room45V1Group15_id, 2
    GotoIfQuestStateCompare 226, 0, 0, Room45V1Chain53_id, 0, 0, 0
    DespawnRoomRowObjects Room45V1Group13_id
    End
Room45V1Chain43:
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group11_id, 0
    SetTileObjectAnimState Room45V1Group15_id, 3
    SetQuestState 1, 229
    End
Room45V1Chain44:
    SetTileObjectAnimStateWithSpeed 0, 255
    DespawnTileObject Room45V1Group16_id, 0
    DespawnTileObject Room45V1Group17_id, 0
    End
Room45V1Chain45:
    SetStoryStage 23
    ReturnToOverworld 43, 0
    End
Room45V1Chain46:
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group7_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group12_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group13_id, 0
    DelayedRespawnRowAndRunChainFrames 0, 0, 0
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group14_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group15_id, 0
    End
Room45V1Chain47:
    End
Room45V1Chain48:
    End
Room45V1Chain49:
    SetTileObjectAnimState Room45V1Group15_id, 1
    End
Room45V1Chain50:
    ArmChainYield 1
    GotoIfStoryStageCompare 0, 22, Room45V1Chain54_id, 0, 0, 0
    SetStoryStage 23
    End
Room45V1Chain51:
    GotoIfQuestStateCompare 224, 0, 1, Room45V1Chain12_id, 0, 0, 0
    End
Room45V1Chain52:
    GotoIfQuestStateCompare 224, 0, 1, Room45V1Chain13_id, 0, 0, 0
    End
Room45V1Chain53:
    GrantPartyExperience 10, 65535
    End
Room45V1Chain54:
    GrantPartyExperience 25, 65535
    End
Room45V1Chain55:
    ArmChainYield 1
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    GotoIfStoryStageCompare 0, 30, 0, 0, Room45V1Group1_id, 0
    SetBattleDefeatState 10
    ArmChainYield 0
    End
Room45V1Chain56:
    DespawnTileObject Room45V1Group0_id, 3
    RespawnRowAndRunChain Room45V1Group22_id, 0
    End
Room45V1Chain57:
    DespawnTileObject Room45V1Group0_id, 2
    RespawnRowAndRunChain Room45V1Group23_id, 0
    End
Room45V1Chain58:
    GotoIfQuestStateCompare 224, 0, 0, Room45V1Chain25_id, 0, 0, 0
    End
Room45V1Chain59:
    DespawnRoomRowObjects Room45V1Group6_id
    PlaySoundById 22
    SetTileObjectAnimState Room45V0Group0_id, 3
    QueueTileObjectMove 0, 255, 0, 61, 1500, 0
    End
Room45V1Chain60:
    GrantPartyExperience 50, 65535
    PlayRoomSoundEffect 26
    SetQuestState 1, 231
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group24_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room45V1Chain61:
    SetTileObjectAnimState Room45V0Group0_id, 3
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group24_id, 0
    DespawnRoomRowObjects Room45V1Group6_id
    End
Room45V1Chain62:
    DelayedRespawnRowAndRunChainFrames 3, 0, Room45V1Chain67_id
    End
Room45V1Chain63:
    DespawnTileObject Room45V1Group6_id, 0
    End
Room45V1Chain64:
    DespawnTileObject Room45V1Group6_id, 2
    End
Room45V1Chain65:
    SetQuestState 1, 233
    QueueTileObjectMove Room45V1Group18_id, 0, 0, 72, 1500, 60
    End
Room45V1Chain66:
    SetQuestState 1, 234
    QueueTileObjectMove Room45V1Group19_id, 0, 0, 71, 1500, 60
    End
Room45V1Chain67:
    GotoIfQuestStateCompare 236, 0, 1, Room45V1Chain78_id, 0, 0, 0
    End
Room45V1Chain68:
    SetQuestState 1, 236
    GrantPartyExperience 50, 65535
    End
Room45V1Chain69:
    @ "Locked."
    ShowRoomDialog 624
    End
Room45V1Chain70:
    DespawnTileObject Room45V1Group19_id, 0
    StartBattle 11, 0, 0
    End
Room45V1Chain71:
    DespawnTileObject Room45V1Group18_id, 0
    StartBattle 11, 0, 0
    End
Room45V1Chain72:
    GotoIfQuestStateCompare 233, 0, 1, Room45V1Chain63_id, 0, 0, 0
    GotoIfQuestStateCompare 234, 0, 1, Room45V1Chain64_id, 0, 0, 0
    GotoIfQuestStateCompare 231, 1, 0, Room45V1Chain75_id, 0, 0, 0
    End
Room45V1Chain73:
    ArmChainYield 1
    DelayedRespawnRowAndRunChainFrames 0, Room45V1Group4_id, 0
    StartTileObjectScript 588, 27, 2, Room45V1Group4_id, 0, 0, 0, 6, 255, 255, 255
    SetTileObjectFacing Room45V1Group4_id, 0, 6
    StartTileObjectScript 573, 27, 2, 0, 255, 0, 0, 2, 255, 255, 255
    SetTileObjectFacing 0, 255, 2
    @ "Any luck?"
    @ "No. You?"
    @ "I'm afraid not. They must have gone this way."
    ShowRoomDialog 562
    StartTileObjectScript 573, 27, 2, Room45V1Group4_id, 0, 0, 0, 2, 255, 255, 255
    DespawnTileObject Room45V1Group4_id, 0
    RecruitPartyFollower 5
    SetTileObjectFacing 0, 255, 4
    DelayedRespawnRowAndRunChainFrames 0, 0, Room45V1Chain15_id
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room45V1Chain74:
    GotoIfQuestStateCompare 236, 0, 0, Room45V1Chain10_id, 0, 0, 0
    End
Room45V1Chain75:
    DespawnRoomRowObjects Room45V1Group6_id
    End
Room45V1Chain76:
    GotoIfQuestStateCompare 237, 0, 0, Room45V1Chain77_id, 0, 0, 0
    End
Room45V1Chain77:
    @ "I bet I can sever these ropes with Diffindo."
    ShowRoomDialog 567
    SetQuestState 1, 237
    End
Room45V1Chain78:
    SetTileObjectAnimState Room45V0Group0_id, 1
    End
    EndSubBlock Room45V1End

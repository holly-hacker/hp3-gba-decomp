    .include "asm/room_blob.inc"

Room02Blob:
    RoomBlob 1
    PlayerEntry 718, 1434, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room02V0
    VariantEntry Room02V1

    SubBlock Room02V0, 1, Room02V0Routes, Room02V0Chains, Room02V0End
    OffsetTable Room02V0Groups, 1
    Offsets Room02V0Group0
    EndTable
    Group Room02V0Group0, 6
    Chest 1290, 165, flag_id=25, reward_id=102
    Chest 391, 803, flag_id=24, reward_id=56
    Chest 708, 749, flag_id=26, reward_id=56
    Chest 970, 1100, flag_id=27, reward_id=88
    Chest 113, 536, flag_id=82, reward_id=109
    Chest 1112, 853, flag_id=106, reward_id=101
    OffsetTable Room02V0Routes, 0
    EndTable
    OffsetTable Room02V0Chains, 1
    Offsets Room02V0Chain0
    EndTable
Room02V0Chain0:
    SetBattleDefeatState 4
    End
    EndSubBlock Room02V0End

    SubBlock Room02V1, 1, Room02V1Routes, Room02V1Chains, Room02V1End
    OffsetTable Room02V1Groups, 3, 1
    Offsets Room02V1Group0, Room02V1Group1, Room02V1Group2
    EndTable
    Group Room02V1Group0, 31
    Prop 676, 1120, kind=46, arg_13=0
    MovePlayer 870, 1140, target_x=1003, target_y=1133
    Prop 354, 696, kind=52
    Prop 539, 699, kind=52
    Prop 437, 870, kind=51
    Prop 416, 869, kind=51
    Prop 395, 870, kind=51
    Prop 373, 870, kind=51
    Prop 437, 848, kind=51
    Prop 416, 848, kind=51
    Prop 395, 848, kind=51
    Prop 352, 848, kind=51
    Prop 636, 385, kind=51
    Prop 636, 361, kind=51
    Prop 636, 406, kind=51
    Prop 352, 870, kind=51
    Prop 373, 848, kind=51
    MovePlayer 965, 1170, target_x=842, target_y=1161
    MovePlayer 1077, 407, target_x=1013, target_y=397
    MovePlayer 1012, 405, target_x=934, target_y=400
    Prop 537, 737, kind=46, arg_13=0
    Chest 422, 296, flag_id=105, reward_id=65, chain=Room02V1Chain1_id
    Chest 243, 534, flag_id=104, reward_id=64, chain=Room02V1Chain1_id
    Chest 1318, 146, flag_id=101, reward_id=63, chain=Room02V1Chain1_id
    Chest 1399, 885, flag_id=100, reward_id=64, chain=Room02V1Chain1_id
    Chest 403, 1165, flag_id=103, reward_id=63, chain=Room02V1Chain1_id
    Chest 710, 503, flag_id=102, reward_id=66, chain=Room02V1Chain1_id
    MovePlayer 942, 405, target_x=1101, target_y=398
    TriggerZone 717, 1491, half_width=34, half_height=16, chain=Room02V1Chain3_id
    Prop 861, 672, kind=6, arg_12=1
    Prop 735, 1120, kind=6, arg_12=1
    Group Room02V1Group1, 0
    Group Room02V1Group2, 2
    TriggerZone 591, 349, half_width=13, half_height=32, chain=Room02V1Chain4_id
    Npc 592, 348, sprite=104, facing=0
    OffsetTable Room02V1Routes, 1
    Offsets Room02V1Route0
    EndTable
Room02V1Route0:
    Route 2
    Waypoint 590, 344
    Waypoint 590, 355
    OffsetTable Room02V1Chains, 7, 1
    Offsets Room02V1Chain0, Room02V1Chain1, Room02V1Chain2, Room02V1Chain3, Room02V1Chain4, Room02V1Chain5
    Offsets Room02V1Chain6
    EndTable
Room02V1Chain0:
    ClearOverworldMonstersDisabled
    GotoIfQuestStateCompare 14, 1, 17, Room02V1Chain6_id, 0, Room02V1Group2_id, 0
    End
Room02V1Chain1:
    ArmChainYield 1
    AddQuestState 1, 231
    GotoIfQuestStateCompare 231, 3, 4, Room02V1Chain2_id, 0, 0, 0
    End
Room02V1Chain2:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    GrantPartyExperience 10, 65535
    PlayRoomSoundEffect 24
    DelayedRespawnRowAndRunChain 0, Room02V1Group1_id, 0
    SetQuestState QUEST_OBJ_RETURN_INGREDIENTS_TO_SNAPE, QUEST_OBJECTIVE_INDEX
    @ "There, we have all the ingredients. Now we need to get them back to class."
    ShowRoomDialog 318
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room02V1Chain3:
    ArmChainYield 1
    SetOverworldMonstersDisabled
    ReturnToOverworld 1, 1
    End
Room02V1Chain4:
    DespawnTileObject Room02V1Group2_id, 1
    StartBattle 9, 0, Room02V1Chain5_id
    End
Room02V1Chain5:
    SetQuestState 17, 14
    End
Room02V1Chain6:
    StartObjectAnimSequence Room02V1Group2_id, 1, 0, 0, Room02V1Route0_id, 0, 0, 0, 0, 0
    End
    EndSubBlock Room02V1End

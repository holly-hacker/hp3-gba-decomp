    .include "asm/room_blob.inc"

Room35Blob:
    RoomBlob 2
    PlayerEntry 432, 733, 0, 0
    PlayerEntry 99, 713, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room35V0
    VariantEntry Room35V1

    SubBlock Room35V0, 1, Room35V0Routes, Room35V0Chains, Room35V0End
    OffsetTable Room35V0Groups, 1
    Offsets Room35V0Group0
    EndTable
    Group Room35V0Group0, 5
    Door 47, 711, half_width=13, half_height=29, destination_room=20, exit_param=4
    Door 387, 743, half_width=14, half_height=18, destination_room=34, exit_param=2
    Chest 606, 343, flag_id=35, reward_id=128
    Chest 296, 1089, flag_id=36, reward_id=60
    Chest 105, 931, flag_id=37, reward_id=124, kind=2
    OffsetTable Room35V0Routes, 0
    EndTable
    OffsetTable Room35V0Chains, 1
    Offsets Room35V0Chain0
    EndTable
Room35V0Chain0:
    End
    EndSubBlock Room35V0End

    SubBlock Room35V1, 1, Room35V1Routes, Room35V1Chains, Room35V1End
    OffsetTable Room35V1Groups, 2, 1
    Offsets Room35V1Group0, Room35V1Group1
    EndTable
    Group Room35V1Group0, 2
    TriggerZone 420, 739, half_width=21, half_height=21, chain=Room35V1Chain9_id
    TriggerZone 94, 719, half_width=19, half_height=45, chain=Room35V1Chain11_id
    Group Room35V1Group1, 18
    MovePlayer 287, 271, target_x=371, target_y=233, variant=1
    Switch 446, 334, variant=1, unk_08=4, on_deactivate_chain=Room35V1Chain2_id
    Switch 365, 335, variant=1, unk_08=4, on_deactivate_chain=Room35V1Chain2_id
    Prop 419, 369, kind=81, arg_0f=1
    Prop 390, 369, kind=81, arg_0f=1
    MovePlayer 543, 488, target_x=472, target_y=673, variant=1, arg_0e=23
    MovePlayer 212, 985, target_x=163, target_y=921, variant=1
    TileAnimation 501, 371, anim_id=27
    Prop 470, 495, kind=46, arg_13=0
    Breakable 508, 462, variant=0, group0=Room35V1Group1_id, group1=Room35V1Group1_id
    Chest 551, 365, flag_id=80, reward_id=74, chain=Room35V1Chain4_id
    TriggerZone 350, 889, half_width=21, half_height=17, chain=Room35V1Chain5_id
    Npc 351, 890, sprite=38, facing=6
    Chest 310, 889, flag_id=81, reward_id=74, chain=Room35V1Chain4_id
    TriggerZone 92, 717, half_width=0, half_height=0, rearm_delay=3, trigger_kind=1
    MovePlayer 512, 761, target_x=538, target_y=822
    Prop 387, 422, kind=81
    Prop 426, 422, kind=81
    OffsetTable Room35V1Routes, 0
    EndTable
    OffsetTable Room35V1Chains, 24, 1
    Offsets Room35V1Chain0, Room35V1Chain1, Room35V1Chain2, Room35V1Chain3, Room35V1Chain4, Room35V1Chain5
    Offsets Room35V1Chain6, Room35V1Chain7, Room35V1Chain8, Room35V1Chain9, Room35V1Chain10, Room35V1Chain11
    Offsets Room35V1Chain12, Room35V1Chain13, Room35V1Chain14, Room35V1Chain15, Room35V1Chain16, Room35V1Chain17
    Offsets Room35V1Chain18, Room35V1Chain19, Room35V1Chain20, Room35V1Chain21, Room35V1Chain22, Room35V1Chain23
    EndTable
Room35V1Chain0:
    ClearOverworldMonstersDisabled
    GotoIfQuestStateCompare QUEST_OBJECTIVE_INDEX, 0, QUEST_OBJ_FIND_BOOK_PAGES, Room35V1Chain12_id, 0, 0, 0
    End
Room35V1Chain1:
    AddQuestState 1, 128
    GotoIfQuestStateCompare 128, 0, 2, Room35V1Chain3_id, 0, 0, 0
    End
Room35V1Chain2:
    GotoIfQuestStateCompare 6, 1, 67, Room35V1Chain17_id, 0, 0, 0
    End
Room35V1Chain3:
    SetTileObjectAnimState Room35V1Group1_id, 7
    GotoIfQuestStateCompare 6, 1, 67, Room35V1Chain8_id, 0, 0, 0
    PlaySoundById 22
    End
Room35V1Chain4:
    AddQuestState 1, 4
    GotoIfQuestStateCompare 4, 0, 1, Room35V1Chain13_id, Room35V1Chain16_id, 0, 0
    End
Room35V1Chain5:
    StartBattle 10, 0, Room35V1Chain20_id
    DespawnTileObject Room35V1Group1_id, 12
    End
Room35V1Chain6:
    SetTileObjectAnimStateValue Room35V1Group1_id, 3, 5
    SetTileObjectAnimStateValue Room35V1Group1_id, 4, 5
    DespawnTileObject Room35V1Group1_id, 9
    SetTileObjectAnimState Room35V1Group1_id, 7
    End
Room35V1Chain7:
    PlayTileObjectAnimation Room35V1Group1_id, 12, 25
    SetQuestState 23, 8
    End
Room35V1Chain8:
    SetQuestState 67, 6
    GrantPartyExperience 10, 65535
    SetTileObjectAnimStateValue Room35V1Group1_id, 3, 5
    SetTileObjectAnimStateValue Room35V1Group1_id, 4, 5
    DespawnTileObject Room35V1Group1_id, 9
    End
Room35V1Chain9:
    GotoIfStoryStageCompare 0, 8, Room35V1Chain10_id, 0, Room35V1Group1_id, 0
    GotoIfStoryStageCompare 0, 8, Room35V1Chain18_id, 0, 0, 0
    End
Room35V1Chain10:
    DespawnTileObject Room35V1Group0_id, 0
    DespawnTileObject Room35V1Group0_id, 1
    End
Room35V1Chain11:
    DespawnTileObject Room35V1Group0_id, 0
    End
Room35V1Chain12:
    DelayedRespawnRowAndRunChainFrames 3, 0, Room35V1Chain23_id
    RespawnRowAndRunChain 0, Room35V1Chain9_id
    End
Room35V1Chain13:
    @ "Here's the first book page. We'd better find the rest."
    ShowRoomDialog 420
    End
Room35V1Chain14:
    @ "Here's another book page."
    ShowRoomDialog 421
    End
Room35V1Chain15:
    @ "Great! We've found all the pages! Let's take them back to Madam Pince."
    ShowRoomDialog 422
    End
Room35V1Chain16:
    GotoIfQuestStateCompare 4, 1, 5, Room35V1Chain14_id, Room35V1Chain15_id, 0, 0
    End
Room35V1Chain17:
    SubtractQuestState 1, 128
    GotoIfQuestStateCompare 128, 0, 1, Room35V1Chain3_id, 0, 0, 0
    End
Room35V1Chain18:
    GotoIfQuestStateCompare 12, 1, 27, Room35V1Chain7_id, Room35V1Chain19_id, 0, 0
    End
Room35V1Chain19:
    DespawnTileObject Room35V1Group1_id, 12
    DespawnTileObject Room35V1Group1_id, 11
    End
Room35V1Chain20:
    SetQuestState 27, 12
    End
Room35V1Chain21:
    SetTileObjectAnimState Room35V1Group1_id, 9
    End
Room35V1Chain22:
    GotoIfQuestStateCompare 6, 1, 67, Room35V1Chain21_id, 0, 0, 0
    End
Room35V1Chain23:
    GotoIfQuestStateCompare 6, 0, 67, Room35V1Chain6_id, 0, 0, 0
    End
    EndSubBlock Room35V1End

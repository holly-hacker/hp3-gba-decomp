    .include "asm/room_blob.inc"

Room10Blob:
    RoomBlob 4
    PlayerEntry 630, 791, 0, 0
    PlayerEntry 177, 409, 1, 0
    PlayerEntry 1518, 788, 2, 0
    PlayerEntry 193, 621, 3, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room10V0
    VariantEntry Room10V1

    SubBlock Room10V0, 1, Room10V0Routes, Room10V0Chains, Room10V0End
    OffsetTable Room10V0Groups, 1
    Offsets Room10V0Group0
    EndTable
    Group Room10V0Group0, 4
    Door 1519, 828, half_width=23, half_height=11, destination_room=9
    Door 575, 829, half_width=24, half_height=19, destination_room=15, exit_param=7
    Chest 1038, 272, flag_id=115, reward_id=4
    Chest 1450, 605, flag_id=62, reward_id=128
    OffsetTable Room10V0Routes, 0
    EndTable
    OffsetTable Room10V0Chains, 1
    Offsets Room10V0Chain0
    EndTable
Room10V0Chain0:
    End
    EndSubBlock Room10V0End

    SubBlock Room10V1, 1, Room10V1Routes, Room10V1Chains, Room10V1End
    OffsetTable Room10V1Groups, 2, 1
    Offsets Room10V1Group0, Room10V1Group1
    EndTable
    Group Room10V1Group0, 0
    Group Room10V1Group1, 2
    Npc 187, 622, sprite=99, facing=2
    Npc 197, 630, sprite=5, facing=2
    OffsetTable Room10V1Routes, 2
    Offsets Room10V1Route0, Room10V1Route1
    EndTable
Room10V1Route0:
    Route 2
    Waypoint 197, 630
    Waypoint 387, 630, on_arrival_chain=Room10V1Chain2_id
Room10V1Route1:
    Route 2
    Waypoint 187, 622
    Waypoint 376, 622
    OffsetTable Room10V1Chains, 4, 1
    Offsets Room10V1Chain0, Room10V1Chain1, Room10V1Chain2, Room10V1Chain3
    EndTable
Room10V1Chain0:
    GotoIfStoryStageCompare 0, 20, Room10V1Chain3_id, 0, 0, 0
    End
Room10V1Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetOverworldMonstersDisabled
    PlayMusicModuleAndFlagIfChain1 16
    QueueTileObjectMove Room10V1Group1_id, 1, 0, 0, 1800, 0
    ArmChainYield 0
    StartObjectAnimSequence Room10V1Group1_id, 1, 0, 0, Room10V1Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room10V1Group1_id, 0, 0, 0, Room10V1Route1_id, 0, 1, 0, 0, 0
    End
Room10V1Chain2:
    ArmChainYield 1
    SetQuestState 1, 232
    ReturnToOverworld 28, 1
    End
Room10V1Chain3:
    GotoIfQuestStateCompare 232, 0, 1, Room10V1Chain1_id, 0, Room10V1Group1_id, 0
    End
    EndSubBlock Room10V1End

    .include "asm/room_blob.inc"

Room08Blob:
    RoomBlob 2
    PlayerEntry 161, 308, 0, 0
    PlayerEntry 29, 370, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room08V0
    VariantEntry Room08V1

    SubBlock Room08V0, 1, Room08V0Routes, Room08V0Chains, Room08V0End
    OffsetTable Room08V0Groups, 1
    Offsets Room08V0Group0
    EndTable
    Group Room08V0Group0, 1
    Door 7, 385, half_width=11, half_height=34, destination_room=15, exit_param=1
    OffsetTable Room08V0Routes, 0
    EndTable
    OffsetTable Room08V0Chains, 1
    Offsets Room08V0Chain0
    EndTable
Room08V0Chain0:
    End
    EndSubBlock Room08V0End

    SubBlock Room08V1, 1, Room08V1Routes, Room08V1Chains, Room08V1End
    OffsetTable Room08V1Groups, 3, 1
    Offsets Room08V1Group0, Room08V1Group1, Room08V1Group2
    EndTable
    Group Room08V1Group0, 0
    Group Room08V1Group1, 1
    Door 191, 295, half_width=13, half_height=39, destination_room=16
    Group Room08V1Group2, 1
    TriggerZone 185, 300, half_width=13, half_height=54, rearm_delay=5, trigger_kind=1, chain=Room08V1Chain1_id
    OffsetTable Room08V1Routes, 0
    EndTable
    OffsetTable Room08V1Chains, 5, 1
    Offsets Room08V1Chain0, Room08V1Chain1, Room08V1Chain2, Room08V1Chain3, Room08V1Chain4
    EndTable
Room08V1Chain0:
    GotoIfStoryStageCompare 5, 24, 0, Room08V1Chain4_id, Room08V1Group1_id, 0
    GotoIfStoryStageCompare 3, 25, Room08V1Chain2_id, 0, Room08V1Group2_id, 0
    End
Room08V1Chain1:
    @ "We'd better get Buckbeak to a safe place before we go back inside."
    ShowRoomDialog 600
    End
Room08V1Chain2:
    GotoIfQuestStateCompare 130, 0, 2, Room08V1Chain3_id, 0, 0, 0
    End
Room08V1Chain3:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RecruitPartyFollower 8
    SetQuestState 1, 130
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room08V1Chain4:
    GotoIfQuestStateCompare 130, 5, 1, 0, 0, Room08V1Group2_id, 0
    End
    EndSubBlock Room08V1End

    .include "asm/room_blob.inc"

Room09Blob:
    RoomBlob 1
    PlayerEntry 159, 35, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room09V0
    VariantEntry Room09V1

    SubBlock Room09V0, 1, Room09V0Routes, Room09V0Chains, Room09V0End
    OffsetTable Room09V0Groups, 1
    Offsets Room09V0Group0
    EndTable
    Group Room09V0Group0, 2
    Door 159, 9, half_width=19, half_height=10, destination_room=10, exit_param=2
    Chest 474, 283, flag_id=116, reward_id=53
    OffsetTable Room09V0Routes, 0
    EndTable
    OffsetTable Room09V0Chains, 1
    Offsets Room09V0Chain0
    EndTable
Room09V0Chain0:
    End
    EndSubBlock Room09V0End

    SubBlock Room09V1, 1, Room09V1Routes, Room09V1Chains, Room09V1End
    OffsetTable Room09V1Groups, 1, 1
    Offsets Room09V1Group0
    EndTable
    Group Room09V1Group0, 1
    Prop 145, 109, kind=6, arg_12=1
    OffsetTable Room09V1Routes, 0
    EndTable
    OffsetTable Room09V1Chains, 1, 1
    Offsets Room09V1Chain0
    EndTable
Room09V1Chain0:
    End
    EndSubBlock Room09V1End

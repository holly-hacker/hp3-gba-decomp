    .include "asm/room_blob.inc"

Room48Blob:
    RoomBlob 2
    PlayerEntry 79, 339, 0, 0
    PlayerEntry 366, 325, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room48V0
    VariantEntry Room48V1

    SubBlock Room48V0, 1, Room48V0Routes, Room48V0Chains, Room48V0End
    OffsetTable Room48V0Groups, 1
    Offsets Room48V0Group0
    EndTable
    Group Room48V0Group0, 2
    Door 76, 389, half_width=40, half_height=20, destination_room=45, exit_param=5
    Door 384, 333, half_width=11, half_height=40, destination_room=49
    OffsetTable Room48V0Routes, 0
    EndTable
    OffsetTable Room48V0Chains, 1
    Offsets Room48V0Chain0
    EndTable
Room48V0Chain0:
    End
    EndSubBlock Room48V0End

    SubBlock Room48V1, 1, Room48V1Routes, Room48V1Chains, Room48V1End
    OffsetTable Room48V1Groups, 1, 1
    Offsets Room48V1Group0
    EndTable
    Group Room48V1Group0, 0
    OffsetTable Room48V1Routes, 0
    EndTable
    OffsetTable Room48V1Chains, 1, 1
    Offsets Room48V1Chain0
    EndTable
Room48V1Chain0:
    End
    EndSubBlock Room48V1End

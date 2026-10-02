    .include "asm/room_blob.inc"

Room54Blob:
    RoomBlob 2
    PlayerEntry 42, 255, 0, 0
    PlayerEntry 459, 258, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room54V0
    VariantEntry Room54V1

    SubBlock Room54V0, 1, Room54V0Routes, Room54V0Chains, Room54V0End
    OffsetTable Room54V0Groups, 1
    Offsets Room54V0Group0
    EndTable
    Group Room54V0Group0, 4
    Prop 42, 219, kind=8
    Door 10, 241, half_width=10, half_height=14, destination_room=53, exit_param=1
    Door 501, 241, half_width=9, half_height=16, destination_room=50
    Npc 119, 253, sprite=36, facing=5
    OffsetTable Room54V0Routes, 0
    EndTable
    OffsetTable Room54V0Chains, 1
    Offsets Room54V0Chain0
    EndTable
Room54V0Chain0:
    End
    EndSubBlock Room54V0End

    SubBlock Room54V1, 1, Room54V1Routes, Room54V1Chains, Room54V1End
    OffsetTable Room54V1Groups, 1, 1
    Offsets Room54V1Group0
    EndTable
    Group Room54V1Group0, 0
    OffsetTable Room54V1Routes, 0
    EndTable
    OffsetTable Room54V1Chains, 1, 1
    Offsets Room54V1Chain0
    EndTable
Room54V1Chain0:
    End
    EndSubBlock Room54V1End

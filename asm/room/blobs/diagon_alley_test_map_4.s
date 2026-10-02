    .include "asm/room_blob.inc"

Room53Blob:
    RoomBlob 2
    PlayerEntry 50, 256, 0, 0
    PlayerEntry 456, 255, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room53V0
    VariantEntry Room53V1

    SubBlock Room53V0, 1, Room53V0Routes, Room53V0Chains, Room53V0End
    OffsetTable Room53V0Groups, 1
    Offsets Room53V0Group0
    EndTable
    Group Room53V0Group0, 3
    Prop 50, 213, kind=3
    Door 10, 240, half_width=8, half_height=14, destination_room=52, exit_param=1
    Door 501, 241, half_width=9, half_height=13, destination_room=54
    OffsetTable Room53V0Routes, 0
    EndTable
    OffsetTable Room53V0Chains, 1
    Offsets Room53V0Chain0
    EndTable
Room53V0Chain0:
    End
    EndSubBlock Room53V0End

    SubBlock Room53V1, 1, Room53V1Routes, Room53V1Chains, Room53V1End
    OffsetTable Room53V1Groups, 1, 1
    Offsets Room53V1Group0
    EndTable
    Group Room53V1Group0, 2
    Npc 107, 255, sprite=99, facing=2
    Npc 107, 255, sprite=2, facing=2
    OffsetTable Room53V1Routes, 1
    Offsets Room53V1Route0
    EndTable
Room53V1Route0:
    Route 4
    Waypoint 135, 255
    Waypoint 390, 255
    Waypoint 390, 302
    Waypoint 135, 302
    OffsetTable Room53V1Chains, 1, 1
    Offsets Room53V1Chain0
    EndTable
Room53V1Chain0:
    SetTileObjectSpecialFlag Room53V1Group0_id, 1, 1
    PlayTileObjectAnimation Room53V1Group0_id, 1, 22
    StartObjectAnimSequence Room53V1Group0_id, 1, 0, 0, Room53V1Route0_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room53V1Group0_id, 0, 0, 0, Room53V1Route0_id, 0, 0, 0, 0, 0
    End
    EndSubBlock Room53V1End

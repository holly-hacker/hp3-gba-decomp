    .include "asm/room_blob.inc"

Room46Blob:
    RoomBlob 2
    PlayerEntry 157, 514, 0, 0
    PlayerEntry 57, 475, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room46V0
    VariantEntry Room46V1

    SubBlock Room46V0, 1, Room46V0Routes, Room46V0Chains, Room46V0End
    OffsetTable Room46V0Groups, 1
    Offsets Room46V0Group0
    EndTable
    Group Room46V0Group0, 2
    Door 50, 531, half_width=23, half_height=13, destination_room=45, exit_param=2
    Door 156, 571, half_width=23, half_height=13, destination_room=45, exit_param=3
    OffsetTable Room46V0Routes, 0
    EndTable
    OffsetTable Room46V0Chains, 1
    Offsets Room46V0Chain0
    EndTable
Room46V0Chain0:
    End
    EndSubBlock Room46V0End

    SubBlock Room46V1, 1, Room46V1Routes, Room46V1Chains, Room46V1End
    OffsetTable Room46V1Groups, 1, 1
    Offsets Room46V1Group0
    EndTable
    Group Room46V1Group0, 3
    ContactTrigger 105, 347, chain=0
    TriggerZone 156, 295, half_width=11, half_height=9, rearm_delay=3, trigger_kind=1, chain=Room46V1Chain1_id
    Prop 155, 250, kind=51
    OffsetTable Room46V1Routes, 1
    Offsets Room46V1Route0
    EndTable
Room46V1Route0:
    Route 2
    Waypoint 156, 296
    Waypoint 156, 405, on_arrival_chain=Room46V1Chain2_id
    OffsetTable Room46V1Chains, 3, 1
    Offsets Room46V1Chain0, Room46V1Chain1, Room46V1Chain2
    EndTable
Room46V1Chain0:
    End
Room46V1Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ClearTileObjectFlagBit 0, 255, 9
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room46V1Route0_id, 0, 6, 0, 0, 0
    End
Room46V1Chain2:
    SetTileObjectAnimStateWithSpeed 0, 255
    End
    EndSubBlock Room46V1End

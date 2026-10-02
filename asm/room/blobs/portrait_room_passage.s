    .include "asm/room_blob.inc"

Room32Blob:
    RoomBlob 2
    PlayerEntry 49, 204, 0, 2
    PlayerEntry 256, 103, 1, 6
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room32V0
    VariantEntry Room32V1

    SubBlock Room32V0, 1, Room32V0Routes, Room32V0Chains, Room32V0End
    OffsetTable Room32V0Groups, 1
    Offsets Room32V0Group0
    EndTable
    Group Room32V0Group0, 0
    OffsetTable Room32V0Routes, 0
    EndTable
    OffsetTable Room32V0Chains, 1
    Offsets Room32V0Chain0
    EndTable
Room32V0Chain0:
    End
    EndSubBlock Room32V0End

    SubBlock Room32V1, 1, Room32V1Routes, Room32V1Chains, Room32V1End
    OffsetTable Room32V1Groups, 3, 1
    Offsets Room32V1Group0, Room32V1Group1, Room32V1Group2
    EndTable
    Group Room32V1Group0, 2
    TriggerZone 248, 109, half_width=15, half_height=15, respawn_group=Room32V1Group1_id, chain=Room32V1Chain1_id
    TriggerZone 53, 203, half_width=15, half_height=15, respawn_group=Room32V1Group2_id, chain=Room32V1Chain2_id
    Group Room32V1Group1, 1
    DoorAlt 65, 199, half_width=10, half_height=10, destination_room=1
    Group Room32V1Group2, 1
    DoorAlt 242, 109, half_width=10, half_height=10, destination_room=0
    OffsetTable Room32V1Routes, 0
    EndTable
    OffsetTable Room32V1Chains, 3, 1
    Offsets Room32V1Chain0, Room32V1Chain1, Room32V1Chain2
    EndTable
Room32V1Chain0:
    End
Room32V1Chain1:
    PlayRoomSoundEffect 41
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    PlaySpecialSceneEffect 4
    DespawnTileObject Room32V1Group0_id, 1
    End
Room32V1Chain2:
    PlayRoomSoundEffect 40
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    PlaySpecialSceneEffect 5
    DespawnTileObject Room32V1Group0_id, 0
    End
    EndSubBlock Room32V1End

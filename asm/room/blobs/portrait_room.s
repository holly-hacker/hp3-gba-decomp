    .include "asm/room_blob.inc"

Room31Blob:
    RoomBlob 9
    PlayerEntry 202, 190, 0, 4
    PlayerEntry 122, 284, 1, 2
    PlayerEntry 431, 191, 2, 4
    PlayerEntry 543, 189, 3, 4
    PlayerEntry 656, 190, 4, 4
    PlayerEntry 216, 329, 5, 4
    PlayerEntry 432, 328, 6, 4
    PlayerEntry 533, 329, 7, 4
    PlayerEntry 519, 401, 8, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room31V0
    VariantEntry Room31V1

    SubBlock Room31V0, 1, Room31V0Routes, Room31V0Chains, Room31V0End
    OffsetTable Room31V0Groups, 1
    Offsets Room31V0Group0
    EndTable
    Group Room31V0Group0, 10
    DoorAlt 195, 158, half_width=18, half_height=9, destination_room=18, exit_param=4
    DoorAlt 428, 161, half_width=19, half_height=6, destination_room=19
    DoorAlt 548, 159, half_width=19, half_height=8, destination_room=20, exit_param=6
    DoorAlt 659, 158, half_width=19, half_height=6, destination_room=21
    DoorAlt 215, 293, half_width=22, half_height=9, destination_room=22
    DoorAlt 430, 293, half_width=22, half_height=9, destination_room=23
    DoorAlt 542, 293, half_width=19, half_height=10, destination_room=24
    Chest 108, 193, flag_id=15, reward_id=99
    Door 79, 292, half_width=10, half_height=25, destination_room=16, exit_param=5
    Door 519, 449, half_width=24, half_height=6, destination_room=17
    OffsetTable Room31V0Routes, 0
    EndTable
    OffsetTable Room31V0Chains, 1
    Offsets Room31V0Chain0
    EndTable
Room31V0Chain0:
    SetDefeatWarpSelector 2
    End
    EndSubBlock Room31V0End

    SubBlock Room31V1, 1, Room31V1Routes, Room31V1Chains, Room31V1End
    OffsetTable Room31V1Groups, 2, 1
    Offsets Room31V1Group0, Room31V1Group1
    EndTable
    Group Room31V1Group0, 0
    Group Room31V1Group1, 0
    OffsetTable Room31V1Routes, 0
    EndTable
    OffsetTable Room31V1Chains, 3, 1
    Offsets Room31V1Chain0, Room31V1Chain1, Room31V1Chain2
    EndTable
Room31V1Chain0:
    GotoIfStoryStageCompare 0, 17, Room31V1Chain2_id, 0, 0, 0
    End
Room31V1Chain1:
    @ "Locked."
    ShowRoomDialog 624
    End
Room31V1Chain2:
    ClearOverworldMonstersDisabled
    End
    EndSubBlock Room31V1End

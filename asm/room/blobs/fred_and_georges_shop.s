    .include "asm/room_blob.inc"

Room36Blob:
    RoomBlob 1
    PlayerEntry 101, 191, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room36V0
    VariantEntry Room36V1

    SubBlock Room36V0, 1, Room36V0Routes, Room36V0Chains, Room36V0End
    OffsetTable Room36V0Groups, 1
    Offsets Room36V0Group0
    EndTable
    Group Room36V0Group0, 2
    Chest 126, 151, flag_id=38, reward_id=106
    Door 59, 186, half_width=6, half_height=19, destination_room=24, exit_param=4
    OffsetTable Room36V0Routes, 0
    EndTable
    OffsetTable Room36V0Chains, 1
    Offsets Room36V0Chain0
    EndTable
Room36V0Chain0:
    SetDefeatWarpSelector 2 @ Hospital Wing
    End
    EndSubBlock Room36V0End

    SubBlock Room36V1, 1, Room36V1Routes, Room36V1Chains, Room36V1End
    OffsetTable Room36V1Groups, 1, 1
    Offsets Room36V1Group0
    EndTable
    Group Room36V1Group0, 2
    Npc 122, 136, sprite=29, facing=4, interact_cooldown=3, interact_mode=1, chain=Room36V1Chain1_id
    Npc 143, 136, sprite=30, facing=4, interact_cooldown=3, interact_mode=1, chain=Room36V1Chain1_id
    OffsetTable Room36V1Routes, 0
    EndTable
    OffsetTable Room36V1Chains, 2, 1
    Offsets Room36Noop, Room36V1Chain1
    EndTable
Room36Noop:
    End
Room36V1Chain1:
    EnterFredAndGeorgesShop 0, 0, 0
    End
    EndSubBlock Room36V1End

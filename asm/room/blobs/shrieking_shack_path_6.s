    .include "asm/room_blob.inc"

Room49Blob:
    RoomBlob 1
    PlayerEntry 165, 510, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room49V0
    VariantEntry Room49V1

    SubBlock Room49V0, 1, Room49V0Routes, Room49V0Chains, Room49V0End
    OffsetTable Room49V0Groups, 1
    Offsets Room49V0Group0
    EndTable
    Group Room49V0Group0, 1
    Door 115, 516, half_width=14, half_height=26, destination_room=48, exit_param=1
    OffsetTable Room49V0Routes, 0
    EndTable
    OffsetTable Room49V0Chains, 1
    Offsets Room49V0Chain0
    EndTable
Room49V0Chain0:
    End
    EndSubBlock Room49V0End

    SubBlock Room49V1, 1, Room49V1Routes, Room49V1Chains, Room49V1End
    OffsetTable Room49V1Groups, 1, 1
    Offsets Room49V1Group0
    EndTable
    Group Room49V1Group0, 1
    Switch 60, 153, variant=6
    OffsetTable Room49V1Routes, 0
    EndTable
    OffsetTable Room49V1Chains, 3, 1
    Offsets Room49V1Chain0, Room49V1Chain1, Room49V1Chain2
    EndTable
Room49V1Chain0:
    End
Room49V1Chain1:
    ArmChainYield 1
    GotoIfQuestStateCompare 229, 0, 0, Room49V1Chain2_id, 0, 0, 0
    SetQuestState 1, 229
    End
Room49V1Chain2:
    GrantPartyExperience 10, 65535
    End
    EndSubBlock Room49V1End

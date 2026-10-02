    .include "asm/room_blob.inc"

Room47Blob:
    RoomBlob 1
    PlayerEntry 834, 676, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room47V0
    VariantEntry Room47V1

    SubBlock Room47V0, 1, Room47V0Routes, Room47V0Chains, Room47V0End
    OffsetTable Room47V0Groups, 1
    Offsets Room47V0Group0
    EndTable
    Group Room47V0Group0, 3
    Door 883, 677, half_width=13, half_height=46, destination_room=45, exit_param=4
    TileAnimation 264, 303, anim_id=50
    TileAnimation 393, 240, anim_id=51
    OffsetTable Room47V0Routes, 0
    EndTable
    OffsetTable Room47V0Chains, 1
    Offsets Room47V0Chain0
    EndTable
Room47V0Chain0:
    End
    EndSubBlock Room47V0End

    SubBlock Room47V1, 1, Room47V1Routes, Room47V1Chains, Room47V1End
    OffsetTable Room47V1Groups, 5, 1
    Offsets Room47V1Group0, Room47V1Group1, Room47V1Group2, Room47V1Group3, Room47V1Group4
    EndTable
    Group Room47V1Group0, 2
    Switch 810, 143, variant=6, on_activate_chain=Room47V1Chain4_id
    TriggerZone 473, 254, half_width=0, half_height=0
    Group Room47V1Group1, 5
    Prop 446, 259, kind=51
    Prop 473, 259, kind=51
    Prop 501, 259, kind=51
    Prop 524, 259, kind=51
    Prop 421, 259, kind=51
    Group Room47V1Group2, 2
    Prop 77, 651, kind=80
    TriggerZone 77, 652, half_width=17, half_height=20, require_a_press=1, chain=Room47V1Chain1_id
    Group Room47V1Group3, 1
    TriggerZone 293, 314, half_width=22, half_height=26, rearm_delay=4, trigger_kind=1, require_a_press=1, chain=Room47V1Chain2_id
    Group Room47V1Group4, 1
    TriggerZone 470, 328, half_width=78, half_height=3, chain=Room47V1Chain8_id
    OffsetTable Room47V1Routes, 0
    EndTable
    OffsetTable Room47V1Chains, 9, 1
    Offsets Room47V1Chain0, Room47V1Chain1, Room47V1Chain2, Room47V1Chain3, Room47V1Chain4, Room47V1Chain5
    Offsets Room47V1Chain6, Room47V1Chain7, Room47V1Chain8
    EndTable
Room47V1Chain0:
    GotoIfQuestStateCompare 230, 5, 1, 0, 0, Room47V1Group3_id, 0
    GotoIfQuestStateCompare 230, 0, 0, 0, 0, Room47V1Group2_id, 0
    GotoIfQuestStateCompare 230, 0, 2, Room47V1Chain6_id, 0, 0, Room47V1Group4_id
    End
Room47V1Chain1:
    SetQuestState 1, 230
    DespawnTileObject Room47V1Group2_id, 0
    GrantRoomReward 75, 0
    ShowRewardPickupMessage 75
    End
Room47V1Chain2:
    GotoIfQuestStateCompare 230, 0, 1, Room47V1Chain3_id, 0, 0, 0
    End
Room47V1Chain3:
    ArmChainYield 1
    DespawnTileObject Room47V1Group3_id, 0
    DespawnRoomRowObjects Room47V1Group4_id
    SetQuestState 2, 230
    CancelObjectAnimSequence 0, 255
    SetTileObjectAnimState Room47V0Group0_id, 1
    DelayedRespawnRowAndRunChain 2, 0, 0
    PlaySoundById 39
    QueueTileObjectMove Room47V1Group0_id, 1, 0, 0, 1200, 0
    SetTileObjectAnimState Room47V0Group0_id, 2
    DelayedRespawnRowAndRunChain 2, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    ConsumeRoomItem 75
.ifdef VERSION_JP
    ShowItemRemovedMessage 75
.endif
    DelayedRespawnRowAndRunChain 1, 0, 0
    UnmuteAllMusicChannels
    RespawnRowAndRunChain Room47V1Group1_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room47V1Chain4:
    ArmChainYield 1
    GotoIfQuestStateCompare 228, 0, 0, Room47V1Chain5_id, 0, 0, 0
    SetQuestState 1, 228
    End
Room47V1Chain5:
    GrantPartyExperience 10, 65535
    PlaySoundById 37
    End
Room47V1Chain6:
    CancelObjectAnimSequence 0, 255
    SetTileObjectAnimState Room47V0Group0_id, 1
    SetTileObjectAnimState Room47V0Group0_id, 2
    DelayedRespawnRowAndRunChainFrames 0, Room47V1Group1_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room47V1Chain7:
    End
Room47V1Chain8:
    @ "There's no way to get over this gap. If we can find a way to turn this valve handle, I can cast my Glacius Spell and freeze the water."
    ShowRoomDialog 569
    End
    EndSubBlock Room47V1End

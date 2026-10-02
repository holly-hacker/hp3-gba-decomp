    .include "asm/room_blob.inc"

Room07Blob:
    RoomBlob 2
    PlayerEntry 77, 222, 0, 2
    PlayerEntry 517, 228, 1, 6
    StageIndex 4
    StageToVariantAll 2
    VariantEntry Room07V0
    VariantEntry Room07V1
    VariantEntry Room07V2
    VariantEntry Room07V3

    SubBlock Room07V0, 1, Room07V0Routes, Room07V0Chains, Room07V0End
    OffsetTable Room07V0Groups, 1
    Offsets Room07V0Group0
    EndTable
    Group Room07V0Group0, 1
    Chest 385, 161, flag_id=13, reward_id=58
    OffsetTable Room07V0Routes, 0
    EndTable
    OffsetTable Room07V0Chains, 1
    Offsets Room07V0Chain0
    EndTable
Room07V0Chain0:
    End
    EndSubBlock Room07V0End

    SubBlock Room07V1, 1, Room07V1Routes, Room07V1Chains, Room07V1End
    OffsetTable Room07V1Groups, 4, 1
    Offsets Room07V1Group0, Room07V1Group1, Room07V1Group2, Room07V1Group3
    EndTable
    Group Room07V1Group0, 1
    TriggerZone 40, 219, half_width=41, half_height=53, rearm_delay=4, trigger_kind=1, require_a_press=1, chain=Room07V1Chain2_id
    Group Room07V1Group1, 1
    Npc 525, 224, sprite=21, facing=6
    Group Room07V1Group2, 4
    TriggerZone 420, 219, half_width=4, half_height=38, rearm_delay=1, chain=Room07V1Chain3_id
    Npc 125, 160, sprite=19, facing=4
    TriggerZone 137, 159, half_width=41, half_height=53, rearm_delay=4, trigger_kind=1, require_a_press=1, chain=Room07V1Chain2_id
    TriggerZone 519, 211, half_width=30, half_height=36, require_a_press=1, chain=Room07V1Chain4_id
    Group Room07V1Group3, 1
    TriggerZone 527, 214, half_width=34, half_height=34, rearm_delay=2, trigger_kind=1, require_a_press=1, chain=Room07V1Chain5_id
    OffsetTable Room07V1Routes, 0
    EndTable
    OffsetTable Room07V1Chains, 6, 1
    Offsets Room07V1Chain0, Room07V1Chain1, Room07V1Chain2, Room07V1Chain3, Room07V1Chain4, Room07V1Chain5
    EndTable
Room07V1Chain0:
    GotoIfStoryStageCompare 0, 10, 0, 0, Room07V1Group1_id, 0
    GotoIfQuestStateCompare 226, 0, 0, 0, 0, Room07V1Group2_id, Room07V1Group3_id
    End
Room07V1Chain1:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 0, Room07V1Group1_id, 0
    End
Room07V1Chain2:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "Have you seen the conductor?"
    @ "He was going towards the front of the train, looking very cross, I might add."
    ShowRoomDialog 129
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room07V1Chain3:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room07V1Chain4:
    ArmChainYield 1
    @ "Excuse me..."
    @ "Yes, miss?"
    @ "Erm... Professor Lupin was wondering if you might get the train moving again - if that's possible?"
    @ "Of course it's possible. Tell Professor Lupin we'll be underway very soon."
    @ "OK. Thank you very much."
    ShowRoomDialog 132
    DelayedRespawnRowAndRunChain 0, Room07V1Group3_id, 0
    SetQuestState 1, 246
    DespawnTileObject Room07V1Group2_id, 2
    End
Room07V1Chain5:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "Better return to your seat, miss. We'll be at Hogsmeade very shortly."
    ShowRoomDialog 133
    SetTileObjectAnimStateWithSpeed 0, 255
    End
    EndSubBlock Room07V1End

    SubBlock Room07V2, 1, Room07V2Routes, Room07V2Chains, Room07V2End
    OffsetTable Room07V2Groups, 4, 1
    Offsets Room07V2Group0, Room07V2Group1, Room07V2Group2, Room07V2Group3
    EndTable
    Group Room07V2Group0, 3
    Npc 121, 161, sprite=19, facing=4
    TriggerZone 534, 220, half_width=14, half_height=22, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room07V2Chain4_id
    TriggerZone 44, 215, half_width=13, half_height=34, chain=Room07V2Chain5_id
    Group Room07V2Group1, 3
    TriggerZone 139, 187, half_width=27, half_height=19, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room07V2Chain2_id
    TriggerZone 173, 161, half_width=14, half_height=24, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room07V2Chain2_id
    TriggerZone 92, 217, half_width=9, half_height=47, chain=Room07V2Chain3_id
    Group Room07V2Group2, 1
    TriggerZone 142, 161, half_width=40, half_height=51, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room07V2Chain1_id
    Group Room07V2Group3, 1
    TriggerZone 144, 160, half_width=40, half_height=51, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room07V2Chain8_id
    OffsetTable Room07V2Routes, 0
    EndTable
    OffsetTable Room07V2Chains, 9, 1
    Offsets Room07V2Chain0, Room07V2Chain1, Room07V2Chain2, Room07V2Chain3, Room07V2Chain4, Room07V2Chain5
    Offsets Room07V2Chain6, Room07V2Chain7, Room07V2Chain8
    EndTable
Room07V2Chain0:
    GotoIfQuestStateCompare 6, 0, 5, Room07V2Chain6_id, 0, Room07V2Group1_id, Room07V2Group3_id
    End
Room07V2Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "I've sold out of chocolate, I'm afraid."
    ShowRoomDialog 137
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room07V2Chain2:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 227
    SetQuestState 1, 226
    QueueTileObjectMove Room07V2Group0_id, 0, 0, 0, 1700, 0
    @ "A bar of chocolate, please."
    @ "There you are, my dear. That'll be one Sickle."
    @ "Thanks."
    ShowRoomDialog 136
    QueueTileObjectMove 0, 255, 0, 0, 1500, 0
    DelayedRespawnRowAndRunChain 0, Room07V2Group2_id, 0
    DespawnTileObject Room07V2Group1_id, 0
    DespawnTileObject Room07V2Group1_id, 1
    SetQuestState 1, 246
    DespawnTileObject Room07V2Group1_id, 2
    SetQuestState 6, 6
    SetQuestState 56, 25
    GrantRoomReward 76, 0
.ifdef VERSION_JP
    ShowRewardPickupMessage 76
.endif
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room07V2Chain3:
    ArmChainYield 1
    SetQuestState 1, 227
    @ "Here it is! The buffet car!"
    ShowRoomDialog 135
    End
Room07V2Chain4:
    @ "Locked."
    ShowRoomDialog 624
    End
Room07V2Chain5:
    SetStoryStage 2
    ReturnToOverworld 5, 1
    End
Room07V2Chain6:
    GotoIfQuestStateCompare 227, 0, 0, 0, Room07V2Chain7_id, 0, 0
    End
Room07V2Chain7:
    DespawnTileObject Room07V2Group1_id, 2
    End
Room07V2Chain8:
    @ "Sorry, I can't help you at the moment."
    ShowRoomDialog 182
    End
    EndSubBlock Room07V2End

    SubBlock Room07V3, 1, Room07V3Routes, Room07V3Chains, Room07V3End
    OffsetTable Room07V3Groups, 1, 1
    Offsets Room07V3Group0
    EndTable
    Group Room07V3Group0, 2
    Npc 125, 161, sprite=19, facing=4
    TriggerZone 533, 218, half_width=11, half_height=22, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room07V3Chain1_id
    OffsetTable Room07V3Routes, 0
    EndTable
    OffsetTable Room07V3Chains, 2, 1
    Offsets Room07V3Chain0, Room07V3Chain1
    EndTable
Room07V3Chain0:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetAllQueuedMoveParams 0, 1, 0, 0, 65535
    End
Room07V3Chain1:
    @ "Locked."
    ShowRoomDialog 624
    End
    EndSubBlock Room07V3End

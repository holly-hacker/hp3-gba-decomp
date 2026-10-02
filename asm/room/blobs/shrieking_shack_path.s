    .include "asm/room_blob.inc"

Room44Blob:
    RoomBlob 2
    PlayerEntry 167, 502, 0, 6
    PlayerEntry 951, 935, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room44V0
    VariantEntry Room44V1

    SubBlock Room44V0, 1, Room44V0Routes, Room44V0Chains, Room44V0End
    OffsetTable Room44V0Groups, 1
    Offsets Room44V0Group0
    EndTable
    Group Room44V0Group0, 1
    Door 953, 1006, half_width=39, half_height=20, destination_room=45
    OffsetTable Room44V0Routes, 0
    EndTable
    OffsetTable Room44V0Chains, 1
    Offsets Room44V0Chain0
    EndTable
Room44V0Chain0:
    ClearOverworldMonstersDisabled
    End
    EndSubBlock Room44V0End

    SubBlock Room44V1, 1, Room44V1Routes, Room44V1Chains, Room44V1End
    OffsetTable Room44V1Groups, 4, 1
    Offsets Room44V1Group0, Room44V1Group1, Room44V1Group2, Room44V1Group3
    EndTable
    Group Room44V1Group0, 1
    TriggerZone 233, 505, half_width=8, half_height=33, chain=Room44V1Chain6_id
    Group Room44V1Group1, 1
    TriggerZone 70, 464, half_width=17, half_height=22, chain=Room44V1Chain8_id
    Group Room44V1Group2, 2
    Npc 281, 512, sprite=103, facing=2
    TriggerZone 281, 511, half_width=35, half_height=29, chain=Room44V1Chain7_id
    Group Room44V1Group3, 1
    TriggerZone 70, 462, half_width=17, half_height=22, rearm_delay=3, trigger_kind=1, chain=Room44V1Chain9_id
    OffsetTable Room44V1Routes, 1
    Offsets Room44V1Route0
    EndTable
Room44V1Route0:
    Route 2
    Waypoint 296, 511
    Waypoint 270, 511
    OffsetTable Room44V1Chains, 12, 1
    Offsets Room44V1Chain0, Room44V1Chain1, Room44V1Chain2, Room44V1Chain3, Room44V1Chain4, Room44V1Chain5
    Offsets Room44V1Chain6, Room44V1Chain7, Room44V1Chain8, Room44V1Chain9, Room44V1Chain10, Room44V1Chain11
    EndTable
Room44V1Chain0:
    DelayedRespawnRowAndRunChainFrames 2, 0, Room44V1Chain3_id
    End
Room44V1Chain1:
    SetQuestState 1, QUEST_ALT_PRESENTATION
    GotoIfQuestStateCompare 253, 0, 0, Room44V1Chain11_id, 0, Room44V1Group2_id, 0
    End
Room44V1Chain2:
    SetQuestState 1, 253
    SetDefeatWarpSelector 7 @ Shrieking Shack Path
    End
Room44V1Chain3:
    GotoIfStoryStageCompare 0, 23, Room44V1Chain1_id, 0, Room44V1Group1_id, Room44V1Group3_id
    End
Room44V1Chain4:
    DespawnTileObject Room44V1Group2_id, 0
    StartBattle 8, 0, Room44V1Chain2_id
    End
Room44V1Chain5:
    SetDefeatWarpSelector 10 @ Shrieking Shack - Path 2
    End
Room44V1Chain6:
    SetDefeatWarpSelector 7 @ Shrieking Shack Path
    End
Room44V1Chain7:
    GotoIfQuestStateCompare 253, 0, 0, Room44V1Chain4_id, 0, 0, 0
    End
Room44V1Chain8:
    ClearQuestStateUpperHalf
    ReturnToOverworld 15, 6
    End
Room44V1Chain9:
    @ "Locked."
    ShowRoomDialog 624
    End
Room44V1Chain10:
    DespawnTileObject Room44V1Group2_id, 0
    End
Room44V1Chain11:
    StartObjectAnimSequence Room44V1Group2_id, 0, 0, 0, Room44V1Route0_id, 0, 0, 0, 0, 0
    End
    EndSubBlock Room44V1End

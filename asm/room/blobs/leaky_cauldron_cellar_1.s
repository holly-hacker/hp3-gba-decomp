    .include "asm/room_blob.inc"

Room38Blob:
    RoomBlob 2
    PlayerEntry 386, 398, 0, 2
    PlayerEntry 684, 389, 1, 4
    StageIndex 4
    StageToVariant 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    VariantEntry Room38V0
    VariantEntry Room38V1
    VariantEntry Room38V2
    VariantEntry Room38V3

    SubBlock Room38V0, 1, Room38V0Routes, Room38V0Chains, Room38V0End
    OffsetTable Room38V0Groups, 1
    Offsets Room38V0Group0
    EndTable
    Group Room38V0Group0, 7
    TileAnimation 660, 307, anim_id=0
    TileAnimation 174, 592, anim_id=2
    Prop 807, 328, kind=23, arg_13=0
    Prop 1069, 328, kind=23, arg_13=0
    Chest 1205, 247, flag_id=4, reward_id=57
    Chest 660, 704, flag_id=5, reward_id=122
    Chest 139, 97, flag_id=6, reward_id=60
    OffsetTable Room38V0Routes, 0
    EndTable
    OffsetTable Room38V0Chains, 1
    Offsets Room38V0Chain0
    EndTable
Room38V0Chain0:
    End
    EndSubBlock Room38V0End

    SubBlock Room38V1, 1, Room38V1Routes, Room38V1Chains, Room38V1End
    OffsetTable Room38V1Groups, 6, 1
    Offsets Room38V1Group0, Room38V1Group1, Room38V1Group2, Room38V1Group3, Room38V1Group4, Room38V1Group5
    EndTable
    Group Room38V1Group0, 21
    Door 309, 379, half_width=12, half_height=19, destination_room=42, exit_param=1
    Prop 727, 403, kind=5, arg_10=1
    Prop 719, 383, kind=5, arg_10=1
    Prop 1357, 367, kind=5, arg_10=1
    Prop 987, 523, kind=5, arg_10=1
    Prop 819, 882, kind=1, arg_0f=1
    TriggerZone 467, 388, half_width=29, half_height=52, chain=Room38V1Chain10_id
    TriggerZone 658, 387, half_width=58, half_height=45, chain=Room38V1Chain12_id
    TriggerZone 187, 637, half_width=26, half_height=10, unk_0e=1, chain=Room38V1Chain15_id
    TriggerZone 547, 674, half_width=10, half_height=39, chain=Room38V1Chain18_id
    TriggerZone 1292, 528, half_width=7, half_height=32, chain=Room38V1Chain19_id
    TriggerZone 703, 857, half_width=11, half_height=44, chain=Room38V1Chain17_id
    TriggerZone 388, 420, half_width=19, half_height=63, chain=Room38V1Chain16_id
    TriggerZone 267, 218, half_width=25, half_height=45, chain=Room38V1Chain14_id
    TriggerZone 565, 386, half_width=9, half_height=38, chain=Room38V1Chain27_id
    TriggerZone 763, 388, half_width=19, half_height=38, chain=Room38V1Chain28_id
    TriggerRect 790, 834, left=0, top=11, right=14, bottom=62
    TileAnimation 784, 858, anim_id=1
    TriggerZone 678, 339, half_width=16, half_height=11, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room38V1Chain24_id
    TriggerZone 388, 210, half_width=15, half_height=26, trigger_kind=2, chain=Room38V1Chain31_id
    TriggerZone 470, 215, half_width=17, half_height=12, chain=Room38V1Chain33_id
    Group Room38V1Group1, 0
    Group Room38V1Group2, 4
    Npc 360, 209, sprite=0, facing=6
    TriggerZone 353, 210, half_width=45, half_height=45, chain=Room38V1Chain6_id
    Prop 361, 209, kind=14, arg_0e=0, arg_13=0
    TriggerZone 307, 221, half_width=19, half_height=45, chain=Room38V1Chain5_id
    Group Room38V1Group3, 1
    Prop 401, 254, kind=1, arg_0f=1
    Group Room38V1Group4, 1
    Prop 430, 261, kind=1
    Group Room38V1Group5, 1
    Prop 430, 261, kind=1, arg_0f=1
    OffsetTable Room38V1Routes, 0
    EndTable
    OffsetTable Room38V1Chains, 36, 1
    Offsets Room38V1Chain0, Room38V1Chain1, Room38V1Chain2, Room38V1Chain3, Room38V1Chain4, Room38V1Chain5
    Offsets Room38V1Chain6, Room38V1Chain7, Room38V1Chain8, Room38V1Chain9, Room38V1Chain10, Room38V1Chain11
    Offsets Room38V1Chain12, Room38V1Chain13, Room38V1Chain14, Room38V1Chain15, Room38V1Chain16, Room38V1Chain17
    Offsets Room38V1Chain18, Room38V1Chain19, Room38V1Chain20, Room38V1Chain21, Room38V1Chain22, Room38V1Chain23
    Offsets Room38V1Chain24, Room38V1Chain25, Room38V1Chain26, Room38V1Chain27, Room38V1Chain28, Room38V1Chain29
    Offsets Room38V1Chain30, Room38V1Chain31, Room38V1Chain32, Room38V1Chain33, Room38V1Chain34, Room38V1Chain35
    EndTable
Room38V1Chain0:
    SetBattleDefeatState 16
    SetQuestState 1, 233
    GotoIfQuestStateCompare 224, 0, 2, Room38V1Chain30_id, 0, 0, 0
    GotoIfQuestStateCompare 251, 0, 1, 0, 0, Room38V1Group3_id, Room38V1Group4_id
    GotoIfQuestStateCompare QUEST_COMPLETION_COUNT, 3, 1, Room38V1Chain29_id, 0, 0, 0
    End
Room38V1Chain1:
    ArmChainYield 1
    @ "It's really dusty down here."
    @ "Where is that bottle hiding?"
    ShowRoomDialog 31
    SetQuestState 1, 245
    End
Room38V1Chain2:
    @ "Tom really needs to tidy up down here."
    ShowRoomDialog 32
    SetQuestState 1, 246
    End
Room38V1Chain3:
    @ "This place could do with a spring clean..."
    ShowRoomDialog 33
    SetQuestState 1, QUEST_CELLAR1_INTRO_DIALOG_SHOWN
    End
Room38V1Chain4:
    @ "This place is really dark. I'd better cast Lumos so I don't fall over."
    ShowRoomDialog 34
    SetQuestState 1, 248
    End
Room38V1Chain5:
    GotoIfQuestStateCompare QUEST_CELLAR1_RAT_TONIC_FOUND, 0, 1, 0, 0, 0, 0
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    StartTileObjectScript 335, 211, 0, 0, 255, 0, 0, 2, 255, 255, 255
    @ "There's the Rat Tonic!"
    ShowRoomDialog 35
    ArmChainYield 0
    PlayTileObjectAnimation Room38V1Group2_id, 0, 0
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 2, 0, 0
    PlaySoundById 41
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    PlayTileObjectAnimation Room38V1Group2_id, 0, 1
    ArmChainYield 1
    @ "Oh! It's had too much Rat Tonic! I'd better get the rest of the Tonic and get out!"
    ShowRoomDialog 37
    SetTileObjectAnimStateWithSpeed 0, 255
    ArmChainYield 0
    End
Room38V1Chain6:
    DespawnTileObject Room38V1Group2_id, 0
    StartBattle 1, 0, Room38V1Chain22_id
    End
Room38V1Chain7:
    ArmChainYield 1
    ArmChainYield 0
    End
Room38V1Chain8:
    DelayedRespawnRowAndRunChain 0, 0, 0
    GotoIfQuestStateCompare QUEST_CELLAR1_RAT_TONIC_FOUND, 0, 1, 0, 0, 0, 0
    End
Room38V1Chain9:
    ArmChainYield 1
    @ "Press the L or R Buttons to change spells. Press the B Button to cast the spell. Try using Lumos near the gap."
    ShowRoomDialog 615
    SetQuestState 1, 235
    End
Room38V1Chain10:
    GotoIfQuestStateCompare 235, 0, 0, Room38V1Chain9_id, 0, 0, 0
    End
Room38V1Chain11:
    ArmChainYield 1
    @ "If I cast Flipendo I'll be able to push and break certain things..."
    ShowRoomDialog 26
    SetQuestState 1, 236
    End
Room38V1Chain12:
    GotoIfQuestStateCompare 236, 0, 0, Room38V1Chain11_id, 0, 0, 0
    End
Room38V1Chain13:
    AddQuestState 1, 237
    End
Room38V1Chain14:
    GotoIfQuestStateCompare QUEST_CELLAR1_RAT_TONIC_FOUND, 0, 0, 0, 0, Room38V1Group2_id, 0
    End
Room38V1Chain15:
    SetTileObjectAnimState Room38V0Group0_id, 1
    PlaySoundById 22
    End
Room38V1Chain16:
    GotoIfQuestStateCompare 245, 0, 0, Room38V1Chain1_id, 0, 0, 0
    End
Room38V1Chain17:
    GotoIfQuestStateCompare 246, 0, 0, Room38V1Chain2_id, 0, 0, 0
    End
Room38V1Chain18:
    GotoIfQuestStateCompare 248, 0, 0, Room38V1Chain4_id, 0, 0, 0
    End
Room38V1Chain19:
    GotoIfQuestStateCompare QUEST_CELLAR1_INTRO_DIALOG_SHOWN, 0, 0, Room38V1Chain3_id, 0, 0, 0
    End
Room38V1Chain20:
    PlayTileObjectAnimation Room38V1Group2_id, 0, 1
    End
Room38V1Chain21:
    GrantPartyExperience 5, 65535
    SetQuestState 2, 236
    End
Room38V1Chain22:
    DespawnTileObject Room38V1Group2_id, 2
    SetQuestState 1, QUEST_CELLAR1_RAT_TONIC_FOUND
    FullHealParty
    SetQuestState QUEST_OBJ_DELIVER_RAT_TONIC_TO_RON, QUEST_OBJECTIVE_INDEX
    SetStoryStage 5
    GrantRoomReward 62, 0
    ArmChainYield 1
    ShowRewardPickupMessage 62
    End
Room38V1Chain23:
    SetTileObjectAnimState Room38V1Group0_id, 17
    SetQuestState 2, 224
    GrantPartyExperience 5, 65535
    DespawnTileObject Room38V1Group0_id, 5
    DespawnTileObject Room38V0Group0_id, 0
    End
Room38V1Chain24:
    @ "Locked."
    ShowRoomDialog 624
    End
Room38V1Chain25:
    GrantPartyExperience 5, 65535
    ArmChainYield 1
    SetQuestState 2, 235
    @ "You've just gained your first level! You will now have more Stamina Points, Magic Points and defensive capabilities to help you in magical encounters. You can look at your statistics by pressing START (which brings up the Main Menu) and then selecting Status/Equip."
    ShowRoomDialog 660
    End
Room38V1Chain26:
    DelayedRespawnRowAndRunChainFrames 0, Room38V1Group5_id, 0
    DespawnTileObject Room38V1Group4_id, 0
    End
Room38V1Chain27:
    GotoIfQuestStateCompare 235, 0, 1, Room38V1Chain25_id, 0, 0, 0
    End
Room38V1Chain28:
    GotoIfQuestStateCompare 236, 0, 1, Room38V1Chain21_id, 0, 0, 0
    End
Room38V1Chain29:
    DespawnTileObject Room38V1Group0_id, 7
    DespawnTileObject Room38V1Group0_id, 6
    DespawnTileObject Room38V1Group0_id, 14
    DespawnTileObject Room38V1Group0_id, 15
    End
Room38V1Chain30:
    SetTileObjectAnimState Room38V1Group0_id, 17
    DespawnTileObject Room38V1Group0_id, 5
    DespawnTileObject Room38V1Group0_id, 16
    End
Room38V1Chain31:
    SetQuestState 1, 251
    End
Room38V1Chain32:
    DespawnRoomRowObjects Room38V1Group4_id
    DelayedRespawnRowAndRunChainFrames 0, Room38V1Group3_id, 0
    End
Room38V1Chain33:
    GotoIfQuestStateCompare 251, 0, 1, 0, Room38V1Chain26_id, 0, 0
    End
Room38V1Chain34:
    @ "Locked."
    ShowRoomDialog 624
    End
Room38V1Chain35:
    End
    EndSubBlock Room38V1End

    SubBlock Room38V2, 1, Room38V2Routes, Room38V2Chains, Room38V2End
    OffsetTable Room38V2Groups, 7, 1
    Offsets Room38V2Group0, Room38V2Group1, Room38V2Group2, Room38V2Group3, Room38V2Group4, Room38V2Group5
    Offsets Room38V2Group6
    EndTable
    Group Room38V2Group0, 18
    TriggerZone 7, 13, half_width=0, half_height=0
    Prop 432, 292, kind=1, arg_0f=1
    Prop 432, 262, kind=1, arg_0f=1
    Prop 579, 356, kind=3, facing=4
    Prop 712, 366, kind=5, arg_10=1
    Prop 700, 373, kind=5, arg_10=1
    Prop 700, 387, kind=5, arg_10=1
    Prop 711, 399, kind=5, arg_10=1
    Prop 725, 402, kind=5, arg_10=1
    Prop 1187, 250, kind=3, facing=4
    Prop 1336, 374, kind=5, arg_10=1
    Prop 1366, 395, kind=5, arg_10=1
    Prop 876, 783, kind=1, arg_0f=1
    Prop 555, 778, kind=5, arg_10=1
    Prop 575, 779, kind=5, arg_10=1
    Prop 595, 780, kind=5, arg_10=1
    Prop 105, 106, kind=3, facing=4
    Prop 466, 196, kind=3, facing=4
    Group Room38V2Group1, 1
    TriggerZone 505, 386, half_width=6, half_height=46
    Group Room38V2Group2, 0
    Group Room38V2Group3, 1
    TriggerZone 749, 382, half_width=7, half_height=41, respawn_group=Room38V2Group2_id
    Group Room38V2Group4, 1
    TriggerZone 821, 711, half_width=20, half_height=21
    Group Room38V2Group5, 1
    TriggerZone 186, 498, half_width=58, half_height=10, respawn_group=Room38V2Group6_id
    Group Room38V2Group6, 2
    Prop 170, 298, kind=5, arg_10=1
    Prop 186, 291, kind=5, arg_10=1
    OffsetTable Room38V2Routes, 0
    EndTable
    OffsetTable Room38V2Chains, 6, 1
    Offsets Room38V2Chain0, Room38V2Chain1, Room38V2Chain2, Room38V2Chain3, Room38V2Chain4, Room38V2Chain5
    EndTable
Room38V2Chain0:
    DelayedRespawnRowAndRunChain 0, Room38V2Group3_id, 0
    End
Room38V2Chain1:
    @ "C'mon you lot! We need to leave for King's Cross station right away if we want to catch the Hogwarts Express!"
    ShowRoomDialog 122
    End
Room38V2Chain2:
    ArmChainYield 1
    QueueTileObjectMove Room38V2Group0_id, 12, 0, 0, 5000, 0
    @ "C'mon you lot! We need to leave for King's Cross station right away if we want to catch the Hogwarts Express!"
    ShowRoomDialog 122
    QueueTileObjectMove 0, 255, 0, 0, 5000, 0
    ArmChainYield 0
    End
Room38V2Chain3:
    End
Room38V2Chain4:
    End
Room38V2Chain5:
    End
    EndSubBlock Room38V2End

    SubBlock Room38V3, 1, Room38V3Routes, Room38V3Chains, Room38V3End
    OffsetTable Room38V3Groups, 4, 1
    Offsets Room38V3Group0, Room38V3Group1, Room38V3Group2, Room38V3Group3
    EndTable
    Group Room38V3Group0, 8
    Door 676, 343, half_width=24, half_height=7, destination_room=39
    Prop 980, 518, kind=5, arg_10=1
    Prop 1371, 366, kind=5, arg_10=1
    TriggerZone 444, 393, half_width=46, half_height=74, chain=Room38V3Chain6_id
    TileAnimation 784, 858, anim_id=1, flag=1
    TriggerZone 187, 637, half_width=26, half_height=10, unk_0e=1, chain=Room38V3Chain4_id
    TriggerZone 388, 210, half_width=15, half_height=26, trigger_kind=2, chain=Room38V3Chain5_id
    Door 309, 379, half_width=12, half_height=19, destination_room=42, exit_param=1
    Group Room38V3Group1, 1
    Prop 401, 254, kind=1, arg_0f=1
    Group Room38V3Group2, 1
    Prop 430, 261, kind=1, arg_0f=1
    Group Room38V3Group3, 2
    Npc 563, 391, sprite=5, facing=2
    Npc 607, 392, sprite=4, facing=2
    OffsetTable Room38V3Routes, 2
    Offsets Room38V3Route0, Room38V3Route1
    EndTable
Room38V3Route0:
    Route 3
    Waypoint 609, 386
    Waypoint 679, 386
    Waypoint 679, 348, on_arrival_chain=Room38V3Chain3_id
Room38V3Route1:
    Route 4
    Waypoint 564, 386
    Waypoint 608, 386
    Waypoint 679, 386
    Waypoint 679, 347, on_arrival_chain=Room38V3Chain2_id
    OffsetTable Room38V3Chains, 7, 1
    Offsets Room38V3Chain0, Room38V3Chain1, Room38V3Chain2, Room38V3Chain3, Room38V3Chain4, Room38V3Chain5
    Offsets Room38V3Chain6
    EndTable
Room38V3Chain0:
    SetBattleDefeatState 0
    GotoIfQuestStateCompare 251, 0, 1, 0, 0, Room38V3Group1_id, Room38V3Group2_id
    End
Room38V3Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 253
    QueueTileObjectMove Room38V3Group3_id, 0, 0, 0, 1200, 0
    Unk02 Room38V3Group3_id, 0, 4
    Unk02 Room38V3Group3_id, 1, 4
    ArmChainYield 0
    StartObjectAnimSequence Room38V3Group3_id, 1, 0, 0, Room38V3Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room38V3Group3_id, 0, 0, 0, Room38V3Route1_id, 0, 1, 0, 0, 0
    End
Room38V3Chain2:
    DespawnTileObject Room38V3Group3_id, 0
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room38V3Chain3:
    DespawnTileObject Room38V3Group3_id, 1
    End
Room38V3Chain4:
    SetTileObjectAnimState Room38V0Group0_id, 1
    PlaySoundById 22
    End
Room38V3Chain5:
    SetQuestState 1, 251
    End
Room38V3Chain6:
    GotoIfQuestStateCompare 253, 0, 0, Room38V3Chain1_id, 0, Room38V3Group3_id, 0
    End
    EndSubBlock Room38V3End

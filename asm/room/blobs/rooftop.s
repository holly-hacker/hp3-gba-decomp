    .include "asm/room_blob.inc"

Room25Blob:
    RoomBlob 2
    PlayerEntry 408, 1484, 0, 4
    PlayerEntry 393, 312, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room25V0
    VariantEntry Room25V1

    SubBlock Room25V0, 1, Room25V0Routes, Room25V0Chains, Room25V0End
    OffsetTable Room25V0Groups, 1
    Offsets Room25V0Group0
    EndTable
    Group Room25V0Group0, 6
    Chest 688, 753, flag_id=53, reward_id=112
    Chest 123, 1378, flag_id=54, reward_id=129
    Chest 152, 939, flag_id=55, reward_id=57
    Chest 663, 1225, flag_id=56, reward_id=59
    TileAnimation 561, 1138, anim_id=31
    TileAnimation 529, 1146, anim_id=32
    OffsetTable Room25V0Routes, 0
    EndTable
    OffsetTable Room25V0Chains, 1
    Offsets Room25V0Chain0
    EndTable
Room25V0Chain0:
    ClearOverworldMonstersDisabled
    End
    EndSubBlock Room25V0End

    SubBlock Room25V1, 1, Room25V1Routes, Room25V1Chains, Room25V1End
    OffsetTable Room25V1Groups, 24, 1
    Offsets Room25V1Group0, Room25V1Group1, Room25V1Group2, Room25V1Group3, Room25V1Group4, Room25V1Group5
    Offsets Room25V1Group6, Room25V1Group7, Room25V1Group8, Room25V1Group9, Room25V1Group10, Room25V1Group11
    Offsets Room25V1Group12, Room25V1Group13, Room25V1Group14, Room25V1Group15, Room25V1Group16, Room25V1Group17
    Offsets Room25V1Group18, Room25V1Group19, Room25V1Group20, Room25V1Group21, Room25V1Group22, Room25V1Group23
    EndTable
    Group Room25V1Group0, 8
    TriggerZone 576, 1172, half_width=52, half_height=13, chain=Room25V1Chain14_id
    TriggerZone 321, 951, half_width=85, half_height=14, respawn_group=Room25V1Group5_id
    Npc 391, 221, sprite=28, facing=4
    TriggerZone 392, 220, half_width=98, half_height=6, chain=Room25TalkMalfoy_id
    TriggerZone 179, 399, half_width=18, half_height=17, chain=Room25V1Chain18_id
    TriggerZone 591, 407, half_width=18, half_height=17, chain=Room25V1Chain18_id
    TriggerZone 238, 1160, half_width=40, half_height=7, chain=Room25V1Chain15_id
    TriggerZone 390, 313, half_width=127, half_height=4, chain=Room25V1Chain50_id
    Group Room25V1Group1, 0
    Group Room25V1Group2, 0
    Group Room25V1Group3, 1
    Npc 398, 316, sprite=34, facing=6
    Group Room25V1Group4, 1
    Npc 398, 316, sprite=31, facing=2
    Group Room25V1Group5, 8
    TimedHazard 147, 728, variant=2
    TimedHazard 251, 728, variant=2
    TimedHazard 259, 600, variant=2
    TimedHazard 116, 828, variant=1
    TimedHazard 116, 771, variant=0
    TimedHazard 117, 627, variant=0
    TimedHazard 316, 599, variant=2
    TriggerZone 198, 926, half_width=5, half_height=42, chain=Room25V1Chain24_id
    Group Room25V1Group6, 0
    Group Room25V1Group7, 0
    Group Room25V1Group8, 2
    TriggerZone 182, 321, half_width=26, half_height=13, chain=Room25V1Chain7_id
    TriggerZone 585, 321, half_width=15, half_height=9, chain=Room25V1Chain8_id
    Group Room25V1Group9, 0
    Group Room25V1Group10, 2
    Npc 371, 49, sprite=36, facing=4
    Npc 391, 49, sprite=101, facing=4
    Group Room25V1Group11, 2
    TriggerZone 577, 1148, half_width=28, half_height=28, trigger_kind=5, chain=Room25V1Chain2_id
    TriggerZone 583, 745, half_width=19, half_height=17, chain=Room25V1Chain23_id
    Group Room25V1Group12, 8
    Npc 507, 1492, sprite=12, facing=0
    Npc 544, 1474, sprite=12, facing=0
    Npc 579, 1491, sprite=12, facing=0
    TriggerZone 543, 1361, half_width=52, half_height=26, chain=Room25V1Chain47_id
    TriggerZone 589, 482, half_width=26, half_height=8, chain=Room25V1Chain26_id
    Npc 528, 1485, sprite=12, facing=0
    Npc 562, 1485, sprite=12, facing=0
    Npc 545, 1501, sprite=12, facing=0
    Group Room25V1Group13, 0
    Group Room25V1Group14, 8
    Npc 197, 1441, sprite=12, facing=0
    Npc 233, 1425, sprite=12, facing=0
    Npc 263, 1440, sprite=12, facing=0
    TriggerZone 234, 1331, half_width=52, half_height=31, chain=Room25V1Chain13_id
    TriggerZone 192, 565, half_width=42, half_height=8, chain=Room25V1Chain25_id
    Npc 216, 1434, sprite=12, facing=0
    Npc 249, 1433, sprite=12, facing=0
    Npc 233, 1448, sprite=12, facing=0
    Group Room25V1Group15, 7
    Npc 164, 1061, sprite=12, facing=0
    Npc 190, 1060, sprite=12, facing=0
    Npc 214, 1061, sprite=12, facing=0
    TriggerZone 155, 907, half_width=35, half_height=40, chain=Room25V1Chain13_id
    Npc 239, 1061, sprite=12, facing=0
    Npc 265, 1061, sprite=12, facing=0
    Npc 291, 1061, sprite=12, facing=0
    Group Room25V1Group16, 4
    Npc 561, 745, sprite=12, facing=2
    Npc 581, 745, sprite=12, facing=2
    Npc 602, 744, sprite=12, facing=2
    TriggerZone 582, 746, half_width=52, half_height=20, chain=Room25V1Chain47_id
    Group Room25V1Group17, 2
    Npc 593, 440, sprite=12, facing=2
    TriggerZone 590, 387, half_width=18, half_height=20, chain=Room25V1Chain49_id
    Group Room25V1Group18, 2
    Npc 180, 442, sprite=12, facing=2
    TriggerZone 179, 393, half_width=18, half_height=20, chain=Room25V1Chain49_id
    Group Room25V1Group19, 2
    TriggerZone 183, 320, half_width=26, half_height=13, chain=Room25V1Chain41_id
    TriggerZone 586, 322, half_width=15, half_height=9, chain=Room25V1Chain42_id
    Group Room25V1Group20, 1
    Npc 232, 1076, sprite=34, facing=0
    Group Room25V1Group21, 2
    Npc 236, 1047, sprite=31, facing=0
    TriggerZone 573, 1197, half_width=73, half_height=28, chain=Room25V1Chain45_id
    Group Room25V1Group22, 1
    Npc 576, 1208, sprite=31, facing=0
    Group Room25V1Group23, 2
    Npc 576, 1200, sprite=34, facing=0
    TriggerZone 239, 1160, half_width=52, half_height=13, chain=Room25V1Chain46_id
    OffsetTable Room25V1Routes, 27
    Offsets Room25V1Route0, Room25V1Route1, Room25V1Route2, Room25V1Route3, Room25V1Route4, Room25V1Route5
    Offsets Room25V1Route6, Room25V1Route7, Room25V1Route8, Room25V1Route9, Room25V1Route10, Room25V1Route11
    Offsets Room25V1Route12, Room25V1Route13, Room25V1Route14, Room25V1Route15, Room25V1Route16, Room25V1Route17
    Offsets Room25V1Route18, Room25V1Route19, Room25V1Route20, Room25V1Route21, Room25V1Route22, Room25V1Route23
    Offsets Room25V1Route24, Room25V1Route25, Room25V1Route26
    EndTable
Room25V1Route0:
    Route 2
    Waypoint 200, 315
    Waypoint 289, 314
Room25V1Route1:
    Route 2
    Waypoint 563, 314
    Waypoint 484, 315
Room25V1Route2:
    Route 1
    Waypoint 384, 86, on_arrival_chain=Room25V1Chain19_id
Room25V1Route3:
    Route 1
    Waypoint 507, 1367
Room25V1Route4:
    Route 1
    Waypoint 544, 1348
Room25V1Route5:
    Route 1
    Waypoint 579, 1365
Room25V1Route6:
    Route 1
    Waypoint 197, 1341
Room25V1Route7:
    Route 1
    Waypoint 233, 1313
Room25V1Route8:
    Route 1
    Waypoint 263, 1344
Room25V1Route9:
    Route 1
    Waypoint 180, 387
Room25V1Route10:
    Route 1
    Waypoint 593, 381
Room25V1Route11:
    Route 1
    Waypoint 528, 1359
Room25V1Route12:
    Route 1
    Waypoint 562, 1359
Room25V1Route13:
    Route 1
    Waypoint 545, 1373
Room25V1Route14:
    Route 1
    Waypoint 216, 1324
Room25V1Route15:
    Route 1
    Waypoint 249, 1325
Room25V1Route16:
    Route 1
    Waypoint 233, 1343
Room25V1Route17:
    Route 3
    Waypoint 164, 925
    Waypoint 140, 925
    Waypoint 139, 881
Room25V1Route18:
    Route 3
    Waypoint 190, 925
    Waypoint 165, 925
    Waypoint 164, 881
Room25V1Route19:
    Route 3
    Waypoint 214, 925
    Waypoint 140, 926
    Waypoint 140, 907
Room25V1Route20:
    Route 3
    Waypoint 239, 925
    Waypoint 166, 925
    Waypoint 165, 904
Room25V1Route21:
    Route 3
    Waypoint 265, 925
    Waypoint 190, 925
    Waypoint 190, 903
Room25V1Route22:
    Route 2
    Waypoint 291, 924
    Waypoint 166, 924
Room25V1Route23:
    Route 2
    Waypoint 236, 1088
    Waypoint 236, 1197
Room25V1Route24:
    Route 1
    Waypoint 236, 1042
Room25V1Route25:
    Route 1
    Waypoint 576, 1196
Room25V1Route26:
    Route 2
    Waypoint 576, 1224
    Waypoint 421, 1225
    OffsetTable Room25V1Chains, 51, 1
    Offsets Room25V1Chain0, Room25V1Chain1, Room25V1Chain2, Room25V1Chain3, Room25V1Chain4, Room25V1Chain5
    Offsets Room25V1Chain6, Room25V1Chain7, Room25V1Chain8, Room25V1Chain9, Room25V1Chain10, Room25V1Chain11
    Offsets Room25V1Chain12, Room25V1Chain13, Room25V1Chain14, Room25V1Chain15, Room25TalkMalfoy, Room25V1Chain17
    Offsets Room25V1Chain18, Room25V1Chain19, Room25V1Chain20, Room25V1Chain21, Room25V1Chain22, Room25V1Chain23
    Offsets Room25V1Chain24, Room25V1Chain25, Room25V1Chain26, Room25V1Chain27, Room25V1Chain28, Room25V1Chain29
    Offsets Room25V1Chain30, Room25V1Chain31, Room25V1Chain32, Room25V1Chain33, Room25V1Chain34, Room25V1Chain35
    Offsets Room25V1Chain36, Room25V1Chain37, Room25V1Chain38, Room25V1Chain39, Room25V1Chain40, Room25V1Chain41
    Offsets Room25V1Chain42, Room25V1Chain43, Room25V1Chain44, Room25V1Chain45, Room25V1Chain46, Room25V1Chain47
    Offsets Room25V1Chain48, Room25V1Chain49, Room25V1Chain50
    EndTable
Room25V1Chain0:
    SetQuestState QUEST_OBJ_RESCUE_SIRIUS, QUEST_OBJECTIVE_INDEX
    GotoIfQuestStateCompare 233, 0, 0, Room25V1Chain1_id, 0, 0, 0
    DelayedRespawnRowAndRunChain 1, 0, Room25V1Chain20_id
    End
Room25V1Chain1:
    SetQuestState 1, 233
    SetDefeatWarpSelector 6 @ Rooftop
    End
Room25V1Chain2:
    SetTileObjectAnimState Room25V0Group0_id, 4
    DelayedRespawnRowAndRunChainFrames 2, 0, Room25V1Chain9_id
    DelayedRespawnRowAndRunChainFrames 1, Room25V1Group2_id, 0
    End
Room25V1Chain3:
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 225
    DespawnTileObject Room25V1Group0_id, 0
    DespawnTileObject Room25V0Group0_id, 0
    ArmChainYield 1
    StartObjectAnimSequence 0, 255, 0, 0, Room25V1Route24_id, 0, 1, 0, 0, 0
    ArmChainYield 0
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group20_id, 0
    RemovePartyFollower 6
    ArmChainYield 1
    PlaySoundById 177
    @ "Hermione, I'll go this way. Maybe you could try looking around for a faster route?"
    @ "Okay. I'll meet up with you at the tower."
    ShowRoomDialog 606
    ShowLoadingScreenTransition 27, 28, 32, 255
    GotoIfStoryStageCompare 0, 27, Room25V1Chain43_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 28, Room25V1Chain44_id, 0, 0, 0
    End
Room25V1Chain4:
    CancelObjectAnimSequence 0, 255
    RemovePartyFollower 5
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group22_id, 0
    ArmChainYield 1
    StartObjectAnimSequence 0, 255, 0, 0, Room25V1Route25_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group22_id, 0, 0, 0, Room25V1Route25_id, 0, 1, 0, 0, 0
    DespawnRoomRowObjects Room25V1Group22_id
    Unk2A 5, 255, 255, 255
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group23_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain5:
    CancelObjectAnimSequence 0, 255
    RemovePartyFollower 5
    DelayedRespawnRowAndRunChain 0, Room25V1Group11_id, 0
    DelayedRespawnRowAndRunChain 0, Room25V1Group22_id, 0
    ArmChainYield 1
    StartObjectAnimSequence Room25V1Group22_id, 0, 0, 0, Room25V1Route26_id, 0, 1, 0, 0, 0
    DespawnRoomRowObjects Room25V1Group22_id
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain6:
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 225
    DespawnTileObject Room25V1Group0_id, 6
    DespawnTileObject Room25V1Group0_id, 0
    ArmChainYield 1
    @ "A pipe must have burst here. Maybe we should split up?"
    ShowRoomDialog 605
    @ "I bet I can get through very quickly this way. Why don't you peek around the other side and see if there's anything you missed?"
    @ "Okay. I'll meet up with you at the tower."
    ShowRoomDialog 607
    ShowLoadingScreenTransition 27, 28, 32, 255
    GotoIfStoryStageCompare 0, 27, Room25V1Chain4_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 28, Room25V1Chain5_id, 0, 0, 0
    End
Room25V1Chain7:
    RespawnRowAndRunChain Room25V1Group3_id, 0
    CancelObjectAnimSequence 0, 255
    SetDefeatWarpSelector 19 @ Rooftop
    DespawnTileObject Room25V1Group8_id, 1
    StartObjectAnimSequence 0, 255, 0, 0, Room25V1Route0_id, 0, 1, 0, 0, 0
    ArmChainYield 1
    StartTileObjectScript 315, 63, 1, Room25V1Group3_id, 0, 0, 0, 6, 255, 255, 255
    @ "Hermione! You got here quickly! We must get to Sirius. The Dementors are coming!"
    ShowRoomDialog 608
    StartTileObjectScript 290, 57, 1, Room25V1Group3_id, 0, 0, 0, 6, 255, 255, 255
    DespawnTileObject Room25V1Group3_id, 0
    RecruitPartyFollower 6
    SetQuestState 2, 225
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group19_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain8:
    RespawnRowAndRunChain Room25V1Group4_id, 0
    CancelObjectAnimSequence 0, 255
    SetDefeatWarpSelector 19 @ Rooftop
    DespawnTileObject Room25V1Group8_id, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room25V1Route1_id, 0, 1, 0, 0, 0
    ArmChainYield 1
    StartTileObjectScript 465, 58, 1, Room25V1Group4_id, 0, 0, 0, 2, 255, 255, 255
    @ "Hermione! You got here quickly! We must get to Sirius. The Dementors are coming!"
    ShowRoomDialog 609
    StartTileObjectScript 484, 58, 1, Room25V1Group4_id, 0, 0, 0, 6, 255, 255, 255
    DespawnTileObject Room25V1Group4_id, 0
    RecruitPartyFollower 5
    SetQuestState 2, 225
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group19_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain9:
    DelayedRespawnRowAndRunChainFrames 0, 0, Room25V1Chain10_id
    DelayedRespawnRowAndRunChainFrames 6, 0, Room25V1Chain10_id
    DelayedRespawnRowAndRunChainFrames 12, 0, Room25V1Chain11_id
    End
Room25V1Chain10:
    PlaySoundById 105
    End
Room25V1Chain11:
    PlaySoundById 107
    End
Room25V1Chain12:
    End
Room25V1Chain13:
    PlaySoundById 161
    ReturnToOverworld 25, 0
    End
Room25V1Chain14:
    GotoIfQuestStateCompare 225, 0, 0, Room25V1Chain6_id, 0, 0, 0
    End
Room25V1Chain15:
    GotoIfQuestStateCompare 225, 0, 0, Room25V1Chain3_id, 0, 0, 0
    End
@ Talking to Malfoy before the final battle
Room25TalkMalfoy:
    ArmChainYield 1
    @ "Malfoy!"
    @ "What are you doing here, Potter? In a hurry to get somewhere?"
    @ "Stay out of the way, Malfoy."
    ShowRoomDialog 610
    ArmChainYield 0
    DespawnTileObject Room25V1Group0_id, 2
    StartBattle 5, 0, Room25V1Chain17_id
    End
Room25V1Chain17:
    PauseMusic
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group10_id, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room25V1Route2_id, 0, 1, 0, 0, 0
    End
Room25V1Chain18:
    GotoIfQuestStateCompare 225, 0, 1, 0, 0, Room25V1Group8_id, 0
    End
Room25V1Chain19:
    ArmChainYield 1
    @ "How - how - ?"
    @ "Sirius, the Dementors are coming! You'd better go. Quickly, before they get here..."
    @ "How can I ever thank-"
    @ "GO!"
    @ "We'll see each other again. You are - truly your father's son, Harry..."
    ShowRoomDialog 611
    PlayCutscene 11, 0, 0
    End
Room25V1Chain20:
    GotoIfStoryStageCompare 3, 27, 0, 0, Room25V1Group11_id, 0
    End
Room25V1Chain21:
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group13_id, 0
    End
Room25V1Chain22:
    ReturnToOverworld 25, 0
    End
Room25V1Chain23:
    ArmChainYield 1
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group12_id, 0
    CancelObjectAnimSequence 0, 255
    SetTileObjectFacing 0, 255, 2
    QueueTileObjectMove Room25V1Group12_id, 1, 0, 0, 1200, 0
    PlayMusicModuleAndFlagIfChain1 9
    ArmChainYield 0
    StartObjectAnimSequence Room25V1Group12_id, 0, 0, 0, Room25V1Route3_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group12_id, 1, 0, 0, Room25V1Route4_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group12_id, 2, 0, 0, Room25V1Route5_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group12_id, 5, 0, 0, Room25V1Route11_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group12_id, 6, 0, 0, Room25V1Route12_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group12_id, 7, 0, 0, Room25V1Route13_id, 0, 1, 0, 0, 0
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 2, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain24:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group14_id, 0
    SetTileObjectFacing 0, 255, 6
    QueueTileObjectMove Room25V1Group14_id, 1, 0, 0, 1200, 0
    PlayMusicModuleAndFlagIfChain1 9
    ArmChainYield 0
    StartObjectAnimSequence Room25V1Group14_id, 0, 0, 0, Room25V1Route6_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group14_id, 1, 0, 0, Room25V1Route7_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group14_id, 2, 0, 0, Room25V1Route8_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group14_id, 5, 0, 0, Room25V1Route14_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group14_id, 6, 0, 0, Room25V1Route15_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group14_id, 7, 0, 0, Room25V1Route16_id, 0, 1, 0, 0, 0
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 2, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain25:
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group15_id, 0
    DespawnRoomRowObjects Room25V1Group14_id
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetTileObjectFacing 0, 255, 0
    QueueTileObjectMove Room25V1Group15_id, 4, 0, 0, 1200, 0
    ArmChainYield 0
    StartObjectAnimSequence Room25V1Group15_id, 0, 0, 0, Room25V1Route17_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group15_id, 1, 0, 0, Room25V1Route18_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group15_id, 2, 0, 0, Room25V1Route19_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group15_id, 4, 0, 0, Room25V1Route20_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group15_id, 5, 0, 0, Room25V1Route21_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room25V1Group15_id, 6, 0, 0, Room25V1Route22_id, 0, 1, 0, 0, 0
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 2, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain26:
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group16_id, 0
    DespawnRoomRowObjects Room25V1Group12_id
    End
Room25V1Chain27:
    SetTileObjectFacing Room25V1Group12_id, 0, 0
    End
Room25V1Chain28:
    SetTileObjectFacing Room25V1Group12_id, 1, 0
    End
Room25V1Chain29:
    SetTileObjectFacing Room25V1Group12_id, 2, 0
    End
Room25V1Chain30:
    SetTileObjectFacing Room25V1Group18_id, 0, 0
    End
Room25V1Chain31:
    SetTileObjectFacing Room25V1Group17_id, 0, 0
    End
Room25V1Chain32:
    SetTileObjectFacing Room25V1Group14_id, 0, 0
    End
Room25V1Chain33:
    SetTileObjectFacing Room25V1Group14_id, 1, 0
    End
Room25V1Chain34:
    SetTileObjectFacing Room25V1Group14_id, 2, 0
    End
Room25V1Chain35:
    SetTileObjectFacing Room25V1Group15_id, 0, 0
    End
Room25V1Chain36:
    SetTileObjectFacing Room25V1Group15_id, 1, 0
    End
Room25V1Chain37:
    SetTileObjectFacing Room25V1Group15_id, 2, 0
    End
Room25V1Chain38:
    SetTileObjectFacing Room25V1Group16_id, 0, 0
    End
Room25V1Chain39:
    SetTileObjectFacing Room25V1Group16_id, 1, 0
    End
Room25V1Chain40:
    SetTileObjectFacing Room25V1Group16_id, 2, 0
    End
Room25V1Chain41:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group18_id, 0
    SetTileObjectFacing 0, 255, 2
    QueueTileObjectMove Room25V1Group18_id, 0, 0, 0, 1200, 0
    StartObjectAnimSequence Room25V1Group18_id, 0, 0, 0, Room25V1Route9_id, 0, 1, 0, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain42:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group17_id, 0
    SetTileObjectFacing 0, 255, 2
    QueueTileObjectMove Room25V1Group17_id, 0, 0, 0, 1200, 0
    StartObjectAnimSequence Room25V1Group17_id, 0, 0, 0, Room25V1Route10_id, 0, 1, 0, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain43:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    StartObjectAnimSequence Room25V1Group20_id, 0, 0, 0, Room25V1Route23_id, 0, 1, 0, 0, 0
    DespawnRoomRowObjects Room25V1Group20_id
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain44:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    StartObjectAnimSequence Room25V1Group20_id, 0, 0, 0, Room25V1Route24_id, 0, 1, 0, 0, 0
    DespawnRoomRowObjects Room25V1Group20_id
    Unk2A 6, 255, 255, 255
    DelayedRespawnRowAndRunChainFrames 0, Room25V1Group21_id, 0
    DelayedRespawnRowAndRunChain 0, Room25V1Group11_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room25V1Chain45:
    DespawnRoomRowObjects Room25V1Group21_id
    End
Room25V1Chain46:
    DespawnRoomRowObjects Room25V1Group23_id
    End
Room25V1Chain47:
    PlaySoundById 166
    ReturnToOverworld 25, 0
    End
Room25V1Chain48:
    SetDefeatWarpSelector 19 @ Rooftop
    End
Room25V1Chain49:
    ReturnToOverworld 25, 1
    End
Room25V1Chain50:
    GotoIfQuestStateCompare 225, 0, 2, 0, 0, Room25V1Group19_id, 0
    End
    EndSubBlock Room25V1End

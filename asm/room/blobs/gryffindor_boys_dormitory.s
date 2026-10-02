    .include "asm/room_blob.inc"

Room28Blob:
    RoomBlob 3
    PlayerEntry 288, 464, 0, 0
    PlayerEntry 338, 183, 1, 4
    PlayerEntry 320, 185, 2, 4
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room28V0
    VariantEntry Room28V1

    SubBlock Room28V0, 1, Room28V0Routes, Room28V0Chains, Room28V0End
    OffsetTable Room28V0Groups, 1
    Offsets Room28V0Group0
    EndTable
    Group Room28V0Group0, 4
    Chest 151, 293, flag_id=41, reward_id=91
    TileAnimation 373, 213, anim_id=34
    TileAnimation 338, 86, anim_id=35
    Door 287, 496, half_width=18, half_height=13, destination_room=29, exit_param=1
    OffsetTable Room28V0Routes, 0
    EndTable
    OffsetTable Room28V0Chains, 1
    Offsets Room28V0Chain0
    EndTable
Room28V0Chain0:
    SetDefeatWarpSelector 2
    End
    EndSubBlock Room28V0End

    SubBlock Room28V1, 1, Room28V1Routes, Room28V1Chains, Room28V1End
    OffsetTable Room28V1Groups, 6, 1
    Offsets Room28V1Group0, Room28V1Group1, Room28V1Group2, Room28V1Group3, Room28V1Group4, Room28V1Group5
    EndTable
    Group Room28V1Group0, 0
    Group Room28V1Group1, 1
    TriggerZone 289, 343, half_width=64, half_height=9, chain=Room28V1Chain2_id
    Group Room28V1Group2, 1
    TriggerZone 288, 362, half_width=70, half_height=9, chain=Room28V1Chain8_id
    Group Room28V1Group3, 4
    Npc 415, 295, sprite=32, facing=0
    Npc 165, 293, sprite=63, facing=0
    Npc 415, 325, sprite=39, facing=0
    Npc 140, 293, sprite=47, facing=0
    Group Room28V1Group4, 1
    Prop 296, 226, kind=83
    Group Room28V1Group5, 2
    Npc 230, 293, sprite=63, facing=2
    Npc 415, 300, sprite=32, facing=6
    OffsetTable Room28V1Routes, 13
    Offsets Room28V1Route0, Room28V1Route1, Room28V1Route2, Room28V1Route3, Room28V1Route4, Room28V1Route5
    Offsets Room28V1Route6, Room28V1Route7, Room28V1Route8, Room28V1Route9, Room28V1Route10, Room28V1Route11
    Offsets Room28V1Route12
    EndTable
Room28V1Route0:
    Route 4
    Waypoint 320, 185
    Waypoint 320, 295
    Waypoint 375, 295
    Waypoint 393, 295, on_arrival_chain=Room28V1Chain3_id
Room28V1Route1:
    Route 5
    Waypoint 250, 293
    Waypoint 257, 293
    Waypoint 290, 293
    Waypoint 315, 293
    Waypoint 377, 293, on_arrival_chain=Room28V1Chain4_id
Room28V1Route2:
    Route 6
    Waypoint 415, 300
    Waypoint 415, 305
    Waypoint 415, 310
    Waypoint 340, 310, on_arrival_chain=Room28V1Chain5_id
    Waypoint 322, 310
    Waypoint 322, 415
Room28V1Route3:
    Route 3
    Waypoint 377, 293
    Waypoint 312, 293
    Waypoint 312, 415, on_arrival_chain=Room28V1Chain6_id
Room28V1Route4:
    Route 2
    Waypoint 325, 351
    Waypoint 325, 200, on_arrival_chain=Room28V1Chain12_id
Room28V1Route5:
    Route 4
    Waypoint 415, 295
    Waypoint 315, 295
    Waypoint 315, 365
    Waypoint 290, 365, on_arrival_chain=Room28V1Chain10_id
Room28V1Route6:
    Route 3
    Waypoint 165, 293
    Waypoint 255, 293
    Waypoint 255, 365
Room28V1Route7:
    Route 3
    Waypoint 415, 300
    Waypoint 325, 300
    Waypoint 325, 365
Room28V1Route8:
    Route 2
    Waypoint 325, 340
    Waypoint 325, 220, on_arrival_chain=Room28V1Chain17_id
Room28V1Route9:
    Route 2
    Waypoint 325, 200
    Waypoint 338, 183, on_arrival_chain=Room28V1Chain9_id
Room28V1Route10:
    Route 2
    Waypoint 338, 183
    Waypoint 322, 190, on_arrival_chain=Room28V1Chain16_id
Room28V1Route11:
    Route 3
    Waypoint 322, 238
    Waypoint 322, 244
    Waypoint 313, 244, on_arrival_chain=Room28V1Chain14_id
Room28V1Route12:
    Route 2
    Waypoint 322, 190
    Waypoint 322, 238, on_arrival_chain=Room28V1Chain15_id
    OffsetTable Room28V1Chains, 20, 1
    Offsets Room28V1Chain0, Room28V1Chain1, Room28V1Chain2, Room28V1Chain3, Room28V1Chain4, Room28V1Chain5
    Offsets Room28V1Chain6, Room28V1Chain7, Room28V1Chain8, Room28V1Chain9, Room28V1Chain10, Room28V1Chain11
    Offsets Room28V1Chain12, Room28V1Chain13, Room28V1Chain14, Room28V1Chain15, Room28V1Chain16, Room28V1Chain17
    Offsets Room28V1Chain18, Room28V1Chain19
    EndTable
Room28V1Chain0:
    GotoIfStoryStageCompare 0, 19, Room28V1Chain1_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 20, Room28V1Chain7_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 21, Room28V1Chain18_id, 0, 0, 0
    End
Room28V1Chain1:
    SetTileObjectAnimState Room28V0Group0_id, 2
    SetQuestState 1, QUEST_ALT_PRESENTATION
    GotoIfQuestStateCompare 231, 0, 0, 0, 0, Room28V1Group1_id, 0
    GotoIfQuestStateCompare 231, 0, 1, Room28V1Chain11_id, Room28V1Chain18_id, Room28V1Group5_id, 0
    End
Room28V1Chain2:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    Unk02 0, 255, 2
    Unk02 Room28V0Group0_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room28V1Route8_id, 0, 1, 0, 0, 0
    End
Room28V1Chain3:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "Ron? What's going on?"
    @ "Black! Sirius Black! With a knife!"
    @ "What?"
    @ "Here! Just now! Slashed the curtains! Woke me up!!"
    @ "We'd better get Professor McGonagall!"
    ShowRoomDialog 506
    Unk02 Room28V1Group5_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence Room28V1Group5_id, 0, 0, 0, Room28V1Route1_id, 0, 1, 0, 0, 0
    End
Room28V1Chain4:
    ArmChainYield 1
    @ "Don't go without me!"
    ShowRoomDialog 507
    Unk02 Room28V0Group0_id, 0, 2
    QueueTileObjectMove 0, 255, 0, 0, 1000, 0
    ArmChainYield 0
    StartObjectAnimSequence Room28V1Group5_id, 1, 0, 0, Room28V1Route2_id, 0, 1, 0, 0, 0
    End
Room28V1Chain5:
    StartObjectAnimSequence Room28V1Group5_id, 0, 0, 0, Room28V1Route3_id, 0, 1, 0, 0, 0
    End
Room28V1Chain6:
    ArmChainYield 1
    DespawnRoomRowObjects Room28V1Group1_id
    DespawnRoomRowObjects Room28V1Group5_id
    SetQuestState QUEST_OBJ_GO_TO_COMMON_ROOM_AFTER_LUPIN, QUEST_OBJECTIVE_INDEX
    SetQuestState 2, 231
    SetQuestState 2, 230
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room28V1Chain7:
    SetTileObjectAnimState Room28V0Group0_id, 1
    SetTileObjectAnimState Room28V0Group0_id, 2
    SetQuestState 1, QUEST_ALT_PRESENTATION
    GotoIfQuestStateCompare 232, 0, 0, 0, 0, Room28V1Group2_id, 0
    GotoIfQuestStateCompare 232, 0, 1, Room28V1Chain19_id, 0, 0, 0
    End
Room28V1Chain8:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room28V1Route4_id, 0, 1, 0, 0, 0
    End
Room28V1Chain9:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "It's a lovely night..."
    ShowRoomDialog 527
    SetTileObjectFacing 0, 255, 0
    @ "There's Crookshanks! But what's that walking alongside him?"
    ShowRoomDialog 528
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetQuestState 1, 232
    ReturnToOverworld 10, 3
    End
Room28V1Chain10:
    ArmChainYield 1
    DespawnRoomRowObjects Room28V1Group3_id
    DespawnRoomRowObjects Room28V1Group2_id
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room28V1Route11_id, 0, 1, 0, 0, 0
    End
Room28V1Chain11:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, QUEST_ALT_PRESENTATION
    SetTileObjectAnimState Room28V0Group0_id, 1
    @ "AAARRRGGGHHH! NOOOOOOOOOOOO!"
    ShowRoomDialog 505
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room28V1Route0_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room28V1Group5_id, 1, 0, 0, 2000, 0
    End
Room28V1Chain12:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "I'm exhausted, but I can't sleep... there's too much going on in my head..."
    ShowRoomDialog 526
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room28V1Route9_id, 0, 1, 0, 0, 0
    End
Room28V1Chain13:
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room28V1Group4_id, 0
    RespawnRowAndRunChain Room28V1Group3_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room28V1Route12_id, 0, 1, 0, 0, 0
    End
Room28V1Chain14:
    ArmChainYield 1
    @ "It's a note from Hagrid: 'Dear Harry, we lost the trial. Buckbeak's execution date to be fixed. Hagrid'."
    ShowRoomDialog 530
    @ "Oh, no! They can't do this! Buckbeak isn't dangerous! I have to find Ron and Hermione."
    ShowRoomDialog 531
    DespawnRoomRowObjects Room28V1Group4_id
    SetStoryStage 21
    SetQuestState QUEST_OBJ_FIND_RON_AND_HERMIONE, QUEST_OBJECTIVE_INDEX
    SetQuestState 0, 232
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room28V1Chain15:
    ArmChainYield 0
    StartObjectAnimSequence Room28V1Group3_id, 0, 0, 0, Room28V1Route5_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room28V1Group3_id, 2, 0, 0, Room28V1Route7_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room28V1Group3_id, 1, 0, 0, Room28V1Route6_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room28V1Group3_id, 3, 0, 0, Room28V1Route6_id, 0, 1, 0, 0, 0
    End
Room28V1Chain16:
    ArmChainYield 1
    SetQuestState 0, QUEST_ALT_PRESENTATION
    PlayCutscene 1, 0, Room28V1Chain13_id
    End
Room28V1Chain17:
    ArmChainYield 1
    SetQuestState 1, 231
    ReturnToOverworld 28, 2
    End
Room28V1Chain18:
    SetTileObjectAnimState Room28V0Group0_id, 1
    End
Room28V1Chain19:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetTileObjectFacing 0, 255, 4
    @ "It's a black dog!"
    ShowRoomDialog 529
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room28V1Route10_id, 0, 1, 0, 0, 0
    End
    EndSubBlock Room28V1End

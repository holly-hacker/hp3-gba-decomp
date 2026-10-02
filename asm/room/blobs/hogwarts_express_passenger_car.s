    .include "asm/room_blob.inc"

Room06Blob:
    RoomBlob 2
    PlayerEntry 590, 184, 0, 6
    PlayerEntry 82, 185, 1, 2
    StageIndex 4
    StageToVariant 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    VariantEntry Room06V0
    VariantEntry Room06V1
    VariantEntry Room06V2
    VariantEntry Room06V3

    SubBlock Room06V0, 1, Room06V0Routes, Room06V0Chains, Room06V0End
    OffsetTable Room06V0Groups, 1
    Offsets Room06V0Group0
    EndTable
    Group Room06V0Group0, 3
    TileAnimation 142, 178, anim_id=19
    TileAnimation 304, 179, anim_id=20
    TileAnimation 461, 182, anim_id=21
    OffsetTable Room06V0Routes, 0
    EndTable
    OffsetTable Room06V0Chains, 1
    Offsets Room06V0Chain0
    EndTable
Room06V0Chain0:
    End
    EndSubBlock Room06V0End

    SubBlock Room06V1, 1, Room06V1Routes, Room06V1Chains, Room06V1End
    OffsetTable Room06V1Groups, 13, 1
    Offsets Room06V1Group0, Room06V1Group1, Room06V1Group2, Room06V1Group3, Room06V1Group4, Room06V1Group5
    Offsets Room06V1Group6, Room06V1Group7, Room06V1Group8, Room06V1Group9, Room06V1Group10, Room06V1Group11
    Offsets Room06V1Group12
    EndTable
    Group Room06V1Group0, 6
    Npc 143, 123, sprite=15, facing=2
    TriggerZone 510, 233, half_width=16, half_height=17, chain=Room06V1Chain13_id
    TriggerZone 56, 189, half_width=21, half_height=22, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room06V1Chain15_id
    TriggerZone 628, 186, half_width=14, half_height=23, rearm_delay=1, chain=Room06V1Chain16_id
    TriggerZone 404, 234, half_width=26, half_height=18, chain=Room06V1Chain19_id
    TriggerZone 82, 108, half_width=15, half_height=8, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room06V1Chain15_id
    Group Room06V1Group1, 3
    TriggerZone 484, 223, half_width=20, half_height=4, require_a_press=1, chain=Room06V1Chain6_id
    TriggerZone 329, 223, half_width=20, half_height=4, require_a_press=1, chain=Room06V1Chain5_id
    TriggerZone 176, 223, half_width=20, half_height=4, require_a_press=1, chain=Room06V1Chain4_id
    Group Room06V1Group2, 2
    Npc 174, 186, sprite=32, facing=0
    Npc 174, 216, sprite=34, facing=0
    Group Room06V1Group3, 2
    Npc 578, 208, sprite=34, facing=0
    Npc 570, 179, sprite=32, facing=2
    Group Room06V1Group4, 7
    Npc 327, 123, sprite=22, facing=4, interact_cooldown=3, interact_mode=1, chain=Room06V1Chain25_id
    Npc 342, 149, sprite=23, facing=6, interact_cooldown=3, interact_mode=1, chain=Room06V1Chain26_id
    Npc 313, 152, sprite=28, facing=2, interact_cooldown=3, interact_mode=1, chain=Room06V1Chain24_id
    Npc 464, 149, sprite=26, facing=2, interact_cooldown=3, interact_mode=1, chain=Room06V1Chain21_id, arg_0f=0
    Npc 476, 123, sprite=27, facing=4, interact_cooldown=3, interact_mode=1, chain=Room06V1Chain20_id
    Npc 493, 144, sprite=29, facing=6, interact_cooldown=3, interact_mode=1, chain=Room06V1Chain22_id
    Npc 490, 168, sprite=30, facing=0, interact_cooldown=3, interact_mode=1, chain=Room06V1Chain23_id
    Group Room06V1Group5, 1
    TriggerZone 282, 233, half_width=12, half_height=22, chain=Room06V1Chain9_id
    Group Room06V1Group6, 0
    Group Room06V1Group7, 1
    TriggerZone 172, 170, half_width=37, half_height=14, chain=Room06V1Chain1_id
    Group Room06V1Group8, 0
    Group Room06V1Group9, 1
    Npc 299, 239, sprite=63, facing=6
    Group Room06V1Group10, 2
    Npc 100, 233, sprite=21, facing=4, arg_0f=0
    TriggerZone 100, 234, half_width=23, half_height=23, chain=Room06V1Chain17_id
    Group Room06V1Group11, 2
    TriggerZone 100, 231, half_width=23, half_height=23, rearm_delay=3, trigger_kind=1, chain=Room06V1Chain18_id
    Npc 100, 233, sprite=21, facing=4, arg_0f=0
    Group Room06V1Group12, 1
    Npc 218, 239, sprite=63, facing=6
    OffsetTable Room06V1Routes, 7
    Offsets Room06V1Route0, Room06V1Route1, Room06V1Route2, Room06V1Route3, Room06V1Route4, Room06V1Route5
    Offsets Room06V1Route6
    EndTable
Room06V1Route0:
    Route 2
    Waypoint 298, 239
    Waypoint 218, 239, on_arrival_chain=Room06V1Chain11_id
Room06V1Route1:
    Route 1
    Waypoint 195, 239
Room06V1Route2:
    Route 2
    Waypoint 174, 145
    Waypoint 192, 145, on_arrival_chain=Room06V1Chain29_id
Room06V1Route3:
    Route 3
    Waypoint 174, 146
    Waypoint 174, 191, on_arrival_chain=Room06V1Chain33_id
    Waypoint 174, 229, on_arrival_chain=Room06V1Chain32_id
Room06V1Route4:
    Route 3
    Waypoint 192, 146
    Waypoint 174, 146
    Waypoint 174, 246, on_arrival_chain=Room06V1Chain30_id
Room06V1Route5:
    Route 3
    Waypoint 175, 146
    Waypoint 192, 146
    Waypoint 192, 118, on_arrival_chain=Room06V1Chain28_id
Room06V1Route6:
    Route 1
    Waypoint 195, 239, on_arrival_chain=Room06V1Chain31_id
    OffsetTable Room06V1Chains, 36, 1
    Offsets Room06V1Chain0, Room06V1Chain1, Room06V1Chain2, Room06V1Chain3, Room06V1Chain4, Room06V1Chain5
    Offsets Room06V1Chain6, Room06V1Chain7, Room06V1Chain8, Room06V1Chain9, Room06V1Chain10, Room06V1Chain11
    Offsets Room06V1Chain12, Room06V1Chain13, Room06V1Chain14, Room06V1Chain15, Room06V1Chain16, Room06V1Chain17
    Offsets Room06V1Chain18, Room06V1Chain19, Room06V1Chain20, Room06V1Chain21, Room06V1Chain22, Room06V1Chain23
    Offsets Room06V1Chain24, Room06V1Chain25, Room06V1Chain26, Room06V1Chain27, Room06V1Chain28, Room06V1Chain29
    Offsets Room06V1Chain30, Room06V1Chain31, Room06V1Chain32, Room06V1Chain33, Room06V1Chain34, Room06V1Chain35
    EndTable
Room06V1Chain0:
    GotoIfQuestStateCompare 224, 0, 0, Room06V1Chain34_id, 0, 0, 0
    RespawnRowAndRunChain Room06V1Group4_id, 0
    RespawnRowAndRunChain Room06V1Group1_id, 0
    GotoIfQuestStateCompare 6, 1, 0, 0, 0, Room06V1Group12_id, 0
    GotoIfQuestStateCompare 6, 0, 0, 0, 0, Room06V1Group7_id, 0
    GotoIfQuestStateCompare 224, 0, 0, Room06V1Chain2_id, Room06V1Chain8_id, Room06V1Group3_id, 0
    GotoIfQuestStateCompare 235, 0, 15, Room06V1Chain10_id, 0, 0, 0
    GotoIfQuestStateCompare 8, 0, 9, Room06V1Chain35_id, 0, 0, 0
    End
Room06V1Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ClearTileObjectFlagBit 0, 255, 9
    StartTileObjectScript 174, 153, 0, 0, 255, 0, 0, 7, 255, 255, 255
    RespawnRowAndRunChain Room06V1Group2_id, 0
    RemovePartyFollower 7
    RemovePartyFollower 6
    ArmChainYield 0
    StartObjectAnimSequence Room06V1Group2_id, 0, 0, 0, Room06V1Route2_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room06V1Group2_id, 1, 0, 0, Room06V1Route5_id, 0, 1, 0, 0, 0
    End
Room06V1Chain2:
    PlaySoundById 63
    PlayTileObjectAnimation Room06V1Group0_id, 0, 7
    SetQuestState 1, 224
    SetQuestState QUEST_OBJ_FIND_YOUR_SEAT, QUEST_OBJECTIVE_INDEX
    InvokeChainIfEnabled 0, Room06V1Chain3_id
    SetQuestState 9, 8
    End
Room06V1Chain3:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetTileObjectFacing 0, 255, 6
    @ "We'd better hurry up and find seats."
    ShowRoomDialog 86
    StartTileObjectScript 570, 184, 0, Room06V1Group3_id, 1, 0, 0, 6, 255, 255, 255
    StartTileObjectScript 590, 184, 0, Room06V1Group3_id, 1, 0, 0, 6, 255, 255, 255
    DespawnTileObject Room06V1Group3_id, 1
    RecruitPartyFollower 7
    StartTileObjectScript 590, 184, 0, Room06V1Group3_id, 0, 0, 0, 2, 255, 255, 255
    DespawnTileObject Room06V1Group3_id, 0
    RecruitPartyFollower 6
    SetBattleDefeatState 1
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room06V1Chain4:
    SetTileObjectAnimState Room06V0Group0_id, 0
    CancelObjectAnimSequence 0, 255
    PlaySoundById 14
    DelayedRespawnRowAndRunChainFrames 15, 0, Room06V1Chain27_id
    End
Room06V1Chain5:
    SetTileObjectAnimState Room06V0Group0_id, 1
    CancelObjectAnimSequence 0, 255
    PlaySoundById 14
    DelayedRespawnRowAndRunChainFrames 15, 0, Room06V1Chain27_id
    End
Room06V1Chain6:
    SetTileObjectAnimState Room06V0Group0_id, 2
    CancelObjectAnimSequence 0, 255
    PlaySoundById 14
    DelayedRespawnRowAndRunChainFrames 15, 0, Room06V1Chain27_id
    End
Room06V1Chain7:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    UnmuteAllMusicChannels
    PlaySpecialSceneEffect 1
    DelayedRespawnRowAndRunChain 5, 0, 0
    StartTileObjectScript 168, 124, 0, 0, 255, 0, 0, 0, 255, 255, 255
    SetQuestState 1, 6
    SetQuestState 15, 235
    ClearAllQueuedMoves
    SetTileObjectFacing 0, 255, 0
    RespawnRowAndRunChain Room06V1Group9_id, 0
    @ "What's going on? Why's the train stopped?"
    ShowRoomDialog 111
    StartTileObjectScript 170, 147, 0, 0, 255, 0, 0, 4, 255, 255, 255
    Unk02 Room06V1Group9_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence Room06V1Group9_id, 0, 0, 0, Room06V1Route0_id, 0, 1, 0, 0, 0
    SetQuestState 0, 8
    End
Room06V1Chain8:
    PlayTileObjectAnimation Room06V1Group0_id, 0, 7
    End
Room06V1Chain9:
    End
Room06V1Chain10:
    DespawnTileObject Room06V1Group7_id, 0
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    End
Room06V1Chain11:
    ArmChainYield 1
    SetTileObjectFacing Room06V1Group9_id, 0, 6
    StartTileObjectScript 175, 239, 0, 0, 255, 0, 0, 2, 255, 255, 255
    StartTileObjectScript 195, 239, 0, 0, 255, 0, 0, 2, 255, 255, 255
    SetTileObjectFacing 0, 255, 2
    ArmChainYield 0
    StartObjectAnimSequence Room06V1Group2_id, 0, 0, 0, Room06V1Route3_id, 0, 1, 0, 0, 0
    End
Room06V1Chain12:
    DespawnTileObject Room06V1Group0_id, 0
    End
Room06V1Chain13:
    GotoIfQuestStateCompare 6, 3, 3, Room06V1Chain12_id, 0, 0, 0
    End
Room06V1Chain14:
    SetAllQueuedMoveParams 0, 1, 0, 0, 65535
    End
Room06V1Chain15:
    @ "Locked."
    ShowRoomDialog 624
    End
Room06V1Chain16:
    SetStoryStage 3
    ReturnToOverworld 6, 1
    End
Room06V1Chain17:
    @ "Excuse me..."
    @ "Yes, miss?"
    @ "Erm... Professor Lupin was wondering if you might get the train moving again - if that's possible?"
    @ "Of course it's possible. Tell Professor Lupin we'll be underway very soon."
    @ "OK. Thank you very much."
    ShowRoomDialog 132
    SetQuestState 1, 246
    DelayedRespawnRowAndRunChain 0, Room06V1Group11_id, 0
    SetBattleDefeatState 1
    SetQuestState 11, 6
    SetQuestState QUEST_OBJ_RETURN_TO_LUPIN, QUEST_OBJECTIVE_INDEX
    End
Room06V1Chain18:
    @ "Better return to your seat, miss. We'll be at Hogsmeade very shortly."
    ShowRoomDialog 133
    End
Room06V1Chain19:
    GotoIfQuestStateCompare 6, 0, 7, 0, 0, Room06V1Group10_id, 0
    GotoIfQuestStateCompare 6, 3, 11, 0, 0, Room06V1Group11_id, 0
    End
Room06V1Chain20:
    @ "How nice to see you."
    ShowRoomDialog 102
    End
Room06V1Chain21:
    @ "Hello."
    ShowRoomDialog 103
    End
Room06V1Chain22:
    @ "Great to see you."
    ShowRoomDialog 104
    End
Room06V1Chain23:
    @ "Really good to see you."
    ShowRoomDialog 105
    End
Room06V1Chain24:
    @ "Well, look who it is."
    ShowRoomDialog 106
    End
Room06V1Chain25:
    @ "We don't speak to Gryffindors."
    ShowRoomDialog 107
    End
Room06V1Chain26:
    @ "Who do you think you're talking to?"
    ShowRoomDialog 108
    End
Room06V1Chain27:
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room06V1Chain28:
    SetTileObjectFacing Room06V1Group2_id, 1, 6
    ArmChainYield 1
    QueueTileObjectMove Room06V1Group0_id, 0, 0, 0, 1100, 0
    @ "These look like the only empty seats."
    @ "Who d'you reckon he is?"
    @ "Professor R. J. Lupin. He's the new Defense Against the Dark Arts teacher."
    @ "Zzzzzz¸"
    ShowRoomDialog 109
    QueueTileObjectMove 0, 255, 9, 0, 1500, 0
    InvokeChainIfEnabled 0, Room06V1Chain7_id
    End
Room06V1Chain29:
    SetTileObjectFacing Room06V1Group2_id, 0, 6
    End
Room06V1Chain30:
    SetTileObjectFacing Room06V1Group2_id, 1, 2
    ArmChainYield 1
    @ "Harry, I can't find my toad, Trevor. Can you help me find him?"
    @ "Where did you last see him?"
    @ "Someone said they saw him near the baggage car - but I don't think we're allowed in there."
    @ "Don't worry, Neville, we'll find him for you."
    @ "Thanks, Harry. I'll wait here for you."
    ShowRoomDialog 143
    StartObjectAnimSequence Room06V1Group2_id, 0, 0, 0, Room06V1Route1_id, 0, 1, 0, 0, 0
    SetTileObjectFacing Room06V1Group2_id, 0, 2
    StartObjectAnimSequence Room06V1Group2_id, 1, 0, 0, Room06V1Route6_id, 0, 1, 0, 0, 0
    End
Room06V1Chain31:
    SetTileObjectFacing Room06V1Group2_id, 1, 2
    RecruitPartyFollower 6
    DespawnTileObject Room06V1Group2_id, 1
    RecruitPartyFollower 7
    DespawnTileObject Room06V1Group2_id, 0
    SetQuestState QUEST_OBJ_FIND_TREVOR, QUEST_OBJECTIVE_INDEX
    SetTileObjectFlagBit 0, 255, 9
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room06V1Chain32:
    SetTileObjectFacing Room06V1Group2_id, 0, 2
    End
Room06V1Chain33:
    StartObjectAnimSequence Room06V1Group2_id, 1, 0, 0, Room06V1Route4_id, 0, 1, 0, 0, 0
    End
Room06V1Chain34:
    Unk2A 5, 255, 255, 255
    RemovePartyFollower 7
    RemovePartyFollower 6
    SetTileObjectFacing 0, 255, 6
    End
Room06V1Chain35:
    PlaySoundById 63
    End
    EndSubBlock Room06V1End

    SubBlock Room06V2, 1, Room06V2Routes, Room06V2Chains, Room06V2End
    OffsetTable Room06V2Groups, 5, 1
    Offsets Room06V2Group0, Room06V2Group1, Room06V2Group2, Room06V2Group3, Room06V2Group4
    EndTable
    Group Room06V2Group0, 2
    Npc 163, 137, sprite=15, facing=4
    Npc 173, 147, sprite=16, facing=2
    Group Room06V2Group1, 2
    TriggerZone 166, 145, half_width=40, half_height=49, chain=Room06V2Chain3_id
    Npc 193, 124, sprite=34, facing=5
    Group Room06V2Group2, 1
    TriggerZone 167, 146, half_width=40, half_height=49, rearm_delay=4, trigger_kind=1, chain=Room06V2Chain4_id
    Group Room06V2Group3, 2
    TriggerZone 173, 147, half_width=40, half_height=49, chain=Room06V2Chain6_id
    Npc 193, 154, sprite=32, facing=7
    Group Room06V2Group4, 1
    TriggerZone 173, 147, half_width=40, half_height=49, rearm_delay=4, trigger_kind=1, chain=Room06V2Chain5_id
    OffsetTable Room06V2Routes, 0
    EndTable
    OffsetTable Room06V2Chains, 11, 1
    Offsets Room06V2Chain0, Room06V2Chain1, Room06V2Chain2, Room06V2Chain3, Room06V2Chain4, Room06V2Chain5
    Offsets Room06V2Chain6, Room06V2Chain7, Room06V2Chain8, Room06V2Chain9, Room06V2Chain10
    EndTable
Room06V2Chain0:
    GotoIfStoryStageCompare 0, 9, Room06V2Chain9_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 10, Room06V2Chain10_id, 0, 0, 0
    GotoIfQuestStateCompare 235, 0, 1, 0, 0, 0, 0
    End
Room06V2Chain1:
    DelayedRespawnRowAndRunChain 0, Room06V2Group1_id, 0
    End
Room06V2Chain2:
    DelayedRespawnRowAndRunChain 0, Room06V2Group2_id, 0
    End
Room06V2Chain3:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 189, 153, 0, 0, 255, 0, 0, 1, 255, 255, 255
    @ "Here's the chocolate, Professor!"
    @ "Well done, Mr. Weasley."
    ShowRoomDialog 138
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room06V2Chain4:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 189, 153, 0, 0, 255, 0, 0, 1, 255, 255, 255
    StartTileObjectScript 173, 216, 0, 0, 255, 0, 0, 4, 255, 255, 255
    End
Room06V2Chain5:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 189, 153, 0, 0, 255, 0, 0, 1, 255, 255, 255
    @ "There you are, Harry!"
    @ "Um... Hello..."
    @ "I am Cornelius Fudge, Harry, the Minister for Magic."
    @ "Hello, Mr. Fudge. Have you had any luck with catching Sirius Black yet?"
    @ "What's that?"
    @ "Sirius Black, the murderer who killed thirteen people with a single curse and who recently escaped from Azkaban prison?"
    @ "Oh, that Sirius Black - well, no, not yet, but it's only a matter of time. The Azkaban guards have never yet failed. Now, allow me to escort you to your room. Follow me closely - we don't want you getting lost¸"
    @ "All right, thank you."
    ShowRoomDialog 0
    StartTileObjectScript 173, 216, 0, 0, 255, 0, 0, 4, 255, 255, 255
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room06V2Chain6:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 189, 153, 0, 0, 255, 0, 0, 1, 255, 255, 255
    @ "Job done, Professor Lupin."
    @ "Thank you, Miss Granger."
    ShowRoomDialog 139
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room06V2Chain7:
    DelayedRespawnRowAndRunChain 0, Room06V2Group3_id, 0
    SetAllQueuedMoveParams 0, 1, 0, 0, 65535
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 190, 148, 0, 0, 255, 0, 0, 6, 255, 255, 255
    @ "Job done, Professor Lupin."
    @ "Thank you, Miss Granger."
    ShowRoomDialog 139
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room06V2Chain8:
    DelayedRespawnRowAndRunChain 0, Room06V2Group4_id, 0
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 187, 126, 0, 0, 255, 0, 0, 5, 255, 255, 255
    StartTileObjectScript 182, 232, 0, 0, 255, 0, 0, 4, 255, 255, 255
    End
Room06V2Chain9:
    GotoIfQuestStateCompare 227, 0, 0, Room06V2Chain2_id, 0, 0, 0
    GotoIfQuestStateCompare 227, 0, 1, Room06V2Chain1_id, 0, 0, 0
    End
Room06V2Chain10:
    GotoIfQuestStateCompare 227, 0, 0, Room06V2Chain8_id, 0, 0, 0
    GotoIfQuestStateCompare 227, 0, 1, Room06V2Chain7_id, 0, 0, 0
    End
    EndSubBlock Room06V2End

    SubBlock Room06V3, 1, Room06V3Routes, Room06V3Chains, Room06V3End
    OffsetTable Room06V3Groups, 3, 1
    Offsets Room06V3Group0, Room06V3Group1, Room06V3Group2
    EndTable
    Group Room06V3Group0, 18
    Prop 581, 240, kind=0, facing=6, arg_10=1
    TriggerZone 482, 224, half_width=20, half_height=4, require_a_press=1, chain=Room06V3Chain3_id
    TriggerZone 327, 224, half_width=20, half_height=4, require_a_press=1, chain=Room06V3Chain2_id
    TriggerZone 175, 224, half_width=20, half_height=4, require_a_press=1, chain=Room06V3Chain1_id
    Npc 165, 119, sprite=47, facing=2, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain12_id, arg_0f=0
    Npc 164, 164, sprite=60, facing=4, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain6_id, arg_0f=0
    Npc 187, 164, sprite=51, facing=0, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain7_id, arg_0f=0
    TriggerZone 619, 176, half_width=8, half_height=35, chain=Room06V3Chain24_id
    Npc 318, 114, sprite=44, facing=4, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain14_id, arg_0f=0
    Npc 340, 128, sprite=46, facing=6, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain9_id
    Npc 315, 148, sprite=59, facing=2, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain10_id, arg_0f=0
    Npc 480, 117, sprite=44, facing=4, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain11_id
    Npc 469, 133, sprite=42, facing=6, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain13_id
    Prop 76, 240, kind=0, facing=2, arg_10=1
    TriggerZone 55, 181, half_width=5, half_height=20, chain=Room06V3Chain17_id
    Npc 186, 118, sprite=57, facing=4, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain5_id, arg_0f=0
    Npc 565, 189, sprite=61, facing=6, interact_cooldown=3, interact_mode=1, chain=Room06V3Chain15_id
    TriggerZone 84, 106, half_width=15, half_height=8, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room06V3Chain27_id
    Group Room06V3Group1, 2
    Npc 559, 232, sprite=106, facing=0
    TriggerZone 558, 232, half_width=19, half_height=21, chain=Room06V3Chain19_id
    Group Room06V3Group2, 1
    TriggerZone 252, 232, half_width=22, half_height=26, chain=Room06V3Chain29_id
    OffsetTable Room06V3Routes, 5
    Offsets Room06V3Route0, Room06V3Route1, Room06V3Route2, Room06V3Route3, Room06V3Route4
    EndTable
Room06V3Route0:
    Route 5
    Waypoint 167, 140
    Waypoint 184, 140
    Waypoint 175, 140
    Waypoint 175, 120
    Waypoint 167, 120
Room06V3Route1:
    Route 5
    Waypoint 340, 140
    Waypoint 340, 158
    Waypoint 318, 159
    Waypoint 318, 125
    Waypoint 340, 125
Room06V3Route2:
    Route 6
    Waypoint 489, 130
    Waypoint 470, 130
    Waypoint 470, 150
    Waypoint 470, 160
    Waypoint 489, 160
    Waypoint 489, 143
Room06V3Route3:
    Route 10
    Waypoint 570, 182
    Waypoint 570, 183
    Waypoint 570, 233
    Waypoint 92, 233
    Waypoint 93, 183
    Waypoint 50, 183
    Waypoint 87, 183
    Waypoint 87, 237
    Waypoint 563, 237
    Waypoint 563, 183
Room06V3Route4:
    Route 2
    Waypoint 545, 230
    Waypoint 563, 229
    OffsetTable Room06V3Chains, 31, 1
    Offsets Room06V3Chain0, Room06V3Chain1, Room06V3Chain2, Room06V3Chain3, Room06V3Chain4, Room06V3Chain5
    Offsets Room06V3Chain6, Room06V3Chain7, Room06V3Chain8, Room06V3Chain9, Room06V3Chain10, Room06V3Chain11
    Offsets Room06V3Chain12, Room06V3Chain13, Room06V3Chain14, Room06V3Chain15, Room06V3Chain16, Room06V3Chain17
    Offsets Room06V3Chain18, Room06V3Chain19, Room06V3Chain20, Room06V3Chain21, Room06V3Chain22, Room06V3Chain23
    Offsets Room06V3Chain24, Room06V3Chain25, Room06V3Chain26, Room06V3Chain27, Room06V3Chain28, Room06V3Chain29
    Offsets Room06V3Chain30
    EndTable
Room06V3Chain0:
    GotoIfQuestStateCompare 6, 0, 11, Room06V3Chain28_id, 0, Room06V3Group1_id, 0
    GotoIfQuestStateCompare 6, 0, 1, Room06V3Chain30_id, 0, 0, 0
    DelayedRespawnRowAndRunChain 0, 0, Room06V3Chain16_id
    End
Room06V3Chain1:
    CancelObjectAnimSequence 0, 255
    SetTileObjectAnimState Room06V0Group0_id, 0
    PlaySoundById 14
    DelayedRespawnRowAndRunChainFrames 15, 0, Room06V3Chain23_id
    End
Room06V3Chain2:
    CancelObjectAnimSequence 0, 255
    SetTileObjectAnimState Room06V0Group0_id, 1
    PlaySoundById 14
    DelayedRespawnRowAndRunChainFrames 15, 0, Room06V3Chain23_id
    End
Room06V3Chain3:
    CancelObjectAnimSequence 0, 255
    SetTileObjectAnimState Room06V0Group0_id, 2
    PlaySoundById 14
    DelayedRespawnRowAndRunChainFrames 15, 0, Room06V3Chain23_id
    End
Room06V3Chain4:
    @ "I'm going to miss Mum and Dad."
    ShowRoomDialog 87
    End
Room06V3Chain5:
    @ "All my new owl does is sleep!"
    ShowRoomDialog 88
    End
Room06V3Chain6:
    @ "I hope there aren't any leaves on the line..."
    ShowRoomDialog 89
    End
Room06V3Chain7:
    @ "Hello. Nice day for a train ride."
    ShowRoomDialog 90
    End
Room06V3Chain8:
    @ "I hope I've packed everything."
    ShowRoomDialog 91
    End
Room06V3Chain9:
    @ "I predict that Divination class will be a lot of fun."
    ShowRoomDialog 92
    End
Room06V3Chain10:
    @ "One of my school books just growled at me!"
    ShowRoomDialog 93
    End
Room06V3Chain11:
    @ "I wonder who'll be teaching the Care of Magical Creatures class?"
    ShowRoomDialog 94
    End
Room06V3Chain12:
    @ "I hope Professor Snape isn't as nasty as everyone says."
    ShowRoomDialog 95
    End
Room06V3Chain13:
    @ "Train rides make me sleepy. I'll probably sleep all the way to Hogwarts."
    ShowRoomDialog 96
    End
Room06V3Chain14:
    @ "I think I'll try out for the Quidditch team this year."
    ShowRoomDialog 97
    End
Room06V3Chain15:
    @ "Muggle Studies sounds interesting; their peculiar artifacts and funny habits fascinate me."
    ShowRoomDialog 98
    End
Room06V3Chain16:
    StartObjectAnimSequence Room06V3Group0_id, 4, 0, 0, Room06V3Route0_id, 0, 0, 60, 0, 0
    StartObjectAnimSequence Room06V3Group0_id, 9, 0, 0, Room06V3Route1_id, 0, 0, 60, 0, 0
    StartObjectAnimSequence Room06V3Group0_id, 12, 0, 0, Room06V3Route2_id, 0, 0, 60, 0, 0
    StartObjectAnimSequence Room06V3Group0_id, 16, 0, 0, Room06V3Route3_id, 0, 0, 0, 0, 0
    End
Room06V3Chain17:
    SetStoryStage 0
    ReturnToOverworld 6, 0
    End
Room06V3Chain18:
    GotoIfQuestStateCompare 6, 0, 11, Room06V3Chain22_id, Room06V3Chain21_id, 0, 0
    End
Room06V3Chain19:
    DespawnTileObject Room06V3Group1_id, 0
    StartBattle 13, 0, Room06V3Chain20_id
    End
Room06V3Chain20:
    SetQuestState 12, 6
    PlaySpecialSceneEffect 2
    End
Room06V3Chain21:
    ArmChainYield 1
    SetStoryStage 0
    ReturnToOverworld 5, 0
    End
Room06V3Chain22:
    ArmChainYield 1
    SetStoryStage 10
    ReturnToOverworld 5, 0
    End
Room06V3Chain23:
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room06V3Chain24:
    GotoIfQuestStateCompare 250, 3, 1, Room06V3Chain25_id, Room06V3Chain21_id, 0, 0
    End
Room06V3Chain25:
    GotoIfQuestStateCompare 250, 0, 2, Room06V3Chain26_id, Room06V3Chain22_id, 0, 0
    End
Room06V3Chain26:
    ArmChainYield 1
    SetStoryStage 9
    ReturnToOverworld 5, 0
    End
Room06V3Chain27:
    @ "Locked."
    ShowRoomDialog 624
    End
Room06V3Chain28:
    StartObjectAnimSequence Room06V3Group1_id, 0, 0, 0, Room06V3Route4_id, 0, 0, 0, 0, 0
    End
Room06V3Chain29:
    PlaySpecialSceneEffect 3
    SetQuestState 1, 251
    End
Room06V3Chain30:
    GotoIfQuestStateCompare 251, 0, 0, 0, 0, Room06V3Group2_id, 0
    End
    EndSubBlock Room06V3End

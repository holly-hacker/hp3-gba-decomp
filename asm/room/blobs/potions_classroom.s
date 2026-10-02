    .include "asm/room_blob.inc"

Room01Blob:
    RoomBlob 2
    PlayerEntry 505, 484, 0, 4
    PlayerEntry 360, 214, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room01V0
    VariantEntry Room01V1

    SubBlock Room01V0, 1, Room01V0Routes, Room01V0Chains, Room01V0End
    OffsetTable Room01V0Groups, 1
    Offsets Room01V0Group0
    EndTable
    Group Room01V0Group0, 2
    Door 559, 484, half_width=10, half_height=20, destination_room=18, exit_param=2
    Chest 88, 451, flag_id=23, reward_id=61
    OffsetTable Room01V0Routes, 0
    EndTable
    OffsetTable Room01V0Chains, 1
    Offsets Room01V0Chain0
    EndTable
Room01V0Chain0:
    End
    EndSubBlock Room01V0End

    SubBlock Room01V1, 1, Room01V1Routes, Room01V1Chains, Room01V1End
    OffsetTable Room01V1Groups, 18, 1
    Offsets Room01V1Group0, Room01V1Group1, Room01V1Group2, Room01V1Group3, Room01V1Group4, Room01V1Group5
    Offsets Room01V1Group6, Room01V1Group7, Room01V1Group8, Room01V1Group9, Room01V1Group10, Room01V1Group11
    Offsets Room01V1Group12, Room01V1Group13, Room01V1Group14, Room01V1Group15, Room01V1Group16, Room01V1Group17
    EndTable
    Group Room01V1Group0, 0
    Group Room01V1Group1, 10
    TriggerZone 106, 373, half_width=38, half_height=11, respawn_group=Room01V1Group2_id, chain=Room01V1Chain13_id
    TriggerZone 265, 369, half_width=44, half_height=11, respawn_group=Room01V1Group2_id, chain=Room01V1Chain14_id
    Npc 239, 320, sprite=55, facing=4, interact_cooldown=1, interact_mode=1, chain=Room01V1Chain4_id, arg_0f=0
    Npc 118, 325, sprite=43, facing=0, interact_cooldown=1, interact_mode=1, chain=Room01V1Chain7_id, arg_0f=0
    Npc 107, 345, sprite=56, facing=2, interact_cooldown=1, interact_mode=1, chain=Room01V1Chain10_id, arg_0f=0
    Npc 111, 441, sprite=40, facing=2, interact_cooldown=1, interact_mode=1, chain=Room01V1Chain11_id, arg_0f=0
    Npc 269, 418, sprite=47, facing=6, interact_cooldown=1, interact_mode=1, chain=Room01V1Chain5_id, arg_0f=0
    Npc 183, 383, sprite=44, facing=0, interact_cooldown=1, interact_mode=1, chain=Room01V1Chain6_id, arg_0f=0
    Npc 275, 200, sprite=43, facing=4, interact_cooldown=1, interact_mode=1, chain=Room01V1Chain12_id
    Npc 250, 450, sprite=28, facing=0, interact_cooldown=3, interact_mode=1, chain=Room01V1Chain46_id, arg_0f=0
    Group Room01V1Group2, 2
    Npc 375, 194, sprite=20, facing=4
    Npc 354, 210, sprite=0, facing=4
    Group Room01V1Group3, 2
    Npc 283, 212, sprite=20, facing=2, interact_cooldown=3, interact_mode=1, chain=Room01V1Chain44_id, arg_0f=0
    TriggerZone 316, 219, half_width=60, half_height=37, chain=Room01V1Chain22_id
    Group Room01V1Group4, 1
    TriggerZone 323, 487, half_width=17, half_height=23, chain=Room01V1Chain30_id
    Group Room01V1Group5, 1
    Prop 204, 248, kind=82, arg_13=0
    Group Room01V1Group6, 1
    Npc 287, 406, sprite=31, facing=0
    Group Room01V1Group7, 1
    Npc 286, 407, sprite=32, facing=0
    Group Room01V1Group8, 1
    TriggerZone 375, 177, half_width=21, half_height=10, chain=Room01V1Chain29_id
    Group Room01V1Group9, 1
    TriggerZone 327, 489, half_width=14, half_height=32, rearm_delay=1, trigger_kind=1, chain=Room01V1Chain32_id
    Group Room01V1Group10, 1
    TriggerZone 327, 488, half_width=7, half_height=32, rearm_delay=1, trigger_kind=1, chain=Room01V1Chain33_id
    Group Room01V1Group11, 1
    TriggerZone 375, 176, half_width=18, half_height=10, chain=Room01V1Chain29_id
    Group Room01V1Group12, 1
    Npc 185, 300, sprite=31, facing=0
    Group Room01V1Group13, 1
    Npc 185, 300, sprite=32, facing=0
    Group Room01V1Group14, 1
    Npc 236, 269, sprite=31, facing=6
    Group Room01V1Group15, 1
    Npc 235, 268, sprite=32, facing=6
    Group Room01V1Group16, 1
    Npc 360, 211, sprite=34, facing=6, arg_0f=0
    Group Room01V1Group17, 1
    TriggerZone 377, 179, half_width=27, half_height=15, rearm_delay=2, trigger_kind=1, require_a_press=1, chain=Room01V1Chain45_id
    OffsetTable Room01V1Routes, 15
    Offsets Room01V1Route0, Room01V1Route1, Room01V1Route2, Room01V1Route3, Room01V1Route4, Room01V1Route5
    Offsets Room01V1Route6, Room01V1Route7, Room01V1Route8, Room01V1Route9, Room01V1Route10, Room01V1Route11
    Offsets Room01V1Route12, Room01V1Route13, Room01V1Route14
    EndTable
Room01V1Route0:
    Route 2
    Waypoint 375, 217
    Waypoint 282, 217, on_arrival_chain=Room01V1Chain15_id
Room01V1Route1:
    Route 4
    Waypoint 275, 200
    Waypoint 260, 200
    Waypoint 260, 250, on_arrival_chain=Room01V1Chain16_id
    Waypoint 260, 340
Room01V1Route2:
    Route 3
    Waypoint 262, 217
    Waypoint 150, 217
    Waypoint 150, 233, on_arrival_chain=Room01V1Chain42_id
Room01V1Route3:
    Route 4
    Waypoint 300, 220
    Waypoint 235, 220
    Waypoint 235, 295
    Waypoint 210, 295
Room01V1Route4:
    Route 2
    Waypoint 274, 479, on_arrival_chain=Room01V1Chain34_id
    Waypoint 274, 444
Room01V1Route5:
    Route 2
    Waypoint 378, 214, on_arrival_chain=Room01V1Chain47_id
    Waypoint 378, 185
Room01V1Route6:
    Route 1
    Waypoint 210, 295, on_arrival_chain=Room01V1Chain41_id
Room01V1Route7:
    Route 2
    Waypoint 235, 295
    Waypoint 210, 295
Room01V1Route8:
    Route 3
    Waypoint 210, 295
    Waypoint 285, 320
    Waypoint 285, 355
Room01V1Route9:
    Route 4
    Waypoint 130, 322
    Waypoint 246, 322
    Waypoint 272, 322
    Waypoint 272, 455
Room01V1Route10:
    Route 4
    Waypoint 107, 380
    Waypoint 185, 383
    Waypoint 280, 380
    Waypoint 280, 455
Room01V1Route11:
    Route 2
    Waypoint 270, 200
    Waypoint 270, 480, on_arrival_chain=Room01V1Chain40_id
Room01V1Route12:
    Route 1
    Waypoint 210, 295, on_arrival_chain=Room01V1Chain39_id
Room01V1Route13:
    Route 3
    Waypoint 350, 220
    Waypoint 235, 220
    Waypoint 235, 280, on_arrival_chain=Room01V1Chain28_id
Room01V1Route14:
    Route 1
    Waypoint 375, 211, on_arrival_chain=Room01V1Chain35_id
    OffsetTable Room01V1Chains, 48, 1
    Offsets Room01V1Chain0, Room01V1Chain1, Room01V1Chain2, Room01V1Chain3, Room01V1Chain4, Room01V1Chain5
    Offsets Room01V1Chain6, Room01V1Chain7, Room01V1Chain8, Room01V1Chain9, Room01V1Chain10, Room01V1Chain11
    Offsets Room01V1Chain12, Room01V1Chain13, Room01V1Chain14, Room01V1Chain15, Room01V1Chain16, Room01V1Chain17
    Offsets Room01V1Chain18, Room01V1Chain19, Room01V1Chain20, Room01V1Chain21, Room01V1Chain22, Room01V1Chain23
    Offsets Room01V1Chain24, Room01V1Chain25, Room01V1Chain26, Room01V1Chain27, Room01V1Chain28, Room01V1Chain29
    Offsets Room01V1Chain30, Room01V1Chain31, Room01V1Chain32, Room01V1Chain33, Room01V1Chain34, Room01V1Chain35
    Offsets Room01V1Chain36, Room01V1Chain37, Room01V1Chain38, Room01V1Chain39, Room01V1Chain40, Room01V1Chain41
    Offsets Room01V1Chain42, Room01V1Chain43, Room01V1Chain44, Room01V1Chain45, Room01V1Chain46, Room01V1Chain47
    EndTable
Room01V1Chain0:
    GotoIfStoryStageCompare 0, 4, Room01V1Chain18_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 4, Room01V1Chain17_id, 0, 0, 0
    GotoIfStoryStageCompare 4, 4, 0, 0, Room01V1Group17_id, 0
    GotoIfStoryStageCompare 2, 4, 0, 0, Room01V1Group17_id, 0
    End
Room01V1Chain1:
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room01V1Group1_id, 0
    DelayedRespawnRowAndRunChainFrames 10, 0, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room01V1Chain2:
    ArmChainYield 1
    QueueTileObjectMove Room01V1Group2_id, 0, 0, 0, 1850, 0
    Unk02 Room01V1Group2_id, 1, 5
    SetTileObjectFacing Room01V1Group2_id, 1, 2
    SetTileObjectFacing Room01V1Group2_id, 1, 4
    SetTileObjectFacing Room01V1Group2_id, 1, 6
    StartTileObjectScript 218, 210, 0, Room01V1Group2_id, 1, 0, 0, 6, 255, 255, 255
    DelayedRespawnRowAndRunChain 1, 0, 0
    DespawnTileObject Room01V1Group2_id, 1
    @ "Settle down, settle down. Today we shall be making a new potion, a Shrinking Solution."
    ShowRoomDialog 295
    Unk02 Room01V1Group2_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence Room01V1Group2_id, 0, 0, 0, Room01V1Route0_id, 0, 1, 0, 0, 0
    End
Room01V1Chain3:
    @ "I wonder why Professor Snape appears to dislike Gryffindors so much?"
    ShowRoomDialog 291
    End
Room01V1Chain4:
    @ "I hate Potions."
    ShowRoomDialog 287
    End
Room01V1Chain5:
    @ "Professor Snape's always so unpleasant."
    ShowRoomDialog 288
    End
Room01V1Chain6:
    @ "I don't speak to Gryffindors."
    ShowRoomDialog 289
    End
Room01V1Chain7:
    @ "Gryffindor always seems to lose house points in Snape's lessons."
    ShowRoomDialog 290
    End
Room01V1Chain8:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RemovePartyFollower 5
    DelayedRespawnRowAndRunChainFrames 1, Room01V1Group6_id, 0
    DelayedRespawnRowAndRunChainFrames 1, Room01V1Group9_id, 0
    QueueTileObjectMove 0, 255, 0, 0, 1650, 0
    @ "Weasley, while I am reluctant to assign you a task as complex as finding and carrying, I live in hope that you will surprise me."
    @ "I require potion ingredients from the Potions store room. Bring them back here to me Weasley, and take Granger with you."
    @ "The potion requires daisy root, Shrivelfig, rat spleen, dead caterpillar and leech juice."
    @ "Do not think of this as an opportunity to avoid the lesson, Weasley. Tardiness will be punished."
    @ "Yes, Professor."
    ShowRoomDialog 297
    SetQuestState QUEST_OBJ_FIND_POTION_INGREDIENTS, QUEST_OBJECTIVE_INDEX
    SetQuestState 1, 225
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room01V1Chain9:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RemovePartyFollower 7
    DelayedRespawnRowAndRunChainFrames 1, Room01V1Group7_id, 0
    DelayedRespawnRowAndRunChainFrames 1, Room01V1Group10_id, 0
    QueueTileObjectMove 0, 255, 0, 0, 1650, 0
    @ "Feeling particularly keen today, are we, Potter? Very well..."
    @ "Go to the Potions store room, Potter, retrieve some herbs and then bring them back to me. Take Miss Granger along with you."
    @ "The potion requires daisy root, Shrivelfig, rat spleen, dead caterpillar and leech juice."
    @ "Do not think of this as an opportunity to avoid the lesson, Potter."
    @ "Yes, Professor."
    @ "Let's go to the Potions store room, Hermione."
    ShowRoomDialog 298
    SetQuestState QUEST_OBJ_FIND_POTION_INGREDIENTS, QUEST_OBJECTIVE_INDEX
    SetQuestState 0, 225
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room01V1Chain10:
    @ "I much prefer Potions to Transfiguration."
    ShowRoomDialog 292
    End
Room01V1Chain11:
    @ "I think Snape's the best teacher at Hogwarts."
    ShowRoomDialog 293
    End
Room01V1Chain12:
    @ "Professor Snape's lessons are so smelly..."
    ShowRoomDialog 294
    End
Room01V1Chain13:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    ClearTileObjectFlagBit 0, 255, 9
    StartTileObjectScript 122, 115, 1, 0, 255, 0, 0, 0, 255, 255, 255
    PlaySoundById 51
    DelayedRespawnRowAndRunChainFrames 2, 0, 0
    SetTileObjectFacing Room01V1Group1_id, 2, 1
    DelayedRespawnRowAndRunChainFrames 5, 0, 0
    SetTileObjectFacing Room01V1Group1_id, 6, 1
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    SetTileObjectFacing 0, 255, 1
    DelayedRespawnRowAndRunChainFrames 3, 0, 0
    SetTileObjectFacing Room01V1Group1_id, 7, 1
    SetTileObjectFlagBit 0, 255, 9
    DespawnTileObject Room01V1Group1_id, 1
    InvokeChainIfEnabled 0, Room01V1Chain2_id
    End
Room01V1Chain14:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    ClearTileObjectFlagBit 0, 255, 9
    StartTileObjectScript 239, 121, 1, 0, 255, 0, 0, 0, 255, 255, 255
    PlaySoundById 51
    DelayedRespawnRowAndRunChainFrames 2, 0, 0
    SetTileObjectFacing Room01V1Group1_id, 3, 1
    DelayedRespawnRowAndRunChainFrames 5, 0, 0
    SetTileObjectFacing 0, 255, 1
    DelayedRespawnRowAndRunChainFrames 3, 0, 0
    SetTileObjectFacing Room01V1Group1_id, 4, 1
    DelayedRespawnRowAndRunChainFrames 3, 0, 0
    SetTileObjectFacing Room01V1Group1_id, 5, 1
    DespawnTileObject Room01V1Group1_id, 0
    SetTileObjectFlagBit 0, 255, 9
    InvokeChainIfEnabled 0, Room01V1Chain2_id
    End
Room01V1Chain15:
    ArmChainYield 1
    Unk02 Room01V1Group1_id, 8, 3
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence Room01V1Group1_id, 8, 0, 0, Room01V1Route1_id, 0, 1, 0, 0, 0
    End
Room01V1Chain16:
    StartObjectAnimSequence Room01V1Group2_id, 0, 0, 0, Room01V1Route2_id, 0, 1, 0, 0, 0
    End
Room01V1Chain17:
    GotoIfQuestStateCompare 224, 0, 0, Room01V1Chain1_id, 0, Room01V1Group8_id, 0
    GotoIfQuestStateCompare 224, 0, 1, Room01V1Chain19_id, 0, 0, 0
    End
Room01V1Chain18:
    SetOverworldMonstersDisabled
    End
Room01V1Chain19:
    ArmChainYield 1
    RemovePartyFollower 6
    RespawnRowAndRunChain Room01V1Group1_id, 0
    RespawnRowAndRunChain Room01V1Group3_id, 0
    DespawnTileObject Room01V1Group1_id, 0
    DespawnTileObject Room01V1Group1_id, 1
    RespawnRowAndRunChain Room01V1Group11_id, 0
    RespawnRowAndRunChain Room01V1Group16_id, 0
    End
Room01V1Chain20:
    GotoIfStoryStageCompare 0, 4, Room01V1Chain29_id, 0, 0, 0
    End
Room01V1Chain21:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChainFrames 5, 0, 0
    GotoIfQuestStateCompare 231, 4, 4, Room01V1Chain25_id, Room01V1Chain27_id, 0, 0
    End
Room01V1Chain22:
    GotoIfQuestStateCompare 225, 1, 0, Room01V1Chain21_id, Room01V1Chain23_id, 0, 0
    End
Room01V1Chain23:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    GotoIfQuestStateCompare 231, 4, 4, Room01V1Chain24_id, Room01V1Chain26_id, 0, 0
    End
Room01V1Chain24:
    ArmChainYield 1
    StartTileObjectScript 305, 214, 0, 0, 255, 0, 0, 0, 255, 255, 255
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    @ "I seem to recall that I requested more herbs than this, Potter. Kindly return to the store room and collect the remaining herbs."
    ShowRoomDialog 299
    ArmChainYield 0
    InvokeChainIfEnabled 0, Room01V1Chain36_id
    End
Room01V1Chain25:
    ArmChainYield 1
    StartTileObjectScript 305, 214, 0, 0, 255, 0, 0, 0, 255, 255, 255
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    @ "I seem to recall that I requested more ingredients than this, Weasley. Do not return to me again without all the ingredients."
    ShowRoomDialog 300
    ArmChainYield 0
    InvokeChainIfEnabled 0, Room01V1Chain36_id
    End
Room01V1Chain26:
    ArmChainYield 1
    StartTileObjectScript 305, 214, 0, 0, 255, 0, 0, 0, 255, 255, 255
    @ "Quite remarkable, Potter. You appear to have achieved the task without drawing too much attention to yourself."
    ShowRoomDialog 310
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    RespawnRowAndRunChain Room01V1Group13_id, 0
    InvokeChainIfEnabled 0, Room01V1Chain31_id
    End
Room01V1Chain27:
    ArmChainYield 1
    StartTileObjectScript 305, 214, 0, 0, 255, 0, 0, 0, 255, 255, 255
    @ "You surprise me, Mr. Weasley. I was expecting you to return empty handed."
    ShowRoomDialog 311
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    RespawnRowAndRunChain Room01V1Group12_id, 0
    InvokeChainIfEnabled 0, Room01V1Chain31_id
    End
Room01V1Chain28:
    ArmChainYield 1
    SetTileObjectFacing 0, 255, 0
    SetTileObjectFacing Room01V1Group16_id, 0, 6
    SetTileObjectFacing Room01V1Group3_id, 0, 4
    Unk02 Room01V1Group16_id, 0, 1
    DelayedRespawnRowAndRunChainFrames 15, 0, 0
    ConsumeRoomItem 63
    ConsumeRoomItem 64
    ConsumeRoomItem 65
    ConsumeRoomItem 77
    ConsumeRoomItem 66
    ShowItemRemovedMessage 63
    ShowItemRemovedMessage 64
    ShowItemRemovedMessage 65
    ShowItemRemovedMessage 66
    ShowItemRemovedMessage 77
    @ "Don't think you're leaving just yet. The Shrinking Solution has yet to be brewed."
    @ "Uh-oh, how are we going to brew the potion?"
    @ "Maybe Hermione knows?"
    @ "It isn't difficult. Simply put the herbs and ingredients into the cauldron."
    @ "There go the herbs..."
    @ "And now for the ingredients..."
    ShowRoomDialog 315
    DelayedRespawnRowAndRunChain 2, 0, 0
    RespawnRowAndRunChain Room01V1Group5_id, 0
    PlaySoundById 66
    DelayedRespawnRowAndRunChain 2, 0, 0
    @ "It's worked!"
    @ "I suppose you expect a reward... Take this Wingardium Leviosa spellbook. And try not to use it in a way that will get you expelled. Your next class is Defense Against the Dark Arts. You are dismissed."
    ShowRoomDialog 316
    GrantPartySpell 5
    GrantPartySpell 6
    GrantPartySpell 7
    ShowSpellLearnedMessage 8, 1
    SetQuestState QUEST_OBJ_GO_TO_STAFF_ROOM, QUEST_OBJECTIVE_INDEX
    DespawnRoomRowObjects Room01V1Group11_id
    RespawnRowAndRunChain Room01V1Group4_id, 0
    GotoIfQuestStateCompare 225, 1, 0, Room01V1Chain37_id, Room01V1Chain38_id, 0, 0
    End
Room01V1Chain29:
    SetQuestState 1, 224
    ClearOverworldMonstersDisabled
    SetStoryStage 4
    ReturnToOverworld 2, 0
    End
Room01V1Chain30:
    @ "It's almost time for Defense Against the Dark Arts class."
    @ "I've just seen a notice on the staff-room door saying that we should all meet up inside the staff-room for Defense Against the Dark Arts."
    @ "OK, let's go."
    ShowRoomDialog 335
    ClearOverworldMonstersDisabled
    End
Room01V1Chain31:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    Unk02 Room01V1Group16_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room01V1Route3_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room01V1Group16_id, 0, 0, 0, Room01V1Route13_id, 0, 1, 0, 0, 0
    End
Room01V1Chain32:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "Do not think of this as an opportunity to avoid the lesson, Weasley. Tardiness will be punished."
    @ "Yes, Professor."
    ShowRoomDialog 319
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room01V1Route4_id, 0, 1, 0, 0, 0
    End
Room01V1Chain33:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "Do not think of this as an opportunity to avoid the lesson, Potter."
    @ "Yes, Professor."
    ShowRoomDialog 320
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room01V1Route4_id, 0, 1, 0, 0, 0
    End
Room01V1Chain34:
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room01V1Chain35:
    ArmChainYield 1
    RecruitPartyFollower 6
    ReturnToOverworld 2, 0
    End
Room01V1Chain36:
    StartObjectAnimSequence 0, 255, 0, 0, Room01V1Route5_id, 0, 1, 0, 0, 0
    End
Room01V1Chain37:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    SetTileObjectFacing 0, 255, 4
    ArmChainYield 0
    StartObjectAnimSequence Room01V1Group16_id, 0, 0, 0, Room01V1Route7_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room01V1Group12_id, 0, 0, 0, Room01V1Route12_id, 0, 1, 0, 0, 0
    End
Room01V1Chain38:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    SetTileObjectFacing 0, 255, 4
    ArmChainYield 0
    StartObjectAnimSequence Room01V1Group16_id, 0, 0, 0, Room01V1Route7_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room01V1Group13_id, 0, 0, 0, Room01V1Route6_id, 0, 1, 0, 0, 0
    End
Room01V1Chain39:
    ArmChainYield 1
    DespawnRoomRowObjects Room01V1Group12_id
    DespawnRoomRowObjects Room01V1Group16_id
    RecruitPartyFollower 5
    RecruitPartyFollower 6
    InvokeChainIfEnabled 0, Room01V1Chain43_id
    End
Room01V1Chain40:
    ArmChainYield 1
    DespawnRoomRowObjects Room01V1Group1_id
    DespawnRoomRowObjects Room01V1Group3_id
    DelayedRespawnRowAndRunChain 1, 0, 0
    PlaySoundById 23
    ClearQuestStateUpperHalf
    RespawnRowAndRunChain Room01V1Group17_id, 0
    SetStoryStage 5
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room01V1Chain41:
    ArmChainYield 1
    DespawnRoomRowObjects Room01V1Group13_id
    DespawnRoomRowObjects Room01V1Group16_id
    RecruitPartyFollower 7
    RecruitPartyFollower 6
    InvokeChainIfEnabled 0, Room01V1Chain43_id
    End
Room01V1Chain42:
    ArmChainYield 1
    SetTileObjectFacing Room01V1Group2_id, 0, 4
    SetTileObjectFacing Room01V1Group1_id, 8, 6
    @ "I require a volunteer to gather ingredients for this potion."
    ShowRoomDialog 296
    SetQuestState QUEST_OBJ_FIND_POTION_INGREDIENTS, QUEST_OBJECTIVE_INDEX
    ShowLoadingScreenTransition 5, 6, 32, 255
    GotoIfStoryStageCompare 0, 5, Room01V1Chain9_id, Room01V1Chain8_id, 0, 0
    End
Room01V1Chain43:
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room01V1Route8_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room01V1Group1_id, 2, 0, 0, Room01V1Route9_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room01V1Group1_id, 6, 0, 0, Room01V1Route9_id, 3, 1, 0, 0, 0
    StartObjectAnimSequence Room01V1Group1_id, 3, 0, 0, Room01V1Route9_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room01V1Group1_id, 4, 0, 0, Room01V1Route10_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room01V1Group1_id, 7, 0, 0, Room01V1Route10_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room01V1Group1_id, 8, 0, 0, Room01V1Route11_id, 0, 1, 0, 0, 0
    End
Room01V1Chain44:
    @ "Good evening, Sirius. How I hoped I would be the one to catch you¸"
    ShowRoomDialog 482
    End
Room01V1Chain45:
    @ "Locked."
    ShowRoomDialog 624
    End
Room01V1Chain46:
    @ "Thinking of trying to catch Black single-handed, Potter?"
    ShowRoomDialog 346
    End
Room01V1Chain47:
    StartObjectAnimSequence Room01V1Group16_id, 0, 0, 0, Room01V1Route14_id, 0, 1, 0, 0, 0
    End
    EndSubBlock Room01V1End

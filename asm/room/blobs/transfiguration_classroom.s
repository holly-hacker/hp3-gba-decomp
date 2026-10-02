    .include "asm/room_blob.inc"

Room03Blob:
    RoomBlob 2
    PlayerEntry 674, 385, 0, 0
    PlayerEntry 219, 469, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room03V0
    VariantEntry Room03V1

    SubBlock Room03V0, 1, Room03V0Routes, Room03V0Chains, Room03V0End
    OffsetTable Room03V0Groups, 1
    Offsets Room03V0Group0
    EndTable
    Group Room03V0Group0, 3
    Door 671, 347, half_width=26, half_height=14, destination_room=16, exit_param=3
    TileAnimation 46, 212, anim_id=16
    Chest 275, 273, flag_id=19, reward_id=119
    OffsetTable Room03V0Routes, 0
    EndTable
    OffsetTable Room03V0Chains, 1
    Offsets Room03V0Chain0
    EndTable
Room03V0Chain0:
    End
    EndSubBlock Room03V0End

    SubBlock Room03V1, 1, Room03V1Routes, Room03V1Chains, Room03V1End
    OffsetTable Room03V1Groups, 10, 1
    Offsets Room03V1Group0, Room03V1Group1, Room03V1Group2, Room03V1Group3, Room03V1Group4, Room03V1Group5
    Offsets Room03V1Group6, Room03V1Group7, Room03V1Group8, Room03V1Group9
    EndTable
    Group Room03V1Group0, 1
    TriggerZone 198, 468, half_width=9, half_height=29, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room03V1Chain22_id
    Group Room03V1Group1, 2
    Npc 315, 250, sprite=17, facing=4
    TriggerZone 544, 397, half_width=9, half_height=66, chain=Room03V1Chain11_id
    Group Room03V1Group2, 1
    Npc 440, 438, sprite=34, facing=0
    Group Room03V1Group3, 1
    Npc 340, 530, sprite=32, facing=6
    Group Room03V1Group4, 1
    Npc 315, 250, sprite=18, facing=4
    Group Room03V1Group5, 8
    Npc 313, 420, sprite=71, facing=0, interact_cooldown=1, interact_mode=1, chain=Room03V1Chain3_id, arg_0f=0
    Npc 339, 420, sprite=91, facing=0, interact_cooldown=1, interact_mode=1, chain=Room03V1Chain4_id, arg_0f=0
    Npc 461, 418, sprite=79, facing=0, interact_cooldown=1, interact_mode=1, chain=Room03V1Chain5_id, arg_0f=0
    Npc 433, 514, sprite=83, facing=0, interact_cooldown=1, interact_mode=1, chain=Room03V1Chain6_id, arg_0f=0
    Npc 462, 515, sprite=87, facing=0, interact_cooldown=1, interact_mode=1, chain=Room03V1Chain7_id, arg_0f=0
    Npc 478, 580, sprite=43, facing=0, interact_cooldown=1, interact_mode=1, chain=Room03V1Chain10_id
    TriggerZone 387, 480, half_width=0, half_height=0
    TriggerZone 387, 388, half_width=0, half_height=0
    Group Room03V1Group6, 3
    Npc 338, 512, sprite=64, facing=0
    Npc 435, 418, sprite=68, facing=0
    Npc 310, 512, sprite=69, facing=0
    Group Room03V1Group7, 6
    Npc 312, 427, sprite=39, facing=0
    Npc 339, 428, sprite=59, facing=0
    Npc 462, 426, sprite=47, facing=0
    Npc 433, 522, sprite=51, facing=0
    Npc 463, 523, sprite=55, facing=0
    Npc 467, 579, sprite=43, facing=0
    Group Room03V1Group8, 1
    Npc 310, 530, sprite=34, facing=2
    Group Room03V1Group9, 1
    TriggerZone 671, 356, half_width=39, half_height=25, chain=Room03V1Chain25_id
    OffsetTable Room03V1Routes, 11
    Offsets Room03V1Route0, Room03V1Route1, Room03V1Route2, Room03V1Route3, Room03V1Route4, Room03V1Route5
    Offsets Room03V1Route6, Room03V1Route7, Room03V1Route8, Room03V1Route9, Room03V1Route10
    EndTable
Room03V1Route0:
    Route 4
    Waypoint 508, 438
    Waypoint 368, 438, on_arrival_chain=Room03V1Chain12_id
    Waypoint 368, 530
    Waypoint 310, 530, on_arrival_chain=Room03V1Chain2_id
Room03V1Route1:
    Route 5
    Waypoint 315, 250
    Waypoint 315, 340
    Waypoint 245, 340
    Waypoint 245, 470
    Waypoint 195, 470, on_arrival_chain=Room03V1Chain20_id
Room03V1Route2:
    Route 7
    Waypoint 315, 432
    Waypoint 351, 432
    Waypoint 471, 432
    Waypoint 515, 432
    Waypoint 515, 380
    Waypoint 660, 380
    Waypoint 660, 358
Room03V1Route3:
    Route 8
    Waypoint 466, 530
    Waypoint 434, 530
    Waypoint 404, 530
    Waypoint 404, 462
    Waypoint 520, 462
    Waypoint 520, 400
    Waypoint 680, 400
    Waypoint 680, 360
Room03V1Route4:
    Route 5
    Waypoint 340, 530
    Waypoint 380, 530
    Waypoint 380, 445
    Waypoint 515, 445
    Waypoint 508, 445
Room03V1Route5:
    Route 7
    Waypoint 460, 575
    Waypoint 395, 575
    Waypoint 395, 435
    Waypoint 545, 435
    Waypoint 545, 385
    Waypoint 670, 385
    Waypoint 670, 360, on_arrival_chain=Room03V1Chain14_id
Room03V1Route6:
    Route 4
    Waypoint 310, 530
    Waypoint 273, 530
    Waypoint 273, 471
    Waypoint 205, 470, on_arrival_chain=Room03V1Chain17_id
Room03V1Route7:
    Route 4
    Waypoint 424, 434
    Waypoint 386, 435
    Waypoint 386, 530
    Waypoint 310, 530, on_arrival_chain=Room03V1Chain16_id
Room03V1Route8:
    Route 4
    Waypoint 220, 470
    Waypoint 260, 470
    Waypoint 260, 530
    Waypoint 310, 530, on_arrival_chain=Room03V1Chain23_id
Room03V1Route9:
    Route 2
    Waypoint 310, 530
    Waypoint 340, 530, on_arrival_chain=Room03V1Chain13_id
Room03V1Route10:
    Route 2
    Waypoint 310, 530
    Waypoint 340, 530, on_arrival_chain=Room03V1Chain24_id
    OffsetTable Room03V1Chains, 26, 1
    Offsets Room03V1Chain0, Room03V1Chain1, Room03V1Chain2, Room03V1Chain3, Room03V1Chain4, Room03V1Chain5
    Offsets Room03V1Chain6, Room03V1Chain7, Room03V1Chain8, Room03V1Chain9, Room03V1Chain10, Room03V1Chain11
    Offsets Room03V1Chain12, Room03V1Chain13, Room03V1Chain14, Room03V1Chain15, Room03V1Chain16, Room03V1Chain17
    Offsets Room03V1Chain18, Room03V1Chain19, Room03V1Chain20, Room03V1Chain21, Room03V1Chain22, Room03V1Chain23
    Offsets Room03V1Chain24, Room03V1Chain25
    EndTable
Room03V1Chain0:
    GotoIfStoryStageCompare 5, 2, Room03V1Chain21_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 1, Room03V1Chain18_id, 0, 0, 0
    End
Room03V1Chain1:
    ArmChainYield 0
    ResetPartyLeaderSelection
    SetQuestState 1, 2
    RespawnRowAndRunChain Room03V1Group1_id, 0
    RespawnRowAndRunChain Room03V1Group5_id, 0
    End
Room03V1Chain2:
    ArmChainYield 1
    RespawnRowAndRunChain Room03V1Group3_id, 0
    RemovePartyFollower 7
    SetTileObjectFacing Room03V1Group3_id, 0, 0
    SetTileObjectFacing 0, 255, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    QueueTileObjectMove Room03V1Group1_id, 0, 0, 0, 1400, 0
    @ "Attention, class! Today's lesson will concern Animagi."
    @ "Animagi are wizards who can transform at will into animals. Like this..."
    ShowRoomDialog 198
    DespawnRoomRowObjects Room03V1Group2_id
    DespawnRoomRowObjects Room03V1Group3_id
    RespawnRowAndRunChain Room03V1Group6_id, 0
    PlayTileObjectAnimation Room03V1Group1_id, 0, 9
    StartTileObjectScript 310, 93, 2, 0, 255, 0, 0, 0, 255, 255, 255
    PauseMusic
    PlaySoundById 62
    QueueTileObjectMove Room03V1Group5_id, 7, 0, 0, 1200, 0
    QueueTileObjectMove Room03V1Group5_id, 6, 0, 0, 600, 0
    DelayedRespawnRowAndRunChainFrames 15, 0, 0
    QueueTileObjectMove Room03V1Group5_id, 7, 0, 0, 600, 0
    QueueTileObjectMove Room03V1Group1_id, 0, 0, 0, 1200, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    PlayTileObjectAnimation Room03V1Group1_id, 0, 10
    UnmuteAllMusicChannels
    ResumeMusic
    @ "What's got into you all today? That's the first time my transformation's not got applause from a class."
    @ "Now - I need someone to assist me in a Transfiguration challenge. Any volunteers?"
    ShowRoomDialog 199
    DelayedRespawnRowAndRunChain 1, 0, 0
    InvokeChainIfEnabled 0, Room03V1Chain15_id
    End
Room03V1Chain3:
    @ "I've forgotten who teaches Transfiguration."
    ShowRoomDialog 202
    End
Room03V1Chain4:
    @ "Have you got Transfiguration next?"
    ShowRoomDialog 203
    End
Room03V1Chain5:
    @ "Professor McGonagall seems really strict."
    ShowRoomDialog 204
    End
Room03V1Chain6:
    @ "I'd hate to make Professor McGonagall angry."
    ShowRoomDialog 205
    End
Room03V1Chain7:
    @ "I love Transfiguration; it's my favorite subject."
    ShowRoomDialog 206
    End
Room03V1Chain8:
    @ "I prefer Potions to Transfiguration."
    ShowRoomDialog 207
    End
Room03V1Chain9:
    @ "I just don't get Transfiguration."
    ShowRoomDialog 208
    End
Room03V1Chain10:
    @ "Actually, Professor McGonagall can be really nice."
    ShowRoomDialog 209
    End
Room03V1Chain11:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ResetPartyLeaderSelection
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room03V1Route0_id, 0, 1, 0, 0, 0
    End
Room03V1Chain12:
    RespawnRowAndRunChain Room03V1Group2_id, 0
    RemovePartyFollower 6
    End
Room03V1Chain13:
    ArmChainYield 1
    DespawnTileObject Room03V1Group3_id, 0
    RecruitPartyFollower 7
    DespawnTileObject Room03V1Group8_id, 0
    RecruitPartyFollower 6
    Unk02 Room03V1Group7_id, 0, 2
    Unk02 Room03V1Group7_id, 2, 2
    Unk02 Room03V1Group7_id, 4, 2
    Unk02 Room03V1Group7_id, 1, 2
    Unk02 Room03V1Group7_id, 3, 2
    Unk02 Room03V1Group7_id, 5, 2
    ArmChainYield 0
    StartObjectAnimSequence Room03V1Group7_id, 0, 0, 0, Room03V1Route2_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room03V1Group7_id, 1, 0, 0, Room03V1Route2_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room03V1Group7_id, 2, 0, 0, Room03V1Route2_id, 2, 1, 0, 0, 0
    StartObjectAnimSequence Room03V1Group7_id, 4, 0, 0, Room03V1Route3_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room03V1Group7_id, 3, 0, 0, Room03V1Route3_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room03V1Group7_id, 5, 0, 0, Room03V1Route5_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room03V1Route4_id, 0, 1, 0, 0, 0
    End
Room03V1Chain14:
    ArmChainYield 1
    DespawnRoomRowObjects Room03V1Group7_id
    @ "It's time for Care of Magical Creatures class with Hagrid - come on!"
    @ "I just hope he isn't too nervous..."
    @ "I'm really looking forward to this. Let's go."
    ShowRoomDialog 229
    ClearQuestStateUpperHalf
    SetQuestState 17, 25
    RespawnRowAndRunChain Room03V1Group9_id, 0
    SetStoryStage 2
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room03V1Chain15:
    ArmChainYield 1
    @ "Mr. Potter, Miss Granger, I shall enter a maze. You must find your own way into the maze and locate me as quickly as you can. Ready... Begin!"
    ShowRoomDialog 200
    PlayTileObjectAnimation Room03V1Group1_id, 0, 9
    RespawnRowAndRunChain Room03V1Group4_id, 0
    QueueTileObjectMove Room03V1Group4_id, 0, 0, 0, 1500, 0
    DespawnTileObject Room03V1Group1_id, 0
    Unk02 Room03V1Group4_id, 0, 3
    Unk02 0, 255, 2
    RespawnRowAndRunChain Room03V1Group2_id, 0
    DespawnTileObject Room03V1Group6_id, 1
    ArmChainYield 0
    StartObjectAnimSequence Room03V1Group4_id, 0, 0, 0, Room03V1Route1_id, 0, 1, 0, 0, 0
    End
Room03V1Chain16:
    ArmChainYield 1
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    RecruitPartyFollower 6
    DespawnTileObject Room03V1Group2_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room03V1Route6_id, 0, 1, 0, 0, 0
    End
Room03V1Chain17:
    ArmChainYield 1
    Unk02 0, 255, 1
    SetQuestState 1, 223
    SetQuestState 16, 25
    ReturnToOverworld 4, 0
    End
Room03V1Chain18:
    GotoIfQuestStateCompare 223, 0, 0, Room03V1Chain1_id, Room03V1Chain19_id, 0, 0
    End
Room03V1Chain19:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room03V1Group7_id, 0
    RespawnRowAndRunChain Room03V1Group3_id, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room03V1Route8_id, 0, 1, 0, 0, 0
    End
Room03V1Chain20:
    ArmChainYield 1
    DespawnTileObject Room03V1Group4_id, 0
    QueueTileObjectMove Room03V1Group2_id, 0, 0, 0, 1200, 0
    DespawnTileObject Room03V1Group6_id, 2
    StartTileObjectScript 310, 18, 2, 0, 255, 0, 0, 0, 255, 255, 255
    Unk02 Room03V1Group2_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence Room03V1Group2_id, 0, 0, 0, Room03V1Route7_id, 0, 1, 0, 0, 0
    End
Room03V1Chain21:
    SetOverworldMonstersDisabled
    End
Room03V1Chain22:
    @ "Locked."
    ShowRoomDialog 624
    End
Room03V1Chain23:
    ArmChainYield 1
    GrantPartyExperience 25, 65535
    PlayRoomSoundEffect 24
    @ "Excellent, Mr. Potter. As a reward, you may have this Petrificus Totalus spellbook. Class is dismissed."
    ShowRoomDialog 201
    GrantPartySpell 6
    GrantPartySpell 7
    GrantPartySpell 5
    ShowSpellLearnedMessage 7, 1
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room03V1Route10_id, 0, 1, 0, 0, 0
    End
Room03V1Chain24:
    ArmChainYield 1
    RespawnRowAndRunChain Room03V1Group8_id, 0
    RemovePartyFollower 6
    ArmChainYield 0
    StartObjectAnimSequence Room03V1Group8_id, 0, 0, 0, Room03V1Route9_id, 0, 1, 0, 0, 0
    End
Room03V1Chain25:
    ClearOverworldMonstersDisabled
    End
    EndSubBlock Room03V1End

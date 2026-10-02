    .include "asm/room_blob.inc"

Room34Blob:
    RoomBlob 3
    PlayerEntry 52, 472, 0, 2
    PlayerEntry 59, 712, 1, 2
    PlayerEntry 392, 636, 2, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room34V0
    VariantEntry Room34V1

    SubBlock Room34V0, 1, Room34V0Routes, Room34V0Chains, Room34V0End
    OffsetTable Room34V0Groups, 1
    Offsets Room34V0Group0
    EndTable
    Group Room34V0Group0, 8
    Door 27, 473, half_width=8, half_height=30, destination_room=19, exit_param=3
    Door 33, 715, half_width=8, half_height=30, destination_room=19, exit_param=2
    Door 425, 629, half_width=8, half_height=20, destination_room=35
    Chest 107, 321, flag_id=31, reward_id=58
    Chest 494, 545, flag_id=32, reward_id=107
    Chest 454, 1095, flag_id=33, reward_id=61
    Chest 528, 245, flag_id=34, reward_id=105
    Prop 496, 438, kind=81
    OffsetTable Room34V0Routes, 0
    EndTable
    OffsetTable Room34V0Chains, 1
    Offsets Room34V0Chain0
    EndTable
Room34V0Chain0:
    SetBattleDefeatState 2
    End
    EndSubBlock Room34V0End

    SubBlock Room34V1, 1, Room34V1Routes, Room34V1Chains, Room34V1End
    OffsetTable Room34V1Groups, 17, 1
    Offsets Room34V1Group0, Room34V1Group1, Room34V1Group2, Room34V1Group3, Room34V1Group4, Room34V1Group5
    Offsets Room34V1Group6, Room34V1Group7, Room34V1Group8, Room34V1Group9, Room34V1Group10, Room34V1Group11
    Offsets Room34V1Group12, Room34V1Group13, Room34V1Group14, Room34V1Group15, Room34V1Group16
    EndTable
    Group Room34V1Group0, 3
    TileAnimation 400, 775, anim_id=26
    TriggerZone 97, 482, half_width=9, half_height=33, chain=Room34V1Chain9_id
    TriggerZone 98, 742, half_width=8, half_height=52, chain=Room34V1Chain9_id
    Group Room34V1Group1, 1
    Npc 212, 647, sprite=96, facing=4
    Group Room34V1Group2, 2
    Prop 374, 333, kind=48
    Prop 400, 341, kind=47
    Group Room34V1Group3, 8
    Prop 435, 263, kind=81, arg_0f=1
    Prop 467, 395, kind=81, arg_0f=1
    Prop 443, 395, kind=81
    Prop 429, 875, kind=81, arg_0f=1
    Prop 475, 892, kind=81, arg_0f=1
    Prop 442, 926, kind=81, arg_0f=1
    Prop 530, 920, kind=81
    Prop 455, 330, kind=81
    Group Room34V1Group4, 9
    Switch 463, 860, variant=1, on_activate_chain=Room34V1Chain5_id, on_deactivate_chain=Room34V1Chain7_id
    MovePlayer 321, 482, target_x=439, target_y=409, variant=1
    MovePlayer 433, 199, target_x=518, target_y=226
    MovePlayer 528, 178, target_x=435, target_y=201, variant=1
    MovePlayer 523, 422, target_x=496, target_y=571, variant=1, arg_0e=45
    MovePlayer 320, 893, target_x=238, target_y=896, variant=1
    Switch 428, 964, variant=1, on_activate_chain=Room34V1Chain5_id, on_deactivate_chain=Room34V1Chain7_id
    Switch 488, 1005, variant=1, on_activate_chain=Room34V1Chain5_id, on_deactivate_chain=Room34V1Chain7_id
    MovePlayer 495, 646, target_x=540, target_y=795
    Group Room34V1Group5, 3
    Breakable 420, 161, variant=0, member0=0, member1=1
    Breakable 574, 757, variant=0, group2=Room34V1Group3_id, member2=5
    Breakable 532, 1052, variant=0, group2=Room34V1Group3_id, member2=5
    Group Room34V1Group6, 5
    TriggerZone 105, 497, half_width=17, half_height=45, chain=Room34V1Chain2_id
    TriggerZone 96, 744, half_width=28, half_height=51, chain=Room34V1Chain3_id
    TriggerZone 259, 728, half_width=11, half_height=41, chain=Room34V1Chain24_id
    TriggerZone 237, 466, half_width=17, half_height=66, chain=Room34V1Chain25_id
    TriggerZone 388, 639, half_width=17, half_height=45, chain=Room34V1Chain37_id
    Group Room34V1Group7, 3
    Chest 369, 204, flag_id=78, reward_id=74, chain=Room34V1Chain8_id
    Chest 340, 355, flag_id=79, reward_id=74, chain=Room34V1Chain8_id
    Chest 497, 757, flag_id=77, reward_id=74, chain=Room34V1Chain8_id
    Group Room34V1Group8, 3
    TriggerZone 74, 478, half_width=8, half_height=27, chain=Room34V1Chain12_id
    TriggerZone 76, 722, half_width=8, half_height=30, chain=Room34V1Chain14_id
    TriggerZone 353, 627, half_width=12, half_height=103, chain=Room34V1Chain36_id
    Group Room34V1Group9, 1
    TriggerZone 179, 986, half_width=36, half_height=11, chain=Room34V1Chain15_id
    Group Room34V1Group10, 1
    TriggerZone 312, 1063, half_width=11, half_height=15, chain=Room34V1Chain17_id
    Group Room34V1Group11, 2
    Npc 213, 652, sprite=96, facing=4, arg_0f=0
    TriggerZone 215, 665, half_width=37, half_height=29, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room34V1Chain18_id
    Group Room34V1Group12, 1
    TriggerZone 218, 677, half_width=37, half_height=29, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room34V1Chain30_id
    Group Room34V1Group13, 4
    Npc 265, 699, sprite=34, facing=6
    Prop 199, 698, kind=90
    Npc 249, 722, sprite=32, facing=6
    TriggerZone 193, 701, half_width=9, half_height=23, trigger_kind=3, chain=Room34V1Chain53_id
    Group Room34V1Group14, 2
    TriggerZone 303, 1037, half_width=25, half_height=24, chain=Room34V1Chain16_id
    Prop 833, 310, kind=81, arg_0f=1
    Group Room34V1Group15, 0
    Group Room34V1Group16, 2
    Npc 213, 652, sprite=96, facing=4, interact_cooldown=3, interact_mode=1, chain=Room34V1Chain54_id, arg_0f=0
    TriggerZone 210, 676, half_width=21, half_height=23, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room34V1Chain54_id
    OffsetTable Room34V1Routes, 12
    Offsets Room34V1Route0, Room34V1Route1, Room34V1Route2, Room34V1Route3, Room34V1Route4, Room34V1Route5
    Offsets Room34V1Route6, Room34V1Route7, Room34V1Route8, Room34V1Route9, Room34V1Route10, Room34V1Route11
    EndTable
Room34V1Route0:
    Route 4
    Waypoint 135, 500
    Waypoint 135, 695
    Waypoint 210, 695
    Waypoint 210, 690, on_arrival_chain=Room34V1Chain4_id
Room34V1Route1:
    Route 3
    Waypoint 135, 710
    Waypoint 210, 710
    Waypoint 210, 690, on_arrival_chain=Room34V1Chain4_id
Room34V1Route2:
    Route 4
    Waypoint 135, 500
    Waypoint 135, 700
    Waypoint 215, 700
    Waypoint 215, 690, on_arrival_chain=Room34V1Chain13_id
Room34V1Route3:
    Route 3
    Waypoint 135, 710
    Waypoint 215, 710
    Waypoint 215, 690, on_arrival_chain=Room34V1Chain13_id
Room34V1Route4:
    Route 3
    Waypoint 149, 699
    Waypoint 146, 726, on_arrival_chain=Room34V1Chain52_id
    Waypoint 82, 726, on_arrival_chain=Room34V1Chain23_id
Room34V1Route5:
    Route 4
    Waypoint 136, 457
    Waypoint 136, 706
    Waypoint 204, 705
    Waypoint 204, 698, on_arrival_chain=Room34V1Chain4_id
Room34V1Route6:
    Route 4
    Waypoint 237, 724
    Waypoint 237, 699
    Waypoint 212, 699
    Waypoint 212, 691, on_arrival_chain=Room34V1Chain4_id
Room34V1Route7:
    Route 4
    Waypoint 290, 670
    Waypoint 290, 700
    Waypoint 215, 700
    Waypoint 215, 690, on_arrival_chain=Room34V1Chain13_id
Room34V1Route8:
    Route 4
    Waypoint 352, 634
    Waypoint 352, 710
    Waypoint 230, 710
    Waypoint 230, 690, on_arrival_chain=Room34V1Chain4_id
Room34V1Route9:
    Route 1
    Waypoint 247, 699
Room34V1Route10:
    Route 2
    Waypoint 171, 700
    Waypoint 179, 700, on_arrival_chain=Room34V1Chain50_id
Room34V1Route11:
    Route 1
    Waypoint 187, 709, on_arrival_chain=Room34V1Chain51_id
    OffsetTable Room34V1Chains, 57, 1
    Offsets Room34V1Chain0, Room34V1Chain1, Room34V1Chain2, Room34V1Chain3, Room34V1Chain4, Room34V1Chain5
    Offsets Room34V1Chain6, Room34V1Chain7, Room34V1Chain8, Room34V1Chain9, Room34V1Chain10, Room34V1Chain11
    Offsets Room34V1Chain12, Room34V1Chain13, Room34V1Chain14, Room34V1Chain15, Room34V1Chain16, Room34V1Chain17
    Offsets Room34V1Chain18, Room34V1Chain19, Room34V1Chain20, Room34V1Chain21, Room34V1Chain22, Room34V1Chain23
    Offsets Room34V1Chain24, Room34V1Chain25, Room34V1Chain26, Room34V1Chain27, Room34V1Chain28, Room34V1Chain29
    Offsets Room34V1Chain30, Room34V1Chain31, Room34V1Chain32, Room34V1Chain33, Room34V1Chain34, Room34V1Chain35
    Offsets Room34V1Chain36, Room34V1Chain37, Room34V1Chain38, Room34V1Chain39, Room34V1Chain40, Room34V1Chain41
    Offsets Room34V1Chain42, Room34V1Chain43, Room34V1Chain44, Room34V1Chain45, Room34V1Chain46, Room34V1Chain47
    Offsets Room34V1Chain48, Room34V1Chain49, Room34V1Chain50, Room34V1Chain51, Room34V1Chain52, Room34V1Chain53
    Offsets Room34V1Chain54, Room34V1Chain55, Room34V1Chain56
    EndTable
Room34V1Chain0:
    ClearOverworldMonstersDisabled
    GotoIfStoryStageCompare 0, 8, Room34V1Chain55_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 15, Room34V1Chain11_id, 0, 0, 0
    End
Room34V1Chain1:
    RespawnRowAndRunChain Room34V1Group3_id, 0
    RespawnRowAndRunChain Room34V1Group1_id, 0
    RespawnRowAndRunChain Room34V1Group4_id, 0
    RespawnRowAndRunChain Room34V1Group6_id, 0
    RespawnRowAndRunChain Room34V1Group2_id, 0
    RespawnRowAndRunChain Room34V1Group5_id, 0
    RespawnRowAndRunChain Room34V1Group7_id, 0
    RespawnRowAndRunChain Room34V1Group12_id, 0
    RespawnRowAndRunChain 0, Room34V1Chain56_id
    End
Room34V1Chain2:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room34V1Group6_id
    @ "Let's ask Madam Pince where we can find the book we need."
    ShowRoomDialog 414
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room34V1Route0_id, 0, 1, 0, 0, 0
    End
Room34V1Chain3:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room34V1Group6_id
    @ "Let's ask Madam Pince where we can find the book we need."
    ShowRoomDialog 414
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room34V1Route1_id, 0, 1, 0, 0, 0
    End
Room34V1Chain4:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    SetTileObjectFacing 0, 255, 0
    @ "What can I do for you?"
    @ "We were wondering if you have a good book on werewolves?"
    @ "I'm afraid that our only werewolf reference book had a tussle with 'The Monster Book of Monsters'. As a result, there are pages everywhere..."
    @ "Why don't we find the torn pages? Then I can place them back in the book with the Reparo Spell!"
    @ "I would appreciate you doing that, Miss Granger."
    @ "OK, let's get to it."
    ShowRoomDialog 415
    SetQuestState 28, 25
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room34V1Chain5:
    AddQuestState 1, 131
    GotoIfQuestStateCompare 131, 0, 3, Room34V1Chain6_id, 0, 0, 0
    End
Room34V1Chain6:
    SetTileObjectAnimState Room34V1Group0_id, 0
    GotoIfQuestStateCompare 1, 1, 19, Room34V1Chain28_id, 0, 0, 0
    End
Room34V1Chain7:
    GotoIfQuestStateCompare 1, 1, 19, Room34V1Chain38_id, 0, 0, 0
    End
Room34V1Chain8:
    AddQuestState 1, 4
    GotoIfQuestStateCompare 4, 0, 1, Room34V1Chain39_id, Room34V1Chain42_id, 0, 0
    End
Room34V1Chain9:
    GotoIfQuestStateCompare 224, 0, 5, Room34V1Chain10_id, 0, 0, 0
    End
Room34V1Chain10:
    SetStoryStage 8
    End
Room34V1Chain11:
    GotoIfQuestStateCompare 230, 0, 0, Room34V1Chain27_id, Room34V1Chain32_id, Room34V1Group8_id, 0
    End
Room34V1Chain12:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room34V1Group8_id
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room34V1Route2_id, 0, 1, 0, 0, 0
    End
Room34V1Chain13:
    ArmChainYield 1
    @ "We're looking for a book on wizard law, Madam Pince."
    @ "Very well; the legal section is on the south side of the library."
    ShowRoomDialog 439
    RespawnRowAndRunChain Room34V1Group9_id, 0
    SetQuestState 3, 230
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room34V1Chain14:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room34V1Group8_id
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room34V1Route3_id, 0, 1, 0, 0, 0
    End
Room34V1Chain15:
    CancelObjectAnimSequence 0, 255
    GrantPartyExperience 10, 65535
    @ "Here's the legal section! It looks like no one's been here in a long time..."
    @ "Let's try and find books that refer to Hippogriff-baiting."
    ShowRoomDialog 440
    RespawnRowAndRunChain Room34V1Group14_id, 0
    DespawnRoomRowObjects Room34V1Group9_id
    SetQuestState 4, 230
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room34V1Chain16:
    CancelObjectAnimSequence 0, 255
    RespawnRowAndRunChain Room34V1Group10_id, 0
    DespawnRoomRowObjects Room34V1Group14_id
    @ "I can't find anything on Hippogriffs!"
    @ "There're certainly a lot of obscure titles here."
    ShowRoomDialog 441
    SetQuestState 5, 230
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room34V1Chain17:
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room34V1Group10_id
    DespawnRoomRowObjects Room34V1Group11_id
    RespawnRowAndRunChain Room34V1Group16_id, 0
    @ "Look, this must be the book Hermione mentioned! It's got a section dealing with the Committee for the Disposal of Dangerous Creatures!"
    @ "Let's have a look!"
    @ "It doesn't look good."
    @ "We can't tell Hagrid that!"
    @ "Let's find Hermione. Maybe she'll be able to make sense of it all."
    ShowRoomDialog 442
    SetQuestState 33, 25
    SetQuestState 1, 230
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room34V1Chain18:
    @ "We're looking for a book on wizard law, Madam Pince."
    @ "Very well; the legal section is on the south side of the library."
    ShowRoomDialog 439
    End
Room34V1Chain19:
    GotoIfQuestStateCompare 229, 1, 0, Room34V1Chain20_id, 0, 0, 0
    End
Room34V1Chain20:
    GotoIfQuestStateCompare 4, 3, 5, Room34V1Chain49_id, Room34V1Chain22_id, 0, 0
    End
Room34V1Chain21:
    ArmChainYield 1
    @ "Reparo!"
    ShowRoomDialog 418
    ArmChainYield 0
    PlaySoundById 54
    RespawnRowAndRunChain 0, Room34V1Chain31_id
    ConsumeRoomItem 74
    ConsumeRoomItem 74
    ConsumeRoomItem 74
    ConsumeRoomItem 74
    ConsumeRoomItem 74
    SetQuestState 27, 4
    End
Room34V1Chain22:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "You've done splendidly, but you don't have all the pages. Hurry and get the rest!"
    ShowRoomDialog 416
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room34V1Chain23:
    ArmChainYield 1
    SetQuestState 29, 25
    SetStoryStage 9
    DespawnTileObject Room34V1Group13_id, 0
    End
Room34V1Chain24:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room34V1Group6_id
    @ "Let's ask Madam Pince where we can find the book we need."
    ShowRoomDialog 414
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room34V1Route6_id, 0, 1, 0, 0, 0
    End
Room34V1Chain25:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room34V1Group6_id
    @ "Let's ask Madam Pince where we can find the book we need."
    ShowRoomDialog 414
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room34V1Route5_id, 0, 1, 0, 0, 0
    End
Room34V1Chain26:
    DespawnRoomRowObjects Room34V1Group6_id
    End
Room34V1Chain27:
    RespawnRowAndRunChain Room34V1Group11_id, 0
    End
Room34V1Chain28:
    GrantPartyExperience 10, 65535
    SetQuestState 19, 1
    DespawnTileObject Room34V1Group5_id, 1
    DespawnTileObject Room34V1Group5_id, 2
    DelayedRespawnRowAndRunChainFrames 0, 0, Room34V1Chain48_id
    End
Room34V1Chain29:
    SetTileObjectAnimState Room34V1Group0_id, 0
    End
Room34V1Chain30:
    GotoIfQuestStateCompare 4, 2, 0, Room34V1Chain20_id, 0, 0, 0
    End
Room34V1Chain31:
    @ "You two go back to class and stall Snape. I'll write up the research and be there soon."
    @ "OK."
    ShowRoomDialog 419
    DespawnTileObject Room34V1Group13_id, 1
    StartObjectAnimSequence Room34V1Group13_id, 0, 0, 0, Room34V1Route4_id, 0, 1, 0, 0, 0
    ArmChainYield 1
    ArmChainYield 0
    End
Room34V1Chain32:
    GotoIfQuestStateCompare 230, 0, 3, Room34V1Chain34_id, Room34V1Chain33_id, Room34V1Group11_id, 0
    End
Room34V1Chain33:
    GotoIfQuestStateCompare 230, 0, 4, Room34V1Chain35_id, Room34V1Chain45_id, Room34V1Group11_id, 0
    End
Room34V1Chain34:
    RespawnRowAndRunChain Room34V1Group9_id, 0
    End
Room34V1Chain35:
    RespawnRowAndRunChain Room34V1Group14_id, 0
    End
Room34V1Chain36:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room34V1Group8_id
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room34V1Route7_id, 0, 1, 0, 0, 0
    End
Room34V1Chain37:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room34V1Group6_id
    @ "Let's ask Madam Pince where we can find the book we need."
    ShowRoomDialog 414
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room34V1Route8_id, 0, 1, 0, 0, 0
    End
Room34V1Chain38:
    SubtractQuestState 1, 131
    GotoIfQuestStateCompare 131, 0, 2, Room34V1Chain29_id, 0, 0, 0
    End
Room34V1Chain39:
    @ "Here's the first book page. We'd better find the rest."
    ShowRoomDialog 420
    End
Room34V1Chain40:
    @ "Here's another book page."
    ShowRoomDialog 421
    End
Room34V1Chain41:
    @ "Great! We've found all the pages! Let's take them back to Madam Pince."
    ShowRoomDialog 422
    End
Room34V1Chain42:
    GotoIfQuestStateCompare 4, 0, 5, Room34V1Chain41_id, Room34V1Chain40_id, 0, 0
    End
Room34V1Chain43:
    SetTileObjectAnimStateValue Room34V1Group3_id, 3, 5
    SetTileObjectAnimStateValue Room34V1Group3_id, 4, 5
    SetTileObjectAnimStateValue Room34V1Group3_id, 5, 5
    SetTileObjectAnimState Room34V1Group0_id, 0
    DespawnTileObject Room34V1Group4_id, 0
    DespawnTileObject Room34V1Group4_id, 6
    DespawnTileObject Room34V1Group4_id, 7
    End
Room34V1Chain44:
    SetTileObjectAnimState Room34V1Group5_id, 0
    End
Room34V1Chain45:
    GotoIfQuestStateCompare 230, 0, 5, Room34V1Chain46_id, 0, Room34V1Group11_id, 0
    End
Room34V1Chain46:
    RespawnRowAndRunChain Room34V1Group10_id, 0
    End
Room34V1Chain47:
    SetTileObjectAnimState Room34V1Group5_id, 2
    DelayedRespawnRowAndRunChainFrames 10, 0, Room34V1Chain48_id
    End
Room34V1Chain48:
    SetTileObjectAnimStateValue Room34V1Group3_id, 3, 5
    SetTileObjectAnimStateValue Room34V1Group3_id, 4, 5
    SetTileObjectAnimStateValue Room34V1Group3_id, 5, 5
    End
Room34V1Chain49:
    DespawnTileObject Room34V1Group12_id, 0
    GrantPartyExperience 50, 65535
    ResetPartyLeaderSelection
    RemovePartyFollower 7
    RespawnRowAndRunChain Room34V1Group13_id, 0
    RemovePartyFollower 6
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room34V1Route10_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room34V1Group13_id, 0, 0, 0, Room34V1Route9_id, 0, 1, 0, 0, 0
    End
Room34V1Chain50:
    @ "Excellent, you have all the pages! Would you like to repair the book now, please?"
    ShowRoomDialog 417
    CancelObjectAnimSequence 0, 255
    PlayTileObjectAnimation Room34V1Group13_id, 0, 8
    ArmChainYield 1
    ArmChainYield 0
    PlaySoundById 73
    End
Room34V1Chain51:
    DespawnTileObject Room34V1Group13_id, 2
    RecruitPartyFollower 7
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room34V1Chain52:
    StartObjectAnimSequence Room34V1Group13_id, 2, 0, 0, Room34V1Route11_id, 0, 1, 0, 0, 0
    DespawnTileObject Room34V1Group13_id, 1
    End
Room34V1Chain53:
    SetTileObjectAnimState Room34V1Group13_id, 1
    DelayedRespawnRowAndRunChainFrames 20, 0, Room34V1Chain21_id
    End
Room34V1Chain54:
    @ "Is there something else I can help you with?"
    ShowRoomDialog 446
    End
Room34V1Chain55:
    GotoIfQuestStateCompare 4, 1, 27, Room34V1Chain1_id, 0, 0, 0
    End
Room34V1Chain56:
    GotoIfQuestStateCompare 1, 0, 19, Room34V1Chain43_id, 0, 0, 0
    GotoIfQuestStateCompare 25, 2, 27, Room34V1Chain26_id, 0, 0, 0
    End
    EndSubBlock Room34V1End

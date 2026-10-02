    .include "asm/room_blob.inc"

Room39Blob:
    RoomBlob 2
    PlayerEntry 456, 936, 0, 0
    PlayerEntry 88, 124, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room39V0
    VariantEntry Room39V1

    SubBlock Room39V0, 1, Room39V0Routes, Room39V0Chains, Room39V0End
    OffsetTable Room39V0Groups, 1
    Offsets Room39V0Group0
    EndTable
    Group Room39V0Group0, 8
    TileAnimation 199, 79, anim_id=3
    TileAnimation 568, 923, anim_id=4
    Prop 665, 865, kind=6, arg_12=1
    Prop 161, 160, kind=6, arg_12=1
    Chest 418, 672, flag_id=7, reward_id=83
    Chest 234, 197, flag_id=8, reward_id=84
    Chest 1054, 690, flag_id=9, reward_id=98
    Chest 441, 309, flag_id=10, reward_id=96
    OffsetTable Room39V0Routes, 0
    EndTable
    OffsetTable Room39V0Chains, 1
    Offsets Room39V0Chain0
    EndTable
Room39V0Chain0:
    End
    EndSubBlock Room39V0End

    SubBlock Room39V1, 1, Room39V1Routes, Room39V1Chains, Room39V1End
    OffsetTable Room39V1Groups, 17, 1
    Offsets Room39V1Group0, Room39V1Group1, Room39V1Group2, Room39V1Group3, Room39V1Group4, Room39V1Group5
    Offsets Room39V1Group6, Room39V1Group7, Room39V1Group8, Room39V1Group9, Room39V1Group10, Room39V1Group11
    Offsets Room39V1Group12, Room39V1Group13, Room39V1Group14, Room39V1Group15, Room39V1Group16
    EndTable
    Group Room39V1Group0, 9
    TriggerZone 252, 135, half_width=18, half_height=21, trigger_kind=3, chain=Room39V1Chain1_id
    TriggerZone 571, 939, half_width=21, half_height=25, trigger_kind=3, chain=Room39V1Chain2_id
    TriggerZone 184, 146, half_width=41, half_height=4, chain=Room39V1Chain21_id
    TriggerZone 62, 192, half_width=28, half_height=20, trigger_kind=1, chain=Room39V1Chain24_id
    TriggerRect 351, 439, left=238, top=0, right=36, bottom=73, chain=Room39V1Chain41_id
    TriggerZone 454, 957, half_width=16, half_height=5, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room39V1Chain34_id
    TriggerZone 618, 946, half_width=7, half_height=21, chain=Room39V1Chain52_id
    TriggerZone 684, 825, half_width=15, half_height=12, chain=Room39V1Chain53_id
    TriggerZone 515, 450, half_width=9, half_height=24, respawn_group=Room39V1Group1_id, chain=Room39V1Chain33_id
    Group Room39V1Group1, 2
    Npc 360, 588, sprite=32, facing=0
    Prop 358, 556, kind=7, arg_08=361, arg_0a=476, arg_0f=1
    Group Room39V1Group2, 1
    Npc 441, 444, sprite=34, facing=6
    Group Room39V1Group3, 0
    Group Room39V1Group4, 1
    Npc 316, 137, sprite=34, facing=6
    Group Room39V1Group5, 1
    Npc 183, 168, sprite=32, facing=0
    Group Room39V1Group6, 1
    TriggerZone 179, 111, half_width=45, half_height=21, respawn_group=Room39V1Group4_id, chain=Room39V1Chain16_id
    Group Room39V1Group7, 0
    Group Room39V1Group8, 0
    Group Room39V1Group9, 1
    TriggerZone 179, 110, half_width=25, half_height=30, respawn_group=Room39V1Group3_id, chain=Room39V1Chain17_id
    Group Room39V1Group10, 0
    Group Room39V1Group11, 9
    TriggerZone 686, 859, half_width=20, half_height=4, chain=Room39V1Chain42_id
    TriggerZone 666, 874, half_width=29, half_height=26, chain=Room39V1Chain36_id
    Prop 358, 556, kind=7, arg_08=361, arg_0a=476, arg_0f=1
    TriggerZone 203, 328, half_width=12, half_height=8, respawn_group=Room39V1Group8_id, chain=Room39V1Chain51_id
    TriggerZone 195, 225, half_width=20, half_height=4, chain=Room39V1Chain29_id
    Npc 311, 192, sprite=4, facing=6
    TriggerZone 312, 201, half_width=24, half_height=18, respawn_group=Room39V1Group6_id, chain=Room39V1Chain12_id
    TriggerZone 549, 932, half_width=15, half_height=24, chain=Room39V1Chain38_id
    TriggerZone 84, 158, half_width=28, half_height=6, trigger_kind=1, chain=Room39V1Chain19_id
    Group Room39V1Group12, 1
    TriggerZone 682, 889, half_width=19, half_height=14, chain=Room39V1Chain39_id
    Group Room39V1Group13, 1
    TriggerZone 359, 506, half_width=53, half_height=33, respawn_group=Room39V1Group2_id, chain=Room39V1Chain30_id
    Group Room39V1Group14, 1
    TriggerZone 556, 938, half_width=25, half_height=21, chain=Room39V1Chain37_id
    Group Room39V1Group15, 3
    TriggerZone 686, 788, half_width=15, half_height=12, chain=Room39V1Chain5_id
    TriggerZone 482, 761, half_width=35, half_height=37, chain=Room39V1Chain6_id
    TriggerZone 292, 767, half_width=4, half_height=20, chain=Room39V1Chain7_id
    Group Room39V1Group16, 8
    TriggerZone 484, 442, half_width=7, half_height=12, chain=Room39V1Chain10_id
    TriggerZone 240, 416, half_width=21, half_height=8, chain=Room39V1Chain11_id
    TriggerZone 648, 947, half_width=7, half_height=19, chain=Room39V1Chain8_id
    TriggerZone 724, 863, half_width=5, half_height=11, chain=Room39V1Chain9_id
    TriggerZone 336, 322, half_width=3, half_height=25, chain=Room39V1Chain28_id
    Npc 428, 161, sprite=5, facing=6, interact_mode=1
    TriggerZone 430, 165, half_width=90, half_height=15, chain=Room39V1Chain13_id
    TriggerZone 622, 486, half_width=3, half_height=61, chain=Room39V1Chain44_id
    OffsetTable Room39V1Routes, 5
    Offsets Room39V1Route0, Room39V1Route1, Room39V1Route2, Room39V1Route3, Room39V1Route4
    EndTable
Room39V1Route0:
    Route 7
    Waypoint 316, 134
    Waypoint 240, 133
    Waypoint 240, 115
    Waypoint 220, 114
    Waypoint 220, 102
    Waypoint 175, 102
    Waypoint 175, 104, on_arrival_chain=Room39V1Chain25_id
Room39V1Route1:
    Route 4
    Waypoint 155, 106
    Waypoint 83, 106
    Waypoint 84, 153
    Waypoint 64, 185, on_arrival_chain=Room39V1Chain24_id
Room39V1Route2:
    Route 3
    Waypoint 499, 443
    Waypoint 235, 442
    Waypoint 235, 319
Room39V1Route3:
    Route 4
    Waypoint 408, 444
    Waypoint 285, 444
    Waypoint 232, 444, on_arrival_chain=Room39V1Chain32_id
    Waypoint 232, 355, on_arrival_chain=Room39V1Chain31_id
Room39V1Route4:
    Route 1
    Waypoint 162, 106
    OffsetTable Room39V1Chains, 55, 1
    Offsets Room39V1Chain0, Room39V1Chain1, Room39V1Chain2, Room39V1Chain3, Room39V1Chain4, Room39V1Chain5
    Offsets Room39V1Chain6, Room39V1Chain7, Room39V1Chain8, Room39V1Chain9, Room39V1Chain10, Room39V1Chain11
    Offsets Room39V1Chain12, Room39V1Chain13, Room39V1Chain14, Room39V1Chain15, Room39V1Chain16, Room39V1Chain17
    Offsets Room39V1Chain18, Room39V1Chain19, Room39V1Chain20, Room39V1Chain21, Room39V1Chain22, Room39V1Chain23
    Offsets Room39V1Chain24, Room39V1Chain25, Room39V1Chain26, Room39V1Chain27, Room39V1Chain28, Room39V1Chain29
    Offsets Room39V1Chain30, Room39V1Chain31, Room39V1Chain32, Room39V1Chain33, Room39V1Chain34, Room39V1Chain35
    Offsets Room39V1Chain36, Room39V1Chain37, Room39V1Chain38, Room39V1Chain39, Room39V1Chain40, Room39V1Chain41
    Offsets Room39V1Chain42, Room39V1Chain43, Room39V1Chain44, Room39V1Chain45, Room39V1Chain46, Room39V1Chain47
    Offsets Room39V1Chain48, Room39V1Chain49, Room39V1Chain50, Room39V1Chain51, Room39V1Chain52, Room39V1Chain53
    Offsets Room39V1Chain54
    EndTable
Room39V1Chain0:
    DelayedRespawnRowAndRunChainFrames 1, 0, Room39V1Chain40_id
    SetDefeatWarpSelector 15 @ Leaky Cauldron - Cellar 2
    End
Room39V1Chain1:
    SetTileObjectAnimState Room39V0Group0_id, 0
    End
Room39V1Chain2:
    SetTileObjectAnimState Room39V0Group0_id, 1
    DelayedRespawnRowAndRunChain 0, 0, Room39V1Chain42_id
    DespawnRoomRowObjects Room39V1Group14_id
    End
Room39V1Chain3:
    End
Room39V1Chain4:
    End
Room39V1Chain5:
    @ "They must have gone down here."
    @ "Be careful, Ron. It's dangerous down there."
    ShowRoomDialog 49
    End
Room39V1Chain6:
    @ "Scabbers!"
    ShowRoomDialog 47
    End
Room39V1Chain7:
    @ "Scabbers, where are you?"
    ShowRoomDialog 48
    End
Room39V1Chain8:
    @ "Crookshanks! Oh, where are you?"
    ShowRoomDialog 51
    End
Room39V1Chain9:
    @ "Crookshanks is going to need a bath if he's been running around down here."
    ShowRoomDialog 52
    End
Room39V1Chain10:
    @ "Where could they be?"
    ShowRoomDialog 53
    End
Room39V1Chain11:
    @ "Come out, Crookshanks!"
    ShowRoomDialog 54
    End
Room39V1Chain12:
    @ "Got him! It's OK, Scabbers, you're safe now."
    ShowRoomDialog 50
    DespawnTileObject Room39V1Group11_id, 5
    DespawnTileObject Room39V1Group11_id, 3
    SetTileObjectAnimState Room39V0Group0_id, 0
    SetQuestState 1, QUEST_CELLAR2_SCABBERS_CAUGHT
    SetQuestState QUEST_OBJ_SPEAK_TO_WEASLEYS, QUEST_OBJECTIVE_INDEX
    DelayedRespawnRowAndRunChainFrames 0, 0, Room39V1Chain46_id
    End
Room39V1Chain13:
    ArmChainYield 1
    StartTileObjectScript 399, 155, 0, 0, 255, 0, 0, 2, 255, 255, 255
    DelayedRespawnRowAndRunChainFrames 0, 0, Room39V1Chain46_id
    @ "Got you, you naughty cat!"
    @ "We'd better go and find Ron."
    ShowRoomDialog 55
    DespawnTileObject Room39V1Group16_id, 5
    DespawnTileObject Room39V0Group0_id, 3
    SetQuestState 1, QUEST_CELLAR2_CROOKSHANKS_CAUGHT
    SetQuestState QUEST_OBJ_SPEAK_TO_WEASLEYS, QUEST_OBJECTIVE_INDEX
    DelayedRespawnRowAndRunChain 0, Room39V1Group5_id, 0
    DelayedRespawnRowAndRunChain 0, Room39V1Group9_id, 0
    End
Room39V1Chain14:
    End
Room39V1Chain15:
    DelayedRespawnRowAndRunChain 0, 0, 0
    End
Room39V1Chain16:
    CancelObjectAnimSequence 0, 255
    StartObjectAnimSequence Room39V1Group4_id, 0, 0, 0, Room39V1Route0_id, 0, 1, 0, 0, 0
    SetQuestState QUEST_OBJ_SPEAK_TO_WEASLEYS, QUEST_OBJECTIVE_INDEX
    End
Room39V1Chain17:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 183, 128, 0, Room39V1Group5_id, 0, 0, 0, 0, 255, 255, 255
    @ "I found Crookshanks. Did you manage to find Scabbers?"
    @ "Yes, I did - no thanks to your cat."
    @ "Bad Crookshanks! Don't run away again!"
    ShowRoomDialog 57
    StartObjectAnimSequence 0, 255, 0, 0, Room39V1Route4_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room39V1Group5_id, 0, 0, 0, Room39V1Route4_id, 0, 1, 0, 0, 0
    DespawnTileObject Room39V1Group5_id, 0
    RemovePartyFollower 6
    RecruitPartyFollower 6
    RecruitPartyFollower 7
    SetQuestState QUEST_OBJ_SPEAK_TO_WEASLEYS, QUEST_OBJECTIVE_INDEX
    SetTileObjectAnimStateWithSpeed 0, 255
    DelayedRespawnRowAndRunChainFrames 0, 0, Room39V1Chain35_id
    End
Room39V1Chain18:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    StartTileObjectScript 183, 140, 0, Room39V1Group5_id, 0, 0, 0, 0, 255, 255, 255
    NoOpAlt 0xffffff0a
    @ "I found Crookshanks. Did you manage to find Scabbers?"
    @ "Yes, I did - no thanks to your cat."
    @ "Bad Crookshanks! Don't run away again!"
    ShowRoomDialog 56
    SetTileObjectAnimStateWithSpeed 0, 255
    SetStoryStage 8
    End
Room39V1Chain19:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    @ "Scabbers, where are you?"
    ShowRoomDialog 48
    StartTileObjectScript 89, 100, 0, 0, 255, 0, 0, 2, 255, 255, 255
    SetTileObjectAnimStateWithSpeed 0, 255
    ArmChainYield 0
    End
Room39V1Chain20:
    End
Room39V1Chain21:
    GrantPartyExperience 5, 65535
    End
Room39V1Chain22:
    ArmChainYield 0
    StartTileObjectScript 242, 58, 2, Room39V0Group0_id, 0, 0, 0, 6, 255, 255, 255
    ArmChainYield 1
    StartTileObjectScript 360, 56, 2, Room39V0Group0_id, 0, 0, 0, 0, 255, 255, 255
    DelayedRespawnRowAndRunChain 0, 0, 0
    ArmChainYield 1
    End
Room39V1Chain23:
    End
Room39V1Chain24:
    ArmChainYield 1
    SetStoryStage 8
    ReturnToOverworld 40, 3
    End
Room39V1Chain25:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "I found Crookshanks. Did you manage to find Scabbers?"
    @ "Yes, I did - no thanks to your cat."
    @ "Bad Crookshanks! Don't run away again!"
    ShowRoomDialog 56
    StartObjectAnimSequence 0, 255, 0, 0, Room39V1Route4_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room39V1Group4_id, 0, 0, 0, Room39V1Route4_id, 0, 1, 0, 0, 0
    DespawnTileObject Room39V1Group4_id, 0
    RemovePartyFollower 7
    RecruitPartyFollower 7
    RecruitPartyFollower 6
    SetQuestState QUEST_OBJ_SPEAK_TO_WEASLEYS, QUEST_OBJECTIVE_INDEX
    SetTileObjectAnimStateWithSpeed 0, 255
    DelayedRespawnRowAndRunChainFrames 0, 0, Room39V1Chain35_id
    End
Room39V1Chain26:
    @ "Harry, this gate is locked and we don't have a key. I wonder if I should try casting Alohomora on it?"
    ShowRoomDialog 620
    End
Room39V1Chain27:
    @ "These stairs look damaged. I wonder if the Reparo Spell would help?"
    ShowRoomDialog 616
    End
Room39V1Chain28:
    DespawnRoomRowObjects Room39V1Group11_id
    GotoIfQuestStateCompare 251, 0, 1, Room39V1Chain49_id, 0, 0, 0
    End
Room39V1Chain29:
    DespawnRoomRowObjects Room39V1Group12_id
    End
Room39V1Chain30:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChain 1, 0, 0
    QueueTileObjectMove Room39V1Group2_id, 0, 0, 0, 1200, 0
    @ "Thanks!"
    ShowRoomDialog 85
    ArmChainYield 0
    StartObjectAnimSequence Room39V1Group2_id, 0, 0, 0, Room39V1Route3_id, 0, 1, 0, 0, 0
    End
Room39V1Chain31:
    DespawnRoomRowObjects Room39V1Group2_id
    End
Room39V1Chain32:
    ArmChainYield 1
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room39V1Chain33:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetTileObjectFacing 0, 255, 6
    QueueTileObjectMove Room39V1Group1_id, 0, 0, 0, 1200, 0
    PlayTileObjectAnimation Room39V1Group1_id, 0, 4
    DelayedRespawnRowAndRunChain 1, 0, 0
    PlayTileObjectAnimation Room39V1Group1_id, 0, 4
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetTileObjectFacing Room39V1Group1_id, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    @ "Thanks!"
    ShowRoomDialog 85
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room39V1Chain34:
    @ "Locked."
    ShowRoomDialog 624
    End
Room39V1Chain35:
    StartObjectAnimSequence 0, 255, 0, 0, Room39V1Route1_id, 0, 1, 0, 0, 0
    SetQuestState QUEST_OBJ_GREET_WEASLEYS, QUEST_OBJECTIVE_INDEX
    End
Room39V1Chain36:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "This door's locked!"
    ShowRoomDialog 81
    @ "I can use the Alohomora Spell to unlock it."
    ShowRoomDialog 83
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room39V1Chain37:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "These stairs are broken!"
    ShowRoomDialog 78
    @ "I can fix them with the Reparo Spell."
    ShowRoomDialog 79
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room39V1Chain38:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "These stairs are broken!"
    ShowRoomDialog 78
    @ "I think we should look for another way in."
    ShowRoomDialog 80
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room39V1Chain39:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "This door's locked!"
    ShowRoomDialog 81
    @ "I think we should look for another way in."
    ShowRoomDialog 82
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room39V1Chain40:
    GotoIfQuestStateCompare QUEST_STORY_STAGE, 0, 6, Room39V1Chain48_id, 0, Room39V1Group12_id, Room39V1Group11_id
    End
Room39V1Chain41:
    GotoIfStoryStageCompare 1, 6, Room39V1Chain44_id, 0, Room39V1Group13_id, 0
    End
Room39V1Chain42:
    GotoIfQuestStateCompare 237, 0, 0, Room39V1Chain43_id, 0, 0, 0
    End
Room39V1Chain43:
    GrantPartyExperience 5, 65535
    SetQuestState 1, 237
    End
Room39V1Chain44:
    GotoIfQuestStateCompare QUEST_CELLAR2_XP5_GIVEN, 0, 0, Room39V1Chain45_id, 0, 0, 0
    End
Room39V1Chain45:
    GrantPartyExperience 5, 65535
    SetQuestState 1, QUEST_CELLAR2_XP5_GIVEN
    End
Room39V1Chain46:
    GotoIfQuestStateCompare QUEST_CELLAR2_XP20_GIVEN, 0, 0, Room39V1Chain47_id, 0, 0, 0
    End
Room39V1Chain47:
    GrantPartyExperience 20, 65535
    SetQuestState 1, QUEST_CELLAR2_XP20_GIVEN
    End
Room39V1Chain48:
    DelayedRespawnRowAndRunChainFrames 0, Room39V1Group14_id, 0
    End
Room39V1Chain49:
    DespawnTileObject Room39V0Group0_id, 3
    DelayedRespawnRowAndRunChain 0, Room39V1Group5_id, 0
    DelayedRespawnRowAndRunChain 0, Room39V1Group9_id, 0
    End
Room39V1Chain50:
    DespawnTileObject Room39V1Group11_id, 6
    DespawnTileObject Room39V1Group11_id, 5
    DespawnTileObject Room39V1Group11_id, 3
    SetTileObjectAnimState Room39V0Group0_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room39V1Group6_id, 0
    End
Room39V1Chain51:
    GotoIfQuestStateCompare QUEST_CELLAR2_SCABBERS_CAUGHT, 0, 1, Room39V1Chain50_id, 0, 0, 0
    End
Room39V1Chain52:
    GotoIfQuestStateCompare QUEST_CELLAR2_CROOKSHANKS_CAUGHT, 0, 0, 0, Room39V1Chain49_id, Room39V1Group16_id, 0
    End
Room39V1Chain53:
    GotoIfQuestStateCompare QUEST_CELLAR2_SCABBERS_CAUGHT, 0, 0, 0, 0, Room39V1Group15_id, 0
    End
Room39V1Chain54:
    DespawnTileObject Room39V0Group0_id, 3
    DelayedRespawnRowAndRunChain 0, Room39V1Group5_id, 0
    DelayedRespawnRowAndRunChain 0, Room39V1Group9_id, 0
    End
    EndSubBlock Room39V1End

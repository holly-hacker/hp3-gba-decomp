    .include "asm/room_blob.inc"

Room42Blob:
    RoomBlob 3
    PlayerEntry 426, 620, 0, 0
    PlayerEntry 79, 259, 1, 0
    PlayerEntry 544, 566, 2, 0
    StageIndex 4
    StageToVariant 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    VariantEntry Room42V0
    VariantEntry Room42V1
    VariantEntry Room42V2
    VariantEntry Room42V3

    SubBlock Room42V0, 1, Room42V0Routes, Room42V0Chains, Room42V0End
    OffsetTable Room42V0Groups, 1
    Offsets Room42V0Group0
    EndTable
    Group Room42V0Group0, 22
    Door 609, 562, half_width=6, half_height=30, destination_room=40
    Prop 274, 392, kind=0, facing=2, arg_10=1, arg_13=0
    Prop 330, 295, kind=0, facing=5, arg_10=1, arg_13=0
    Npc 303, 354, sprite=9, facing=2
    Npc 326, 270, sprite=11, facing=2
    Npc 331, 388, sprite=10, facing=2
    Prop 304, 317, kind=0, arg_10=1
    Prop 472, 237, kind=0, facing=7, arg_10=1, arg_13=0
    Prop 718, 464, kind=0, facing=7, arg_10=1
    Prop 53, 118, kind=23, arg_13=0
    Prop 119, 118, kind=23, arg_13=0
    Prop 242, 118, kind=23, arg_13=0
    Prop 307, 118, kind=23, arg_13=0
    Prop 455, 471, kind=23, arg_13=0
    Prop 293, 256, kind=22, arg_13=0
    Prop 310, 262, kind=22, arg_13=0
    Prop 303, 290, kind=22, arg_13=0
    Prop 290, 379, kind=22, arg_13=0
    Prop 311, 377, kind=22, arg_13=0
    Prop 276, 260, kind=0, facing=2, arg_10=1, arg_13=0
    Prop 276, 297, kind=0, facing=2, arg_10=1, arg_13=0
    Chest 717, 434, flag_id=3, reward_id=115
    OffsetTable Room42V0Routes, 0
    EndTable
    OffsetTable Room42V0Chains, 1
    Offsets Room42V0Chain0
    EndTable
Room42V0Chain0:
    End
    EndSubBlock Room42V0End

    SubBlock Room42V1, 1, Room42V1Routes, Room42V1Chains, Room42V1End
    OffsetTable Room42V1Groups, 3, 1
    Offsets Room42V1Group0, Room42V1Group1, Room42V1Group2
    EndTable
    Group Room42V1Group0, 8
    Npc 480, 302, sprite=8, facing=4
    TriggerZone 480, 302, half_width=21, half_height=21, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42TalkPatronBar_id
    TriggerZone 329, 264, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42TalkPatronTopLeft_id
    TriggerZone 333, 387, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42TalkPatronBottom2_id
    TriggerZone 304, 346, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42TalkPatronBottom1_id
    Npc 529, 335, sprite=3, facing=4
    TriggerZone 520, 350, half_width=39, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42TalkTom_id
    TriggerZone 428, 646, half_width=36, half_height=10, rearm_delay=3, trigger_kind=1, chain=Room42LockedDoorEntrance_id
    Group Room42V1Group1, 2
    TriggerZone 125, 262, half_width=25, half_height=31, chain=Room42TryVisitCellar_id
    TriggerZone 151, 272, half_width=25, half_height=31, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42LockedDoorEntrance_id
    Group Room42V1Group2, 2
    TriggerZone 436, 503, half_width=50, half_height=91, chain=Room42TalkFudge1_id
    Npc 432, 504, sprite=1, facing=4
    OffsetTable Room42V1Routes, 1
    Offsets Room42V1Route0
    EndTable
Room42V1Route0:
    Route 4
    Waypoint 438, 508
    Waypoint 535, 509
    Waypoint 533, 570
    Waypoint 600, 566, on_arrival_chain=Room42V1Chain3_id
    OffsetTable Room42V1Chains, 11, 1
    Offsets Room42V1Chain0, Room42TalkFudge1, Room42TalkPatronBar, Room42V1Chain3, Room42TryVisitCellar, Room42V1Chain5
    Offsets Room42TalkPatronTopLeft, Room42TalkPatronBottom1, Room42TalkPatronBottom2, Room42TalkTom, Room42LockedDoorEntrance
    EndTable
Room42V1Chain0:
    GotoIfQuestStateCompare 224, 0, 0, Room42V1Chain5_id, 0, 0, 0
    DelayedRespawnRowAndRunChainFrames 1, Room42V1Group1_id, 0
    End
@ First conversation with Fudge
Room42TalkFudge1:
    ArmChainYield 1
    StartTileObjectScript 419, 10, 2, 0, 255, 0, 0, 0, 255, 255, 255
    @ "There you are, Harry!"
    @ "Um... Hello..."
    @ "I am Cornelius Fudge, Harry, the Minister for Magic."
    @ "Hello, Mr. Fudge. Have you had any luck with catching Sirius Black yet?"
    @ "What's that?"
    @ "Sirius Black, the murderer who killed thirteen people with a single curse and who recently escaped from Azkaban prison?"
    @ "Oh, that Sirius Black - well, no, not yet, but it's only a matter of time. The Azkaban guards have never yet failed. Now, allow me to escort you to your room. Follow me closely - we don't want you getting lost¸"
    @ "All right, thank you."
    ShowRoomDialog 0
    ArmChainYield 0
    Unk02 Room42V1Group2_id, 1, 2
    StartObjectAnimSequence Room42V1Group2_id, 1, 0, 4, Room42V1Route0_id, 0, 1, 0, 0, 0
    ArmChainYield 1
    SetQuestState 1, 224
    SetQuestState 1, QUEST_STORY_STAGE
    End
@ Talk to person at the bar
Room42TalkPatronBar:
    @ "There's nothing like a nice glass of Butterbeer!"
    ShowRoomDialog 7
    End
Room42V1Chain3:
    DespawnTileObject Room42V1Group2_id, 1
    End
@ Try to go to the cellar before the relevant quest is active
Room42TryVisitCellar:
    @ "I don't think I should be going down into the cellar just yet."
    ShowRoomDialog 3
    End
Room42V1Chain5:
    RespawnRowAndRunChain Room42V1Group2_id, 0
    End
@ Talk to the bored-looking patron in blue
Room42TalkPatronTopLeft:
    @ "I'm afraid this seat is taken."
    ShowRoomDialog 8
    End
@ Talk to the patron on the top of the bottom table
Room42TalkPatronBottom1:
    @ "Harry Potter, isn't it?"
    ShowRoomDialog 9
    End
@ Talk to the patron on the right of the bottom table
Room42TalkPatronBottom2:
    @ "I suppose you'll be attending Hogwarts, am I right?"
    ShowRoomDialog 10
    End
@ Talk to Tom the barman
Room42TalkTom:
    @ "I thought you'd be in your room by now, Mr. Potter."
    ShowRoomDialog 6
    End
@ The locked entrance door
Room42LockedDoorEntrance:
    @ "Locked."
    ShowRoomDialog 624
    End
    EndSubBlock Room42V1End

    SubBlock Room42V2, 1, Room42V2Routes, Room42V2Chains, Room42V2End
    OffsetTable Room42V2Groups, 11, 1
    Offsets Room42V2Group0, Room42V2Group1, Room42V2Group2, Room42V2Group3, Room42V2Group4, Room42V2Group5
    Offsets Room42V2Group6, Room42V2Group7, Room42V2Group8, Room42V2Group9, Room42V2Group10
    EndTable
    Group Room42V2Group0, 3
    Npc 527, 335, sprite=3, facing=4, arg_0f=0
    Npc 481, 302, sprite=8, facing=4
    TriggerZone 428, 646, half_width=36, half_height=10, rearm_delay=3, trigger_kind=1, chain=Room42V2Chain24_id
    Group Room42V2Group1, 2
    Npc 720, 384, sprite=32, facing=4, interact_cooldown=5, interact_mode=1
    Npc 705, 390, sprite=4, facing=2, arg_0f=0
    Group Room42V2Group2, 2
    Npc 485, 392, sprite=13, facing=4
    Npc 505, 392, sprite=14, facing=4
    Group Room42V2Group3, 1
    TriggerZone 66, 246, half_width=31, half_height=6, rearm_delay=1, chain=Room42V2Chain3_id
    Group Room42V2Group4, 0
    Group Room42V2Group5, 1
    TriggerZone 548, 393, half_width=49, half_height=79, chain=Room42V2Chain4_id
    Group Room42V2Group6, 0
    Group Room42V2Group7, 6
    TriggerZone 480, 302, half_width=14, half_height=12, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain10_id
    TriggerZone 329, 264, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain11_id
    TriggerZone 334, 389, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain13_id
    TriggerZone 304, 346, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain12_id
    TriggerZone 516, 351, half_width=36, half_height=16, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain5_id
    TriggerZone 143, 266, half_width=10, half_height=21, rearm_delay=6, trigger_kind=1, chain=Room42V2Chain22_id
    Group Room42V2Group8, 6
    TriggerZone 480, 302, half_width=14, half_height=10, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain14_id
    TriggerZone 329, 264, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain15_id
    TriggerZone 333, 380, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain17_id
    TriggerZone 304, 346, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain16_id
    TriggerZone 516, 350, half_width=33, half_height=19, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain7_id
    Door 146, 277, half_width=11, half_height=23, destination_room=38
    Group Room42V2Group9, 3
    TriggerZone 666, 391, half_width=11, half_height=12, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain21_id
    TriggerZone 689, 392, half_width=11, half_height=11, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain20_id
    TriggerZone 720, 385, half_width=19, half_height=19, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V2Chain23_id
    Group Room42V2Group10, 2
    Npc 687, 386, sprite=14, facing=2
    Npc 666, 387, sprite=13, facing=2
    OffsetTable Room42V2Routes, 6
    Offsets Room42V2Route0, Room42V2Route1, Room42V2Route2, Room42V2Route3, Room42V2Route4, Room42V2Route5
    EndTable
Room42V2Route0:
    Route 3
    Waypoint 557, 419
    Waypoint 708, 419
    Waypoint 708, 401
Room42V2Route1:
    Route 2
    Waypoint 633, 392
    Waypoint 676, 392
Room42V2Route2:
    Route 3
    Waypoint 484, 387
    Waypoint 536, 387
    Waypoint 536, 391
Room42V2Route3:
    Route 3
    Waypoint 507, 386
    Waypoint 567, 386
    Waypoint 567, 395, on_arrival_chain=Room42V2Chain8_id
Room42V2Route4:
    Route 3
    Waypoint 567, 386
    Waypoint 619, 386
    Waypoint 687, 386
Room42V2Route5:
    Route 3
    Waypoint 562, 387
    Waypoint 602, 387
    Waypoint 666, 387, on_arrival_chain=Room42V2Chain19_id
    OffsetTable Room42V2Chains, 27, 1
    Offsets Room42V2Chain0, Room42V2Chain1, Room42V2Chain2, Room42V2Chain3, Room42V2Chain4, Room42V2Chain5
    Offsets Room42V2Chain6, Room42V2Chain7, Room42V2Chain8, Room42V2Chain9, Room42V2Chain10, Room42V2Chain11
    Offsets Room42V2Chain12, Room42V2Chain13, Room42V2Chain14, Room42V2Chain15, Room42V2Chain16, Room42V2Chain17
    Offsets Room42V2Chain18, Room42V2Chain19, Room42V2Chain20, Room42V2Chain21, Room42V2Chain22, Room42V2Chain23
    Offsets Room42V2Chain24, Room42V2Chain25, Room42V2Chain26
    EndTable
Room42V2Chain0:
    DelayedRespawnRowAndRunChain 0, Room42V2Group1_id, 0
    GotoIfQuestStateCompare 232, 0, 0, Room42V2Chain6_id, 0, 0, 0
    GotoIfQuestStateCompare 232, 0, 1, Room42V2Chain25_id, 0, 0, 0
    GotoIfStoryStageCompare 5, 3, 0, 0, Room42V2Group7_id, 0
    GotoIfStoryStageCompare 0, 4, Room42V2Chain26_id, 0, 0, 0
    End
Room42V2Chain1:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetQuestState QUEST_OBJ_FIND_RAT_TONIC, QUEST_OBJECTIVE_INDEX
    DelayedRespawnRowAndRunChainFrames 0, Room42V2Group4_id, 0
    SetTileObjectFlagBit 0, 255, 9
    SetStoryStage 3
    SetTileObjectAnimStateWithSpeed 0, 255
    InvokeChainIfEnabled 0, Room42V2Chain9_id
    End
Room42V2Chain2:
    @ "I don't think I should be going down into the cellar just yet."
    ShowRoomDialog 3
    End
Room42V2Chain3:
    @ "This must be the way down to the cellar."
    ShowRoomDialog 30
    End
Room42V2Chain4:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ClearTileObjectFlagBit 0, 255, 9
    StartTileObjectScript 548, 166, 1, 0, 255, 0, 0, 0, 255, 255, 255
    ArmChainYield 0
    StartObjectAnimSequence Room42V2Group2_id, 1, 0, 0, Room42V2Route3_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room42V2Group2_id, 0, 0, 0, Room42V2Route2_id, 0, 1, 0, 0, 0
    End
Room42V2Chain5:
    @ "Excuse me, Tom, I don't suppose you have any Rat Tonic?"
    @ "Indeed I do, Mr. Potter. If you don't mind finding your own way, there's a bottle down in the cellar. It's dark down there, so you might need to use Lumos to find your way."
    @ "I'm sure I can find the Rat Tonic for Ron..."
    ShowRoomDialog 29
    DelayedRespawnRowAndRunChain 0, Room42V2Group3_id, Room42V2Chain18_id
    SetStoryStage 4
    End
Room42V2Chain6:
    DelayedRespawnRowAndRunChain 0, Room42V2Group2_id, 0
    DelayedRespawnRowAndRunChain 0, Room42V2Group5_id, 0
    End
Room42V2Chain7:
    @ "Did you find the Rat Tonic, Mr. Potter?"
    @ "Not yet. I think I'll have another look."
    ShowRoomDialog 40
    End
Room42V2Chain8:
    ArmChainYield 1
    @ "Harry! How are you?"
    @ "Fine, thanks, Mrs. Weasley."
    @ "Hello, Harry."
    ShowRoomDialog 15
    SetQuestState 1, 232
    ArmChainYield 0
    StartObjectAnimSequence Room42V2Group2_id, 1, 0, 0, Room42V2Route4_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room42V2Group2_id, 0, 0, 0, Room42V2Route5_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room42V2Route0_id, 0, 1, 0, 0, 0
    End
Room42V2Chain9:
    RespawnRowAndRunChain Room42V2Group4_id, 0
    RespawnRowAndRunChain Room42V2Group7_id, 0
    RespawnRowAndRunChain Room42V2Group9_id, 0
    End
Room42V2Chain10:
    @ "There's nothing like a nice glass of Butterbeer!"
    ShowRoomDialog 7
    End
Room42V2Chain11:
    @ "I'm afraid this seat is taken."
    ShowRoomDialog 8
    End
Room42V2Chain12:
    @ "Harry Potter, isn't it?"
    ShowRoomDialog 9
    End
Room42V2Chain13:
    @ "I suppose you'll be attending Hogwarts, am I right?"
    ShowRoomDialog 10
    End
Room42V2Chain14:
    @ "Heading for the cellar? Better watch your step. I hear there are rats down there..."
    ShowRoomDialog 11
    End
Room42V2Chain15:
    @ "It's awfully dark down there..."
    ShowRoomDialog 12
    End
Room42V2Chain16:
    @ "I wouldn't go down there if I were you."
    ShowRoomDialog 13
    End
Room42V2Chain17:
    @ "Are you sure you want to go down into the cellar?"
    ShowRoomDialog 14
    End
Room42V2Chain18:
    DespawnRoomRowObjects Room42V2Group7_id
    DelayedRespawnRowAndRunChain 0, Room42V2Group8_id, 0
    End
Room42V2Chain19:
    ArmChainYield 1
    @ "Hi, Harry! So, you managed to make it through the summer?"
    @ "Just about, Ron. Have you heard from Hermione lately?"
    @ "I just saw her in Diagon Alley. She was talking about buying a cat..."
    @ "Speaking of pets, how's your rat, Scabbers?"
    @ "He's been a bit off-color ever since I brought him back from Egypt."
    @ "Why don't you give him a dose of Rat Tonic?"
    @ "I don't have any Rat Tonic left."
    @ "Maybe the innkeeper, Tom, has some. Tell you what, I'll go and ask him."
    ShowRoomDialog 16
    InvokeChainIfEnabled 0, Room42V2Chain1_id
    End
Room42V2Chain20:
    @ "Hello!"
    ShowRoomDialog 18
    End
Room42V2Chain21:
    @ "Good to see you again."
    ShowRoomDialog 19
    End
Room42V2Chain22:
    @ "Maybe I should speak to Tom, the innkeeper, before going down into the cellar¸"
    ShowRoomDialog 17
    End
Room42V2Chain23:
    @ "Did you manage to get any Rat Tonic, Harry?"
    @ "Not yet. I think I'll have another look."
    ShowRoomDialog 84
    End
Room42V2Chain24:
    @ "Locked."
    ShowRoomDialog 624
    End
Room42V2Chain25:
    RespawnRowAndRunChain Room42V2Group9_id, 0
    RespawnRowAndRunChain Room42V2Group10_id, 0
    End
Room42V2Chain26:
    RespawnRowAndRunChain Room42V2Group8_id, 0
    End
    EndSubBlock Room42V2End

    SubBlock Room42V3, 1, Room42V3Routes, Room42V3Chains, Room42V3End
    OffsetTable Room42V3Groups, 9, 1
    Offsets Room42V3Group0, Room42V3Group1, Room42V3Group2, Room42V3Group3, Room42V3Group4, Room42V3Group5
    Offsets Room42V3Group6, Room42V3Group7, Room42V3Group8
    EndTable
    Group Room42V3Group0, 8
    Npc 719, 384, sprite=32, facing=4
    Npc 707, 393, sprite=4, facing=2
    TriggerZone 718, 383, half_width=43, half_height=37, chain=Room42V3Chain2_id
    Npc 530, 335, sprite=3, facing=4
    Npc 481, 301, sprite=8, facing=4
    Door 143, 264, half_width=11, half_height=51, destination_room=38
    TriggerZone 426, 648, half_width=36, half_height=10, rearm_delay=3, trigger_kind=1, chain=Room42V3Chain44_id
    TriggerZone 545, 453, half_width=0, half_height=0, rearm_delay=20, trigger_kind=1
    Group Room42V3Group1, 4
    Npc 346, 232, sprite=13, facing=6
    Npc 326, 232, sprite=14, facing=2
    TriggerZone 249, 152, half_width=6, half_height=54, chain=Room42V3Chain1_id
    TileAnimation 299, 193, anim_id=0
    Group Room42V3Group2, 2
    Npc 547, 524, sprite=34, facing=0
    Npc 526, 524, sprite=5, facing=0
    Group Room42V3Group3, 0
    Group Room42V3Group4, 2
    Npc 417, 260, sprite=14, facing=2
    Npc 447, 260, sprite=13, facing=6
    Group Room42V3Group5, 5
    TriggerZone 481, 302, half_width=14, half_height=12, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain18_id
    TriggerZone 329, 264, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain19_id
    TriggerZone 332, 387, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain21_id
    TriggerZone 304, 346, half_width=14, half_height=14, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain20_id
    TriggerZone 518, 351, half_width=37, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain46_id
    Group Room42V3Group6, 5
    TriggerZone 481, 302, half_width=17, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain27_id
    TriggerZone 330, 264, half_width=17, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain28_id
    TriggerZone 333, 387, half_width=17, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain22_id
    TriggerZone 304, 349, half_width=17, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain29_id
    TriggerZone 518, 351, half_width=38, half_height=16, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain33_id
    Group Room42V3Group7, 5
    TriggerZone 479, 301, half_width=17, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain23_id
    TriggerZone 329, 264, half_width=17, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain24_id
    TriggerZone 332, 387, half_width=17, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain26_id
    TriggerZone 304, 345, half_width=17, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain25_id
    TriggerZone 518, 350, half_width=37, half_height=17, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain34_id
    Group Room42V3Group8, 2
    TriggerZone 416, 260, half_width=14, half_height=12, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain38_id
    TriggerZone 447, 260, half_width=14, half_height=12, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room42V3Chain39_id
    OffsetTable Room42V3Routes, 12
    Offsets Room42V3Route0, Room42V3Route1, Room42V3Route2, Room42V3Route3, Room42V3Route4, Room42V3Route5
    Offsets Room42V3Route6, Room42V3Route7, Room42V3Route8, Room42V3Route9, Room42V3Route10, Room42V3Route11
    EndTable
Room42V3Route0:
    Route 2
    Waypoint 305, 147
    Waypoint 305, 228
Room42V3Route1:
    Route 4
    Waypoint 325, 229
    Waypoint 344, 229
    Waypoint 344, 251
    Waypoint 416, 251, on_arrival_chain=Room42V3Chain40_id
Room42V3Route2:
    Route 5
    Waypoint 346, 226
    Waypoint 363, 226
    Waypoint 363, 251
    Waypoint 443, 251
    Waypoint 440, 251
Room42V3Route3:
    Route 3
    Waypoint 694, 382
    Waypoint 537, 381
    Waypoint 537, 407, on_arrival_chain=Room42V3Chain12_id
Room42V3Route4:
    Route 2
    Waypoint 642, 396
    Waypoint 523, 396
Room42V3Route5:
    Route 3
    Waypoint 679, 383
    Waypoint 569, 383
    Waypoint 567, 405
Room42V3Route6:
    Route 13
    Waypoint 524, 413
    Waypoint 524, 389
    Waypoint 477, 389
    Waypoint 477, 355
    Waypoint 437, 355
    Waypoint 436, 321
    Waypoint 349, 321
    Waypoint 348, 225
    Waypoint 304, 224
    Waypoint 304, 151
    Waypoint 68, 151, on_arrival_chain=Room42V3Chain8_id
    Waypoint 68, 254
    Waypoint 128, 253
Room42V3Route7:
    Route 13
    Waypoint 525, 414
    Waypoint 525, 390
    Waypoint 479, 389
    Waypoint 478, 355
    Waypoint 438, 356
    Waypoint 436, 320
    Waypoint 350, 321
    Waypoint 348, 226
    Waypoint 305, 223
    Waypoint 304, 151
    Waypoint 68, 151
    Waypoint 68, 254
    Waypoint 129, 253
Room42V3Route8:
    Route 1
    Waypoint 547, 448
Room42V3Route9:
    Route 1
    Waypoint 537, 407
Room42V3Route10:
    Route 4
    Waypoint 547, 448
    Waypoint 547, 391
    Waypoint 359, 391
    Waypoint 358, 301
Room42V3Route11:
    Route 4
    Waypoint 537, 407
    Waypoint 537, 382
    Waypoint 358, 382
    Waypoint 358, 281
    OffsetTable Room42V3Chains, 47, 1
    Offsets Room42V3Chain0, Room42V3Chain1, Room42V3Chain2, Room42V3Chain3, Room42V3Chain4, Room42V3Chain5
    Offsets Room42V3Chain6, Room42V3Chain7, Room42V3Chain8, Room42V3Chain9, Room42V3Chain10, Room42V3Chain11
    Offsets Room42V3Chain12, Room42V3Chain13, Room42V3Chain14, Room42V3Chain15, Room42V3Chain16, Room42V3Chain17
    Offsets Room42V3Chain18, Room42V3Chain19, Room42V3Chain20, Room42V3Chain21, Room42V3Chain22, Room42V3Chain23
    Offsets Room42V3Chain24, Room42V3Chain25, Room42V3Chain26, Room42V3Chain27, Room42V3Chain28, Room42V3Chain29
    Offsets Room42V3Chain30, Room42V3Chain31, Room42V3Chain32, Room42V3Chain33, Room42V3Chain34, Room42V3Chain35
    Offsets Room42V3Chain36, Room42V3Chain37, Room42V3Chain38, Room42V3Chain39, Room42V3Chain40, Room42V3Chain41
    Offsets Room42V3Chain42, Room42V3Chain43, Room42V3Chain44, Room42V3Chain45, Room42V3Chain46
    EndTable
Room42V3Chain0:
    DelayedRespawnRowAndRunChain 0, Room42V3Group5_id, 0
    GotoIfQuestStateCompare 249, 0, 0, 0, Room42V3Chain17_id, Room42V3Group1_id, 0
    GotoIfStoryStageCompare 0, 6, Room42V3Chain30_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room42V3Chain31_id, 0, 0, 0
    GotoIfStoryStageCompare 3, 6, Room42V3Chain41_id, 0, 0, 0
    End
Room42V3Chain1:
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 249
    ArmChainYield 1
    QueueTileObjectMove Room42V3Group1_id, 3, 0, 0, 1350, 0
    @ "...makes no sense not to tell him, Molly. Harry's got a right to know."
    @ "Arthur, the truth would terrify him! And Harry will be safe at Hogwarts."
    @ "We thought Azkaban prison was safe. If Black can break out of Azkaban, he can break into Hogwarts. He's deranged, Molly, and he thinks murdering Harry will bring You-Know-Who back to power."
    ShowRoomDialog 41
    QueueTileObjectMove 0, 255, 0, 0, 1500, 0
    DelayedRespawnRowAndRunChainFrames 1, 0, Room42V3Chain14_id
    End
Room42V3Chain2:
    ConsumeRoomItem 62
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 688, 129, 1, 0, 255, 0, 0, 2, 255, 255, 255
    SetTileObjectFacing 0, 255, 2
    @ "There you are, Harry! Did you manage to get any Rat Tonic?"
    @ "Yes. There you go."
    @ "Thanks. This will make you feel better, Scabbers."
    @ "What's wrong, Harry? You look upset."
    @ "I overheard your parents talking about Sirius Black. He wants to kill me..."
    @ "Promise me you won't go looking for trouble, Harry."
    @ "I don't go looking for trouble, Ron. Trouble usually finds me..."
    ShowRoomDialog 36
    ShowItemRemovedMessage 62
    DelayedRespawnRowAndRunChain 0, 0, Room42V3Chain3_id
    End
Room42V3Chain3:
    ArmChainYield 0
    Unk02 Room42V3Group0_id, 1, 2
    Unk02 Room42V3Group0_id, 0, 2
    StartTileObjectScript 523, 140, 1, Room42V3Group0_id, 1, 0, 0, 4, 255, 255, 255
    StartObjectAnimSequence Room42V3Group0_id, 0, 0, 0, Room42V3Route3_id, 0, 1, 0, 0, 0
    ArmChainYield 1
    DelayedRespawnRowAndRunChainFrames 30, 0, Room42V3Chain9_id
    End
Room42V3Chain4:
    ArmChainYield 0
    StartTileObjectScript 527, 186, 1, Room42V3Group2_id, 1, 0, 0, 0, 255, 255, 255
    ArmChainYield 1
    StartTileObjectScript 547, 192, 1, Room42V3Group2_id, 0, 0, 0, 0, 255, 255, 255
    SetTileObjectFacing Room42V3Group2_id, 1, 0
    @ "Hermione - we were wondering when you'd show up!"
    @ "It's really good to see you both again. I'd like you to meet my new cat, Crookshanks."
    @ "You bought that monster?"
    @ "He's gorgeous, isn't he?"
    @ "Squeak! Squeeeeeak!"
    @ "That beast of yours is scaring Scabbers! Keep it away from him!"
    @ "Meoww!"
    ShowRoomDialog 45
    DelayedRespawnRowAndRunChainFrames 3, 0, Room42V3Chain5_id
    End
Room42V3Chain5:
    ArmChainYield 0
    Unk02 Room42V3Group2_id, 1, 3
    Unk02 Room42V3Group0_id, 1, 3
    StartObjectAnimSequence Room42V3Group0_id, 1, 0, 0, Room42V3Route6_id, 2, 1, 0, 0, 0
    ArmChainYield 1
    QueueTileObjectMove Room42V3Group0_id, 1, 0, 0, 1200, 0
    DelayedRespawnRowAndRunChainFrames 0, 0, Room42V3Chain13_id
    End
Room42V3Chain6:
    DespawnTileObject Room42V3Group2_id, 1
    End
Room42V3Chain7:
    DespawnTileObject Room42V3Group0_id, 1
    End
Room42V3Chain8:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    QueueTileObjectMove 0, 255, 0, 0, 1000, 0
    RespawnRowAndRunChain 0, Room42V3Chain6_id
    ArmChainYield 1
    RespawnRowAndRunChain 0, Room42V3Chain7_id
    ArmChainYield 1
    @ "Scabbers! Come back!"
    @ "Crookshanks! Come back! Oh, it's no use!"
    @ "We need to rescue Scabbers!"
    @ "I'll go. Crookshanks is my responsibility."
    @ "I'll go. He's my rat."
    @ "I'll help you find them."
    ShowRoomDialog 46
    @ "Now you must choose who you want in your party. Ron or Hermione will join you until you complete a given task. Each character has additional spells that can be accessed with the L and R Buttons. You can also equip additional party members and access their statistics by pressing START (which brings up the Main Menu)."
    ShowRoomDialog 621
    QueueTileObjectMove Room42V3Group0_id, 7, 0, 0, 1200, 0
    ShowLoadingScreenTransition 6, 7, 32, 255
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    InvokeChainIfEnabled 0, Room42V3Chain35_id
    End
Room42V3Chain9:
    StartObjectAnimSequence 0, 255, 0, 0, Room42V3Route5_id, 0, 1, 0, 0, 0
    End
Room42V3Chain10:
    SetTileObjectFacing Room42V3Group0_id, 1, 4
    End
Room42V3Chain11:
    SetTileObjectFacing Room42V3Group0_id, 0, 4
    End
Room42V3Chain12:
    DelayedRespawnRowAndRunChainFrames 19, Room42V3Group2_id, Room42V3Chain4_id
    End
Room42V3Chain13:
    PlaySoundById 50
    StartObjectAnimSequence Room42V3Group2_id, 1, 0, 0, Room42V3Route7_id, 0, 1, 0, 0, 0
    End
Room42V3Chain14:
    ArmChainYield 1
    StartObjectAnimSequence 0, 255, 0, 0, Room42V3Route0_id, 0, 1, 0, 0, 0
    SetTileObjectFacing 0, 255, 2
    SetTileObjectFacing Room42V3Group1_id, 1, 6
    SetTileObjectFacing Room42V3Group1_id, 0, 6
    @ "I couldn't help hearing. Sorry..."
    @ "That's not the way I'd have chosen for you to find out."
    @ "No - honestly, it's OK. At least I now know what's going on."
    @ "Harry, you must be very scared."
    @ "I'm not. Really. Sirius Black can't be worse than Voldemort, can he?"
    @ "Listen, I want you to give me your word - swear to me that you won't go looking for Black."
    ShowRoomDialog 42
    ArmChainYield 0
    DelayedRespawnRowAndRunChainFrames 14, 0, Room42V3Chain15_id
    StartObjectAnimSequence Room42V3Group1_id, 1, 0, 0, Room42V3Route1_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room42V3Group1_id, 0, 0, 0, Room42V3Route2_id, 0, 1, 0, 0, 0
    DelayedRespawnRowAndRunChain 6, Room42V3Group3_id, 0
    End
Room42V3Chain15:
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room42V3Chain16:
    ArmChainYield 1
    ShowRoomDialog 43
    DelayedRespawnRowAndRunChain 2, Room42V3Group3_id, 0
    End
Room42V3Chain17:
    DelayedRespawnRowAndRunChain 0, Room42V3Group4_id, 0
    DelayedRespawnRowAndRunChain 0, Room42V3Group8_id, 0
    End
Room42V3Chain18:
    @ "There's nothing like a nice glass of Butterbeer!"
    ShowRoomDialog 7
    End
Room42V3Chain19:
    @ "I'm afraid this seat is taken."
    ShowRoomDialog 8
    End
Room42V3Chain20:
    @ "Harry Potter, isn't it?"
    ShowRoomDialog 9
    End
Room42V3Chain21:
    @ "I suppose you'll be attending Hogwarts, am I right?"
    ShowRoomDialog 10
    End
Room42V3Chain22:
    @ "Did you see a cat chase a rat past here?"
    @ "No. I didn't even know they allowed pets in here."
    ShowRoomDialog 76
    End
Room42V3Chain23:
    @ "Have you seen a cat run past here?"
    @ "Was that a cat? It was after a rat. They were running towards the cellar."
    ShowRoomDialog 63
    End
Room42V3Chain24:
    @ "Have you seen a cat run past here?"
    @ "I did indeed. Close on the heels of an unfortunate rat. They were heading for the cellar."
    ShowRoomDialog 64
    End
Room42V3Chain25:
    @ "Did you see a cat chase a rat past here?"
    @ "They went towards the cellar."
    ShowRoomDialog 65
    End
Room42V3Chain26:
    @ "Did you see a cat chase a rat past here?"
    @ "I saw them go down into the cellar."
    ShowRoomDialog 66
    End
Room42V3Chain27:
    @ "Did you see a cat chase a rat past here?"
    @ "Yes. They both went down into the cellar."
    ShowRoomDialog 73
    End
Room42V3Chain28:
    @ "Did you see a cat chase a rat past here?"
    @ "They were heading for the cellar."
    ShowRoomDialog 74
    End
Room42V3Chain29:
    @ "Did you see a cat chase a rat past here?"
    @ "I did. They went down into the cellar."
    ShowRoomDialog 75
    End
Room42V3Chain30:
    DelayedRespawnRowAndRunChain 0, Room42V3Group7_id, Room42V3Chain32_id
    End
Room42V3Chain31:
    DelayedRespawnRowAndRunChain 0, Room42V3Group6_id, Room42V3Chain32_id
    End
Room42V3Chain32:
    DespawnRoomRowObjects Room42V3Group5_id
    End
Room42V3Chain33:
    @ "Tom - have you seen my rat?"
    @ "He was heading for the cellar, with a big cat chasing him."
    ShowRoomDialog 69
    @ "Tom - have you seen my rat?"
    @ "He was heading for the cellar, with a big cat chasing him."
    ShowRoomDialog 69
    End
Room42V3Chain34:
    @ "Tom - have you seen my cat chasing Scabbers past here?"
    @ "Yes, Miss Granger. They were running into the cellar."
    ShowRoomDialog 68
    End
Room42V3Chain35:
    GotoIfStoryStageCompare 0, 6, Room42V3Chain42_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 7, Room42V3Chain43_id, 0, 0, 0
    End
Room42V3Chain36:
    DespawnTileObject Room42V3Group1_id, 1
    End
Room42V3Chain37:
    DespawnTileObject Room42V3Group1_id, 0
    End
Room42V3Chain38:
    @ "Hello!"
    ShowRoomDialog 18
    End
Room42V3Chain39:
    @ "Good to see you again."
    ShowRoomDialog 19
    End
Room42V3Chain40:
    RespawnRowAndRunChain Room42V3Group8_id, 0
    End
Room42V3Chain41:
    DespawnTileObject Room42V3Group0_id, 2
    DespawnTileObject Room42V3Group0_id, 0
    DespawnTileObject Room42V3Group0_id, 1
    DespawnRoomRowObjects Room42V3Group1_id
    End
Room42V3Chain42:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartObjectAnimSequence 0, 255, 0, 0, Room42V3Route8_id, 0, 1, 0, 0, 0
    DespawnTileObject Room42V3Group2_id, 0
    RecruitPartyFollower 6
    SetQuestState QUEST_OBJ_FIND_CROOKSHANKS, QUEST_OBJECTIVE_INDEX
    DelayedRespawnRowAndRunChain 0, Room42V3Group7_id, Room42V3Chain32_id
    ArmChainYield 1
    Unk02 Room42V3Group0_id, 0, 3
    StartObjectAnimSequence Room42V3Group0_id, 0, 0, 0, Room42V3Route11_id, 0, 1, 0, 0, 0
    DespawnTileObject Room42V3Group0_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room42V3Chain43:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartObjectAnimSequence 0, 255, 0, 0, Room42V3Route9_id, 0, 1, 0, 0, 0
    DespawnTileObject Room42V3Group0_id, 0
    RecruitPartyFollower 7
    SetQuestState QUEST_OBJ_FIND_SCABBERS_LEAKY_CAULDRON, QUEST_OBJECTIVE_INDEX
    DelayedRespawnRowAndRunChain 0, Room42V3Group6_id, Room42V3Chain32_id
    ArmChainYield 1
    Unk02 Room42V3Group2_id, 0, 3
    StartObjectAnimSequence Room42V3Group2_id, 0, 0, 0, Room42V3Route10_id, 0, 1, 0, 0, 0
    DespawnTileObject Room42V3Group2_id, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room42V3Chain44:
    @ "Locked."
    ShowRoomDialog 624
    End
Room42V3Chain45:
    SetTileObjectFacing 0, 255, 6
    End
Room42V3Chain46:
    @ "Ron Weasley was looking for you, Mr. Potter."
    ShowRoomDialog 27
    End
    EndSubBlock Room42V3End

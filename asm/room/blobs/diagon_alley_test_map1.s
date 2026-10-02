    .include "asm/room_blob.inc"

Room50Blob:
    RoomBlob 2
    PlayerEntry 60, 255, 0, 0
    PlayerEntry 456, 257, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room50V0
    VariantEntry Room50V1

    SubBlock Room50V0, 1, Room50V0Routes, Room50V0Chains, Room50V0End
    OffsetTable Room50V0Groups, 1
    Offsets Room50V0Group0
    EndTable
    Group Room50V0Group0, 2
    Door 12, 242, half_width=10, half_height=14, destination_room=54, exit_param=1
    Door 502, 242, half_width=9, half_height=15, destination_room=51
    OffsetTable Room50V0Routes, 0
    EndTable
    OffsetTable Room50V0Chains, 1
    Offsets Room50V0Chain0
    EndTable
Room50V0Chain0:
    End
    EndSubBlock Room50V0End

    SubBlock Room50V1, 1, Room50V1Routes, Room50V1Chains, Room50V1End
    OffsetTable Room50V1Groups, 1, 1
    Offsets Room50V1Group0
    EndTable
    Group Room50V1Group0, 26
    Prop 24, 301, kind=5, arg_13=0
    Prop 121, 300, kind=5, arg_13=0
    Prop 216, 301, kind=5, arg_13=0
    Prop 297, 301, kind=5, arg_13=0
    Prop 391, 301, kind=5
    Prop 488, 301, kind=5
    Npc 40, 76, sprite=0, facing=0
    Npc 152, 76, sprite=1, facing=0
    Npc 295, 77, sprite=3, facing=0
    Npc 41, 205, sprite=4, facing=0
    Npc 152, 204, sprite=5, facing=0
    Npc 408, 77, sprite=12, facing=0
    Npc 408, 204, sprite=13, facing=0
    Npc 296, 204, sprite=14, facing=0
    Npc 24, 348, sprite=40, facing=0
    Npc 104, 348, sprite=44, facing=0, arg_0f=0
    Npc 184, 348, sprite=48, facing=0, arg_0f=0
    Npc 266, 348, sprite=52, facing=0, arg_0f=0
    Npc 344, 348, sprite=56, facing=0, arg_0f=0
    Npc 426, 348, sprite=60, facing=0, arg_0f=0
    Npc 25, 461, sprite=41, facing=0, arg_0f=0
    Npc 104, 461, sprite=45, facing=0, arg_0f=0
    Npc 184, 461, sprite=49, facing=0, arg_0f=0
    Npc 265, 461, sprite=53, facing=0, arg_0f=0
    Npc 344, 461, sprite=57, facing=0, arg_0f=0
    Npc 425, 461, sprite=61, facing=0, arg_0f=0
    OffsetTable Room50V1Routes, 20
    Offsets Room50V1Route0, Room50V1Route1, Room50V1Route2, Room50V1Route3, Room50V1Route4, Room50V1Route5
    Offsets Room50V1Route6, Room50V1Route7, Room50V1Route8, Room50V1Route9, Room50V1Route10, Room50V1Route11
    Offsets Room50V1Route12, Room50V1Route13, Room50V1Route14, Room50V1Route15, Room50V1Route16, Room50V1Route17
    Offsets Room50V1Route18, Room50V1Route19
    EndTable
Room50V1Route0:
    Route 4
    Waypoint 40, 55
    Waypoint 119, 55
    Waypoint 119, 135
    Waypoint 40, 135
Room50V1Route1:
    Route 4
    Waypoint 152, 55
    Waypoint 232, 55
    Waypoint 232, 135
    Waypoint 152, 135
Room50V1Route2:
    Route 4
    Waypoint 295, 55
    Waypoint 376, 55
    Waypoint 376, 135
    Waypoint 295, 135
Room50V1Route3:
    Route 4
    Waypoint 408, 55
    Waypoint 488, 55
    Waypoint 488, 135
    Waypoint 408, 135
Room50V1Route4:
    Route 4
    Waypoint 40, 183
    Waypoint 119, 183
    Waypoint 119, 264
    Waypoint 40, 264
Room50V1Route5:
    Route 4
    Waypoint 152, 183
    Waypoint 232, 183
    Waypoint 232, 264
    Waypoint 152, 264
Room50V1Route6:
    Route 4
    Waypoint 295, 183
    Waypoint 376, 183
    Waypoint 376, 264
    Waypoint 295, 264
Room50V1Route7:
    Route 4
    Waypoint 408, 183
    Waypoint 488, 183
    Waypoint 488, 264
    Waypoint 408, 264
Room50V1Route8:
    Route 4
    Waypoint 24, 328
    Waypoint 85, 328
    Waypoint 85, 408
    Waypoint 25, 408
Room50V1Route9:
    Route 4
    Waypoint 105, 327
    Waypoint 165, 328
    Waypoint 165, 408
    Waypoint 105, 408
Room50V1Route10:
    Route 4
    Waypoint 185, 328
    Waypoint 245, 328
    Waypoint 245, 408
    Waypoint 185, 408
Room50V1Route11:
    Route 4
    Waypoint 265, 328
    Waypoint 325, 328
    Waypoint 325, 408
    Waypoint 265, 408
Room50V1Route12:
    Route 4
    Waypoint 345, 328
    Waypoint 405, 328
    Waypoint 405, 408
    Waypoint 345, 408
Room50V1Route13:
    Route 4
    Waypoint 425, 328
    Waypoint 485, 328
    Waypoint 485, 408
    Waypoint 425, 408
Room50V1Route14:
    Route 4
    Waypoint 25, 440
    Waypoint 85, 440
    Waypoint 85, 520
    Waypoint 25, 520
Room50V1Route15:
    Route 4
    Waypoint 105, 440
    Waypoint 165, 440
    Waypoint 165, 520
    Waypoint 105, 520
Room50V1Route16:
    Route 4
    Waypoint 185, 440
    Waypoint 245, 440
    Waypoint 245, 520
    Waypoint 185, 520
Room50V1Route17:
    Route 4
    Waypoint 265, 440
    Waypoint 325, 440
    Waypoint 325, 520
    Waypoint 265, 520
Room50V1Route18:
    Route 4
    Waypoint 345, 440
    Waypoint 405, 440
    Waypoint 405, 520
    Waypoint 345, 520
Room50V1Route19:
    Route 4
    Waypoint 425, 440
    Waypoint 485, 440
    Waypoint 485, 520
    Waypoint 425, 519
    OffsetTable Room50V1Chains, 2, 1
    Offsets Room50V1Chain0, Room50V1Chain1
    EndTable
Room50V1Chain0:
    SetQuestState 1, 1
    DelayedRespawnRowAndRunChain 0, 0, Room50V1Chain1_id
    End
Room50V1Chain1:
    StartObjectAnimSequence Room50V1Group0_id, 6, 0, 0, Room50V1Route0_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 7, 0, 0, Room50V1Route1_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 8, 0, 0, Room50V1Route2_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 11, 0, 0, Room50V1Route3_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 9, 0, 0, Room50V1Route4_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 10, 0, 0, Room50V1Route5_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 13, 0, 0, Room50V1Route6_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 12, 0, 0, Room50V1Route7_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 14, 0, 0, Room50V1Route8_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 15, 0, 0, Room50V1Route9_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 16, 0, 0, Room50V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 17, 0, 0, Room50V1Route11_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 18, 0, 0, Room50V1Route12_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 19, 0, 0, Room50V1Route13_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 20, 0, 0, Room50V1Route14_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 21, 0, 0, Room50V1Route15_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 22, 0, 0, Room50V1Route16_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 23, 0, 0, Room50V1Route17_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 24, 0, 0, Room50V1Route18_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room50V1Group0_id, 25, 0, 0, Room50V1Route19_id, 0, 0, 0, 0, 0
    End
    EndSubBlock Room50V1End

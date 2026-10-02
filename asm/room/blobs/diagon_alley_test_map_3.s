    .include "asm/room_blob.inc"

Room52Blob:
    RoomBlob 2
    PlayerEntry 51, 259, 0, 0
    PlayerEntry 452, 259, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room52V0
    VariantEntry Room52V1

    SubBlock Room52V0, 1, Room52V0Routes, Room52V0Chains, Room52V0End
    OffsetTable Room52V0Groups, 1
    Offsets Room52V0Group0
    EndTable
    Group Room52V0Group0, 3
    Prop 84, 269, kind=1
    Door 12, 241, half_width=11, half_height=15, destination_room=51, exit_param=1
    Door 501, 244, half_width=10, half_height=14, destination_room=53
    OffsetTable Room52V0Routes, 0
    EndTable
    OffsetTable Room52V0Chains, 1
    Offsets Room52V0Chain0
    EndTable
Room52V0Chain0:
    End
    EndSubBlock Room52V0End

    SubBlock Room52V1, 1, Room52V1Routes, Room52V1Chains, Room52V1End
    OffsetTable Room52V1Groups, 1, 1
    Offsets Room52V1Group0
    EndTable
    Group Room52V1Group0, 18
    Npc 40, 76, sprite=31, facing=0
    Npc 152, 76, sprite=32, facing=0
    Npc 40, 189, sprite=34, facing=0
    Npc 152, 188, sprite=35, facing=0
    Npc 296, 77, sprite=30, facing=0
    Npc 408, 77, sprite=29, facing=0
    Npc 296, 188, sprite=27, facing=0
    Npc 40, 316, sprite=23, facing=0
    Npc 152, 317, sprite=28, facing=0
    Npc 408, 189, sprite=33, facing=0
    Prop 423, 302, kind=1, facing=1
    Npc 295, 317, sprite=22, facing=0
    Npc 25, 444, sprite=42, facing=0, arg_0f=0
    Npc 105, 444, sprite=46, facing=0, arg_0f=0
    Npc 184, 444, sprite=50, facing=0, arg_0f=0
    Npc 265, 445, sprite=54, facing=0, arg_0f=0
    Npc 344, 444, sprite=58, facing=0, arg_0f=0
    Npc 425, 444, sprite=62, facing=0
    OffsetTable Room52V1Routes, 17
    Offsets Room52V1Route0, Room52V1Route1, Room52V1Route2, Room52V1Route3, Room52V1Route4, Room52V1Route5
    Offsets Room52V1Route6, Room52V1Route7, Room52V1Route8, Room52V1Route9, Room52V1Route10, Room52V1Route11
    Offsets Room52V1Route12, Room52V1Route13, Room52V1Route14, Room52V1Route15, Room52V1Route16
    EndTable
Room52V1Route0:
    Route 4
    Waypoint 40, 56
    Waypoint 120, 56
    Waypoint 120, 135
    Waypoint 40, 135
Room52V1Route1:
    Route 4
    Waypoint 152, 56
    Waypoint 232, 56
    Waypoint 232, 135
    Waypoint 152, 135
Room52V1Route2:
    Route 4
    Waypoint 40, 168
    Waypoint 120, 168
    Waypoint 120, 248
    Waypoint 40, 248
Room52V1Route3:
    Route 4
    Waypoint 152, 168
    Waypoint 232, 168
    Waypoint 232, 248
    Waypoint 152, 248
Room52V1Route4:
    Route 4
    Waypoint 295, 56
    Waypoint 376, 56
    Waypoint 376, 135
    Waypoint 295, 135
Room52V1Route5:
    Route 4
    Waypoint 408, 56
    Waypoint 488, 56
    Waypoint 488, 135
    Waypoint 408, 135
Room52V1Route6:
    Route 4
    Waypoint 295, 168
    Waypoint 376, 168
    Waypoint 376, 248
    Waypoint 294, 248
Room52V1Route7:
    Route 4
    Waypoint 40, 296
    Waypoint 120, 296
    Waypoint 120, 376
    Waypoint 40, 376
Room52V1Route8:
    Route 4
    Waypoint 152, 296
    Waypoint 232, 296
    Waypoint 232, 376
    Waypoint 152, 376
Room52V1Route9:
    Route 4
    Waypoint 408, 168
    Waypoint 488, 168
    Waypoint 489, 249
    Waypoint 408, 248
Room52V1Route10:
    Route 4
    Waypoint 294, 296
    Waypoint 376, 296
    Waypoint 376, 376
    Waypoint 294, 376
Room52V1Route11:
    Route 4
    Waypoint 25, 425
    Waypoint 85, 425
    Waypoint 85, 505
    Waypoint 25, 505
Room52V1Route12:
    Route 4
    Waypoint 105, 425
    Waypoint 165, 425
    Waypoint 165, 505
    Waypoint 105, 505
Room52V1Route13:
    Route 4
    Waypoint 185, 425
    Waypoint 245, 425
    Waypoint 245, 505
    Waypoint 185, 505
Room52V1Route14:
    Route 4
    Waypoint 265, 425
    Waypoint 325, 425
    Waypoint 325, 505
    Waypoint 265, 505
Room52V1Route15:
    Route 4
    Waypoint 345, 425
    Waypoint 405, 425
    Waypoint 405, 505
    Waypoint 345, 505
Room52V1Route16:
    Route 4
    Waypoint 425, 425
    Waypoint 485, 425
    Waypoint 485, 505
    Waypoint 425, 505
    OffsetTable Room52V1Chains, 2, 1
    Offsets Room52V1Chain0, Room52V1Chain1
    EndTable
Room52V1Chain0:
    DelayedRespawnRowAndRunChain 0, 0, Room52V1Chain1_id
    End
Room52V1Chain1:
    StartObjectAnimSequence Room52V1Group0_id, 0, 0, 0, Room52V1Route0_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 1, 0, 0, Room52V1Route1_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 2, 0, 0, Room52V1Route2_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 3, 0, 0, Room52V1Route3_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 4, 0, 0, Room52V1Route4_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 5, 0, 0, Room52V1Route5_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 6, 0, 0, Room52V1Route6_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 7, 0, 0, Room52V1Route7_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 8, 0, 0, Room52V1Route8_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 9, 0, 0, Room52V1Route9_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 11, 0, 0, Room52V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 12, 0, 0, Room52V1Route11_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 13, 0, 0, Room52V1Route12_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 14, 0, 0, Room52V1Route13_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 15, 0, 0, Room52V1Route14_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 16, 0, 0, Room52V1Route15_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room52V1Group0_id, 17, 0, 0, Room52V1Route16_id, 0, 0, 0, 0, 0
    End
    EndSubBlock Room52V1End

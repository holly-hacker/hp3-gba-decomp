    .include "asm/room_blob.inc"

Room51Blob:
    RoomBlob 2
    PlayerEntry 48, 255, 0, 0
    PlayerEntry 460, 257, 1, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room51V0
    VariantEntry Room51V1

    SubBlock Room51V0, 1, Room51V0Routes, Room51V0Chains, Room51V0End
    OffsetTable Room51V0Groups, 1
    Offsets Room51V0Group0
    EndTable
    Group Room51V0Group0, 3
    Prop 65, 214, kind=0, facing=4, arg_13=0
    Door 13, 241, half_width=7, half_height=16, destination_room=50, exit_param=1
    Door 503, 241, half_width=10, half_height=14, destination_room=52
    OffsetTable Room51V0Routes, 0
    EndTable
    OffsetTable Room51V0Chains, 1
    Offsets Room51V0Chain0
    EndTable
Room51V0Chain0:
    End
    EndSubBlock Room51V0End

    SubBlock Room51V1, 1, Room51V1Routes, Room51V1Chains, Room51V1End
    OffsetTable Room51V1Groups, 1, 1
    Offsets Room51V1Group0
    EndTable
    Group Room51V1Group0, 19
    Npc 39, 60, sprite=21, facing=0, arg_0f=0
    Npc 152, 60, sprite=24, facing=0, arg_0f=0
    Npc 39, 188, sprite=15, facing=0, arg_0f=0
    Npc 152, 188, sprite=20, facing=0, arg_0f=0
    Npc 329, 76, sprite=8, facing=0
    Npc 440, 76, sprite=9, facing=0
    Npc 328, 204, sprite=10, facing=0
    Npc 440, 204, sprite=11, facing=0
    Npc 39, 317, sprite=17, facing=0
    Npc 151, 316, sprite=18, facing=4
    Npc 329, 332, sprite=19, facing=0
    Prop 440, 333, kind=0, facing=3
    Npc 24, 445, sprite=39, facing=0, arg_0f=0
    Npc 103, 445, sprite=43, facing=0, arg_0f=0
    Npc 184, 445, sprite=47, facing=0, arg_0f=0
    Npc 264, 445, sprite=51, facing=0, arg_0f=0
    Npc 345, 445, sprite=55, facing=0, arg_0f=0
    Npc 424, 445, sprite=59, facing=0, arg_0f=0
    TriggerZone 69, 220, half_width=28, half_height=22, require_a_press=1, chain=Room51V1Chain2_id
    OffsetTable Room51V1Routes, 12
    Offsets Room51V1Route0, Room51V1Route1, Room51V1Route2, Room51V1Route3, Room51V1Route4, Room51V1Route5
    Offsets Room51V1Route6, Room51V1Route7, Room51V1Route8, Room51V1Route9, Room51V1Route10, Room51V1Route11
    EndTable
Room51V1Route0:
    Route 4
    Waypoint 40, 40
    Waypoint 120, 40
    Waypoint 120, 120
    Waypoint 40, 120
Room51V1Route1:
    Route 4
    Waypoint 152, 40
    Waypoint 231, 40
    Waypoint 231, 120
    Waypoint 152, 120
Room51V1Route2:
    Route 4
    Waypoint 40, 168
    Waypoint 120, 168
    Waypoint 120, 248
    Waypoint 40, 248
Room51V1Route3:
    Route 4
    Waypoint 152, 167
    Waypoint 231, 168
    Waypoint 231, 248
    Waypoint 152, 248
Room51V1Route4:
    Route 4
    Waypoint 40, 295
    Waypoint 120, 295
    Waypoint 120, 376
    Waypoint 40, 376
Room51V1Route5:
    Route 4
    Waypoint 152, 295
    Waypoint 231, 295
    Waypoint 231, 376
    Waypoint 152, 376
Room51V1Route6:
    Route 4
    Waypoint 25, 424
    Waypoint 85, 424
    Waypoint 85, 504
    Waypoint 25, 504
Room51V1Route7:
    Route 4
    Waypoint 105, 424
    Waypoint 165, 424
    Waypoint 165, 504
    Waypoint 105, 504
Room51V1Route8:
    Route 4
    Waypoint 185, 424
    Waypoint 245, 424
    Waypoint 245, 504
    Waypoint 185, 504
Room51V1Route9:
    Route 4
    Waypoint 265, 424
    Waypoint 325, 424
    Waypoint 325, 504
    Waypoint 265, 504
Room51V1Route10:
    Route 4
    Waypoint 345, 424
    Waypoint 405, 424
    Waypoint 405, 504
    Waypoint 345, 504
Room51V1Route11:
    Route 4
    Waypoint 425, 424
    Waypoint 485, 424
    Waypoint 485, 504
    Waypoint 425, 504
    OffsetTable Room51V1Chains, 3, 1
    Offsets Room51V1Chain0, Room51V1Chain1, Room51V1Chain2
    EndTable
Room51V1Chain0:
    DelayedRespawnRowAndRunChain 0, 0, Room51V1Chain1_id
    End
Room51V1Chain1:
    StartObjectAnimSequence Room51V1Group0_id, 0, 0, 0, Room51V1Route0_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 1, 0, 0, Room51V1Route1_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 2, 0, 0, Room51V1Route2_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 3, 0, 0, Room51V1Route3_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 8, 0, 0, Room51V1Route4_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 12, 0, 0, Room51V1Route6_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 13, 0, 0, Room51V1Route7_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 14, 0, 0, Room51V1Route8_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 15, 0, 0, Room51V1Route9_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 16, 0, 0, Room51V1Route10_id, 0, 0, 0, 0, 0
    StartObjectAnimSequence Room51V1Group0_id, 17, 0, 0, Room51V1Route11_id, 0, 0, 0, 0, 0
    End
Room51V1Chain2:
    UnlockMinigame 0
    UnlockMinigame 1
    UnlockMinigame 2
    UnlockMinigame 3
    StartMinigame 4, 1, 0, 0, 0
    End
    EndSubBlock Room51V1End

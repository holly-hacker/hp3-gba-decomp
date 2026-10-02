@ Assembler macros for per-room resource blobs; see docs/formats/rooms.md.
@ All data is byte-packed: only .byte/.2byte/.4byte are used, never .hword/.word.

.include "asm/room_script.inc"

@ ---- helpers ------------------------------------------------------------
.set _gid, 0                @ group counter, selects the symbols below
.set _mk, 0                 @ member counter inside the current group

.altmacro
.macro _sizesym g, m, size
    .set _sz_&g&_&m, size
.endm

.macro _emitsize g, m
    .byte _sz_&g&_&m
.endm
.noaltmacro

@ Records one member of the current group and its byte size.
.macro _member size
    .set _mk, _mk + 1
    .altmacro
    _sizesym %_gid, %_mk, \size
    .noaltmacro
.endm

@ Pads an offset table of `count` u16 entries to an even number of slots.
.macro _tablepad count
    .if ((\count) & 1) == 0
        .2byte 0xFFFF
    .endif
.endm

@ ---- blob header and stage index ----------------------------------------
.macro RoomBlob entries
    .set RoomBlobBase, .
    .2byte 4 + 8 * (\entries), \entries
.endm

.macro PlayerEntry x, y, id, facing
    .2byte \x, \y, \id
    .byte \facing, 0xFF
.endm

.macro StageIndex variants
    .byte \variants
.endm

@ The variant each of the 33 story stages uses.
.macro StageToVariantAll variant
    .rept 33
        .byte \variant
    .endr
    .2byte 0xFFFF
.endm

@ The variant each of the 33 story stages uses, one value per stage.
.macro StageToVariant variants:vararg
    .byte \variants
    .2byte 0xFFFF
.endm

.macro VariantEntry label
    .2byte \label - RoomBlobBase
    .byte 0, 0, 0, 0, 0, 0
.endm

@ ---- sub-blocks, tables ---------------------------------------------------
.macro SubBlock name, flags, routes, chains, end
\name:
    .set SubBlockBase, .
    .2byte \routes - \name, \chains - \name, \flags, \end - \name
.endm

.macro EndSubBlock name
\name:
    .byte 0, 0, 0xFF, 0xFF
.endm

@ A group of `count` objects: the member count, each member's size, padding
@ to 4 bytes, then the records (emitted by the object macros).
.macro Group name, count
    .set _gid, _gid + 1
    .set _mk, 0
\name:
    .byte \count, 0
    .set _i, 0
    .rept \count
        .set _i, _i + 1
        .altmacro
        _emitsize %_gid, %_i
        .noaltmacro
    .endr
    .rept (4 - ((\count + 2) & 3)) & 3
        .byte 0xFF
    .endr
.endm

@ ---- offset tables --------------------------------------------------------
@ A table of u16 offsets from the table start: OffsetTable, then Offsets lines
@ (any number), then EndTable. Used for object groups, routes and chains.
@ Each listed label also gets a <label>_id symbol holding its runtime number:
@ the position in the table plus `base`. The runtime tables put the default
@ sub-block's group and chain 0 first and the selected variant's after them,
@ so a variant's groups and chains are numbered from 1.
.macro OffsetTable name, count, base=0
\name:
    .set _tbl, \name
    .set _tcount, \count
    .set _tbase, \base
    .set _tn, 0
    .byte \count, 0
.endm

.altmacro
.macro _setid label, value
    .set label&_id, value
.endm
.noaltmacro

.macro Offsets labels:vararg
    .irp l, \labels
        .2byte \l - _tbl
        .altmacro
        _setid \l, %(_tbase + _tn)
        .noaltmacro
        .set _tn, _tn + 1
    .endr
.endm

.macro EndTable
    _tablepad _tcount
.endm

@ ---- object records ------------------------------------------------------
@ Each macro emits one record and registers its size with the enclosing Group.
@ Fields after the positional ones default to the value most records use.

.macro TileAnimation x, y, anim_id, flag=0
    _member 12
    .4byte 1
    .2byte \x, \y
    .byte \anim_id, \flag, 0xff, 0xff
.endm

.macro Door x, y, half_width, half_height, destination_room, exit_param=0, chain=0, require_a_press=0
    _member 16
    .4byte 2
    .2byte \x, \y
    .byte \half_width, \half_height, \exit_param, \destination_room, \chain, \require_a_press, 0xff, 0xff
.endm

.macro Switch x, y, variant, unk_08=0, rearm_delay=0, initial_frame=0, arg_0d=0, on_activate_respawn_group=0, on_activate_chain=2, on_deactivate_respawn_group=0, on_deactivate_chain=0
    _member 20
    .4byte 3
    .2byte \x, \y
    .byte \unk_08, \variant
    .2byte \rearm_delay
    .byte \initial_frame, \arg_0d, \on_activate_respawn_group, \on_activate_chain, \on_deactivate_respawn_group, \on_deactivate_chain, 0xff, 0xff
.endm

.macro TriggerZone x, y, half_width, half_height, rearm_delay=0, trigger_kind=0, require_a_press=0, unk_0e=0, respawn_group=0, chain=0
    _member 20
    .4byte 4
    .2byte \x, \y
    .byte \half_width, \half_height
    .2byte \rearm_delay
    .byte \trigger_kind, \require_a_press, \unk_0e, \respawn_group, \chain, 0xff, 0xff, 0xff
.endm

.macro Prop x, y, kind, arg_08=0, arg_0a=0, facing=0, arg_0e=1, arg_0f=0, arg_10=0, arg_11=0, arg_12=0, arg_13=1, chain=0
    _member 24
    .4byte 5
    .2byte \x, \y, \arg_08, \arg_0a
    .byte \kind, \facing, \arg_0e, \arg_0f, \arg_10, \arg_11, \arg_12, \arg_13, \chain, 0xff, 0xff, 0xff
.endm

.macro Npc x, y, sprite, facing, interact_cooldown=0, interact_mode=0, respawn_group=0, chain=0, arg_0f=1
    _member 16
    .4byte 6
    .2byte \x, \y
    .byte \sprite, \facing
    .2byte \interact_cooldown
    .byte \interact_mode, \respawn_group, \chain, \arg_0f
.endm

.macro TriggerRect x, y, left, top, right, bottom, rearm_delay=0, trigger_kind=2, require_a_press=0, unk_10=0, respawn_group=0, chain=24
    _member 20
    .4byte 7
    .2byte \x, \y
    .byte \left, \top, \right, \bottom
    .2byte \rearm_delay
    .byte \trigger_kind, \require_a_press, \unk_10, \respawn_group, \chain, 0xff
.endm

.macro Breakable x, y, variant, group0=4, member0=3, group1=4, member1=4, group2=0, member2=0, group3=0, member3=0, group4=0, member4=0, group5=0, member5=0, group6=0, member6=0, group7=0, member7=0
    _member 28
    .4byte 8
    .2byte \x, \y
    .byte \variant, \group0, \member0, \group1, \member1, \group2, \member2, \group3, \member3, \group4, \member4, \group5, \member5, \group6, \member6, \group7, \member7, 0xff, 0xff, 0xff
.endm

.macro Chest x, y, flag_id, reward_id, kind=0, chain=0, respawn_group=0
    _member 16
    .4byte 9
    .2byte \x, \y, \flag_id
    .byte \kind, \reward_id, \chain, \respawn_group, 0xff, 0xff
.endm

.macro MovePlayer x, y, target_x, target_y, variant=0, arg_0d=0, arg_0e=0
    _member 16
    .4byte 10
    .2byte \x, \y, \target_x, \target_y
    .byte \variant, \arg_0d, \arg_0e, 0xff
.endm

.macro TimedHazard x, y, variant, arg_08=50, arg_0a=30, respawn_group=0, chain=14
    _member 16
    .4byte 11
    .2byte \x, \y, \arg_08, \arg_0a
    .byte \variant, \respawn_group, \chain, 0xff
.endm

.macro ContactTrigger x, y, chain, respawn_group=0, arg_0a=0
    _member 12
    .4byte 12
    .2byte \x, \y
    .byte \respawn_group, \chain, \arg_0a, 0xff
.endm

.macro DoorAlt x, y, half_width, half_height, destination_room, exit_param=0, chain=0, require_a_press=0
    _member 16
    .4byte 13
    .2byte \x, \y
    .byte \half_width, \half_height, \exit_param, \destination_room, \chain, \require_a_press, 0xff, 0xff
.endm

.macro Route count
    .byte \count, 0, 0, 0
.endm

.macro Waypoint x, y, on_arrival_chain=0
    .2byte \x, \y
    .byte \on_arrival_chain, 0xFF, 0xFF, 0xFF
.endm

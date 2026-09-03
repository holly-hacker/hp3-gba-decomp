	.macro arm_func_start name
	.align 2, 0
	.global \name
	.arm
	.type \name, %function
	.endm

	.macro arm_func_end name
	.size \name, .-\name
	.endm

	.macro thumb_func_start name
	.align 2, 0
	.global \name
	.thumb
	.thumb_func
	.type \name, %function
	.endm

	.macro thumb_func_end name
	.size \name, .-\name
	.endm

	@ Names a Thumb function entry point inside still-raw incbin territory
	@ (the `thumb-func` manifest directive), so its address carries the low
	@ bit real Thumb function pointers always have when taken directly
	@ (e.g. stored in a function-pointer table) rather than only reached
	@ via `bl`. Unlike thumb_func_start, byte-free -- no `.align`, since
	@ this sits immediately before raw incbin bytes that must not shift.
	.macro thumb_func_label name
	.thumb_func
	.global \name
	.type \name, %function
	.endm

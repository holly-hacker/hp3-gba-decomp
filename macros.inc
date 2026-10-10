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

	@ thumb_func_start for a halfword-aligned entry point (gbadisasm output).
	.macro non_word_aligned_thumb_func_start name
	.global \name
	.thumb
	.thumb_func
	.type \name, %function
	.endm

	@ Names a Thumb function entry point inside still-raw incbin territory
	@ (the `thumb-func` manifest directive), so its symbol carries the Thumb
	@ bit. Unlike thumb_func_start, byte-free -- no `.align`, since
	@ this sits immediately before raw incbin bytes that must not shift.
	.macro thumb_func_label name
	.thumb_func
	.global \name
	.type \name, %function
	.endm

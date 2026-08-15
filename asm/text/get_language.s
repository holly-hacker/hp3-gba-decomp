.text

@ Returns the current language ID (0-7, see SetLanguage) that was last
@ passed to SetLanguage.
	thumb_func_start GetLanguage
GetLanguage: @ 0x080425D8
	ldr r0, _080425E0 @ =gCurrentLanguage
	ldrb r0, [r0]
	bx lr
	.align 2, 0
_080425E0: .4byte gCurrentLanguage
	thumb_func_end GetLanguage

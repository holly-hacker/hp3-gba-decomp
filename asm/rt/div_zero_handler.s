.text

@ Called on divisor==0 by umodsi3 (and structurally likely by the
@ sibling divide routine at 0x0804A464, not yet extracted). Does
@ nothing and returns -- the default/no-op case for whatever hook this
@ is meant to be; a real handler could be substituted here without
@ touching the caller.
	thumb_func_start DivZeroHandler
DivZeroHandler: @ us:0x0804A390, jp:0x0804A2BC
	mov pc, lr
	.align 2, 0
	thumb_func_end DivZeroHandler

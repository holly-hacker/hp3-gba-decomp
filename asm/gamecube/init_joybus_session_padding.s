.text

@ Zero fill between InitJoybusSession's 5-byte "GAZE" string and the next
@ 4-aligned object. No code or literal pool references it.
InitJoybusSessionPadding:
	.space 3

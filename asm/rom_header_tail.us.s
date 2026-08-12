.text

ROMHeaderTail: @ 0x080000A0
	.ascii "HARRY POTTER"  @ game title
	.ascii "BHTE"          @ game code
	.ascii "69"            @ maker code
	.byte 0x96             @ fixed value
	.byte 0x00             @ main unit code
	.byte 0x00             @ device type
	.space 7               @ reserved
	.byte 0x00             @ software version
	.byte 0x3B             @ complement check (header checksum)
	.space 2               @ reserved

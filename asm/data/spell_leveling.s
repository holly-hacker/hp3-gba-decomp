.text

@ byte[10], indexed by SpellId. Gates TrackSpellFamiliarity: a spell can
@ never be cast above its own cap.
g_abSpellMaxLevel: @ us:0x0804E5E0
	.byte 3  @ Flipendo
	.byte 1  @ Informus
	.byte 3  @ Verdimillious
	.byte 1  @ Diffindo
	.byte 3  @ Incendio
	.byte 1  @ WingardiumLeviosa
	.byte 2  @ PetrificusTotalus
	.byte 2  @ Glacius
	.byte 2  @ Fumos
	.byte 1  @ Spongify

@ byte[2], indexed by g_abSpellCastLevel[spellId] - 1: a spell starts at
@ cast level 1 (Uno) automatically, so no entry is needed to reach it.
@ Uno->Duo takes 25 uses, Duo->Tria takes 50.
g_abSpellLevelUpThreshold: @ us:0x0804E5EA
	.byte 25, 50

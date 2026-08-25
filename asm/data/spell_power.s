.text

@ ushort[30], indexed spellId*3 + spellLevel. Read by ResolvePlayerAttack
@ as: power = Base[idx] + (Scale[idx] * attacker.level / 9). See
@ docs/memory-map/battle.md.
g_awSpellPowerBase: @ us:0x080538EC
	.hword 10, 20, 15  @ Flipendo
	.hword 0, 0, 0     @ Informus
	.hword 15, 25, 20  @ Verdimillious
	.hword 30, 30, 40  @ Diffindo
	.hword 23, 35, 45  @ Incendio
	.hword 35, 45, 55  @ WingardiumLeviosa
	.hword 0, 0, 0     @ PetrificusTotalus
	.hword 30, 40, 45  @ Glacius
	.hword 0, 0, 0     @ Fumos
	.hword 0, 0, 0     @ Spongify

g_awSpellPowerScale: @ us:0x08053928
	.hword 4, 8, 10    @ Flipendo
	.hword 0, 0, 0     @ Informus
	.hword 6, 12, 14   @ Verdimillious
	.hword 18, 19, 20  @ Diffindo
	.hword 8, 16, 18   @ Incendio
	.hword 20, 21, 22  @ WingardiumLeviosa
	.hword 0, 0, 0     @ PetrificusTotalus
	.hword 18, 20, 20  @ Glacius
	.hword 0, 0, 0     @ Fumos
	.hword 0, 0, 0     @ Spongify

g_awSpellMpCost: @ us:0x08053964
	.hword 0, 10, 20   @ Flipendo
	.hword 0, 0, 0     @ Informus
	.hword 3, 15, 25   @ Verdimillious
	.hword 10, 0, 0    @ Diffindo
	.hword 6, 20, 30   @ Incendio
	.hword 20, 30, 40  @ WingardiumLeviosa
	.hword 10, 15, 20  @ PetrificusTotalus
	.hword 15, 25, 0   @ Glacius
	.hword 8, 30, 0    @ Fumos
	.hword 10, 0, 0    @ Spongify

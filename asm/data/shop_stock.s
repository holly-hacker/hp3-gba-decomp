.text

@ Shop tab stock lists, word[] item ids terminated by 132 (ITEM_COUNT).
@ See docs/formats/items.md's "Shop prices" section.
g_aShopStockMisc: @ us:0x0806B944
	.word 70  @ Chocolate Frogs
	.word 56  @ Wiggenweld Potion
	.word 57  @ Grand Wiggenweld Potion
	.word 58  @ Pepperup Potion
	.word 59  @ Grand Pepperup Potion
	.word 60  @ Antidote to Common Poisons
	.word 61  @ Anti-Paralysis Potion
	.word 132

g_aShopStockBelts: @ us:0x0806B964
	.word 0   @ Ordinary Belt
	.word 1   @ Leather Belt
	.word 2   @ Rope
	.word 3   @ Swedish Shortsnout Dragon-hide Belt
	.word 4   @ Common Welsh Green Dragon-hide Belt
	.word 5   @ Romanian Longhorn Dragon-hide Belt
	.word 6   @ Chinese Fireball Dragon-hide Belt
	.word 7   @ Hungarian Horntail Dragon-hide Belt
	.word 132

@ A curated subset of the Charm category (dwCategory 1, indices 8-19)
@ -- Bracelet/Beads/Head Band/Remembrall (indices 8, 9, 12, 17) are
@ never sold here.
g_aShopStockCharms: @ us:0x0806B988
	.word 10  @ Pocket Watch
	.word 11  @ Quidditch Wrist Guards
	.word 13  @ Eagle Feather Quill
	.word 14  @ Crystal Ball
	.word 15  @ Dragon Liver
	.word 16  @ Rabbit Fur Gloves
	.word 18  @ Spellotape
	.word 19  @ Golden Snitch
	.word 132

g_aShopStockGloves: @ us:0x0806B9AC
	.word 20  @ Mittens
	.word 21  @ Leather Gloves
	.word 22  @ Quidditch Gloves
	.word 23  @ Potions Gloves
	.word 24  @ Swedish Shortsnout Dragon-hide Gloves
	.word 25  @ Common Welsh Green Dragon-hide Gloves
	.word 26  @ Romanian Longhorn Dragon-hide Gloves
	.word 27  @ Chinese Fireball Dragon-hide Gloves
	.word 28  @ Hungarian Horntail Dragon-hide Gloves
	.word 132

g_aShopStockBoots: @ us:0x0806B9D4
	.word 29  @ Sneakers
	.word 30  @ Leather Boots
	.word 31  @ Galoshes
	.word 32  @ Quidditch Boots
	.word 33  @ Swedish Shortsnout Dragon-hide Boots
	.word 34  @ Common Welsh Green Dragon-hide Boots
	.word 35  @ Romanian Longhorn Dragon-hide Boots
	.word 36  @ Chinese Fireball Dragon-hide Boots
	.word 37  @ Hungarian Horntail Dragon-hide Boots
	.word 132

g_aShopStockHats: @ us:0x0806B9FC
	.word 38  @ Cap
	.word 39  @ Black Pointed Hat
	.word 40  @ Rear Admiral's Hat
	.word 41  @ Quidditch Helmet
	.word 42  @ Swedish Shortsnout Dragon-hide Cap
	.word 43  @ Common Welsh Green Dragon-hide Cap
	.word 44  @ Romanian Longhorn Dragon-hide Cap
	.word 45  @ Chinese Fireball Dragon-hide Cap
	.word 46  @ Hungarian Horntail Dragon-hide Cap
	.word 132

g_aShopStockCloaks: @ us:0x0806BA24
	.word 47  @ School Robe
	.word 48  @ Quidditch Robe
	.word 49  @ Winter Cloak
	.word 50  @ Potions Robe
	.word 51  @ Swedish Shortsnout Dragon-hide Cloak
	.word 52  @ Common Welsh Green Dragon-hide Cloak
	.word 53  @ Romanian Longhorn Dragon-hide Cloak
	.word 54  @ Chinese Fireball Dragon-hide Cloak
	.word 55  @ Hungarian Horntail Dragon-hide Cloak
	.word 132

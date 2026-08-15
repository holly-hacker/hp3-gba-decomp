.text

@ SetLanguage(langId), langId 0-7 (English US, English UK, French,
@ German, Spanish, Italian, Dutch, Danish -- in that order).
@ - Stores langId at gCurrentLanguage (read back by GetLanguage).
@ - Looks up langId's ROM string-table blob in the 8-entry pointer
@   table sDialogLanguageTable and hands it to InitDialogTextTable to
@   make it the active one for GetDialogText/DecompressDialogText.
@ - Also sets gLocaleThousandsSep, a locale thousands-separator byte
@   used elsewhere for number formatting: ' ' for French (langId 2),
@   '.' for Italian/Dutch (langId 5-6), ',' for everyone else.
@   Unrelated to the glyph charmap itself.
	thumb_func_start SetLanguage
SetLanguage: @ 0x08042588
	push {r4, lr}
	ldr r4, _080425A8 @ =gCurrentLanguage
	strb r0, [r4]
	ldr r1, _080425AC @ =sDialogLanguageTable
	lsls r0, r0, #2
	adds r0, r0, r1     @ r0 = &languageTable[langId]
	ldr r0, [r0]         @ r0 = this language's blob base
	bl InitDialogTextTable
	ldrb r0, [r4]
	cmp r0, #2           @ French?
	bne _080425B4
	ldr r1, _080425B0 @ =gLocaleThousandsSep
	movs r0, #0x20       @ ' '
	b _080425CC
	.align 2, 0
_080425A8: .4byte gCurrentLanguage
_080425AC: .4byte sDialogLanguageTable
_080425B0: .4byte gLocaleThousandsSep
_080425B4:
	subs r0, #5
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1           @ Italian or Dutch? (langId 5 or 6)
	bhi _080425C8
	ldr r1, _080425C4 @ =gLocaleThousandsSep
	movs r0, #0x2e       @ '.'
	b _080425CC
	.align 2, 0
_080425C4: .4byte gLocaleThousandsSep
_080425C8:
	ldr r1, _080425D4 @ =gLocaleThousandsSep
	movs r0, #0x2c       @ ',' (default)
_080425CC:
	strb r0, [r1]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080425D4: .4byte gLocaleThousandsSep
	thumb_func_end SetLanguage

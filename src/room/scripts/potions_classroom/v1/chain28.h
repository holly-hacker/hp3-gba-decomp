const u8 g_abRoom01V1Chain28[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(0, 255, 0),
    RS_SetTileObjectFacing(17, 0, 6),
    RS_SetTileObjectFacing(4, 0, 4),
    RS_Unk02(17, 0, 1),
    RS_DelayedRespawnRowAndRunChainFrames(15, 0, 0),
    RS_ConsumeRoomItem(63),
    RS_ConsumeRoomItem(64),
    RS_ConsumeRoomItem(65),
    RS_ConsumeRoomItem(77),
    RS_ConsumeRoomItem(66),
    RS_ShowItemRemovedMessage(63),
    RS_ShowItemRemovedMessage(64),
    RS_ShowItemRemovedMessage(65),
    RS_ShowItemRemovedMessage(66),
    RS_ShowItemRemovedMessage(77),
    // "Don't think you're leaving just yet. The Shrinking Solution has yet to be brewed."
    // "Uh-oh, how are we going to brew the potion?"
    // "Maybe Hermione knows?"
    // "It isn't difficult. Simply put the herbs and ingredients into the cauldron."
    // "There go the herbs..."
    // "And now for the ingredients..."
    RS_ShowRoomDialog(315),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_RespawnRowAndRunChain(6, 0),
    RS_PlaySoundById(66),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    // "It's worked!"
    // "I suppose you expect a reward... Take this Wingardium Leviosa spellbook. And try not to use it in a way that will get you expelled. Your next class is Defense Against the Dark Arts. You are dismissed."
    RS_ShowRoomDialog(316),
    RS_GrantPartySpell(5),
    RS_GrantPartySpell(6),
    RS_GrantPartySpell(7),
    RS_ShowSpellLearnedMessage(8, 1),
    RS_SetQuestState(22, 25),
    RS_DespawnRoomRowObjects(12),
    RS_RespawnRowAndRunChain(5, 0),
    RS_GotoIfQuestStateCompare(225, 1, 0, 38, 39, 0, 0),
    RS_End(),
};

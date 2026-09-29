const u8 g_abRoom34V1Chain4[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(0, 255, 0),
    // "What can I do for you?"
    // "We were wondering if you have a good book on werewolves?"
    // "I'm afraid that our only werewolf reference book had a tussle with 'The Monster Book of Monsters'. As a result, there are pages everywhere..."
    // "Why don't we find the torn pages? Then I can place them back in the book with the Reparo Spell!"
    // "I would appreciate you doing that, Miss Granger."
    // "OK, let's get to it."
    RS_ShowRoomDialog(415),
    RS_SetQuestState(28, 25),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};

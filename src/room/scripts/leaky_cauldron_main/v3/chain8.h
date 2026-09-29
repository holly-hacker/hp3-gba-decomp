const u8 g_abRoom42V3Chain8[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1000, 0),
    RS_RespawnRowAndRunChain(0, 7),
    RS_ArmChainYield(1),
    RS_RespawnRowAndRunChain(0, 8),
    RS_ArmChainYield(1),
    // "Scabbers! Come back!"
    // "Crookshanks! Come back! Oh, it's no use!"
    // "We need to rescue Scabbers!"
    // "I'll go. Crookshanks is my responsibility."
    // "I'll go. He's my rat."
    // "I'll help you find them."
    RS_ShowRoomDialog(46),
    // "Now you must choose who you want in your party. Ron or Hermione will join you until you complete a given task. Each character has additional spells that can be accessed with the L and R Buttons. You can also equip additional party members and access their statistics by pressing START (which brings up the Main Menu)."
    RS_ShowRoomDialog(621),
    RS_QueueTileObjectMove(1, 7, 0, 0, 1200, 0),
    RS_ShowLoadingScreenTransition(6, 7, 32, 255),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1200, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_InvokeChainIfEnabled(0, 36),
    RS_End(),
};

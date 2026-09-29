const u8 g_abRoom42V3Chain2[] = {
    RS_ConsumeRoomItem(62),
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(688, 129, 1, 0, 255, 0, 0, 2, 255, 255, 255),
    RS_SetTileObjectFacing(0, 255, 2),
    // "There you are, Harry! Did you manage to get any Rat Tonic?"
    // "Yes. There you go."
    // "Thanks. This will make you feel better, Scabbers."
    // "What's wrong, Harry? You look upset."
    // "I overheard your parents talking about Sirius Black. He wants to kill me..."
    // "Promise me you won't go looking for trouble, Harry."
    // "I don't go looking for trouble, Ron. Trouble usually finds me..."
    RS_ShowRoomDialog(36),
    RS_ShowItemRemovedMessage(62),
    RS_DelayedRespawnRowAndRunChain(0, 0, 4),
    RS_End(),
};

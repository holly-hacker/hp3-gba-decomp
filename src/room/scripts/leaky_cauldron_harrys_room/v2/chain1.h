const u8 g_abRoom41V2Chain1[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_FullHealParty(),
    // "Harry! You must be more careful. Tom found you lying on the floor unconscious. I had to give you some Wiggenweld Potion to make you feel better."
    RS_ShowRoomDialog(44),
    RS_StartTileObjectScript(147, 18, 1, 3, 0, 0, 0, 4, 255, 255, 255),
    RS_DespawnTileObject(3, 0),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};

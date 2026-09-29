// Talking to Malfoy before the final battle
const u8 g_abRoom25TalkMalfoy[] = {
    RS_ArmChainYield(1),
    // "Malfoy!"
    // "What are you doing here, Potter? In a hurry to get somewhere?"
    // "Stay out of the way, Malfoy."
    RS_ShowRoomDialog(610),
    RS_ArmChainYield(0),
    RS_DespawnTileObject(1, 2),
    RS_StartBattle(5, 0, 18),
    RS_End(),
};

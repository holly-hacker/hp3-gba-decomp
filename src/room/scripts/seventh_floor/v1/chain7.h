const u8 g_abRoom24V1Chain7[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(4, 2, 4),
    // "Have at thee, scurvy knave!"
    // "The Fat Lady must be in another portrait..."
    // "Why don't we ask Sir Cadogan? He's bonkers, but he knows all about this floor."
    // "OK, we have to start somewhere."
    // "Hello, Sir Cadogan."
    // "I don't suppose you happened to see the Fat Lady go by here?"
    // "That I did, fair maiden, and in great distress!"
    // "Could you help us find her?"
    // "That I shall, milady, and verily so!"
    RS_ShowRoomDialog(376),
    RS_Unk02(0, 255, 3),
    RS_Unk02(4, 2, 2),
    RS_ArmChainYield(0),
    RS_RespawnRowAndRunChain(0, 11),
    RS_End(),
};

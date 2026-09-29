const u8 g_abRoom27V1Chain1[] = {
    RS_ArmChainYield(1),
    RS_RespawnRowAndRunChain(3, 0),
    RS_RemovePartyFollower(7),
    RS_RespawnRowAndRunChain(4, 0),
    RS_RemovePartyFollower(6),
    RS_StartTileObjectScript(207, 15, 1, 3, 0, 0, 0, 6, 255, 255, 255),
    RS_StartTileObjectScript(213, 32, 1, 4, 0, 0, 0, 6, 255, 255, 255),
    RS_QueueTileObjectMove(2, 1, 0, 0, 1400, 0),
    // "Good afternoon. Today's will be a practical lesson."
    // "I draw your attention to this wardrobe. There's a Boggart in there. Now, what is a Boggart?"
    // "It's a shape-shifter. It can take the shape of whatever it thinks will frighten us most."
    // "Well put. The charm that repels a Boggart is simple. It forces the Boggart to assume a shape that you find amusing. The incantation is Riddikulus."
    RS_ShowRoomDialog(347),
    // "Neville, Lavender, Ron and Parvati, please come forward."
    RS_ShowRoomDialog(348),
    RS_ArmChainYield(0),
    RS_InvokeChainIfEnabled(0, 9),
    RS_End(),
};

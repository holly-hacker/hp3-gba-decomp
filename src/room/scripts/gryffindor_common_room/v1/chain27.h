const u8 g_abRoom29V1Chain27[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "Yes! We won!"
    // "Good for you, Harry!"
    // "I've never seen Professor McGonagall so angry! Malfoy's definitely for it!"
    // "Well done, Harry! Ten Galleons to me! Must find Penelope. Excuse me -"
    RS_ShowRoomDialog(501),
    RS_Unk02(11, 2, 2),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(11, 2, 0, 0, 26, 0, 1, 0, 0, 0),
    RS_End(),
};

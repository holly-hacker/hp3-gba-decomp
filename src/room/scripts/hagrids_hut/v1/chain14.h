const u8 g_abRoom11V1Chain14[] = {
    RS_ArmChainYield(1),
    // "Isn't there anything anyone can do, Hagrid?"
    // "Dumbledore's tried. He's got no power ter overrule the Committee. I expect Lucius Malfoy's threatened 'em."
    // "We'll stay with you, Hagrid¸"
    RS_ShowRoomDialog(546),
    RS_RespawnRowAndRunChain(9, 0),
    RS_RemovePartyFollower(7),
    RS_RemovePartyFollower(6),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(9, 0, 0, 0, 15, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(9, 1, 0, 0, 16, 0, 1, 0, 0, 0),
    RS_End(),
};

const u8 g_abRoom29V1Chain20[] = {
    RS_ArmChainYield(1),
    // "Harry, it was Sirius Black who slashed the Fat Lady's portrait!"
    // "Do you think Black's still in the castle?"
    // "He might be!"
    RS_ShowRoomDialog(407),
    RS_RespawnRowAndRunChain(20, 0),
    RS_RemovePartyFollower(7),
    // "We should be on our way to Defense Against the Dark Arts class."
    // "I wonder if Professor Lupin will even be there? He hasn't looked well lately."
    // "That class does seem to take a toll on its teachers. Let's get going."
    RS_ShowRoomDialog(408),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(9, 0, 0, 0, 58, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 59, 0, 1, 0, 0, 0),
    RS_End(),
};

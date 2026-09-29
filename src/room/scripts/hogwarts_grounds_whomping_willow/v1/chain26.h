const u8 g_abRoom15V1Chain26[] = {
    RS_ArmChainYield(1),
    // "A Hippogriff! Beau'iful, aren' they?"
    // "Ooooooooh!"
    // "Now, firs' thing yeh gotta know abou' Hippogriffs is they're proud. Don't never insult one, 'cause it might be the last thing yeh do. Right then - let's see how yeh get on with Buckbeak."
    RS_ShowRoomDialog(268),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(13, 0, 0, 0, 28, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(10, 1, 0, 0, 27, 0, 1, 0, 0, 0),
    RS_End(),
};

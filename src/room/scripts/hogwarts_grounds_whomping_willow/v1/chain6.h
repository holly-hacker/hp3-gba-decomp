const u8 g_abRoom15V1Chain6[] = {
    RS_ArmChainYield(1),
    // "Firs' thing yeh'll want ter do is open yer books -"
    // "How do we do that if we don't have a copy of 'The Monster Book of Monsters'? I'm afraid, Hagrid, that I've mislaid my copy - and so have Crabbe and Goyle."
    // "Oh, er, well, I¸"
    // "Oh, surely you have extra copies we could borrow?"
    // "Harry, can I have a word?"
    RS_ShowRoomDialog(231),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(2, 0, 0, 0, 9, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 8, 0, 1, 0, 0, 0),
    RS_End(),
};

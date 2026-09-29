const u8 g_abRoom11V1Chain5[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(4, 0, 0),
    RS_DelayedRespawnRowAndRunChainFrames(15, 0, 0),
    // "They're going ter put poor Buckbeak on trial fer attackin' Malfoy..."
    // "Listen, you can't give up. You just need a good defense. You can call us as witnesses."
    // "I'm sure I've read about a case of Hippogriff-baiting¸"
    // "We can look it up for you in the library. Coming, Hermione?"
    // "No. I want a quick word with Professor McGonagall."
    // "Don't worry, we'll work out a defense for Buckbeak. Let's go to the library, Ron."
    RS_ShowRoomDialog(438),
    RS_DelayedRespawnRowAndRunChainFrames(15, 0, 0),
    RS_SetTileObjectFacing(4, 0, 4),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1200, 0),
    RS_Unk02(5, 0, 2),
    RS_InvokeChainIfEnabled(0, 7),
    RS_End(),
};

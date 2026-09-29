const u8 g_abRoom17V1Chain6[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "May I see it? Hmm. And there was no note at all, Potter?"
    // "No."
    // "I see. Well, I'm afraid I will have to take this, Potter."
    // "W-what? Why?"
    // "It will need to be checked for jinxes. It shouldn't take more than a few weeks."
    // "You will have it back if we are sure it is jinx-free. I shall keep you informed."
    RS_ShowRoomDialog(461),
    RS_ConsumeRoomItem(67),
    // "I don't believe it!"
    // "There's nothing wrong with it!"
    RS_ShowRoomDialog(462),
    RS_RespawnRowAndRunChain(5, 0),
    RS_QueueTileObjectMove(5, 0, 0, 0, 2000, 0),
    // "Hermione! What did you go running to McGonagall for?"
    // "Because I thought - and Professor McGonagall agrees with me - that that broom was probably sent to Harry by Sirius Black!"
    RS_ShowRoomDialog(463),
    RS_QueueTileObjectMove(2, 12, 0, 0, 1800, 0),
    // "Merry Christmas! Sit down, sit down! And now - crackers! Or, to be precise, Wizard Cracker Pop-it! A new game I've just invented!"
    RS_ShowRoomDialog(464),
    RS_DespawnRoomRowObjects(4),
    RS_DespawnRoomRowObjects(5),
    RS_DespawnRoomRowObjects(3),
    RS_DespawnTileObject(2, 14),
    RS_RespawnRowAndRunChain(6, 0),
    RS_UnlockMinigame(0),
    RS_StartMinigame(0, 0, 1, 0, 8),
    RS_End(),
};

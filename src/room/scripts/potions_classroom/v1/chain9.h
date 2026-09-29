const u8 g_abRoom01V1Chain9[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_RemovePartyFollower(7),
    RS_DelayedRespawnRowAndRunChainFrames(1, 8, 0),
    RS_DelayedRespawnRowAndRunChainFrames(1, 11, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1650, 0),
    // "Feeling particularly keen today, are we, Potter? Very well..."
    // "Go to the Potions store room, Potter, retrieve some herbs and then bring them back to me. Take Miss Granger along with you."
    // "The potion requires daisy root, Shrivelfig, rat spleen, dead caterpillar and leech juice."
    // "Do not think of this as an opportunity to avoid the lesson, Potter."
    // "Yes, Professor."
    // "Let's go to the Potions store room, Hermione."
    RS_ShowRoomDialog(298),
    RS_SetQuestState(20, 25),
    RS_SetQuestState(0, 225),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};

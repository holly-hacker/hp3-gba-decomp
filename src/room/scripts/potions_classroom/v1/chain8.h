const u8 g_abRoom01V1Chain8[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_RemovePartyFollower(5),
    RS_DelayedRespawnRowAndRunChainFrames(1, 7, 0),
    RS_DelayedRespawnRowAndRunChainFrames(1, 10, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1650, 0),
    // "Weasley, while I am reluctant to assign you a task as complex as finding and carrying, I live in hope that you will surprise me."
    // "I require potion ingredients from the Potions store room. Bring them back here to me Weasley, and take Granger with you."
    // "The potion requires daisy root, Shrivelfig, rat spleen, dead caterpillar and leech juice."
    // "Do not think of this as an opportunity to avoid the lesson, Weasley. Tardiness will be punished."
    // "Yes, Professor."
    RS_ShowRoomDialog(297),
    RS_SetQuestState(20, 25),
    RS_SetQuestState(1, 225),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};

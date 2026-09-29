const u8 g_abRoom15V1Chain58[] = {
    RS_ArmChainYield(1),
    // "Good evening, Sirius. How I hoped I would be the one to catch you¸"
    RS_ShowRoomDialog(580),
    RS_PlayMusicModuleAndFlagIfChain1(16),
    RS_StartTileObjectScript(970, 39, 4, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_SetTileObjectFacing(0, 255, 0),
    RS_DelayedRespawnRowAndRunChainFrames(10, 0, 0),
    // "Professor Snape! You're making a mistake. Sirius Black isn't here to kill me!"
    // "SILENCE! Two more for Azkaban tonight..."
    RS_ShowRoomDialog(578),
    // "Professor Snape - it - it wouldn't hurt to hear what they've got to say, w-would it?"
    // "Professor Lupin could have killed me many times. If he was helping Black, why didn't he just finish me off?"
    // "Get out of the way, Potter."
    RS_ShowRoomDialog(579),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(31, 0, 0, 0, 67, 0, 1, 0, 0, 0),
    RS_StartTileObjectScript(1015, 242, 3, 17, 2, 0, 0, 0, 255, 255, 255),
    RS_StartTileObjectScript(1015, 6, 4, 17, 3, 0, 0, 0, 255, 255, 255),
    RS_StartTileObjectScript(1015, 31, 4, 17, 0, 0, 0, 0, 255, 255, 255),
    RS_StartTileObjectScript(1015, 61, 4, 17, 1, 0, 0, 0, 255, 255, 255),
    RS_StartTileObjectScript(1000, 41, 4, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_StartTileObjectScript(970, 252, 3, 18, 0, 0, 0, 2, 255, 255, 255),
    RS_End(),
};

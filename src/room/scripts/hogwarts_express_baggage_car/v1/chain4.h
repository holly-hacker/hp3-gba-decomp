const u8 g_abRoom05V1Chain4[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChainFrames(1, 0, 0),
    RS_SetTileObjectFacing(0, 255, 0),
    RS_DespawnTileObject(0, 8),
    RS_DelayedRespawnRowAndRunChain(0, 13, 0),
    RS_DespawnTileObject(0, 6),
    RS_SetTileObjectAnimState(13, 0),
    RS_SetQuestState(5, 224),
    RS_PlaySoundById(32),
    RS_DelayedRespawnRowAndRunChain(0, 14, 0),
    RS_QueueTileObjectMove(14, 0, 0, 0, 1500, 2),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectFacing(0, 255, 0),
    RS_DelayedRespawnRowAndRunChain(0, 15, 0),
    // "Oh no! It's broken through!"
    RS_ShowRoomDialog(158),
    RS_QueueTileObjectMove(15, 0, 0, 0, 1500, 1),
    RS_PlaySoundById(22),
    RS_StartTileObjectScript(154, 25, 1, 15, 0, 0, 0, 2, 255, 255, 255),
    RS_StartTileObjectScript(165, 230, 0, 15, 0, 0, 0, 2, 255, 255, 255),
    // "None of us is hiding Sirius Black under our cloaks! Go!"
    RS_ShowRoomDialog(159),
    RS_StartTileObjectScript(184, 183, 0, 14, 0, 0, 0, 6, 255, 255, 255),
    RS_DespawnTileObject(14, 0),
    RS_PlayMusicModuleAndFlagIfChain1(51),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1500, 1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 14),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    // "What was that thing? And what's the matter with Harry?"
    // "That was a Dementor. One of the Dementors of Azkaban. For some reason its presence caused Harry to collapse."
    // "Can't we do something?"
    // "Mr. Weasley, I'd like you to go and find some chocolate so that we can revive Harry."
    // "What can I do to help, Professor?"
    // "Miss Granger, I'd like you to go and find the conductor and get the train going again."
    RS_ShowRoomDialog(114),
    RS_DelayedRespawnRowAndRunChainFrames(0, 22, 0),
    RS_DespawnTileObject(25, 0),
    RS_DespawnTileObject(28, 0),
    RS_DespawnTileObject(1, 2),
    RS_InvokeChainIfEnabled(0, 17),
    RS_End(),
};

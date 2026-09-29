const u8 g_abRoom05V1Chain11[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(0, 3, 0),
    RS_DespawnTileObject(28, 0),
    RS_SetTileObjectAnimState(3, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_DespawnTileObject(3, 0),
    RS_DespawnTileObject(0, 7),
    RS_DespawnTileObject(0, 9),
    RS_DelayedRespawnRowAndRunChain(0, 2, 0),
    RS_SetTileObjectAnimState(2, 0),
    RS_PlaySoundById(32),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectFacing(0, 255, 0),
    RS_DelayedRespawnRowAndRunChain(0, 8, 0),
    RS_QueueTileObjectMove(8, 0, 0, 0, 1500, 1),
    RS_DelayedRespawnRowAndRunChain(0, 15, 0),
    RS_QueueTileObjectMove(15, 0, 0, 0, 1500, 1),
    RS_Unk02(15, 0, 3),
    RS_StartTileObjectScript(338, 230, 0, 15, 0, 0, 0, 0, 255, 255, 255),
    RS_SetTileObjectFacing(15, 0, 0),
    // "None of us is hiding Sirius Black under our cloaks! Go!"
    RS_ShowRoomDialog(159),
    RS_StartTileObjectScript(324, 189, 0, 8, 0, 0, 0, 6, 255, 255, 255),
    RS_DespawnTileObject(8, 0),
    RS_PlayMusicModuleAndFlagIfChain1(51),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1500, 1),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    // "What was that thing? And what's the matter with Harry?"
    // "That was a Dementor. One of the Dementors of Azkaban. For some reason its presence caused Harry to collapse."
    // "Can't we do something?"
    // "Mr. Weasley, I'd like you to go and find some chocolate so that we can revive Harry."
    // "What can I do to help, Professor?"
    // "Miss Granger, I'd like you to go and find the conductor and get the train going again."
    RS_ShowRoomDialog(114),
    RS_InvokeChainIfEnabled(0, 17),
    RS_End(),
};

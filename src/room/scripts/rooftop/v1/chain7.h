const u8 g_abRoom25V1Chain7[] = {
    RS_RespawnRowAndRunChain(4, 0),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetBattleDefeatState(19),
    RS_DespawnTileObject(9, 1),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(315, 63, 1, 4, 0, 0, 0, 6, 255, 255, 255),
    // "Hermione! You got here quickly! We must get to Sirius. The Dementors are coming!"
    RS_ShowRoomDialog(608),
    RS_StartTileObjectScript(290, 57, 1, 4, 0, 0, 0, 6, 255, 255, 255),
    RS_DespawnTileObject(4, 0),
    RS_RecruitPartyFollower(6),
    RS_SetQuestState(2, 225),
    RS_DelayedRespawnRowAndRunChainFrames(0, 20, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};

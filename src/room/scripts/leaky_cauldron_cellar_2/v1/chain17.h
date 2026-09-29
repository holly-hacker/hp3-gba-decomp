const u8 g_abRoom39V1Chain17[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(183, 128, 0, 6, 0, 0, 0, 0, 255, 255, 255),
    // "I found Crookshanks. Did you manage to find Scabbers?"
    // "Yes, I did - no thanks to your cat."
    // "Bad Crookshanks! Don't run away again!"
    RS_ShowRoomDialog(57),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 4, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(6, 0, 0, 0, 4, 0, 1, 0, 0, 0),
    RS_DespawnTileObject(6, 0),
    RS_RemovePartyFollower(6),
    RS_RecruitPartyFollower(6),
    RS_RecruitPartyFollower(7),
    RS_SetQuestState(54, 25),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_DelayedRespawnRowAndRunChainFrames(0, 0, 36),
    RS_End(),
};

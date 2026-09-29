const u8 g_abRoom00V1Chain7[] = {
    RS_DespawnRoomRowObjects(5),
    RS_ArmChainYield(1),
    // "I've already read a great deal about werewolves... I even know how to imitate a werewolf's howl."
    // "Well, good for you, Hermione. I'm sure that'll come in really useful one day."
    // "Let's get going."
    RS_ShowRoomDialog(412),
    RS_StartTileObjectScript(422, 139, 1, 0, 255, 0, 0, 4, 255, 255, 255),
    RS_StartTileObjectScript(422, 139, 1, 3, 0, 0, 0, 2, 255, 255, 255),
    RS_DespawnTileObject(3, 0),
    RS_RecruitPartyFollower(7),
    RS_StartTileObjectScript(422, 139, 1, 4, 0, 0, 0, 2, 255, 255, 255),
    RS_DespawnTileObject(4, 0),
    RS_RecruitPartyFollower(6),
    RS_SetStoryStage(8),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};

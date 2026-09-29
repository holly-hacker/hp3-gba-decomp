const u8 g_abRoom33V2Chain0[] = {
    RS_SetBattleDefeatState(2),
    // "Oh! You're awake. Someone found you unconscious and brought you in for care. You should be more careful."
    RS_ShowRoomDialog(649),
    RS_FullHealParty(),
    RS_GotoIfStoryStageCompare(3, 25, 2, 0, 0, 0),
    RS_End(),
};

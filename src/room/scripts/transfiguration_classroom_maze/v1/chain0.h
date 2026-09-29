const u8 g_abRoom04V1Chain0[] = {
    RS_SetBattleDefeatState(3),
    RS_SetQuestState(0, 128),
    RS_SetQuestState(0, 226),
    RS_GotoIfQuestStateCompare(5, 1, 23, 19, 0, 0, 0),
    RS_GotoIfQuestStateCompare(4, 1, 23, 20, 0, 0, 0),
    RS_ClearOverworldMonstersDisabled(),
    RS_SetQuestState(0, 225),
    RS_SetQuestState(0, 229),
    RS_End(),
};

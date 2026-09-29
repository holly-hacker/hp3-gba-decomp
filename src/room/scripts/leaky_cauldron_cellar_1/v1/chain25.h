const u8 g_abRoom38V1Chain25[] = {
    RS_GrantPartyExperience(5, 65535),
    RS_ArmChainYield(1),
    RS_SetQuestState(2, 235),
    // "You've just gained your first level! You will now have more Stamina Points, Magic Points and defensive capabilities to help you in magical encounters. You can look at your statistics by pressing START (which brings up the Main Menu) and then selecting Status/Equip."
    RS_ShowRoomDialog(660),
    RS_End(),
};

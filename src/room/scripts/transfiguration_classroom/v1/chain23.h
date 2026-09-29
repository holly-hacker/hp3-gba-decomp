const u8 g_abRoom03V1Chain23[] = {
    RS_ArmChainYield(1),
    RS_GrantPartyExperience(25, 65535),
    RS_PlayRoomSoundEffect(24),
    // "Excellent, Mr. Potter. As a reward, you may have this Petrificus Totalus spellbook. Class is dismissed."
    RS_ShowRoomDialog(201),
    RS_GrantPartySpell(6),
    RS_GrantPartySpell(7),
    RS_GrantPartySpell(5),
    RS_ShowSpellLearnedMessage(7, 1),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 10, 0, 1, 0, 0, 0),
    RS_End(),
};

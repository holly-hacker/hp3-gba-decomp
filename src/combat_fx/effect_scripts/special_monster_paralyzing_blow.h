// Chance to paralyze the target on a successful attack (Suits of Armor, Lupin Werewolf).
const u8 g_abSpecialMonsterParalyzingBlowScript[] = {
    BS_StatusEffect(BSSTATUS_ParalyzeMonster, 25, 0),
    BS_End(),
};

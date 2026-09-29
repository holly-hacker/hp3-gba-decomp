// Chance to poison the target on a successful attack (venomous spiders, snake, toads).
const u8 g_abSpecialMonsterPoisonBiteScript[] = {
    BS_StatusEffect(BSSTATUS_Poisoned, 8, 0),
    BS_End(),
};

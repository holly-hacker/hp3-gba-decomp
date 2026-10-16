// Goyle's special attack animation; no status effect.
const u8 g_abSpecialMonsterGoyleAttackScript[] = {
    BS_TeleportToSlotPosition(2),
    BS_WaitFrames(1),
    BS_SetActorAnim(55, 0),
    BS_WaitFrames(1),
    BS_ShowActor(),
    BS_AdvanceAttackOutcome(),
    BS_AdvanceAttackOutcome(),
    BS_WaitForCounter(),
    BS_AdvanceAttackOutcome(),
    BS_AdvanceAttackOutcome(),
    BS_AdvanceAttackOutcome(),
    BS_End(),
};

const u8 g_abEffect1Script[] = {
    BS_SnapToCaster(0),
    BS_SetActorAnim(1, 0),
    BS_SetOamPriority(0),
    BS_ShowActor(),
    BS_PlaySound(73),
    BS_WaitForCounter(),
    BS_End(),
};

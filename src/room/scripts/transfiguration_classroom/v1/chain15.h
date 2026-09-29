const u8 g_abRoom03V1Chain15[] = {
    RS_ArmChainYield(1),
    // "Mr. Potter, Miss Granger, I shall enter a maze. You must find your own way into the maze and locate me as quickly as you can. Ready... Begin!"
    RS_ShowRoomDialog(200),
    RS_PlayTileObjectAnimation(2, 0, 9),
    RS_RespawnRowAndRunChain(5, 0),
    RS_QueueTileObjectMove(5, 0, 0, 0, 1500, 0),
    RS_DespawnTileObject(2, 0),
    RS_Unk02(5, 0, 3),
    RS_Unk02(0, 255, 2),
    RS_RespawnRowAndRunChain(3, 0),
    RS_DespawnTileObject(7, 1),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(5, 0, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_End(),
};

// Try to go to the cellar before the relevant quest is active
const u8 g_abRoom42TryVisitCellar[] = {
    // "I don't think I should be going down into the cellar just yet."
    RS_ShowRoomDialog(3),
    RS_End(),
};

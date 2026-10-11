#include "types.h"
#include "font.h"
#include "text.h"
#include "game/game_modes.h"

#ifdef VERSION_JP
#define CARD_NAME_Y 4
#else
#define CARD_NAME_Y 3
#endif

// Draws the card's name and its description.
void DrawFolioCardDetailText(void)
{
    u32 tileCursor = 1;
    u8 *pText[1];

    SelectTextFont(3, 0, 0);
    SetTextLineHeight(GetTextLineHeight());
    pText[0] = (u8 *)GetDialogText(g_GameModeStackContext.dwCurrentGameModeArg2 + 0x412);
    tileCursor = DrawTextLines(tileCursor, 0x78, CARD_NAME_Y, 0xF0, 0x18, pText, 1);

    SelectTextFont(1, 0, -1);
    SetTextLineHeight(GetTextLineHeight());
    pText[0] = (u8 *)GetDialogText(g_GameModeStackContext.dwCurrentGameModeArg2 + 0x445);
    PrintTextBox(tileCursor, 6, 0x20, 0x68, pText[0], 0);
}

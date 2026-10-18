#include "types.h"
#include "background.h"
#include "actor.h"
#include "choose_party_member.h"
#include "font.h"
#include "modes.h"
#include "text.h"
#include "map.h"

static inline void DrawPanel(u16 tileOffset)
{
    WriteBgGraphicTilemap(2, g_ChooseCharacterState.pBgTilemap, tileOffset, 0, 0, g_dwChooseCharacterBgRow);
}

static inline void PlaceOptionActor(s32 option)
{
    u32 cursor = g_GameModeStackContext.dwCurrentGameModeArg2;

    SetActorPosition(g_ChooseCharacterState.apOptionActors[option],
                     g_aaabChooseCharacterActorX[g_ChooseCharacterState.bStageRow][cursor][option],
                     0x40);
}

// Redraws the character name, the objective text and the option actor positions for the
// cursor position.
void DrawChooseCharacterSelection(void)
{
    u32 textId = 0;
    u8 *pText;

    DrawPanel(0x200);

    SetTextTargetFromBgControl(g_dwBg2Control);
    SelectTextFont(5, 0, -1);
    switch (g_aabChooseCharacterOptionRows[g_ChooseCharacterState.bStageRow]
                                                 [g_GameModeStackContext.dwCurrentGameModeArg2])
    {
    case 1:
        textId = 0x907;  // "Harry"
        break;
    case 2:
        textId = 0x909;  // "Hermione"
        break;
    case 3:
        textId = 0x90A;  // "Harry and Hermione"
        break;
    case 4:
        textId = 0x908;  // "Ron"
        break;
    case 5:
        textId = 0x90B;  // "Harry and Ron"
        break;
    case 6:
        textId = 0x910;  // "Ron and Hermione"
        break;
    }
    pText = GetDialogText(textId);
    DrawStringAligned(0x222, 0x78, (g_dwChooseCharacterBgRow + 2) * 8, pText, 1);

    SelectTextFont(7, 0, -1);
    textId = g_aadwChooseCharacterObjectiveTextIds[g_ChooseCharacterState.bStageRow]
                                                  [g_GameModeStackContext.dwCurrentGameModeArg2];
    pText = GetDialogText(textId);
    PrintTextBox(0x280, 0x78, (g_dwChooseCharacterBgRow + 4) * 8, 0xE8, pText, 1);

    PlaceOptionActor(0);
    PlaceOptionActor(1);
    PlaceOptionActor(2);
}

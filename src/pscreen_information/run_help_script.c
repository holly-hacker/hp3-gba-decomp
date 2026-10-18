#include "background.h"
#include "font.h"
#include "text.h"
#include "cursor.h"
#include "pscreen_information.h"

void RunHelpScript(const u32 *pScript)
{
    u32 i;
    u32 command;
    s32 (*isAvailable)(const u32 *pTextId);
    const u8 *text;

    ClearHelpScreen();
    i = 0;
    for (;;)
    {
        command = pScript[i++];
        switch (command & 0xFF)
        {
        case HelpOpHeader: // Render the header text at the top
            g_HelpState.bPageKind = command >> 8;
            switch (g_HelpState.bPageKind)
            {
            case HelpPageText:
                g_HelpState.pNextPage = NULL;
                g_HelpState.pPrevPage = NULL;
                break;
            case HelpPageMenu:
                g_HelpState.aPageStack[g_HelpState.bPageDepth].pPage = pScript;
                g_HelpState.pCursor = SpawnMenuCursorActor(4);
                g_HelpState.pCursor->pfnTick = TickHelpMenuCursor;
                g_HelpState.pCursor->oam.objMode = 1;
                g_HelpState.pCursor->oam.hFlip = 1;
                SetMenuCursorPosition(g_HelpState.pCursor, 0x12, 0x22);
                break;
            }
            break;

        case HelpOpMenuLinkIf: // Render a link if a callback returns true
            g_HelpState.aEntries[g_HelpState.dwEntryCount].dwTextId = pScript[i++];
            g_HelpState.aEntries[g_HelpState.dwEntryCount].pPage = (const u32 *)pScript[i++];
            isAvailable = (s32 (*)(const u32 *))pScript[i++];
            g_HelpState.aEntries[g_HelpState.dwEntryCount].bAvailable
                = isAvailable(&g_HelpState.aEntries[g_HelpState.dwEntryCount].dwTextId);
            DrawHelpMenuEntry(g_HelpState.dwEntryCount,
                              g_HelpState.dwEntryCount == g_HelpState.bSelectedEntry ? 6 : 0);
            g_HelpState.dwEntryCount++;
            break;

        case HelpOpMenuLink: // Render a link
            g_HelpState.aEntries[g_HelpState.dwEntryCount].dwTextId = pScript[i++];
            g_HelpState.aEntries[g_HelpState.dwEntryCount].pPage = (const u32 *)pScript[i++];
            g_HelpState.aEntries[g_HelpState.dwEntryCount].bAvailable = 1;
            DrawHelpMenuEntry(g_HelpState.dwEntryCount,
                              g_HelpState.dwEntryCount == g_HelpState.bSelectedEntry ? 6 : 0);
            g_HelpState.dwEntryCount++;
            break;

        case HelpOpSelectEntry: // Unused, forces initial selected entry
            g_HelpState.bSelectedEntry = command >> 8;
            break;

        case HelpOpText: // Renders a text block
        {
            u32 x = (command >> 8) & 0xFF;
            u32 y = (command >> 16) & 0xFF;

            command = pScript[i++];
            DrawHelpTextBox(x, y, command & 0xFF, (command >> 8) & 0xFF, pScript[i++], 0);
            break;
        }

        case HelpOpTitle: // Renders a single-line title. Looks like text, but slightly inset
            DrawHelpTextBox(0x10, 0x20, 0xD0, 0x10, pScript[i++], 0);
            break;

        case HelpOpPageNumber: // Renders a page number at the bottom of the page
        {
            u32 current;
            u32 total;

            ClearBgTilemapRect(2, 0xB, 0x12, 9, 1);
            current = (command >> 8) & 0xFF;
            total = (command >> 16) & 0xFF;
            SelectTextFont(2, 0, 0);
            SetTextMacro1Number(current);
            SetTextMacro2Number(total);
            text = GetDialogText(0x8EF);  // "@1/@2"
            g_HelpState.dwTextTileCursor
                = DrawTextLines(g_HelpState.dwTextTileCursor, 0x78, 0x90, 0x30, 0x10, &text, 1);
            break;
        }

        case HelpOpSetTextTileCursor: // Sets the current text cursor to a certain position
            g_HelpState.dwTextTileCursor = command >> 16;
            break;

        case HelpOpSprite: // Puts a sprite on screen, such as the forward/backward arrows
        {
            u32 assetIndex = (command >> 8) & 0xFF;
            u32 x = (command >> 16) & 0xFF;
            u32 y = (command >> 24) & 0xFF;

            SpawnHelpPageSprite(x, y, assetIndex);
            break;
        }

        case HelpOpNextPage: // Sets which page is the next
            g_HelpState.pNextPage = (const u32 *)pScript[i++];
            break;

        case HelpOpPrevPage: // Sets which page is the previous
            g_HelpState.pPrevPage = (const u32 *)pScript[i++];
            break;

        case HelpOpNop:
            break;

        case HelpOpEnd: // Marker to indicate the end of a page
            return;
        }
    }
}

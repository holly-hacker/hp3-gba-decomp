#include "background.h"
#include "color.h"
#include "font.h"
#include "text.h"
#include "text_actor.h"
#include "pscreen_information.h"
#include "gen/graphics/cutscenes.h"

#ifdef VERSION_JP
#define HELP_TITLE_Y 4
#else
#define HELP_TITLE_Y 3
#endif

void SpawnHelpScreenTitle(void)
{
    const u8 *text;

    QueueObjPaletteLoad(GRAPHIC_BLOB_PALETTE_COLORS(gMenuBg3Graphic), 0, 0x10);
    SelectTextFont(3, 0, 0);
    text = GetDialogText(0xA46);  // "Help"
    g_HelpState.pTitleActor = SpawnUnslottedTextActor(&text);
    g_HelpState.pTitleActor->oam.priority = 0;
    SetTextActorCenterPosition(g_HelpState.pTitleActor, 0x78, HELP_TITLE_Y);
}

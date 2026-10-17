#include "types.h"
#include "cheat.h"
#include "combat_2.h"
#include "modes.h"
#include "save.h"
#include "overworld/room.h"
#include "commands.h"

// Cheat menu level args packed in dwCurrentGameModeArg2, one byte each.
#define CHEAT_ARG_LEVEL_CHAR1 ((u8)g_GameModeStackContext.dwCurrentGameModeArg2)
#define CHEAT_ARG_LEVEL_CHAR2 ((u8)(g_GameModeStackContext.dwCurrentGameModeArg2 >> 8))
#define CHEAT_ARG_LEVEL_CHAR0 ((u8)(g_GameModeStackContext.dwCurrentGameModeArg2 >> 16))
#define CHEAT_ARG_STORY_STAGE ((u8)(g_GameModeStackContext.dwCurrentGameModeArg2 >> 24))

void ResetCheatPartyFromArgs(void)
{
    u32 i;

    ResetCharacterToLevel(0, CHEAT_ARG_LEVEL_CHAR0);
    ResetCharacterToLevel(1, CHEAT_ARG_LEVEL_CHAR1);
    ResetCharacterToLevel(2, CHEAT_ARG_LEVEL_CHAR2);

    if (g_abQuestEventState[QUEST_STORY_STAGE] != CHEAT_ARG_STORY_STAGE)
    {
        g_abQuestEventState[QUEST_STORY_STAGE] = CHEAT_ARG_STORY_STAGE;
        for (i = 0xE0; i < 0x100; i++)
            g_abQuestEventState[i] = 0;
        g_abQuestEventState[QUEST_STORY_STAGE] = CHEAT_ARG_STORY_STAGE;
    }
}

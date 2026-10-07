#include "types.h"
#include "game/game_modes.h"
#include "menu/fred_and_georges_shop.h"

void UpdateFredAndGeorgesShop(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        sub_08040F04();
        break;
    case 2:
        sub_0804132C();
        break;
    case 4:
        sub_080407CC();
        break;
    case 6:
        sub_08040A38();
        break;
    case 8:
        sub_08041590();
        break;
    case 10:
        sub_080416CC();
        break;
    case 12:
        sub_08040CA4();
        break;
    case 14:
        sub_080418BC();
        break;
    }
}

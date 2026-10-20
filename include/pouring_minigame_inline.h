#pragma once

#include "types.h"
#include "modes.h"
#include "random.h"
#include "pouring_minigame.h"

// StartServePumpkinJuiceGame inlines the customer spawning below; the file that emits
// the out-of-line copy defines the linkage macro as empty.
#ifndef SPAWN_SERVE_PUMPKIN_JUICE_CUSTOMERS_LINKAGE
#define SPAWN_SERVE_PUMPKIN_JUICE_CUSTOMERS_LINKAGE extern inline
#endif

// Queues 1 to dwRound customers plus the difficulty (arg 3) in every lane.
SPAWN_SERVE_PUMPKIN_JUICE_CUSTOMERS_LINKAGE void SpawnServePumpkinJuiceCustomers(void)
{
    s32 lane;
    u32 i;

    for (lane = 0; lane < SERVE_PUMPKIN_JUICE_LANE_COUNT; lane++)
    {
        g_ServePumpkinJuice.adwCustomerCount[lane] = 0;
        i = 0;
        while (i < Mt19937RandRange(1, g_ServePumpkinJuice.dwRound) + g_GameModeStackContext.dwCurrentGameModeArg3)
        {
            u32 type = PickServePumpkinJuiceCustomerType();

            i++;
            SpawnServePumpkinJuiceCustomer(lane, type, i);
        }
    }
}

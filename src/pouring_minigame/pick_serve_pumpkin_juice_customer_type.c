#include "types.h"
#include "random.h"
#include "pouring_minigame.h"

// Types 2-5 may be in play more than once; the others only once at a time.
u32 PickServePumpkinJuiceCustomerType(void)
{
    u32 type;

    while (1)
    {
        type = Mt19937RandMax(SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT - 1);
        if (type >= 2 && type <= 5)
        {
            g_ServePumpkinJuice.dwCustomerTypesInUse |= g_adwServePumpkinJuiceCustomerTypeBits[type];
            return type;
        }
        else if (!(g_ServePumpkinJuice.dwCustomerTypesInUse & g_adwServePumpkinJuiceCustomerTypeBits[type]))
        {
            g_ServePumpkinJuice.dwCustomerTypesInUse |= g_adwServePumpkinJuiceCustomerTypeBits[type];
            return type;
        }
    }
}

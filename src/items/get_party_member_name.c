#include "types.h"
#include "combat.h"
#include "text.h"
#include "items.h"

u8 *GetPartyMemberName(s32 character)
{
    switch (character)
    {
    case Harry:
        return GetDialogText(0x907);  // "Harry"
    case Hermione:
        return GetDialogText(0x909);  // "Hermione"
    case Ron:
        return GetDialogText(0x908);  // "Ron"
    }

    return NULL;
}

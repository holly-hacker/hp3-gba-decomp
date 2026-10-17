#include "types.h"
#include "pscreen_folio_universitas_inline.h"
#include "items.h"

// Nonzero when all ten cards of a Folio Universitas row have been seen.
u32 IsFolioPageGroupComplete(u32 pageGroupId)
{
    u32 first;
    u32 card;
    u32 end;

    first = pageGroupId * 10;
    end = first + 10;
    for (card = first; card < end; card++)
    {
        if (!FOLIO_CARD_SEEN(card))
            return 0;
    }

    return 1;
}

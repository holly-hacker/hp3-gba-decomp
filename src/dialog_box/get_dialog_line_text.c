#include "types.h"
#include "font.h"
#include "text.h"
#include "dialog.h"
#include "dialog_box.h"

const u8 *GetDialogLineText(u32 textId)
{
    s32 number;

    if (g_aDialogTextInfo[textId].pMacroNumber != NULL)
    {
        number = *g_aDialogTextInfo[textId].pMacroNumber;
        if (number < 0)
            number = -number;
        SetTextMacro1Number(number);
    }
    return GetDialogText(textId);
}

#pragma once

#include "types.h"
#include "object.h"

// Text-and-portrait cutscenes (GameModes Intro through GameCompletedReplayCutscene
// share one init/update/exit set); Credits shares the exit function and the
// cutscene object. The cutscene is selected by g_dwLinearCutsceneIndex,
// GameMode - Credits.
extern Object *g_pLinearCutsceneObject;  // 0x030028B8
extern u8 *g_pLinearCutsceneText;        // 0x030028B4: unread remainder of the cutscene's text
extern u32 g_dwLinearCutsceneIndex;      // 0x030028BC

extern void sub_0801D77C(u32 cutsceneIndex);
extern void sub_0801D6DC(void);

// One entry per cutscene (index 0 is the credits): the BG0 graphic, the first
// dialog text id, and how many text lines or pages it has.
typedef struct {
    const u8 *pGraphic;  // 0x00
    u32 dwTextId;        // 0x04
    u32 dwLineCount;     // 0x08; 1 for a single-page cutscene
} LinearCutsceneEntry;

extern const LinearCutsceneEntry g_aLinearCutsceneTable[10];  // 0x0805E028
extern const u32 g_dwLinearCutsceneBg0Control;                // 0x0805E020
extern const u32 g_dwLinearCutsceneBg1Control;                // 0x0805E024

// Credits scroll state.
extern u32 g_dwCreditsScrollRow;   // 0x030028A8: last text row the scroll reached
extern u32 g_dwCreditsLine;        // 0x030028AC: next text line to draw
extern u32 g_dwCreditsTileCursor;  // 0x030028B0: next free text tile

extern void sub_08007F84(u32 bg, s32 *pOut0, s32 *pOut1);

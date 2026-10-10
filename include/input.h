#pragma once

#include "types.h"
#include "direction.h"

// Controller input state maintained by UpdateKeyInput, called once per
// game-loop iteration from TickGameModeStack, and the menu-cursor helpers
// built on it. See docs/memory-map/input.md.

// g_wKeys* bits (KEYINPUT layout).
enum {
    KeyA      = 0x001,
    KeyB      = 0x002,
    KeySelect = 0x004,
    KeyStart  = 0x008,
    KeyRight  = 0x010,
    KeyLeft   = 0x020,
    KeyUp     = 0x040,
    KeyDown   = 0x080,
    KeyR      = 0x100,
    KeyL      = 0x200,
};

extern u16 g_wKeysHeld;             // 0x030034EC: current held-key bitmask
extern u16 g_wKeysHeldPrevious;     // 0x030034EE: g_wKeysHeld from the previous frame
extern u16 g_wKeysPressed;          // 0x030034F0: keys newly pressed this frame
extern u16 g_wKeysReleased;         // 0x030034F2: keys newly released this frame
extern u16 g_wInputDisabled;        // 0x030034F4: nonzero forces all key state to 0

extern u16 g_awPlayerKeysHeld[2];          // 0x030034F6: per-player held-key masks, link input path
extern u16 g_awPlayerKeysHeldPrevious[2];  // 0x030034FA: previous-frame counterpart of the above
extern u16 g_awPlayerKeysPressed[2];       // 0x030034FE: per-player newly-pressed masks
extern u16 g_awPlayerKeysReleased[2];      // 0x03003502: per-player newly-released masks
// 0x03003506: per-player counterpart of g_wInputDisabled, written alongside
// it by EnableKeyInput and the uncalled DisableKeyInput; no reader found.
extern u16 g_awPlayerInputDisabled_candidate[2];

// Scrolling list/grid cursor state, written only by InitScrollList,
// InitScrollGrid and the StepScroll* functions. A list row is
// g_dwScrollListTopRow + g_dwScrollListCursorRow.
extern u32 g_dwScrollListRowCount;     // 0x0300350C
extern u32 g_dwScrollListTopRow;       // 0x03003510: first visible row
extern u32 g_dwScrollListCursorRow;    // 0x03003514: cursor row within the visible window
extern u32 g_dwScrollGridColumn;       // 0x03003520
extern u32 g_dwScrollGridItemCount;    // 0x03003524
extern u32 g_dwScrollGridColumnCount;  // 0x03003528
extern u32 g_dwScrollGridVisibleRows;  // 0x0300352C

// Direction of the held D-pad, indexed by (keys & 0xF0) >> 4;
// DirectionNone when no single direction is held.
extern const s8 g_abDpadDirection[16];  // 0x08060E7C

extern void UpdateKeyInput(void);
extern u32 StepScrollListSelection(u32 visibleRows, s32 wrap, u32 player);
extern u32 StepScrollGridRow(s32 wrap, u32 player);
extern u32 StepScrollGridColumn(s32 wrap, u32 player);
extern void InitInputSystem(void);
extern void ResetKeyInput(void);
extern void EnableKeyInput(void);
extern void DisableKeyInput(void);
extern Direction GetDpadDirection(void);

// Step *pValue by one within [min, max] when keys contains a decrement or
// increment key; the variants use one player's pressed or held keys. At
// either end it wraps to the other end if wrap is nonzero. Return whether
// *pValue changed. Inline definitions are in input_inline.h.
extern u32 StepCursorByKeys(u32 *pValue, u32 min, u32 max, s32 wrap, u16 keys, u16 decrementKeys, u16 incrementKeys);
extern u32 StepCursorUpDownHeld(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player);
extern u32 StepCursorUpDown(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player);
extern u32 StepCursorLeftRightHeld(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player);
extern u32 StepCursorLeftRight(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player);
extern u32 StepCursorShoulderHeld(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player);
extern u32 StepCursorShoulder(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player);

extern void ToggleFlag(u32 *pFlag);
extern u8 GetAnyPlayerKeysHeld(void);
extern u8 GetAnyPlayerKeysPressed(void);
extern void InitScrollList(u32 rowCount);
extern void InitScrollGrid(u32 selection, u32 itemCount, u32 columnCount, u32 visibleRows);

extern u16 g_awSerialKeysReceived[2];  // 0x03005A0C: per-player key masks received over the link cable

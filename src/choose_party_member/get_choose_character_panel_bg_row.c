#include "types.h"
#include "choose_party_member.h"
#include "overworld/room.h"

// The BG tile row the panel is drawn at, from the camera's Y within its 256-pixel wrap.
s32 GetChooseCharacterPanelBgRow(void)
{
    s32 position[2];

    GetCameraPosition(position);
    position[1] &= 0xFF;
    return (position[1] - 0x40) >> 3;
}

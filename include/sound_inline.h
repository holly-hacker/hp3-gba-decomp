#pragma once

#include "sound.h"

// The ROM inlines this into PlayMusicModule and also keeps an out-of-line copy;
// the file that emits that copy defines the linkage macro as empty.
#ifndef SET_UNREAD_AUDIO_VALUE_LINKAGE
#define SET_UNREAD_AUDIO_VALUE_LINKAGE extern inline
#endif

SET_UNREAD_AUDIO_VALUE_LINKAGE void SetUnreadAudioValue(u8 value)
{
    g_bUnreadAudioValue = value;
}

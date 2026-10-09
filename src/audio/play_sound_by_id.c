#include "types.h"
#include "graphics/audio.h"
#include "mt19937.h"

// Plays sound `id` and returns the Krawall handle, or 0 when a random variant plays nothing.
// A variant row draws Mt19937RandMax2(7): the visual RNG cursor, not the gameplay one.
s32 PlaySoundById(s32 id)
{
    const SoundConfigRow *row;
    const SoundConfigRow *table;
    u8 variant;
    s32 handle;

    handle = 0;
    table = g_aSoundConfig;
    row = table + id;
    switch (row->mode)
    {
    case SoundModeSample:
        handle = kramPlayVeneer(KrawallSamples[g_aSoundSamples[row->index].sampleIndex], 1, 0);
        kramSetFreqVeneer(handle, g_aSoundSamples[row->index].freq);
        break;

    case SoundModeVariants:
        variant = Mt19937RandMax2(7);
        if (g_aSoundVariants[row->index][variant].sampleIndex != SoundVariantNone)
        {
            handle = kramPlayVeneer(KrawallSamples[g_aSoundVariants[row->index][variant].sampleIndex], 1, 0);
            kramSetFreqVeneer(handle, g_aSoundVariants[row->index][variant].freq);
        }
        break;
    }
    return handle;
}

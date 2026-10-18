#include "types.h"
#include "sound.h"
#include "random.h"
#include "3rd_party/krawall.h"

s32 PlaySoundByIdUnlessActive_candidate(s32 id, s32 handle)
{
    const SoundConfigRow *row;
    const SoundConfigRow *table;
    u8 variant;
    s32 newHandle;

    newHandle = 0;
    if (!IsSoundActive_candidate(handle))
    {
        table = g_aSoundConfig;
        row = table + id;
        switch (row->mode)
        {
        case SoundModeSample:
            newHandle = kramPlay(samples[g_aSoundSamples[row->index].sampleIndex], 1, 0);
            kramSetFreq(newHandle, g_aSoundSamples[row->index].freq);
            break;

        case SoundModeVariants:
            variant = Mt19937RandMax2(7);
            if (g_aSoundVariants[row->index][variant].sampleIndex != SoundVariantNone)
            {
                newHandle = kramPlay(samples[g_aSoundVariants[row->index][variant].sampleIndex], 1, 0);
                kramSetFreq(newHandle, g_aSoundVariants[row->index][variant].freq);
            }
            break;
        }
        return newHandle;
    }
    return handle;
}

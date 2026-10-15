#include "types.h"
#include "decompress.h"

u32 GetResourceDecompressedSize(const void *pResource)
{
    return ((const ResourceHeader *)pResource)->size;
}

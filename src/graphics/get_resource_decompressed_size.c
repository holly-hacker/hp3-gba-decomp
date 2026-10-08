#include "types.h"
#include "graphics/graphics.h"

u32 GetResourceDecompressedSize(const void *pResource)
{
    return ((const ResourceHeader *)pResource)->size;
}

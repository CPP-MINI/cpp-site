#include <cstddef>
#include "memory_manipulation.h"

namespace l2 {

std::byte* memcpy(std::byte* dst, const std::byte* src, size_t size)
{   
    std::byte* ret = dst;
    for (size_t i = 0; i < size; ++i)
        *dst++ = *src++;
    return ret;
}

std::byte* memmove(std::byte* dst, const std::byte* src, size_t size)
{
    std::byte* ret = dst;

    if (dst == src)
        return dst;

    if (dst > src)
    {
        // Buffers are disjoint => trivial memcpy
        if ((size_t)(dst - src) >= size)
            return memcpy(dst, src, size);

        // Copying overlaping part first (the end of src is at the begining of dst)
        size_t offset = size - 1;
        for (; src + offset >= dst; --offset)
            *(dst + offset) = *(src + offset);
        
        // Copy non-overlaping part with memcpy
        memcpy(dst, src, offset + 1);
        return ret;
    }
    else {
        // Buffers are disjoint => trivial memcpy
        if ((size_t)(src - dst) >= size)
            return memcpy(dst, src, size);

        // Copy overlaping part first (the begining of src is the end of dst)
        size_t offset = 0;
        for (;src + offset < dst + size; ++offset)
            *(dst + offset) = *(src + offset);

        // Copy non-overlaping part with memcpy
        memcpy(dst+offset, src+offset, size - offset);
        return ret;
    }
}

}

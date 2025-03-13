#pragma once

#include <cstddef>

namespace l2
{

std::byte* memcpy(std::byte* dst, const std::byte* src, size_t size);

std::byte* memmove(std::byte* dst, const std::byte* src, size_t size);

}  // namespace l2

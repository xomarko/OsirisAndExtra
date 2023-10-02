#pragma once

#include <cstdint>

#include "Constants/Platform.h"

template <typename T> class UtlVector;

class EconItemView {
public:
    std::uintptr_t getAttributeList() noexcept
    {
        return std::uintptr_t(this) + WIN32_LINUX(0x244, 0x2F8);
    }

    UtlVector<void*>& customMaterials() noexcept
    {
        return *reinterpret_cast<UtlVector<void*>*>(std::uintptr_t(this) + WIN32_LINUX(0x14, 0x28));
    }

    UtlVector<void*>& visualDataProcessors() noexcept
    {
        return *reinterpret_cast<UtlVector<void*>*>(std::uintptr_t(this) + WIN32_LINUX(0x230, 0x2D8));
    }

    void clearInventoryImageRGBA() noexcept;
};
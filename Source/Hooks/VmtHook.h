#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

#include "../SDK/Constants/Platform.h"

class VmtHook {
public:
    void init(void* base) noexcept;
    void restore() const noexcept;
    void hookAt(std::size_t index, void* fun) const noexcept;

    template<typename T, std::size_t Idx, typename ...Args>
    constexpr auto getOriginal(Args... args) const noexcept
    {
        return reinterpret_cast<T(__thiscall*)(void*, Args...)>(oldVmt[Idx]);
    }

    template<typename T, std::size_t Idx, typename ...Args>
    constexpr auto callOriginal(Args... args) const noexcept
    {
        return getOriginal<T, Idx>(args...)(base, args...);
    }

private:
    void* base;
    std::size_t length;
    std::unique_ptr<std::uintptr_t[]> oldVmt;
};

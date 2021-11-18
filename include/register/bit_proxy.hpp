#pragma once

#include "register/common/types.hpp"

namespace reg
{
    template<template<size_t, typename> class Register, size_t Size, typename AccessModeTag>
    class bit_t
    {
    public:
        bit_t(Register<Size, AccessModeTag>* reg, size_t num) : owner{ reg }, bit_num{ num } { }

    private:
        Register<Size, AccessModeTag>* owner;
        size_t bit_num;
    };
}  // namespace reg
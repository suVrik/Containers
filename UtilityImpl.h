#pragma once

#include "Utility.h"

namespace kw
{

template <class T>
inline typename std::remove_reference_t<T>&& Move(T&& value)
{
    return static_cast<std::remove_reference_t<T>&&>(value);
}

template <class T>
inline T&& Forward(std::remove_reference_t<T>& value)
{
    return static_cast<T&&>(value);
}

template <class T>
inline T&& Forward(std::remove_reference_t<T>&& value)
{
    return static_cast<T&&>(value);
}

} //namespace kw

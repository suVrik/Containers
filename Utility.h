#pragma once

#include "TypeTraits.h"

namespace kw
{

// TODO: Description.
template <class T>
typename TypeTraits::RemoveReference<T>&& Move(T&& value);

// TODO: Description.
template <class T>
inline T&& Forward(TypeTraits::RemoveReference<T>& value);

// TODO: Description.
template <class T>
inline T&& Forward(TypeTraits::RemoveReference<T>&& value);

// TODO: Description.
template<class T>
struct Hash
{
	// Note that by default types don't have any hash functions defined.
};

// TODO: Description.
template<class T>
struct EqualTo
{
	// Returns whether one object is equal to another. Default implementation makes use of operator==.
	bool operator()(const T& Lhs, const T& Rhs) const;
};

// TODO: Description
template<class T>
struct LessThan
{
	// Returns whether one object is less than another. Default implementation makes use of operator<.
	bool operator()(const T& Lhs, const T& Rhs) const;
};

} //namespace kw

#include "UtilityImpl.h"

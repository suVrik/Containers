#pragma once

#include "ContainerUtils.h"

#include <concepts>

namespace kw {

// Specifies whether the given types are the same.
template<class T, class U>
concept SameAs = std::same_as<T, U>;

// Specifies whether the given type Derived is derived from the specified type Base.
template<class Derived, class Base>
concept DerivedFrom = std::derived_from<Derived, Base>;

// Specifies whether the given type From is convertible to the specified type To.
template<class From, class To>
concept ConvertibleTo = std::convertible_to<From, To>;

// Specifies whether the given types share a common reference type.
template<class T, class U>
concept CommonReferenceWith = std::common_reference_with<T, U>;

// Specifies whether the given types share a common type (e.g. for int and double that'd be double).
template<class T, class U>
concept CommonWith = std::common_with<T, U>;

// Specifies whether the given type is an integral type.
template<class T>
concept Integral = std::integral<T>;

// Specifies whether the given type is a signed integral type.
template<class T>
concept SignedIntegral = std::signed_integral<T>;

// Specifies whether the given type is an unsigned integral type.
template<class T>
concept UnsignedIntegral = std::unsigned_integral<T>;

// Specifies whether the given type is a floating-point type.
template<class T>
concept FloatingPoint = std::floating_point<T>;

// Specifies whether the given type LHS is assignable from the specified type RHS.
template<class LHS, class RHS>
concept AssignableFrom = std::assignable_from<LHS, RHS>;

// Specifies whether the given type is destructible.
template<class T>
concept Destructible = std::destructible<T>;

// Specifies whether the given type is constructible from the specified set of argument types.
template<class T, class... Args>
concept ConstructibleFrom = std::constructible_from<T, Args...>;

// Specifies whether the given type can be default constructed.
template<class T>
concept DefaultInitializable = std::default_initializable<T>;

// Specifies whether the given type can be move constructed.
template<class T>
concept MoveConstructible = std::move_constructible<T>;

// Specifies whether the given type can be copy constructed and move constructred.
template<class T>
concept CopyConstructible = std::copy_constructible<T>;

// Specifies whether an object of the given type can be equality compared with another object of the same type.
template<class T>
concept EqualityComparable = std::equality_comparable<T>;

// Specifies whether an object of the given type T can be equality compared with an object of the specified type U.
template<class T, class U>
concept EqualityComparableWith = std::equality_comparable_with<T, U>;

// Specifies whether the given callable type can be invoked with the specified set of argument types.
template<class F, class... Args>
concept Invocable = std::invocable<F, Args...>;

// Specifies whether the given types are the same with possibly different const specifier.
template<class T, class U>
concept SameAsConstless = std::same_as<std::remove_const_t<T>, std::remove_const_t<U>>;

// Specifies whether the given type T is an iterator type over a range of elements of the specified type U.
template<class T, class U>
concept ForwardIterator = requires(T Value)
{
    { *Value } -> SameAsConstless<U&>;
    { ++Value } -> SameAs<T&>;
    { Value++ } -> SameAs<T>;
    { Value == Value } -> SameAs<bool>;
    { Value != Value } -> SameAs<bool>;
};

// Specifies whether the given type T is an iterator type over a contiguous range of elements of the specified type U.
template<class T, class U>
concept ContiguousIterator = ForwardIterator<T, U> && requires(T Value)
{
    { Value - Value } -> SameAs<ptrdiff_t>;
};

// Specifies whether the given type T is a container or a view over elements of specified type U.
template<class T, class U>
concept ForwardIterable = requires(const T& Value)
{
	{ ContainerUtils::GetBegin(Value) } -> ForwardIterator<U>;
	{ ContainerUtils::GetEnd(Value) } -> ForwardIterator<U>;
};

// Specifies whether the given type T is a contiguous container or a view over elements of specified type U.
template<class T, class U>
concept ContiguousIterable = requires(const T& Value)
{
	{ ContainerUtils::GetBegin(Value) } -> ContiguousIterator<U>;
	{ ContainerUtils::GetEnd(Value) } -> ContiguousIterator<U>;
};

} // namespace kw

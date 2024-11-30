#pragma once

#include <type_traits>

namespace kw
{

// TODO: Description.
template<class T, T V>
using IntegralConstant = std::integral_constant<T, V>;

// TODO: Description.
template<bool V>
using BoolConstant = std::bool_constant<V>;

// TODO: Description.
using FalseType = std::false_type;

// TODO: Description.
using TrueType = std::true_type;

// TODO: Description.
template<class T>
using RemoveConst = std::remove_const_t<T>;

// TODO: Description.
template<class T>
using RemoveCV = std::remove_cv_t<T>;

// TODO: Description.
template<class T>
using RemoveVolatile = std::remove_volatile_t<T>;

// TODO: Description.
template<class T>
using AddCv = std::add_cv_t<T>;

// TODO: Description.
template<class T>
using AddConst = std::add_const_t<T>;

// TODO: Description.
template<class T>
using AddVolatile = std::add_volatile_t<T>;

// TODO: Description.
template<class T>
using RemoveReference = std::remove_reference_t<T>;

// TODO: Description.
template<class T>
using AddLvalueReference = std::add_lvalue_reference_t<T>;

// TODO: Description.
template<class T>
using AddRvalueReference = std::add_rvalue_reference_t<T>;

// TODO: Description.
template<class T>
using RemovePointer = std::remove_pointer_t<T>;

// TODO: Description.
template<class T>
using AddPointer = std::add_pointer_t<T>;

// TODO: Description.
template<class T>
using MakeSigned = std::make_signed_t<T>;

// TODO: Description.
template<class T>
using MakeUnsigned = std::make_unsigned_t<T>;

// TODO: Description.
template<class T>
using RemoveExtent = std::remove_extent_t<T>;

// TODO: Description.
template<class T>
using RemoveAllExtents = std::remove_all_extents_t<T>;

// TODO: Description.
template<class T>
using Decay = std::decay_t<T>;

// TODO: Description.
template<class T>
using RemoveCVRef = std::remove_cvref_t<T>;

// TODO: Description.
template<bool V, class T = void>
using EnableIf = std::enable_if_t<V, T>;

// TODO: Description.
template<bool V, class T, class F>
using Conditional = std::conditional_t<V, T, F>;

// TODO: Description.
template<class... T>
using CommonType = std::common_type_t<T...>;

// TODO: Description.
template<class T>
using UnderlyingType = std::underlying_type_t<T>;

// TODO: Description.
template<class T>
using InvokeResult = std::invoke_result_t<T>;

// TODO: Description.
template<class T>
using Void = std::void_t<T>;

// TODO: Description.
template<class T>
using TypeIdentity = std::type_identity_t<T>;

namespace TypeTraits
{

// TODO: Description.
template<class T>
static constexpr bool IsVoid = std::is_void_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsNullPointer = std::is_null_pointer_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsIntegral = std::is_integral_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsFloatingPoint = std::is_floating_point_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsArray = std::is_array_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsEnum = std::is_enum_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsUnion = std::is_union_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsClass = std::is_class_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsFunction = std::is_function_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsPointer = std::is_pointer_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsLvalueReference = std::is_lvalue_reference_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsRvalueReference = std::is_rvalue_reference_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsMemberObjectPointer = std::is_member_object_pointer_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsMemberFunctionPointer = std::is_member_function_pointer_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsFundamental = std::is_fundamental_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsArithmetic = std::is_arithmetic_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsScalar = std::is_scalar_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsObject = std::is_object_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsCompound = std::is_compound_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsReference = std::is_reference_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsMemberPointer = std::is_member_pointer_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsConst = std::is_const_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsVolatile = std::is_volatile_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsTrivial = std::is_trivial_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsTriviallyCopyable = std::is_trivially_copyable_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsStandardLayout = std::is_standard_layout_v<T>;

// TODO: Description.
template<class T>
static constexpr bool HasUniqueObjectRepresentations = std::has_unique_object_representations_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsEmpty = std::is_empty_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsPolymorphic = std::is_polymorphic_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsAbstract = std::is_abstract_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsFinal = std::is_final_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsAggregate = std::is_aggregate_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsSigned = std::is_signed_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsUnsigned = std::is_unsigned_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsBoundedArray = std::is_bounded_array_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsUnboundedArray = std::is_unbounded_array_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsDefaultConstructible = std::is_default_constructible_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsTriviallyDefaultConstructible = std::is_trivially_default_constructible_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsCopyConstructible = std::is_copy_constructible_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsTriviallyCopyConstructible = std::is_trivially_copy_constructible_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsMoveConstructible = std::is_move_constructible_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsTriviallyMoveConstructible = std::is_trivially_move_constructible_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsDestructible = std::is_destructible_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsTriviallyDestructible = std::is_trivially_destructible_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsCopyAssignable = std::is_copy_assignable_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsTriviallyCopyAssignable = std::is_trivially_copy_assignable_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsMoveAssignable = std::is_move_assignable_v<T>;

// TODO: Description.
template<class T>
static constexpr bool IsTriviallyMoveAssignable = std::is_trivially_move_assignable_v<T>;

// TODO: Description.
template<class T>
static constexpr bool HasVirtualDestructor = std::has_virtual_destructor_v<T>;

// TODO: Description.
template<class T, class U>
static constexpr bool IsSwappableWith = std::is_swappable_with_v<T, U>;

// TODO: Description.
template<class T>
static constexpr bool IsSwappable = std::is_swappable_v<T>;

// TODO: Description.
template<class T>
static constexpr size_t AlignmentOf = std::alignment_of_v<T>;

// TODO: Description.
template<class T>
static constexpr size_t Rank = std::rank_v<T>;

// TODO: Description.
template<class T>
static constexpr size_t Extent = std::extent_v<T>;

// TODO: Description.
template<class T, class U>
static constexpr bool IsSame = std::is_same_v<T, U>;

// TODO: Description.
template<class Base, class Derived>
static constexpr bool IsBaseOf = std::is_base_of_v<Base, Derived>;

// TODO: Description.
template<class From, class To>
static constexpr bool IsConvertible = std::is_convertible_v<From, To>;

// TODO: Description.
template<class Fn, class... ArgTypes>
static constexpr bool IsInvocable = std::is_invocable<Fn, ArgTypes...>;

// TODO: Description.
template<class R, class Fn, class... ArgTypes>
static constexpr bool IsInvocableR = std::is_invocable_r<R, Fn, ArgTypes...>;

} // namespace TypeTraits

} // namespace kw

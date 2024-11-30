#pragma once

#include "Concepts.h"

namespace kw
{

// Manages an optional contained value, i.e. a value that may or may not be present.
template<class T>
class alignas(T) Optional
{
public:
	using ValueType = T;

	// Construct an optional that does not contain a value.
	Optional();

	// Construct an optional by copying a value of the specified optional if it has any.
	Optional(const Optional& Other);

	// Construct an optional by moving a value of the specified optional if it has any.
	Optional(Optional&& Other);

	// Construct an optional by converting and copying a value of the specified optional if it has any.
	template<class U>
		requires ConstructibleFrom<ValueType, const U&>
	Optional(const Optional<U>& Other);

	// Construct an optional by converting and moving a value of the specified optional if it has any.
	template<class U>
		requires ConstructibleFrom<ValueType, U&&>
	Optional(Optional<U>&& Other);

	// Construct an optional with the specified value.
	template<class U>
		requires ConstructibleFrom<ValueType, U&&>
	Optional(U&& Other);

	// Destroy the contained value if this optional has any.
	~Optional();

	// Assign the specified optional by copying its value if it has any.
	Optional& operator=(const Optional& Other);

	// Assign the specified optional by moving its value if it has any.
	Optional& operator=(Optional&& Other);

	// Assign the specified optional by converting and copying its value if it has any.
	template<class U>
		requires ConstructibleFrom<ValueType, const U&>
	Optional& operator=(const Optional<U>& Other);

	// Assign the specified optional by converting and moving its value if it has any.
	template<class U>
		requires ConstructibleFrom<ValueType, U&&>
	Optional& operator=(Optional<U>&& Other);

	// Assign the contained value to the specified value.
	template<class U>
		requires ConstructibleFrom<ValueType, U&&>
	Optional& operator=(U&& Other);

	// Construct the contained value in-place. This optional must contain a value.
	template<class... Args>
		requires ConstructibleFrom<ValueType, Args...>
	void Emplace(Args&&... Args);

	// Destroy the contained value.
	void Reset();

	// Return the contained value.
	const ValueType* operator->() const;
	ValueType* operator->();
	const ValueType& operator*() const&;
	ValueType& operator*()&;
	const ValueType&& operator*() const&&;
	ValueType&& operator*()&&;

	// Return whether this optional contains any value.
	explicit operator bool() const;
	bool HasValue() const;

	// Return the contained value. This optional must contain a value.
	const ValueType& GetValue() const&;
	ValueType& GetValue()&;
	const ValueType&& GetValue() const&&;
	ValueType&& GetValue()&&;

	// Return the contained value. If this optional doesn't contain any value, return the specified value.
	template<class U>
		requires ConstructibleFrom<ValueType, U&&>
	ValueType GetValueOr(U&& FallbackValue) const;

	// Compare the specified optionals. If one optional doesn't have a value it's considered to be less than one with a value.
	template<class U>
		requires ThreeWayComparableWith<ValueType, U>
	friend auto operator<=>(const Optional<ValueType>& Lhs, const Optional<U>& Rhs)
	{
		if (Lhs.mHasValue)
		{
			if (Rhs.mHasValue)
			{
				return Lhs <=> Rhs;
			}
			else
			{

			}
		}
		else
		{

		}
	}

private:
	char mData[sizeof(T)];
	bool mHasValue;
};

} // namespace kw

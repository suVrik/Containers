#pragma once

namespace kw
{

// TODO: Description.
template<class T, class U>
struct Pair
{
	using KeyType = T;
	using ValueType = U;

	KeyType Key;
	ValueType Value;

	// TODO: Description.
	template<class OtherKeyType, class OtherValueType>
		requires ThreeWayComparableWith<KeyType, OtherKeyType> && ThreeWayComparableWith<ValueType, OtherValueType>
	friend auto operator<=>(const Pair<KeyType, ValueType>& Lhs, const Pair<OtherKeyType, OtherValueType>& Rhs)
	{
		if (Lhs.Key == Rhs.Key)
		{
			return Lhs.Value <=> Rhs.Value;
		}
		else
		{
			return Lhs.Key <=> Rhs.Key;
		}
	}
};

// Hasher that takes a pair as a parameter but returns hash of a key only. Useful for associative containers.
template<class T, class U, class KeyHash>
struct PairKeyHash
{
	// Return hash of Value.Key using the specified hasher.
	size_t operator()(const Pair<T, U>& Value) const;
};

// Comparator that takes a pair as a parameter but compares keys only. Useful for associative containers.
template<class T, class U, class KeyEqualTo>
struct PairKeyEqualTo
{
	// Return whether Lhs.Key is equal to Rhs.Key using the specified comparator.
	bool operator()(const Pair<T, U>& Lhs, const Pair<T, U>& Rhs) const;
};

// Comparator that takes a pair as a parameter but compares keys only. Useful for associative containers.
template<class T, class U, class KeyLessThan>
struct PairKeyLessThan
{
	// Return whether Lhs.Key is less than Rhs.Key using the specified comparator.
	bool operator()(const Pair<T, U>& Lhs, const Pair<T, U>& Rhs) const;
};

} // namespace kw

#pragma once

namespace kw::ContainerUtils
{

// Return an iterator to the beginning of the given container, view, or array.
template<class T>
auto GetBegin(T& Container)
{
	// Lowercase method call to support initializer list.
	return Container.begin();
}

// Return an iterator to the end of the given container, view, or array.
template<class T>
auto GetEnd(T& Container)
{
	// Lowercase method call to support initializer list.
	return Container.end();
}

// Return size of the given container, view, or array.
template<class T>
auto GetSize(T& Container)
{
	// Lowercase method call to support initializer list.
	return Container.size();
}

// Specialization for C arrays.
template<class T, size_t N>
auto GetBegin(T (&Container)[N])
{
	return Container;
}

// Specialization for C arrays.
template<class T, size_t N>
auto GetEnd(T(&Container)[N])
{
	return Container + N;
}

// Specialization for C arrays.
template<class T, size_t N>
auto GetSize(T(&Container)[N])
{
	return N;
}

} // namespace kw::ContainerUtils

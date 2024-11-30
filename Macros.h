#pragma once

#if defined(_MSC_VER) && !defined(__clang__)
#define KW_NOINLINE __declspec(noinline)
#ifdef _DEBUG
#define KW_OPTIMIZATION_OFF
#define KW_OPTIMIZATION_ON
#else
#define KW_OPTIMIZATION_OFF __pragma(optimize("", off))
#define KW_OPTIMIZATION_ON __pragma(optimize("", on))
#endif // _DEBUG
#else
#define KW_NOINLINE __attribute__((noinline))
#ifdef DEBUG
#define KW_OPTIMIZATION_OFF
#define KW_OPTIMIZATION_ON
#else
#define KW_OPTIMIZATION_OFF _Pragma("clang optimize off")
#define KW_OPTIMIZATION_ON _Pragma("clang optimize on")
#endif // DEBUG
#endif // defined(_MSC_VER) && !defined(__clang__)

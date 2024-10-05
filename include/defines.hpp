#pragma once
#ifndef CL_DEFINES_HPP_
#define CL_DEFINES_HPP_

#if __cplusplus < 201703L
#error "Library is intended to be compiled with C++17 or later."
#endif

#if __cplusplus >= 201103L
#define CL_CPP11 11
#endif

#if __cplusplus >= 201402L
#define CL_CPP14 14
#endif

#if __cplusplus >= 201703L
#define CL_CPP17 17
#endif

#if __cplusplus >= 202002L
#define CL_CPP20 20
#endif

#if __cplusplus >= 202100L
#define CL_CPP23 23
#endif

#ifdef CL_CPP11
#define CL_CONSTEXPR constexpr
#define CL_EXPLICIT explicit
#define CL_NOEXCEPT noexcept
#endif

#ifdef CL_CPP14
#endif

#ifdef CL_CPP17
#define CL_NODISCARD [[nodiscard]]
#define CL_NOEXCEPT_WITH(s) noexcept(s)
#endif

#ifdef CL_CPP20

#define CL_CONCEPT concept
#define CL_REQUIRES requires

// #undef CL_EXPLICIT
#define CL_EXPLICIT_WITH(s) explicit(s)

// #undef CL_NODISCARD
#define CL_NODISCARD_BECAUSE(s) [[nodiscard(s)]]

#endif

#endif
/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file config.hpp
 *
 * This header defines config macros.
 */

#ifndef BOOST_BIT_OPS_DETAIL_CONFIG_HPP_INCLUDED_
#define BOOST_BIT_OPS_DETAIL_CONFIG_HPP_INCLUDED_

#include <boost/config.hpp>

#if defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#if !(defined(BOOST_LIBSTDCXX11) && (BOOST_LIBSTDCXX_VERSION) >= 40700) /* libstdc++ from gcc >= 4.7 in C++11 mode */
// This macro indicates that there is not even a basic <type_traits> standard header that is sufficient for most Boost.BitOps needs.
#define BOOST_BIT_OPS_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS
#endif
#endif // defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)

#if defined(__has_builtin)
#if __has_builtin(__builtin_clz)
#define BOOST_BIT_OPS_DETAIL_HAS_BUILTIN_CLZ
#endif
#if __has_builtin(__builtin_ctz)
#define BOOST_BIT_OPS_DETAIL_HAS_BUILTIN_CTZ
#endif
#if __has_builtin(__builtin_popcount)
#define BOOST_BIT_OPS_DETAIL_HAS_BUILTIN_POPCOUNT
#endif
#elif defined(__GNUC__)
#define BOOST_BIT_OPS_DETAIL_HAS_BUILTIN_CLZ
#define BOOST_BIT_OPS_DETAIL_HAS_BUILTIN_CTZ
#define BOOST_BIT_OPS_DETAIL_HAS_BUILTIN_POPCOUNT
#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_AMD64) || defined(_M_ARM) || defined(_M_ARM64))
#define BOOST_BIT_OPS_DETAIL_HAS_BIT_SCAN_FORWARD
#define BOOST_BIT_OPS_DETAIL_HAS_BIT_SCAN_REVERSE
#endif

// Note: MSVC does not define __LZCNT__, but it defines __AVX2__ and all CPUs supporting AVX2 supports lzcnt
#if (defined(__x86_64__) || defined(__i386__) || defined(_M_IX86) || defined(_M_AMD64)) && (defined(__LZCNT__) || defined(__AVX2__))
#define BOOST_BIT_OPS_DETAIL_HAS_LZCNT
#endif

// Same with __BMI__ and __AVX2__
#if (defined(__x86_64__) || defined(__i386__) || defined(_M_IX86) || defined(_M_AMD64)) && (defined(__BMI__) || defined(__AVX2__))
#if defined(__GNUC__)
#define BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U16
#endif
#define BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U32
#if defined(__x86_64__) || defined(_M_AMD64)
#define BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U64
#endif
#endif

// Same with __POPCNT__ and __AVX__
#if (defined(__x86_64__) || defined(__i386__) || defined(_M_IX86) || defined(_M_AMD64)) && (defined(__POPCNT__) || defined(__AVX__))
#if defined(_MSC_VER)
#define BOOST_BIT_OPS_DETAIL_HAS_POPCNT16
#endif
#define BOOST_BIT_OPS_DETAIL_HAS_POPCNT
#if defined(__x86_64__) || defined(_M_AMD64)
#define BOOST_BIT_OPS_DETAIL_HAS_POPCNT64
#endif
#endif

#if defined(_MSC_VER)
#if (defined(_M_IX86) || defined(_M_AMD64) || defined(_M_IA64)) || _MSC_VER >= 1600
#define BOOST_BIT_OPS_DETAIL_HAS_ROTL8
#define BOOST_BIT_OPS_DETAIL_HAS_ROTL16
#define BOOST_BIT_OPS_DETAIL_HAS_ROTR8
#define BOOST_BIT_OPS_DETAIL_HAS_ROTR16
#endif
#define BOOST_BIT_OPS_DETAIL_HAS_ROTL
#define BOOST_BIT_OPS_DETAIL_HAS_ROTL64
#define BOOST_BIT_OPS_DETAIL_HAS_ROTR
#define BOOST_BIT_OPS_DETAIL_HAS_ROTR64
#endif

#endif // BOOST_BIT_OPS_DETAIL_CONFIG_HPP_INCLUDED_

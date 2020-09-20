/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file countl_zero.hpp
 *
 * This header defines \c countl_zero algorithm, which counts the number of consecutive
 * most significant zero bits in an integer.
 */

#ifndef BOOST_BIT_OPS_COUNTING_COUNTL_ZERO_HPP_INCLUDED_
#define BOOST_BIT_OPS_COUNTING_COUNTL_ZERO_HPP_INCLUDED_

#include <limits>
#include <type_traits>
#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/detail/int_sizes.hpp>

#if defined(__GNUC__)
#if defined(BOOST_BIT_OPS_DETAIL_HAS_LZCNT)
#include <x86intrin.h>
#endif
#elif defined(_MSC_VER)
#include <intrin.h>
#endif

namespace boost {
namespace bit_ops {

namespace detail {

#if defined(BOOST_BIT_OPS_DETAIL_HAS_BUILTIN_CLZ)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= BOOST_BIT_OPS_DETAIL_SIZEOF_INT, unsigned int >::type countl_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__builtin_clz(value) - (std::numeric_limits< unsigned int >::digits - std::numeric_limits< T >::digits));
}

#if BOOST_BIT_OPS_DETAIL_SIZEOF_LONG > BOOST_BIT_OPS_DETAIL_SIZEOF_INT

template< typename T, unsigned int N >
inline typename std::enable_if< N == BOOST_BIT_OPS_DETAIL_SIZEOF_LONG, unsigned int >::type countl_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__builtin_clzl(value));
}

#endif // BOOST_BIT_OPS_DETAIL_SIZEOF_LONG > BOOST_BIT_OPS_DETAIL_SIZEOF_INT

#if BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

template< typename T, unsigned int N >
inline typename std::enable_if< N == BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG, unsigned int >::type countl_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__builtin_clzll(value));
}

#endif // BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

#elif defined(BOOST_BIT_OPS_DETAIL_HAS_BIT_SCAN_REVERSE)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= BOOST_BIT_OPS_DETAIL_SIZEOF_LONG, unsigned int >::type countl_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    unsigned long pos;
    _BitScanReverse(&pos, value);
    return static_cast< unsigned int >((std::numeric_limits< T >::digits - 1u) - pos);
}

#if BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

template< typename T, unsigned int N >
inline typename std::enable_if< N == BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG, unsigned int >::type countl_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
#if defined(_M_AMD64) || defined(_M_ARM64)
    unsigned long pos;
    _BitScanReverse64(&pos, value);
    return static_cast< unsigned int >((std::numeric_limits< T >::digits - 1u) - pos);
#else
    unsigned long upper_pos = 31u;
    unsigned long pos;
    if (!_BitScanReverse(&pos, static_cast< unsigned int >(value >> 32u)))
    {
        _BitScanReverse(&pos, static_cast< unsigned int >(value));
        upper_pos = std::numeric_limits< T >::digits - 1u;
    }
    return static_cast< unsigned int >(upper_pos - pos);
#endif
}

#endif // BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

#else

template< typename T, unsigned int N >
inline unsigned int countl_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    unsigned int count = 0u;
    unsigned int digits = std::numeric_limits< T >::digits / 2u;
    T mask = ~((static_cast< T >(1u) << digits) - 1u);
    for (; digits > 0u; digits >>= 1u, mask <<= digits)
    {
        if ((value & mask) == 0u)
        {
            count += digits;
            value <<= digits;
        }
    }

    return count;
}

#endif

#if defined(BOOST_BIT_OPS_DETAIL_HAS_LZCNT)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= 2u, unsigned int >::type countl_zero(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__lzcnt16(value) - (16u - std::numeric_limits< T >::digits));
}

template< typename T, unsigned int N >
inline typename std::enable_if< N == 4u, unsigned int >::type countl_zero(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__lzcnt(value));
}

template< typename T, unsigned int N >
inline typename std::enable_if< N == 8u, unsigned int >::type countl_zero(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
#if defined(__x86_64__) || defined(_M_AMD64)
    return static_cast< unsigned int >(__lzcnt64(value));
#else
    unsigned int count = static_cast< unsigned int >(__lzcnt(static_cast< unsigned int >(value >> 32u)));
    if (count >= 32u)
        count += static_cast< unsigned int >(__lzcnt(static_cast< unsigned int >(value)));
    return count;
#endif
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_LZCNT)

} // namespace detail

/*!
 * \brief Returns the number of consecutive most significant zero bits in \a value
 *
 * \pre \a value must not be zero
 */
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, unsigned int >::type countl_zero_nz(T value) BOOST_NOEXCEPT
{
    return bit_ops::detail::countl_zero_nz(value, std::integral_constant< unsigned int, sizeof(T) >());
}

//! Returns the number of consecutive most significant zero bits in \a value
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, unsigned int >::type countl_zero(T value) BOOST_NOEXCEPT
{
#if defined(BOOST_BIT_OPS_DETAIL_HAS_LZCNT)
    return bit_ops::detail::countl_zero(value, std::integral_constant< unsigned int, sizeof(T) >());
#else
    return value == 0u ? static_cast< unsigned int >(std::numeric_limits< T >::digits) : bit_ops::countl_zero_nz(value);
#endif
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_COUNTING_COUNTL_ZERO_HPP_INCLUDED_

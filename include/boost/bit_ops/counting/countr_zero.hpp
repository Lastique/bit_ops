/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file countr_zero.hpp
 *
 * This header defines \c countr_zero algorithm, which counts the number of consecutive
 * least significant zero bits in an integer.
 */

#ifndef BOOST_BIT_OPS_COUNTING_COUNTR_ZERO_HPP_INCLUDED_
#define BOOST_BIT_OPS_COUNTING_COUNTR_ZERO_HPP_INCLUDED_

#include <limits>
#include <type_traits>
#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/detail/int_sizes.hpp>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

namespace boost {
namespace bit_ops {

namespace detail {

#if defined(BOOST_BIT_OPS_DETAIL_HAS_BUILTIN_CTZ)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= BOOST_BIT_OPS_DETAIL_SIZEOF_INT, unsigned int >::type countr_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__builtin_ctz(value));
}

#if BOOST_BIT_OPS_DETAIL_SIZEOF_LONG > BOOST_BIT_OPS_DETAIL_SIZEOF_INT

template< typename T, unsigned int N >
inline typename std::enable_if< N == BOOST_BIT_OPS_DETAIL_SIZEOF_LONG, unsigned int >::type countr_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__builtin_ctzl(value));
}

#endif // BOOST_BIT_OPS_DETAIL_SIZEOF_LONG > BOOST_BIT_OPS_DETAIL_SIZEOF_INT

#if BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

template< typename T, unsigned int N >
inline typename std::enable_if< N == BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG, unsigned int >::type countr_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__builtin_ctzll(value));
}

#endif // BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

#elif defined(BOOST_BIT_OPS_DETAIL_HAS_BIT_SCAN_FORWARD)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= BOOST_BIT_OPS_DETAIL_SIZEOF_LONG, unsigned int >::type countr_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    unsigned long pos;
    _BitScanForward(&pos, value);
    return static_cast< unsigned int >(pos);
}

#if BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

template< typename T, unsigned int N >
inline typename std::enable_if< N == BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG, unsigned int >::type countr_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
#if defined(_M_AMD64) || defined(_M_ARM64)
    unsigned long pos;
    _BitScanForward64(&pos, value);
    return static_cast< unsigned int >(pos);
#else
    unsigned long pos;
    if (!_BitScanForward(&pos, static_cast< unsigned int >(value)))
        _BitScanForward(&pos, static_cast< unsigned int >(value >> 32u));
    return static_cast< unsigned int >(pos);
#endif
}

#endif // BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

#else

template< typename T, unsigned int N >
inline unsigned int countr_zero_nz(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    unsigned int count = 0u;
    unsigned int digits = std::numeric_limits< T >::digits / 2u;
    T mask = (static_cast< T >(1u) << digits) - 1u;
    for (; digits > 0u; digits >>= 1u, mask >>= digits)
    {
        if ((value & mask) == 0u)
        {
            count += digits;
            value >>= digits;
        }
    }

    return count;
}

#endif

#if defined(BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U32)

#if defined(BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U16)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= 2u, unsigned int >::type countr_zero(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    // Note: gcc provides the intrinsic with two double underscores
    return static_cast< unsigned int >(__tzcnt_u16(value) - (16u - std::numeric_limits< T >::digits));
}

template< typename T, unsigned int N >
inline typename std::enable_if< N == 4u, unsigned int >::type countr_zero(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(_tzcnt_u32(value));
}

#else // defined(BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U16)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= 4u, unsigned int >::type countr_zero(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(_tzcnt_u32(value) - (32u - std::numeric_limits< T >::digits));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U16)

template< typename T, unsigned int N >
inline typename std::enable_if< N == 8u, unsigned int >::type countr_zero(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
#if defined(BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U64)
    return static_cast< unsigned int >(_tzcnt_u64(value));
#else
    unsigned int count = _tzcnt_u32(static_cast< unsigned int >(value));
    if (count == 32u)
        count += _tzcnt_u32(static_cast< unsigned int >(value >> 32u));
    return count;
#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U64)
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U32)

} // namespace detail

/*!
 * \brief Returns the number of consecutive least significant zero bits in \a value
 *
 * \pre \a value must not be zero
 */
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, unsigned int >::type countr_zero_nz(T value) BOOST_NOEXCEPT
{
    return bit_ops::detail::countr_zero_nz(value, std::integral_constant< unsigned int, sizeof(T) >());
}

//! Returns the number of consecutive least significant zero bits in \a value
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, unsigned int >::type countr_zero(T value) BOOST_NOEXCEPT
{
#if defined(BOOST_BIT_OPS_DETAIL_HAS_TZCNT_U32)
    return bit_ops::detail::countr_zero(value, std::integral_constant< unsigned int, sizeof(T) >());
#else
    return value == 0u ? static_cast< unsigned int >(std::numeric_limits< T >::digits) : bit_ops::countr_zero_nz(value);
#endif
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_COUNTING_COUNTR_ZERO_HPP_INCLUDED_

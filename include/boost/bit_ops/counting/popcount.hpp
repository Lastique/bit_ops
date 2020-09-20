/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file popcount.hpp
 *
 * This header defines \c popcount algorithm, which counts the number of non-zero bits in an integer.
 */

#ifndef BOOST_BIT_OPS_COUNTING_POPCOUNT_HPP_INCLUDED_
#define BOOST_BIT_OPS_COUNTING_POPCOUNT_HPP_INCLUDED_

#include <type_traits>
#include <boost/cstdint.hpp>
#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/detail/int_sizes.hpp>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

namespace boost {
namespace bit_ops {

namespace detail {

#if defined(BOOST_BIT_OPS_DETAIL_HAS_BUILTIN_POPCOUNT)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= BOOST_BIT_OPS_DETAIL_SIZEOF_INT, unsigned int >::type popcount(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__builtin_popcount(value));
}

#if BOOST_BIT_OPS_DETAIL_SIZEOF_LONG > BOOST_BIT_OPS_DETAIL_SIZEOF_INT

template< typename T, unsigned int N >
inline typename std::enable_if< N == BOOST_BIT_OPS_DETAIL_SIZEOF_LONG, unsigned int >::type popcount(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__builtin_popcountl(value));
}

#endif // BOOST_BIT_OPS_DETAIL_SIZEOF_LONG > BOOST_BIT_OPS_DETAIL_SIZEOF_INT

#if BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

template< typename T, unsigned int N >
inline typename std::enable_if< N == BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG, unsigned int >::type popcount(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__builtin_popcountll(value));
}

#endif // BOOST_BIT_OPS_DETAIL_SIZEOF_LLONG > BOOST_BIT_OPS_DETAIL_SIZEOF_LONG

#elif defined(BOOST_BIT_OPS_DETAIL_HAS_POPCNT)

#if defined(BOOST_BIT_OPS_DETAIL_HAS_POPCNT16)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= 2u, unsigned int >::type popcount(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__popcnt16(value));
}

template< typename T, unsigned int N >
inline typename std::enable_if< N == 4u, unsigned int >::type popcount(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__popcnt(value));
}

#else // defined(BOOST_BIT_OPS_DETAIL_HAS_POPCNT16)

template< typename T, unsigned int N >
inline typename std::enable_if< N <= 4u, unsigned int >::type popcount(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(__popcnt(value));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_POPCNT16)

template< typename T, unsigned int N >
inline typename std::enable_if< N == 8u, unsigned int >::type popcount(T value, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
#if defined(BOOST_BIT_OPS_DETAIL_HAS_POPCNT64)
    return static_cast< unsigned int >(__popcnt64(value));
#else
    return static_cast< unsigned int >(__popcnt(static_cast< unsigned int >(value)) + __popcnt(static_cast< unsigned int >(value >> 32u)));
#endif
}

#else

template< typename T >
inline unsigned int popcount(T value, std::integral_constant< unsigned int, 1u >) BOOST_NOEXCEPT
{
    value = (value & 0x55u) + ((value >> 1u) & 0x55u);
    value = (value & 0x33u) + ((value >> 2u) & 0x33u);
    value = value + (value >> 4u);
    return static_cast< unsigned int >(value & 15u);
}

template< typename T >
inline unsigned int popcount(T value, std::integral_constant< unsigned int, 2u >) BOOST_NOEXCEPT
{
    value = (value & 0x5555u) + ((value >> 1u) & 0x5555u);
    value = (value & 0x3333u) + ((value >> 2u) & 0x3333u);
    value = (value + (value >> 4u)) & 0x0F0Fu;
    value = value + (value >> 8u);
    return static_cast< unsigned int >(value & 31u);
}

template< typename T >
inline unsigned int popcount(T value, std::integral_constant< unsigned int, 4u >) BOOST_NOEXCEPT
{
    value = (value & 0x55555555u) + ((value >> 1u) & 0x55555555u);
    value = (value & 0x33333333u) + ((value >> 2u) & 0x33333333u);
    value = (value + (value >> 4u)) & 0x0F0F0F0Fu;
    value = (value + (value >> 8u)) & 0x00FF00FFu;
    value = value + (value >> 16u);
    return static_cast< unsigned int >(value & 63u);
}

template< typename T >
inline unsigned int popcount(T value, std::integral_constant< unsigned int, 8u >) BOOST_NOEXCEPT
{
    value = (value & UINT64_C(0x5555555555555555)) + ((value >> 1u) & UINT64_C(0x5555555555555555));
    value = (value & UINT64_C(0x3333333333333333)) + ((value >> 2u) & UINT64_C(0x3333333333333333));
    value = (value + (value >> 4u)) & UINT64_C(0x0F0F0F0F0F0F0F0F);
    value = (value + (value >> 8u)) & UINT64_C(0x00FF00FF00FF00FF);
    value = value + (value >> 16u);
    value = value + (value >> 32u);
    return static_cast< unsigned int >(value & 127u);
}

#endif

} // namespace detail

//! Returns the number of non-zero bits in \a value
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, unsigned int >::type popcount(T value) BOOST_NOEXCEPT
{
    return bit_ops::detail::popcount(value, std::integral_constant< unsigned int, sizeof(T) >());
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_COUNTING_POPCOUNT_HPP_INCLUDED_

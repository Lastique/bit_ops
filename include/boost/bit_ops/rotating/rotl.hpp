/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file rotl.hpp
 *
 * This header defines \c rotl algorithm, which rotates integer left.
 */

#ifndef BOOST_BIT_OPS_ROTATING_ROTL_HPP_INCLUDED_
#define BOOST_BIT_OPS_ROTATING_ROTL_HPP_INCLUDED_

#include <limits>
#include <type_traits>
#include <boost/bit_ops/detail/config.hpp>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

namespace boost {
namespace bit_ops {

namespace detail {

#if defined(BOOST_BIT_OPS_DETAIL_HAS_ROTL8)

template< typename T >
inline T rotl(T value, unsigned int count, std::integral_constant< unsigned int, 1u >) BOOST_NOEXCEPT
{
    return static_cast< T >(_rotl8(value, count));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_ROTL8)

#if defined(BOOST_BIT_OPS_DETAIL_HAS_ROTL16)

template< typename T >
inline T rotl(T value, unsigned int count, std::integral_constant< unsigned int, 2u >) BOOST_NOEXCEPT
{
    return static_cast< T >(_rotl16(value, count));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_ROTL16)

#if defined(BOOST_BIT_OPS_DETAIL_HAS_ROTL)

template< typename T >
inline T rotl(T value, unsigned int count, std::integral_constant< unsigned int, 4u >) BOOST_NOEXCEPT
{
    return static_cast< T >(_rotl(value, count));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_ROTL)

#if defined(BOOST_BIT_OPS_DETAIL_HAS_ROTL64)

template< typename T >
inline T rotl(T value, unsigned int count, std::integral_constant< unsigned int, 8u >) BOOST_NOEXCEPT
{
    return static_cast< T >(_rotl64(value, count));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_ROTL64)

template< typename T, unsigned int N >
inline T rotl(T value, unsigned int count, std::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< T >((value << count) | (value >> (std::numeric_limits< T >::digits - count)));
}

} // namespace detail

//! Returns \a value rotated left by \a count bits
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, T >::type rotl(T value, unsigned int count) BOOST_NOEXCEPT
{
    return bit_ops::detail::rotl(value, count, std::integral_constant< unsigned int, sizeof(T) >());
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_ROTATING_ROTL_HPP_INCLUDED_

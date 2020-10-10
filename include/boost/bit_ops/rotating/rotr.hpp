/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file rotr.hpp
 *
 * This header defines \c rotr algorithm, which rotates integer right.
 */

#ifndef BOOST_BIT_OPS_ROTATING_ROTR_HPP_INCLUDED_
#define BOOST_BIT_OPS_ROTATING_ROTR_HPP_INCLUDED_

#include <limits>
#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/detail/type_traits/enable_if.hpp>
#include <boost/bit_ops/detail/type_traits/integral_constant.hpp>
#include <boost/bit_ops/detail/type_traits/is_integral.hpp>
#include <boost/bit_ops/detail/type_traits/is_unsigned.hpp>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

namespace boost {
namespace bit_ops {

namespace detail {

#if defined(BOOST_BIT_OPS_DETAIL_HAS_ROTR8)

template< typename T >
inline T rotr(T value, unsigned int count, bit_ops::detail::integral_constant< unsigned int, 1u >) BOOST_NOEXCEPT
{
    return static_cast< T >(_rotr8(value, count));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_ROTR8)

#if defined(BOOST_BIT_OPS_DETAIL_HAS_ROTR16)

template< typename T >
inline T rotr(T value, unsigned int count, bit_ops::detail::integral_constant< unsigned int, 2u >) BOOST_NOEXCEPT
{
    return static_cast< T >(_rotr16(value, count));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_ROTR16)

#if defined(BOOST_BIT_OPS_DETAIL_HAS_ROTR)

template< typename T >
inline T rotr(T value, unsigned int count, bit_ops::detail::integral_constant< unsigned int, 4u >) BOOST_NOEXCEPT
{
    return static_cast< T >(_rotr(value, count));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_ROTR)

#if defined(BOOST_BIT_OPS_DETAIL_HAS_ROTR64)

template< typename T >
inline T rotr(T value, unsigned int count, bit_ops::detail::integral_constant< unsigned int, 8u >) BOOST_NOEXCEPT
{
    return static_cast< T >(_rotr64(value, count));
}

#endif // defined(BOOST_BIT_OPS_DETAIL_HAS_ROTR64)

template< typename T, unsigned int N >
inline T rotr(T value, unsigned int count, bit_ops::detail::integral_constant< unsigned int, N >) BOOST_NOEXCEPT
{
    return static_cast< T >((value >> count) | (value << (std::numeric_limits< T >::digits - count)));
}

} // namespace detail

//! Returns \a value rotated left by \a count bits
template< typename T >
inline typename bit_ops::detail::enable_if<
    bit_ops::detail::is_integral< T >::value && bit_ops::detail::is_unsigned< T >::value,
    T
>::type rotr(T value, unsigned int count) BOOST_NOEXCEPT
{
    return bit_ops::detail::rotr(value, count, bit_ops::detail::integral_constant< unsigned int, sizeof(T) >());
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_ROTATING_ROTR_HPP_INCLUDED_

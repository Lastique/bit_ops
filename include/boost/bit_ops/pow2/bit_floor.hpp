/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file bit_floor.hpp
 *
 * This header defines \c bit_floor algorithm, which produces a nearest power of 2 integer
 * that is less or equal to the input integer.
 */

#ifndef BOOST_BIT_OPS_POW2_BIT_FLOOR_HPP_INCLUDED_
#define BOOST_BIT_OPS_POW2_BIT_FLOOR_HPP_INCLUDED_

#include <limits>
#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/detail/type_traits/enable_if.hpp>
#include <boost/bit_ops/detail/type_traits/is_integral.hpp>
#include <boost/bit_ops/detail/type_traits/is_unsigned.hpp>
#include <boost/bit_ops/count/countl_zero.hpp>

namespace boost {
namespace bit_ops {

/*!
 * \brief Returns the nearest power of 2 integer that is less or equal to \a value
 *
 * \pre \a value must not be zero
 */
template< typename T >
inline typename bit_ops::detail::enable_if<
    bit_ops::detail::is_integral< T >::value && bit_ops::detail::is_unsigned< T >::value,
    T
>::type bit_floor_nz(T value) BOOST_NOEXCEPT
{
    return static_cast< T >(1u) << ((std::numeric_limits< T >::digits - 1u) - bit_ops::countl_zero_nz(value));
}

//! Returns the nearest power of 2 integer that is less or equal to \a value, or 0 if \a value is zero
template< typename T >
inline typename bit_ops::detail::enable_if<
    bit_ops::detail::is_integral< T >::value && bit_ops::detail::is_unsigned< T >::value,
    T
>::type bit_floor(T value) BOOST_NOEXCEPT
{
    return value == 0u ? static_cast< T >(0u) : bit_ops::bit_floor_nz(value);
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_POW2_BIT_FLOOR_HPP_INCLUDED_

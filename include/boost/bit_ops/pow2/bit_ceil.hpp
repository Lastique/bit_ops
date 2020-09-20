/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file bit_ceil.hpp
 *
 * This header defines \c bit_ceil algorithm, which produces a nearest power of 2 integer
 * that is greater or equal to the input integer.
 */

#ifndef BOOST_BIT_OPS_POW2_BIT_CEIL_HPP_INCLUDED_
#define BOOST_BIT_OPS_POW2_BIT_CEIL_HPP_INCLUDED_

#include <limits>
#include <type_traits>
#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/count/countl_zero.hpp>

namespace boost {
namespace bit_ops {

/*!
 * \brief Returns the nearest power of 2 integer that is greater or equal to \a value
 *
 * \pre \a value must not be zero
 */
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, T >::type bit_ceil_nz(T value) BOOST_NOEXCEPT
{
    return static_cast< T >(1u) << ((std::numeric_limits< T >::digits - 1u) - bit_ops::countl_zero_nz(value) + ((value & (value - 1u)) != 0u));
}

//! Returns the nearest power of 2 integer that is greater or equal to \a value
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, T >::type bit_ceil(T value) BOOST_NOEXCEPT
{
    // bit_ceil(0) == bit_ceil(1) == 1
    return value == 0u ? static_cast< T >(1u) : bit_ops::bit_ceil_nz(value);
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_POW2_BIT_CEIL_HPP_INCLUDED_

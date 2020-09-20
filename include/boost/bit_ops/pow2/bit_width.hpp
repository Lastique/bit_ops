/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file bit_width.hpp
 *
 * This header defines \c bit_width algorithm, which produces the minimal number of
 * bits required to represent an integer value.
 */

#ifndef BOOST_BIT_OPS_POW2_BIT_WIDTH_HPP_INCLUDED_
#define BOOST_BIT_OPS_POW2_BIT_WIDTH_HPP_INCLUDED_

#include <limits>
#include <type_traits>
#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/count/countl_zero.hpp>

namespace boost {
namespace bit_ops {

/*!
 * \brief Returns the minimal number of bits required to represent \a value
 *
 * \pre \a value must not be zero
 */
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, unsigned int >::type bit_width_nz(T value) BOOST_NOEXCEPT
{
    return static_cast< unsigned int >(std::numeric_limits< T >::digits - bit_ops::countl_zero_nz(value));
}

//! Returns the minimal number of bits required to represent \a value or 0 if \a value is zero
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, unsigned int >::type bit_width(T value) BOOST_NOEXCEPT
{
    return value == 0u ? 0u : bit_ops::bit_width_nz(value);
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_POW2_BIT_WIDTH_HPP_INCLUDED_

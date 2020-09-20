/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file has_single_bit.hpp
 *
 * This header defines \c has_single_bit algorithm, which returns \c true if the passed integer has a single non-zero bit.
 * This algorithm is functionally equivalent to \c is_power_of_2.
 */

#ifndef BOOST_BIT_OPS_POW2_HAS_SINGLE_BIT_HPP_INCLUDED_
#define BOOST_BIT_OPS_POW2_HAS_SINGLE_BIT_HPP_INCLUDED_

#include <type_traits>
#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/pow2/is_power_of_2.hpp>

namespace boost {
namespace bit_ops {

//! Tests if the integer has a single non-zero bit
template< typename T >
inline BOOST_CONSTEXPR typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, bool >::type has_single_bit(T value) BOOST_NOEXCEPT
{
    return bit_ops::is_power_of_2(value);
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_POW2_HAS_SINGLE_BIT_HPP_INCLUDED_

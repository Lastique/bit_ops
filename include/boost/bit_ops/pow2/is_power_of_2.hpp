/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file is_power_of_2.hpp
 *
 * This header defines \c is_power_of_2 algorithm, which returns \c true if the passed integer is a power of 2.
 */

#ifndef BOOST_BIT_OPS_POW2_IS_POWER_OF_2_HPP_INCLUDED_
#define BOOST_BIT_OPS_POW2_IS_POWER_OF_2_HPP_INCLUDED_

#include <type_traits>
#include <boost/bit_ops/detail/config.hpp>

namespace boost {
namespace bit_ops {

//! Tests if the integer is a power of 2
template< typename T >
inline BOOST_CONSTEXPR typename std::enable_if< std::is_integral< T >::value, bool >::type is_power_of_2(T value) BOOST_NOEXCEPT
{
    typedef typename std::make_unsigned< T >::type unsigned_type;
    return static_cast< bool >((static_cast< unsigned_type >(value) == 0u) ^ ((static_cast< unsigned_type >(value) & (static_cast< unsigned_type >(value) - 1u)) == 0u));
}

//! Tests if the enum is a power of 2
template< typename T >
inline BOOST_CONSTEXPR typename std::enable_if< std::is_enum< T >::value, bool >::type is_power_of_2(T value) BOOST_NOEXCEPT
{
    return bit_ops::is_power_of_2(static_cast< typename std::underlying_type< T >::type >(value));
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_POW2_IS_POWER_OF_2_HPP_INCLUDED_

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

#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/detail/type_traits/enable_if.hpp>
#include <boost/bit_ops/detail/type_traits/is_integral.hpp>
#include <boost/bit_ops/detail/type_traits/is_enum.hpp>
#include <boost/bit_ops/detail/type_traits/is_signed.hpp>
#include <boost/bit_ops/detail/type_traits/is_unsigned.hpp>
#include <boost/bit_ops/detail/type_traits/make_unsigned.hpp>
#include <boost/bit_ops/detail/type_traits/underlying_type.hpp>

namespace boost {
namespace bit_ops {

//! Tests if the integer is a power of 2
template< typename T >
inline BOOST_CONSTEXPR typename bit_ops::detail::enable_if<
    bit_ops::detail::is_integral< T >::value && bit_ops::detail::is_unsigned< T >::value,
    bool
>::type is_power_of_2(T value) BOOST_NOEXCEPT
{
    return static_cast< bool >((value == static_cast< T >(0u)) ^ ((value & (value - static_cast< T >(1u))) == static_cast< T >(0u)));
}

//! Tests if the integer is a power of 2
template< typename T >
inline BOOST_CONSTEXPR typename bit_ops::detail::enable_if<
    bit_ops::detail::is_integral< T >::value && bit_ops::detail::is_signed< T >::value,
    bool
>::type is_power_of_2(T value) BOOST_NOEXCEPT
{
    typedef typename bit_ops::detail::make_unsigned< T >::type unsigned_type;
    return value <= static_cast< T >(0) ? false : bit_ops::is_power_of_2(static_cast< unsigned_type >(value));
}

//! Tests if the enum is a power of 2
template< typename T >
inline BOOST_CONSTEXPR typename bit_ops::detail::enable_if<
    bit_ops::detail::is_enum< T >::value,
    bool
>::type is_power_of_2(T value) BOOST_NOEXCEPT
{
    return bit_ops::is_power_of_2(static_cast< typename bit_ops::detail::underlying_type< T >::type >(value));
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_POW2_IS_POWER_OF_2_HPP_INCLUDED_

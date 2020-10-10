/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file bit_ops/detail/type_traits/underlying_type.hpp
 *
 * This header defines \c underlying_type type trait
 */

#ifndef BOOST_BIT_OPS_DETAIL_TYPE_TRAITS_UNDERLYING_TYPE_HPP_INCLUDED_
#define BOOST_BIT_OPS_DETAIL_TYPE_TRAITS_UNDERLYING_TYPE_HPP_INCLUDED_

#include <boost/bit_ops/detail/config.hpp>
#if !defined(BOOST_BIT_OPS_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/cstdint.hpp>
#endif

namespace boost {
namespace bit_ops {
namespace detail {

#if !defined(BOOST_BIT_OPS_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::underlying_type;
#else
// We cannot detect whether there are negative enum values, but in our use case this is not really important
// because all we want is to safely convert the enum to some unsigned integer to perform bit operations on.
// We convert to unsigned integer to avoid potential signed integer overflow if the enum value does not fit
// in the signed range.
template< typename T, unsigned int Size >
struct underlying_type_impl;
template< typename T >
struct underlying_type_impl< T, 1u > { typedef boost::uint8_t type; };
template< typename T >
struct underlying_type_impl< T, 2u > { typedef boost::uint16_t type; };
template< typename T >
struct underlying_type_impl< T, 4u > { typedef boost::uint32_t type; };
template< typename T >
struct underlying_type_impl< T, 8u > { typedef boost::uint64_t type; };

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template< typename T >
using underlying_type = underlying_type_impl< T, sizeof(T) >;
#else
template< typename T >
struct underlying_type :
    public underlying_type_impl< T, sizeof(T) >
{
};
#endif
#endif

} // namespace detail
} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_DETAIL_TYPE_TRAITS_UNDERLYING_TYPE_HPP_INCLUDED_

/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file bit_ops/detail/type_traits/integral_constant.hpp
 *
 * This header defines \c enable_if wrapper
 */

#ifndef BOOST_BIT_OPS_DETAIL_TYPE_TRAITS_ENABLE_IF_HPP_INCLUDED_
#define BOOST_BIT_OPS_DETAIL_TYPE_TRAITS_ENABLE_IF_HPP_INCLUDED_

#include <boost/bit_ops/detail/config.hpp>
#if !defined(BOOST_BIT_OPS_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/core/enable_if.hpp>
#endif

namespace boost {
namespace bit_ops {
namespace detail {

#if !defined(BOOST_BIT_OPS_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::enable_if;
#elif !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template< bool F, typename R = void >
using enable_if = boost::enable_if_c< F, R >;
#else
template< bool F, typename R = void >
struct enable_if :
    public boost::enable_if_c< F, R >
{
};
#endif

} // namespace detail
} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_DETAIL_TYPE_TRAITS_ENABLE_IF_HPP_INCLUDED_

/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file bit_ops/detail/type_traits/make_unsigned.hpp
 *
 * This header defines \c make_unsigned type trait
 */

#ifndef BOOST_BIT_OPS_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_HPP_INCLUDED_
#define BOOST_BIT_OPS_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_HPP_INCLUDED_

#include <boost/bit_ops/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_BIT_OPS_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/make_unsigned.hpp>
#endif

namespace boost {
namespace bit_ops {
namespace detail {

#if !defined(BOOST_BIT_OPS_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::make_unsigned;
#else
using boost::make_unsigned;
#endif

} // namespace detail
} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_HPP_INCLUDED_

/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file countr_one.hpp
 *
 * This header defines \c countr_one algorithm, which counts the number of consecutive
 * least significant one bits in an integer.
 */

#ifndef BOOST_BIT_OPS_COUNTING_COUNTR_ONE_HPP_INCLUDED_
#define BOOST_BIT_OPS_COUNTING_COUNTR_ONE_HPP_INCLUDED_

#include <boost/bit_ops/detail/config.hpp>
#include <boost/bit_ops/counting/countr_zero.hpp>

namespace boost {
namespace bit_ops {

/*!
 * \brief Returns the number of consecutive least significant one bits in \a value
 *
 * \pre \a value must not be all-ones
 */
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, unsigned int >::type countr_one_nf(T value) BOOST_NOEXCEPT
{
    return bit_ops::countr_zero_nz(static_cast< T >(~value));
}

//! Returns the number of consecutive least significant one bits in \a value
template< typename T >
inline typename std::enable_if< std::is_integral< T >::value && std::is_unsigned< T >::value, unsigned int >::type countr_one(T value) BOOST_NOEXCEPT
{
    return bit_ops::countr_zero(static_cast< T >(~value));
}

} // namespace bit_ops
} // namespace boost

#endif // BOOST_BIT_OPS_COUNTING_COUNTR_ONE_HPP_INCLUDED_

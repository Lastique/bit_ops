/*
 * Copyright Andrey Semashev 2020
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/bit_ops.hpp>

int main()
{
    return boost::bit_ops::countr_zero(192u);
}

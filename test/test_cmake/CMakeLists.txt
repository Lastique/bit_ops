# Copyright Andrey Semashev 2020
#
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
#
# NOTE: This does NOT run the unit tests for Boost.BitOps.
#       It only tests if the CMakeLists.txt file in its root works as expected

cmake_minimum_required(VERSION 3.5)

project(BoostBitOpsCMakeSelfTest)

# Use experimental superproject to pull library dependencies recursively
set(BOOST_ENABLE_CMAKE 1)
add_subdirectory(../../../.. "${CMAKE_CURRENT_BINARY_DIR}/boost_superproject")

add_definitions(-DBOOST_ALL_NO_LIB)

add_executable(boost_bit_ops_cmake_self_test main.cpp)
target_link_libraries(boost_bit_ops_cmake_self_test Boost::bit_ops)

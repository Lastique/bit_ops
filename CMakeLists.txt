# Copyright Andrey Semashev 2020
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.5...3.16)
project(boost_bit_ops VERSION "${BOOST_SUPERPROJECT_VERSION}" LANGUAGES CXX)

add_library(boost_bit_ops INTERFACE)
add_library(Boost::bit_ops ALIAS boost_bit_ops)

target_include_directories(boost_bit_ops INTERFACE include)

target_link_libraries(boost_bit_ops
    INTERFACE
        Boost::config
)

if(BOOST_SUPERPROJECT_VERSION)
    include(BoostInstall)
    boost_install(TARGETS boost_bit_ops HEADER_DIRECTORY include/)
endif()

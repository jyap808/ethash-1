# Copyright 2018 Pawel Bylica.
# Licensed under the Apache License, Version 2.0. See the LICENSE file.

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_executable(
    ethash-test
    helpers.hpp
    test_bit_manipulation.cpp
    test_blake2b.cpp
    test_cases.hpp
    test_ethash.cpp
    test_ethash_cxx.cpp
    test_keccak.cpp
    test_kiss.cpp
    test_managed.cpp
    test_primes.cpp
    test_progpow.cpp
    test_ubqhash.cpp
)

target_link_libraries(ethash-test PRIVATE ethash GTest::gtest GTest::main)
target_include_directories(ethash-test PRIVATE ${ETHASH_PRIVATE_INCLUDE_DIR})

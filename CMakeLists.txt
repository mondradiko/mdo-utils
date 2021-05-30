# Copyright (c) 2021 Marceline Cramer
# SPDX-License-Identifier: MIT

cmake_minimum_required (VERSION 3.18)
project (mdo-utils VERSION 0.0.0)

# options
option (ENABLE_TESTS "Enable testing suite.")

# C standard
set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED TRUE)

if (UNIX)
  add_compile_options (-Wpedantic)
endif ()

# add CMake modules
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include (mondradiko_setup_library)

# manually add config file input for installation
set (MONDRADIKO_CONFIG_IN_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/mdo-config.cmake.in"
)

# setup library
mondradiko_setup_library (mdo-utils MDO_UTILS_OBJ
  src/allocator.c
  src/log.c
  src/result.c
)

# install CMake modules
install (FILES
  cmake/mdo-config.cmake.in
  cmake/mondradiko_create_test.cmake
  cmake/mondradiko_setup_library.cmake
  DESTINATION lib/cmake/mdo-utils
)

# tests
if (ENABLE_TESTS)
  enable_testing ()
  add_subdirectory (tests)
endif ()

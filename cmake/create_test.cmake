# Copyright (c) 2021 Marceline Cramer
# SPDX-License-Identifier: MIT

include (CTest)

if (NOT CRITERION_FOUND)
  include (FindPkgConfig)
  pkg_check_modules (CRITERION criterion>=2.0)
endif ()

function (create_test TEST_LIB TEST_NAME TEST_PATH)
  set (TEST_EXECUTABLE test-${TEST_NAME})
  add_executable (${TEST_EXECUTABLE} ${TEST_PATH})
  target_link_libraries (${TEST_EXECUTABLE} ${TEST_LIB} ${CRITERION_LIBRARIES})
  add_test (NAME ${TEST_NAME} COMMAND ${TEST_EXECUTABLE} --verbose)
endfunction ()

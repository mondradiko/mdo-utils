# Copyright (c) 2021 Marceline Cramer
# SPDX-License-Identifier: MIT

include (CTest)
find_package (cmocka CONFIG REQUIRED)

function (mondradiko_create_test TEST_LIB TEST_NAME TEST_PATH)
  set (TEST_EXECUTABLE test-${TEST_NAME})
  add_executable (${TEST_EXECUTABLE} ${TEST_PATH})
  target_link_libraries (${TEST_EXECUTABLE} ${TEST_LIB} cmocka::cmocka)
  add_test (NAME ${TEST_NAME} COMMAND ${TEST_EXECUTABLE})
endfunction ()

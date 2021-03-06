# Copyright (c) 2021 Marceline Cramer
# SPDX-License-Identifier: MIT

include (CTest)

find_package (cmocka CONFIG REQUIRED)

# use vcpkg cmocka::cmocka target if that's what got imported
if (TARGET cmocka::cmocka)
  set (CMOCKA_LIBRARIES cmocka::cmocka)
endif ()

function (mondradiko_create_test TEST_LIB TEST_NAME TEST_PATH)
  set (TEST_EXECUTABLE test-${TEST_NAME})
  add_executable (${TEST_EXECUTABLE} ${TEST_PATH})
  target_link_libraries (${TEST_EXECUTABLE} ${TEST_LIB} ${CMOCKA_LIBRARIES})
  add_test (NAME ${TEST_NAME} COMMAND ${TEST_EXECUTABLE})
endfunction ()

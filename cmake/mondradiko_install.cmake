# Copyright (c) 2021 Marceline Cramer
# SPDX-License-Identifier: MIT

set (MONDRADIKO_MODULES_PATH "lib/cmake/mondradiko")

include (CMakePackageConfigHelpers)

function (mondradiko_install target)
  set (target-config ${target}-config.cmake)

  # add public headers
  target_include_directories (${target} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
  )

  # package
  configure_package_config_file (
    "${MONDRADIKO_CONFIG_IN_PATH}"
    "${CMAKE_CURRENT_BINARY_DIR}/${target-config}"
    INSTALL_DESTINATION "${MONDRADIKO_MODULES_PATH}/${target}"
  )

  # install library
  install (TARGETS ${target} EXPORT ${target})

  # install headers
  install (DIRECTORY include/mondradiko TYPE INCLUDE)

  # install package config file
  install (FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${target-config}"
    DESTINATION ${MONDRADIKO_MODULES_PATH}
  )

  # export library
  install (EXPORT ${target}
    NAMESPACE mondradiko::
    DESTINATION ${MONDRADIKO_MODULES_PATH}
  )
endfunction ()

# Copyright (c) 2021 Marceline Cramer
# SPDX-License-Identifier: MIT

include (CMakePackageConfigHelpers)

function (mondradiko_install target)
  set (module-path "lib/cmake/${target}")
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
    INSTALL_DESTINATION "${module-path}/${target}"
  )

  # install library
  install (TARGETS ${target} EXPORT ${target})

  # install headers
  file (GLOB target-headers include/*.h)
  install (FILES ${target-headers} DESTINATION include/${target})

  # install package config file
  install (FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${target-config}"
    DESTINATION ${module-path}
  )

  # export library
  install (EXPORT ${target}
    NAMESPACE mondradiko::
    DESTINATION ${module-path}
  )
endfunction ()

function (mondradiko_setup_library LIBRARY_NAME OBJECT_TARGET)
  set (LIBRARY_OBJ "${LIBRARY_NAME}-obj")

  # compile object library
  add_library (${LIBRARY_OBJ} OBJECT ${ARGN})
  target_include_directories (${LIBRARY_OBJ} PUBLIC include)

  # enable linking on non-Windows systems
  if (UNIX)
    target_compile_options (${LIBRARY_OBJ} PRIVATE -fPIC)
  endif ()

  # make shared library
  add_library (${LIBRARY_NAME} SHARED $<TARGET_OBJECTS:${LIBRARY_OBJ}>)

  # install shared library
  mondradiko_install (${LIBRARY_NAME})

  # output object library name
  set (${OBJECT_TARGET} ${LIBRARY_OBJ} PARENT_SCOPE)
endfunction ()

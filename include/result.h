/*! @file result.h
  @brief Wraps result code creation, formatting, and logging.
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdarg.h>  /* for va_list */
#include <stdbool.h> /* for bool */
#include <stddef.h>  /* for size_t */

#include "export.h"
#include "log.h"

#define LOG_RESULT(...) mdo_result_log (__FILE__, __LINE__, __VA_ARGS__)

#define MDO_SUCCESS (0)

/*! @typedef mdo_result_t
  @brief Opaque identifier for result codes.
 */
typedef int mdo_result_t;

/*! @function mdo_result_create_brief
 */
MDO_EXPORT mdo_result_t mdo_result_create (mdo_log_level_t, const char *, int,
                                           bool);

/*!
 */
MDO_EXPORT void mdo_result_cleanup ();

/*! @function mdo_result_success
  @param result The result to test.
  @return False if the result is an error, true if it's a success.
 */
MDO_EXPORT bool mdo_result_success (mdo_result_t);

/*! @function mdo_result_vformat
 */
MDO_EXPORT mdo_result_t mdo_result_vformat (char *, size_t, mdo_result_t,
                                            va_list);

/*! @function mdo_result_format
 */
MDO_EXPORT mdo_result_t mdo_result_format (char *, size_t, mdo_result_t, ...);

/*! @function mdo_result_log
 */
MDO_EXPORT mdo_result_t mdo_result_log (const char *, int, mdo_result_t, ...);

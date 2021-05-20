/*! @file result.h
  @brief Wraps result code creation, formatting, and logging.
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdarg.h> /* for va_list */
#include <stddef.h> /* for size_t */

#include "mondradiko/log.h"

#define LOG_RESULT(...) mdo_result_log (__FILE__, __LINE__, __VA_ARGS__)

#define MDO_SUCCESS (0)

/*! @typedef mdo_result_t
  @brief Opaque identifier for result codes.
 */
typedef int mdo_result_t;

/*! @function mdo_result_create_brief
 */
mdo_result_t mdo_result_create_brief (mdo_log_level_t, const char *, int);

/*! @function mdo_result_create_extended
 */
mdo_result_t mdo_result_create_extended (mdo_log_level_t, const char *, int,
                                         const char *);

/*! @function mdo_result_vformat
 */
mdo_result_t mdo_result_vformat (char *, size_t *, mdo_result_t, va_list);

/*! @function mdo_result_format
 */
mdo_result_t mdo_result_format (char *, size_t *, mdo_result_t, ...);

/*! @function mdo_result_log
 */
mdo_result_t mdo_result_log (const char *, int, mdo_result_t, ...);

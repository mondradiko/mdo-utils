/*! @file test-result.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "test_common.h"

#include "mondradiko/result.h"

#define RESULT_NUM (128 * 1024)
#define FORMAT_LEN (256)

static void
cleanup ()
{
  mdo_result_cleanup ();
}

Test (result, cleanup) { mdo_result_cleanup (); }

Test (result, constant_success, .fini = cleanup)
{
  int success = mdo_result_success (MDO_SUCCESS);
  cr_assert (success);
}

Test (result, create_success, .fini = cleanup)
{
  mdo_result_t result;
  result = mdo_result_create (MDO_LOG_INFO, "Success result", 0, true);
  int success = mdo_result_success (result);
  cr_assert (success);
}

Test (result, create_error, .fini = cleanup)
{
  mdo_result_t result;
  result = mdo_result_create (MDO_LOG_ERROR, "Error result", 0, false);
  int success = mdo_result_success (result);
  cr_assert_not (success);
}

Test (result, format, .fini = cleanup)
{
  mdo_result_t result;
  result = mdo_result_create (MDO_LOG_INFO, "Format: %d %d %d", 3, true);

  char format[FORMAT_LEN];
  mdo_result_t format_result;
  format_result = mdo_result_format (format, FORMAT_LEN, result, 24, 48, 96);

  int result_success = mdo_result_success (result);
  int format_success = mdo_result_success (format_result);

  cr_assert (result_success);
  cr_assert (format_success);
  cr_assert_str_eq ("Format: 24 48 96", format);
}

Test (result, log, .fini = cleanup)
{
  mdo_result_t result;
  result = mdo_result_create (MDO_LOG_INFO, "Format: %d %d %d", 3, true);

  mdo_result_t logged;
  logged = LOG_RESULT (result, 16, 32, 64);

  char format[FORMAT_LEN];
  mdo_result_t formatted;
  formatted = mdo_result_format (format, FORMAT_LEN, logged);

  int result_success = mdo_result_success (result);
  int log_success = mdo_result_success (logged);

  cr_assert (result_success);
  cr_assert (log_success);
  cr_assert_str_eq ("Format: 16 32 64", format);
}

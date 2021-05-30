/*! @file test-result.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "test_common.h"

#include "result.h"

#define RESULT_NUM (128 * 1024)
#define FORMAT_LEN (256)

static void
test_constant_success (void **state)
{
  int success = mdo_result_success (MDO_SUCCESS);
  assert_true (success);
}

static void
test_create_success (void **state)
{
  mdo_result_t result;
  result = mdo_result_create (MDO_LOG_INFO, "Success result", 0, true);
  int success = mdo_result_success (result);
  assert_true (success);
}

static void
test_create_error (void **state)
{
  mdo_result_t result;
  result = mdo_result_create (MDO_LOG_ERROR, "Error result", 0, false);
  int success = mdo_result_success (result);
  assert_false (success);
}

static void
test_format (void **state)
{
  mdo_result_t result;
  result = mdo_result_create (MDO_LOG_INFO, "Format: %d %d %d", 3, true);

  char format[FORMAT_LEN];
  mdo_result_t format_result;
  format_result = mdo_result_format (format, FORMAT_LEN, result, 24, 48, 96);

  int result_success = mdo_result_success (result);
  int format_success = mdo_result_success (format_result);

  assert_true (result_success);
  assert_true (format_success);
  assert_string_equal ("Format: 24 48 96", format);
}

static void
test_log (void **state)
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

  assert_true (result_success);
  assert_true (log_success);
  assert_string_equal ("Format: 16 32 64", format);
}

int
main (void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test (test_constant_success),
    cmocka_unit_test (test_create_success),
    cmocka_unit_test (test_create_error),
    cmocka_unit_test (test_format),
    cmocka_unit_test (test_log),
  };

  return cmocka_run_group_tests (tests, NULL, NULL);
}

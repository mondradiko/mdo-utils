/*! @file test-log.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "test_common.h"

#include "mondradiko/log.h"

static void
test_log (void **state)
{
  LOG_INF ("Info log message");
  LOG_DBG ("Debug log message");
  LOG_MSG ("User log message");
  LOG_WRN ("Warning log message");
  LOG_ERR ("Error log message");
}

int
main (void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test (test_log),
  };

  return cmocka_run_group_tests (tests, NULL, NULL);
}

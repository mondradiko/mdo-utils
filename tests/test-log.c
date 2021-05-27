/*! @file test-log.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "test_common.h"

#include "mondradiko/log.h"

Test (log, log)
{
  LOG_INF ("Info log message");
  LOG_DBG ("Debug log message");
  LOG_MSG ("User log message");
  LOG_WRN ("Warning log message");
  LOG_ERR ("Error log message");
}

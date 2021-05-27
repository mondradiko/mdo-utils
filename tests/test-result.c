/*! @file test-result.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "test_common.h"

#include <stdio.h>

#include "mondradiko/result.h"

#define RESULT_NUM (10)
#define RESULT_LENGTH (256)
#define FORMAT_NUM (10)

Test (result, brief)
{
  char formats[RESULT_NUM][RESULT_LENGTH];
  mdo_result_t results[RESULT_NUM];

  for (int result = 0; result < RESULT_NUM; result++)
    {
      char *format = formats[result];
      snprintf (format, RESULT_LENGTH,
                "Hello, world!\nResult: %d\nFormat: %%d", result);
      results[result] = mdo_result_create_brief (MDO_LOG_MESSAGE, format, 1);
    }

  for (int result = 0; result < 10; result++)
    {
      for (int format = 0; format < 10; format++)
        {
          LOG_RESULT (results[result], format);
        }
    }
}

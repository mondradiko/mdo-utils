/*! @file result.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "mondradiko/result.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct mdo_result_data_s
{
  mdo_log_level_t level;
  const char *brief;
  int format_num;
  const char *extended;
} mdo_result_data_t;

static mdo_result_data_t *s_result_store = NULL;
static size_t s_result_num = 1;
static size_t s_result_capacity = 1024;

mdo_result_t
mdo_result_create_brief (mdo_log_level_t level, const char *brief,
                         int format_num)
{
  return mdo_result_create_extended (level, brief, format_num, NULL);
}

mdo_result_t
mdo_result_create_extended (mdo_log_level_t level, const char *brief,
                            int format_num, const char *extended)
{
  if (!s_result_store)
    {
      s_result_store = calloc (sizeof (mdo_result_data_t), s_result_capacity);
    }
  else if (s_result_num >= s_result_capacity)
    {
      size_t new_capacity = (s_result_capacity >> 1) + s_result_capacity;
      size_t store_size = new_capacity * sizeof (mdo_result_data_t);
      s_result_store = realloc (s_result_store, store_size);
      s_result_capacity = new_capacity;
    }

  mdo_result_t result = s_result_num++;

  mdo_result_data_t *new_result = &s_result_store[result];
  new_result->level = level;
  new_result->brief = brief;
  new_result->format_num = format_num;
  new_result->extended = extended;

  return result;
}

mdo_result_t
mdo_result_vformat (char *message, size_t *capacity, mdo_result_t result,
                    va_list args)
{
  /* TODO(marceline-cramer): Bounds checking */
  const char *format = s_result_store[result].brief;
  vsnprintf (message, *capacity, format, args);
  return result;
}

mdo_result_t
mdo_result_format (char *message, size_t *capacity, mdo_result_t result, ...)
{
  va_list args;
  va_start (args, result);
  mdo_result_vformat (message, capacity, result, args);
  va_end (args);

  return result;
}

mdo_result_t
mdo_result_log (const char *file, int line, mdo_result_t result, ...)
{
  /* TODO(marceline-cramer): Bounds checking */
  mdo_log_level_t level = s_result_store[result].level;
  char message[256];
  size_t capacity = sizeof (message);

  va_list args;
  va_start (args, result);
  mdo_result_vformat (message, &capacity, result, args);
  va_end (args);

  log_at (file, line, level, message);
  return result;
}

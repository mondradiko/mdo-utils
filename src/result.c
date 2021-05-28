/*! @file result.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "mondradiko/result.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_RESULT (1)
#define DEFAULT_CAPACITY (1024)

typedef struct mdo_result_data_s
{
  mdo_log_level_t level;
  bool success;
  char *brief;
  int format_num;
} mdo_result_data_t;

static mdo_result_data_t *s_result_store = NULL;
static size_t s_result_num = FIRST_RESULT;
static size_t s_result_capacity = DEFAULT_CAPACITY;

static mdo_result_data_t *
mdo_result_store_get (mdo_result_t result)
{
  if (!s_result_store)
    return NULL;
  if (result >= s_result_capacity)
    return NULL;
  return &s_result_store[result];
}

static void
mdo_result_store_reserve (size_t desired_capacity)
{
  if (!s_result_store)
    {
      if (desired_capacity > s_result_capacity)
        s_result_capacity = desired_capacity;

      s_result_store = calloc (sizeof (mdo_result_data_t), s_result_capacity);
      return;
    }

  if (desired_capacity <= s_result_capacity)
    return;

  size_t new_capacity = s_result_capacity;

  if (desired_capacity > new_capacity)
    new_capacity = desired_capacity;

  new_capacity += new_capacity >> 1;

  size_t store_size = new_capacity * sizeof (mdo_result_data_t);
  s_result_store = realloc (s_result_store, store_size);
  s_result_capacity = new_capacity;
}

mdo_result_t
mdo_result_create (mdo_log_level_t level, const char *brief, int format_num,
                   bool success)
{
  mdo_result_t result = s_result_num++;

  mdo_result_store_reserve (s_result_num);
  mdo_result_data_t *new_result = mdo_result_store_get (result);

  if (!new_result)
    {
      LOG_ERR ("failed to create new result");
      return result;
    }

  size_t brief_len = strlen (brief);
  char *new_brief = malloc (brief_len + 1);
  strcpy (new_brief, brief);

  new_result->level = level;
  new_result->success = success;
  new_result->brief = new_brief;
  new_result->format_num = format_num;

  return result;
}

void
mdo_result_cleanup ()
{
  if (s_result_store)
    {
      for (size_t i = 0; i < s_result_num; i++)
        {
          free (s_result_store[i].brief);
        }

      free (s_result_store);
    }

  s_result_store = NULL;
  s_result_num = FIRST_RESULT;
  s_result_capacity = DEFAULT_CAPACITY;
}

bool
mdo_result_success (mdo_result_t result)
{
  if (result == MDO_SUCCESS)
    return true;

  mdo_result_data_t *data = mdo_result_store_get (result);

  if (!data)
    return false;

  return data->success;
}

mdo_result_t
mdo_result_vformat (char *message, size_t capacity, mdo_result_t result,
                    va_list args)
{
  /* TODO(marceline-cramer): Bounds checking */
  const char *format = s_result_store[result].brief;
  vsnprintf (message, capacity, format, args);
  return result;
}

mdo_result_t
mdo_result_format (char *message, size_t capacity, mdo_result_t result, ...)
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
  mdo_result_vformat (message, capacity, result, args);
  va_end (args);

  log_at (file, line, level, message);
  return mdo_result_create (level, message, 0, mdo_result_success (result));
}

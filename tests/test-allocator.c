/*! @file test-allocator.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "test_common.h"

#include "allocator.h"

#define BUF_SIZE (1024)
#define BUF_NUM (128)

static void
test_malloc_and_free (void **state)
{
  const mdo_allocator_t *alloc = mdo_default_allocator ();
  void *buf_data = mdo_allocator_malloc (alloc, BUF_SIZE);
  assert_non_null (buf_data);
  mdo_allocator_free (alloc, buf_data);
}

static void
test_calloc_and_free (void **state)
{
  const mdo_allocator_t *alloc = mdo_default_allocator ();
  void *buf_data = mdo_allocator_calloc (alloc, BUF_NUM, BUF_SIZE);
  assert_non_null (buf_data);
  mdo_allocator_free (alloc, buf_data);
}

static void
test_realloc_and_free (void **state)
{
  const mdo_allocator_t *alloc = mdo_default_allocator ();
  void *buf_data = mdo_allocator_malloc (alloc, BUF_SIZE);
  assert_non_null (buf_data);
  buf_data = mdo_allocator_realloc (alloc, buf_data, BUF_SIZE * BUF_NUM);
  assert_non_null (buf_data);
  mdo_allocator_free (alloc, buf_data);
}

int
main (void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test (test_malloc_and_free),
    cmocka_unit_test (test_calloc_and_free),
    cmocka_unit_test (test_realloc_and_free),
  };

  return cmocka_run_group_tests (tests, NULL, NULL);
}

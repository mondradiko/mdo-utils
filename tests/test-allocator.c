/*! @file test-allocator.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "test_common.h"

#include "mondradiko/allocator.h"

#define BUF_SIZE (1024)
#define BUF_NUM (128)

Test (allocator, malloc_and_free)
{
  const mdo_allocator_t *alloc = mdo_default_allocator ();
  void *buf_data = mdo_allocator_malloc (alloc, BUF_SIZE);
  cr_assert_not_null (buf_data);
  mdo_allocator_free (alloc, buf_data);
}

Test (allocator, calloc_and_free)
{
  const mdo_allocator_t *alloc = mdo_default_allocator ();
  void *buf_data = mdo_allocator_calloc (alloc, BUF_NUM, BUF_SIZE);
  cr_assert_not_null (buf_data);
  mdo_allocator_free (alloc, buf_data);
}

Test (allocator, realloc_and_free)
{
  const mdo_allocator_t *alloc = mdo_default_allocator ();
  void *buf_data = mdo_allocator_malloc (alloc, BUF_SIZE);
  cr_assert_not_null (buf_data);
  buf_data = mdo_allocator_realloc (alloc, buf_data, BUF_SIZE * BUF_NUM);
  mdo_allocator_free (alloc, buf_data);
}

/*! @file allocator.c
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#include "mondradiko/allocator.h"

#include <stdlib.h>

#include "mondradiko/export.h"

struct mdo_allocator_s
{
  void *data;
  mdo_allocator_params_t params;
};

MDO_EXPORT void *
mdo_allocator_malloc (const mdo_allocator_t *alloc, size_t size)
{
  return alloc->params.malloc_cb (alloc->data, size);
}

MDO_EXPORT void *
mdo_allocator_calloc (const mdo_allocator_t *alloc, size_t num, size_t size)
{
  return alloc->params.calloc_cb (alloc->data, num, size);
}

MDO_EXPORT void *
mdo_allocator_realloc (const mdo_allocator_t *alloc, void *memory, size_t size)
{
  return alloc->params.realloc_cb (alloc->data, memory, size);
}

MDO_EXPORT void
mdo_allocator_free (const mdo_allocator_t *alloc, void *memory)
{
  alloc->params.free_cb (alloc->data, memory);
}

static void *
mdo_std_malloc (void *data, size_t size)
{
  return malloc (size);
}

static void *
mdo_std_calloc (void *data, size_t num, size_t size)
{
  return calloc (num, size);
}

static void *
mdo_std_realloc (void *data, void *memory, size_t size)
{
  return realloc (memory, size);
}

static void
mdo_std_free (void *data, void *memory)
{
  free (memory);
}

static const mdo_allocator_t s_default_allocator
    = { .params = { .malloc_cb = mdo_std_malloc,
                    .calloc_cb = mdo_std_calloc,
                    .realloc_cb = mdo_std_realloc,
                    .free_cb = mdo_std_free } };

MDO_EXPORT const mdo_allocator_t *
mdo_default_allocator ()
{
  return &s_default_allocator;
}

/*! @file allocator.h
  @brief Abstract interface for using specialized memory allocators.
  @copyright Copyright (c) 2021 Marceline Cramer
  SPDX-License-Identifier: MIT
 */

#pragma once

#include "mondradiko/result.h"

#include <stddef.h> /* for size_t */

/*! @typedef mdo_allocator_t
  @brief A general-purpose dynamic memory allocator. Different implementations
  can be chosen for different use-cases.
 */
typedef struct mdo_allocator_s mdo_allocator_t;

/*! @typedef mdo_allocator_params_t
  A helper structure for passing allocator implementation callbacks to
  #mdo_allocator_create().
 */
typedef struct mdo_allocator_params_s
{

  /*! @function malloc_cb
    @brief Allocates a block of memory from an allocator implementation.
    @param data The userdata set by #mdo_allocator_create().
    @param size The size of the memory to allocate.
    @return A pointer to the freshly allocated memory, or NULL on failure.
   */
  void *(*malloc_cb) (void *, size_t);

  /*! @function calloc_cb
    @brief Allocates an array of elements from an allocator implementation.
    @param data The userdata set by #mdo_allocator_create().
    @param num The number of elements to allocate.
    @param size The size of each element.
    @return A pointer to the freshly allocated array, or NULL on failure.
   */
  void *(*calloc_cb) (void *, size_t, size_t);

  /*! @function realloc_cb
    @brief Re-allocates memory from an allocator implementation.
    @param data The userdata set by #mdo_allocator_create().
    @param memory A pointer to the original memory.
    @param size The new size of the memory.
    @return A pointer to the re-allocated memory, or NULL on failure.
   */
  void *(*realloc_cb) (void *, void *, size_t);

  /*! @function free_cb
    @brief Frees memory from an allocator implementation.
    @param data The userdata set by #mdo_allocator_create().
    @param memory The memory to free.
   */
  void (*free_cb) (void *, void *);

  /*! @function finalize_cb
    Callback to clean up an allocator implementation. Called by
    #mdo_allocator_delete(). Intended to be used to free up any allocated
    resources or otherwise clean up an allocator implementation.
    @param data User-set data. See #mdo_allocator_create().
   */
  void (*finalize_cb) (void *);
} mdo_allocator_params_t;

/*! @function mdo_allocator_create
  @brief Creates an allocator implementation
  @param new_allocator The newly created allocator.
  @param alloc An allocator to create with, or NULL for the default.
  @param data Userdata to pass to the implementation callbacks.
  @param callbacks A structure containing the implementation callbacks.
  See #mdo_allocator_params_t.
  @return An #mdo_result_t.
 */
mdo_result_t mdo_allocator_create (mdo_allocator_t **, const mdo_allocator_t *,
                                   void *, mdo_allocator_params_t *);

/*! @typedef mdo_allocator_delete
  @brief Deletes an allocator implementation. Calls the
  #mdo_allocator_finalize_cb() callback to free up any resources used by the
  implementation.
  @param alloc The allocator to delete.
 */
void mdo_allocator_delete (mdo_allocator_t *);

/*! @function mdo_default_allocator
  @brief Retrieves the default allocator. For now, uses stdlib malloc(),
  free(), etc.
  @return A handle to the global default allocator.
 */
const mdo_allocator_t *mdo_default_allocator ();

/*! @function mdo_allocator_malloc
  @brief Allocates a block of memory from an allocator.
  @param alloc The allocator to allocate from.
  @param size The size of the memory to allocate.
  @return A pointer to the freshly allocated memory, or NULL on failure.
 */
void *mdo_allocator_malloc (const mdo_allocator_t *, size_t);

/*! @function mdo_allocator_calloc
  @brief Allocates an array of elements from an allocator.
  @param alloc The allocator to allocate from.
  @param num The number of elements to allocate.
  @param size The size of each element.
  @return A pointer to the freshly allocated array, or NULL on failure.
 */
void *mdo_allocator_calloc (const mdo_allocator_t *, size_t, size_t);

/*! @function mdo_allocator_realloc
  @brief Re-allocates memory from an allocator.
  @param alloc The allocator to re-allocate from.
  @param memory A pointer to the original memory.
  @param size The new size of the memory.
  @return A pointer to the re-allocated memory, or NULL on failure.
 */
void *mdo_allocator_realloc (const mdo_allocator_t *, void *, size_t);

/*! @function mdo_allocator_free
  @brief Frees memory from an allocator.
  @param alloc The allocator to free from.
  @param memory The memory to free.
 */
void mdo_allocator_free (const mdo_allocator_t *, void *);

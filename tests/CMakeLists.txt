# Copyright (c) 2021 Marceline Cramer
# SPDX-License-Identifier: MIT

include (mondradiko_create_test)

mondradiko_create_test (${MDO_UTILS_OBJ} allocator test-allocator.c)
mondradiko_create_test (${MDO_UTILS_OBJ} log test-log.c)
mondradiko_create_test (${MDO_UTILS_OBJ} result test-result.c)

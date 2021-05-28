# Copyright (c) 2021 Marceline Cramer
# SPDX-License-Identifier: MIT

include (mondradiko_create_test)

mondradiko_create_test (mdo-utils allocator test-allocator.c)
mondradiko_create_test (mdo-utils log test-log.c)
mondradiko_create_test (mdo-utils result test-result.c)

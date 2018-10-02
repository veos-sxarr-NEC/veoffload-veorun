/* Copyright (C) 2017-2018 by NEC Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/**
 * @file veorun.h
 * @brief header to define a data structure transferred from veorun
 */

#ifndef __VE_VEORUN_H__
#define __VE_VEORUN_H__

#define VEORUN_SYMNAME_LEN_MAX (255)
#define VEORUN_VERSION (0x1004F4556UL) /* 'V' 'E' 'O' \0 1 */

#ifdef __cplusplus
extern "C" {
#endif

struct veo__helper_functions {
  uint64_t version;
  uint64_t load_library;
  uint64_t alloc_buff;
  uint64_t free_buff;
  uint64_t find_sym;
  uint64_t create_thread;
  uint64_t call_func;
  uint64_t exit;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif

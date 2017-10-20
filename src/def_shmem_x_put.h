/*
 * Copyright (c) 2016-2017 U.S. Army Research laboratory. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * This software was developed by Brown Deer Technology, LLC. with Copyright
 * assigned to the US Army Research laboratory as required by contract.
 */

#ifndef _def_shmem_x_put_h
#define _def_shmem_x_put_h
#include "shmemx.h"

#define SHMEM_X_PUT_NBI(N,T,S) \
SHMEM_SCOPE void \
shmem_##N##_nbi (T *dest, const T *source, size_t nelems, int pe) \
{ shmemx_memcpy_nbi(shmem_ptr(dest,pe), (void*)source, nelems << S); } \
static void \
shmem_ctx_##N##_nbi (shmem_ctx_t ctx, T *dest, const T *source, size_t nelems, int pe) \
{ shmem_##N##_nbi(dest, source, nelems, pe); }

#define ALIAS_SHMEM_X_PUT_NBI(N,T,A) \
SHMEM_SCOPE void \
shmem_##N##_nbi (T *dest, const T *source, size_t nelems, int pe) \
__attribute__((alias("shmem_" #A "_nbi"))); \
static void \
shmem_ctx_##N##_nbi (shmem_ctx_t ctx, T *dest, const T *source, size_t nelems, int pe) \
__attribute__((alias("shmem_ctx_" #A "_nbi")));

#define SHMEM_X_PUT(N,T,S) \
SHMEM_SCOPE void \
shmem_##N (T *dest, const T *source, size_t nelems, int pe) \
{ shmemx_memcpy(shmem_ptr(dest,pe), (void*)source, nelems << S); } \
static void \
shmem_ctx_##N (shmem_ctx_t ctx, T *dest, const T *source, size_t nelems, int pe) \
{ shmem_##N##_nbi(dest, source, nelems, pe); }

#define ALIAS_SHMEM_X_PUT(N,T,A) \
SHMEM_SCOPE void \
shmem_##N (T *dest, const T *source, size_t nelems, int pe) \
__attribute__((alias("shmem_" #A))); \
static void \
shmem_ctx_##N (shmem_ctx_t ctx, T *dest, const T *source, size_t nelems, int pe) \
__attribute__((alias("shmem_ctx_" #A)));

#endif


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

#ifndef _def_shmem_x_atomic_fetch_or_h
#define _def_shmem_x_atomic_fetch_or_h

#define SHMEM_X_ATOMIC_FETCH_OR(N,T) \
static T \
__shmem_##N##_atomic_fetch_or (T *ptr, T value, int pe) \
{ \
	long* x = (long*)shmem_ptr((void*)&__shmem.lock_atomic_##N, pe); \
	__shmem_set_lock(x); \
	T r = *ptr; \
	T remote = r | value; \
	*ptr = remote; \
	__shmem_clear_lock(x); \
	return r; \
} \
SHMEM_SCOPE T \
shmem_##N##_atomic_fetch_or (T *dest, T value, int pe) \
{ \
	T* ptr = (T*)shmem_ptr((void*)dest, pe); \
	return __shmem_##N##_atomic_fetch_or(ptr, value, pe); \
}

#define ALIAS_SHMEM_X_ATOMIC_FETCH_OR(N,T,A) \
SHMEM_SCOPE T \
shmem_##N##_atomic_fetch_or (T *dest, T value, int pe) \
__attribute__((alias("shmem_" #A "_atomic_fetch_or"))); \
static T \
shmem_ctx_##N##_atomic_fetch_or (shmem_ctx_t ctx, T *dest, T value, int pe) \
__attribute__((alias("shmem_ctx_" #A "_atomic_fetch_or")));

#endif

#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "util.h"

#define RC(T) CAT(Rc_, T)

#define RC_DESTRUCTOR(T) CAT(RC(T),_destructor_t)
#define RC_TYPE_DESTRUCTOR_DEC(T) typedef void (*RC_DESTRUCTOR(T))(T* ptr)

#define RC_TYPE_DEC(T) typedef struct { \
		size_t n_refs; \
		T* p_raw; \
		RC_DESTRUCTOR(T) destructor; \
	} RC(T);

typedef enum {
	RC_RESULT_SUCCESS,
	RC_RESULT_FAILURE_ALLOC
} RcResult;

static inline void rc_check_result(RcResult result) {
	if(result != RC_RESULT_SUCCESS) {
		const char* result_str = NULL;
		switch(result) {
			case RC_RESULT_FAILURE_ALLOC:
				result_str = "RC_RESULT_FAILURE_ALLOC";
				break;
		}
		DIE("%s: failure result: %s\n", __func__, result_str);
	}
}

#define RC_METHOD_NAME(T,N) CAT(CAT(RC(T),_),N)

#define RC_NEW(T) RC_METHOD_NAME(T,new)
#define RC_NEW_DEC(T) RcResult RC_NEW(T)(RC(T)** out, T* init_value, RC_DESTRUCTOR(T) destructor)
#define RC_NEW_DEF(T) RC_NEW_DEC(T) {\
		RC(T)* local_out = (RC(T)*) malloc(sizeof(RC(T))); \
		if(local_out == NULL) { \
			return RC_RESULT_FAILURE_ALLOC; \
		} \
		local_out->n_refs = 1; \
		local_out->p_raw = init_value; \
		local_out->destructor = destructor; \
		*out = local_out; \
		return RC_RESULT_SUCCESS;\
	}

#define RC_PASS(T) RC_METHOD_NAME(T,pass)
#define RC_METHOD_PASS_DEC(T) RC(T)* RC_PASS(T)(RC(T)* self)
#define RC_METHOD_PASS_DEF(T) RC_METHOD_PASS_DEC(T) { \
		if(self->n_refs <= 0) { \
			DIE("%s: managed pointer has already been freed.\n", __func__); \
		} \
		self->n_refs++; \
		return self; \
	}
#define RC_DROP(T) RC_METHOD_NAME(T,drop)
#define RC_METHOD_DROP_DEC(T) void RC_DROP(T)(RC(T)* self)
#define RC_METHOD_DROP_DEF(T) RC_METHOD_DROP_DEC(T) { \
		self->n_refs--; \
		if(self->n_refs <= 0) { \
			self->destructor(self->p_raw); \
			free(self); \
		} \
	}

#define RC_GET(X) (X)->p_raw

#define RC_DEC(T) \
	RC_TYPE_DESTRUCTOR_DEC(T); \
	RC_TYPE_DEC(T); \
	RC_NEW_DEC(T); \
	RC_METHOD_PASS_DEC(T); \
	RC_METHOD_DROP_DEC(T);
#define RC_DEF(T) \
	RC_NEW_DEF(T) \
	RC_METHOD_PASS_DEF(T) \
	RC_METHOD_DROP_DEF(T)


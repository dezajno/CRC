#include "custom_type.h"

#include <stdlib.h>
#include <stdio.h>

struct CustomType {
	int test_int;
	float test_float;
};

RC_DEF(CustomType)

void CustomType_new(CustomType** self_out) {
	CustomType* self = (CustomType*)malloc(sizeof(CustomType));
	// Ignore self == NULL for simplicity
	self->test_int = 42;
	self->test_float = 4.2;
	*self_out = self;
	printf("Instance of CustomType created\n");
}

void CustomType_print(CustomType* self) {
	printf("CustomType(%d,%.2f)\n", self->test_int, self->test_float);
}

void CustomType_destroy(CustomType* self) {
	free(self);
	printf("Instance of CustomType destroyed\n");
}


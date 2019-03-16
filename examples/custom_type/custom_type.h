#pragma once

#include "rc.h"

typedef struct CustomType CustomType;
RC_DEC(CustomType)

void CustomType_new(CustomType** self_out);
void CustomType_print(CustomType* self);
void CustomType_destroy(CustomType* self);


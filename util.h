#pragma once

#define DIE(S...) \
	fprintf(stderr, S); \
	abort();

#define CAT(a,b) __CAT(a,b)
#define __CAT(a,b) a ## b


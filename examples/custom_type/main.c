#include "custom_type.h"

#include <stdlib.h>
#include <stdio.h>

// RC(CustomType) is the type of the reference counter for our CustomType
void custom_fn(RC(CustomType)* param) {
	// managed ptr can be obtained via RC_GET
	CustomType_print( RC_GET(param) );
	// drop current reference
	RC_DROP(CustomType)(param);
}

int main() {
	// create instance of custom type
	CustomType* raw_ptr;
	CustomType_new(&raw_ptr);
	
	// wrap instance of custom type into reference counter (rc)
	RC(CustomType)* rc_ptr;
	// abort if rc was not successfully created
	rc_check_result( RC_NEW(CustomType)(&rc_ptr, raw_ptr, CustomType_destroy) );
	
	// call function using RC_PASS for passing the reference counter
	printf("Before custom_fn\n");
	custom_fn( RC_PASS(CustomType)(rc_ptr) );
	printf("After custom_fn\n");

	// end of main function: drop current rc. This is done whenever
	// a rc goes out of scope
	RC_DROP(CustomType)(rc_ptr);
	// destroy rc itself. This is only done once for one rc
	RC_DESTROY(CustomType)(rc_ptr);
	return EXIT_SUCCESS;
}


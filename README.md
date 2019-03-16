# CRC - Reference counting in C

CRC provides reference counted pointers at a runtime cost.
In order to make the reference counters type safe, functions and types for the
reference counting are not defined directly. Instead, macros are provided that
expand to the declarations and definitions for reference counting of a specific
type.

## Files
- [rc.h](./rc.h): Main file, defining "generic" macros that expand to declarations and 
definitions for custom types.
- [util.h](./util.h): Definies generally usable utilities such as the `CAT` macro for
concatenation.

## Examples
Examples are provided in the <./examples> sub-folder. Each example is in its
own folder. A Makefile is provided for each example. Building the examples has
been tested under Xubuntu 18.04 using gcc 7.3 and the c11 standard.


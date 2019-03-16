# CRC - Reference counter in c

CRC provides reference counted pointers at a runtime cost.
In order to make the reference counters type safe, functions and types for the reference counting are not defined directly. Instead, macros are provided that expand to the declarations and definitions for reference counting of a specific type.


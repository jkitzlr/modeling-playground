# TODOs

Most important; CMake!

## Things to do

1. Floating legs/anything with payments based on some index (e.g. linkers, TRS, etc.) should have the necessary MarketDataId values as members--then the base leg can just include MarketData (optional?) in the signature of all of its calc methods.

## Questions/ things to figure out

1. Need to think it makes sense for Tenor to be abstract--only reason is for BusDays as would prefer to store the buscal as an internal detail to keep it from leaking into the interface. For now, Schedule will take in an int which is a number of months...need some parsing logic to convert that primitive into the appropriate instance. TBD...

## General; C++ questions

Because I'm a fucking noob...

1. Should smart pointers be passed by value or by reference? At least for shared_ptr, seems like the copy into the function's frame would cause the ref counter to +; but does that matter for this purpose?

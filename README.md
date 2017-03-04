# INMPI

This is a collection of utility functions that are useful in supercomputing
and mostly numerical simulation. The code is sufficiently obfuscated so that
it is not modified, as this is not a collaborative project.

There are two experimental elements in this distribution: a distributed parallel
mutual exclusion variable and a distributed parallel semaphore. In both cases
CPU resources are consumed on the MPI process that maintains the elements, you
have been warned.

Updated: IN 2017/03/03


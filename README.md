# parallel-pi
A program, developed in C, that uses pthreads and the Monte Carlo method to estimate pi.

This program deploys 4 pthreads in parallel to estimte pi using the Monte Carlo method. The threads generate a number of random points on a Cartesian plane, then count how many fall within the defined circle. The parent thread then calculates and outputs the estimate value of pi.

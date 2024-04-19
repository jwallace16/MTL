# MTL
Matrix Template Library

This header-only library provides template methods for matrix operations with specific focus towards use in flight dynamics and simulation.

# Setup, Build, and Test
Ensure the following software are installed: Make, CMake, GCC, and Git.

## Clone this repo
    git clone git@github.com:jwallace16/MTL.git

## Generate Makefiles
    cmake -B build

## Build and Run Unit Tests
    cd build
    make ENABLE_UNIT_TESTS true
    cd unit-test
    ./TestMatrix

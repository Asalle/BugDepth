#!/bin/bash

# Remove the '-DBUILD_TESTING:BOOL=TRUE' flag if you don't want the test to be built
#rm -rf build &> /dev/null
#mkdir build
cd build
cmake ..
#cmake -DBUILD_TESTING:BOOL=TRUE ..
make

#!/bin/bash

export Qt5_DIR="/opt/qt/5.10.1/gcc_64/lib/cmake/Qt5/"

# Remove the '-DBUILD_TESTING:BOOL=TRUE' flag if you don't want the test to be built
#rm -rf build &> /dev/null
#mkdir build
cd build
#cmake ..
cmake -DBUILD_TESTING:BOOL=FALSE ..
make

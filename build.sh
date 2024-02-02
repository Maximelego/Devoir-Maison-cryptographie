#!/bin/sh
# Checking if the build directory must be re-created.
if test -d ./build
then 
    rm -r build
fi

# Creating the build folder.
mkdir build
cd build

# Building project
cmake ..
make
#!/bin/bash

set -e

echo "Building..."

if [ -d "build" ]; then
    rm -rf build
fi

mkdir -p build
cd build
cmake .. > /dev/null
make

echo ""
echo "Build successful!"
echo "Executable: build/describe_object"
echo ""
echo "Examples:"
echo "  ./build/describe_object circle 5"
echo "  ./build/describe_object square 4"
echo "  ./build/describe_object rect 3 7"

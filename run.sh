#!/bin/bash

cd build
cmake --build _builds --config Release
cd _builds
./aly
cd .. && cd ..
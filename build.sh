#/usr/bin/bash

rm -rf ./build/ && cmake -B build -S ./firmware && cmake --build build
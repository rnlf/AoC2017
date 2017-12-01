#!/bin/bash

g++ -std=c++17 -O3 -o day_01_1 day_01.cpp
g++ -std=c++17 -O3 -o day_01_2 -DPART2 day_01.cpp

./day_01_1 input
./day_01_2 input

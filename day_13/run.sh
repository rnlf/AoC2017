#!/bin/bash -e

CXX=clang++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_13_1 day_13.cpp
#$CXX -DPART2 -std=c++17 -Ofast -o day_13_2 day_13.cpp


$GDB ./day_13_1 input
#$GDB ./day_13_2 input

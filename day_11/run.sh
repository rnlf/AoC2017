#!/bin/bash -e

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_11_1 day_11.cpp
#$CXX -DPART2 -std=c++17 -Ofast -o day_11_2 day_11.cpp


$GDB ./day_11_1 input
#$GDB ./day_11_2 input

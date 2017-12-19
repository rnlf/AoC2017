#!/bin/bash -e

CXX=clang++

#GDB="gdb --args"

$CXX -std=c++17 -g -o day_19_1 day_19.cpp
#$CXX -DPART2 -std=c++17 -Ofast -o day_19_2 day_19.cpp


$GDB ./day_19_1 input

#$GDB ./day_19_2 

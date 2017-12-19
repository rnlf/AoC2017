#!/bin/bash -e

CXX=clang++

#GDB="gdb --args"

$CXX -std=c++17 -g -o day_18_1 day_18.cpp
#$CXX -DPART2 -std=c++17 -Ofast -o day_18_2 day_18.cpp


$GDB ./day_18_1 

#$GDB ./day_18_2 

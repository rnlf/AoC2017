#!/bin/bash -e

CXX=clang++

#GDB="gdb --args"

INPUT=stpzcrnm
#INPUT=flqrgnkx

$CXX -std=c++17 -g -o day_14_1 day_14.cpp
#$CXX -DPART2 -std=c++17 -Ofast -o day_14_2 day_14.cpp


$GDB ./day_14_1 $INPUT
#$GDB ./day_14_2 input

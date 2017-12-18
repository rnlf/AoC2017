#!/bin/bash -e

CXX=clang++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_16_1 day_16.cpp
$CXX -DPART2 -std=c++17 -Ofast -o day_16_2 day_16.cpp


$GDB ./day_16_1 input
$GDB ./day_16_2 input

#!/bin/bash -e

CXX=clang++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_15_1 day_15.cpp
$CXX -DPART2 -std=c++17 -Ofast -o day_15_2 day_15.cpp


$GDB ./day_15_1
$GDB ./day_15_2

#!/bin/bash -e

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_10_1 day_10.cpp
$CXX -DPART2 -std=c++17 -Ofast -o day_10_2 day_10.cpp


$GDB ./day_10_1 input
$GDB ./day_10_2 input

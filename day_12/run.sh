#!/bin/bash -e

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_12_1 day_12.cpp
$CXX -DPART2 -std=c++17 -Ofast -o day_12_2 day_12.cpp


$GDB ./day_12_1 input
$GDB ./day_12_2 input

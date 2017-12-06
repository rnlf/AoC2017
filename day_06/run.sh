#!/bin/bash -e

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_06_1 day_06.cpp
$CXX -std=c++17 -Ofast -o day_06_2 -DPART2 day_06.cpp


$GDB ./day_06_1 input
$GDB ./day_06_2 input

#!/bin/bash -e

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_05_1 day_05.cpp
$CXX -std=c++17 -Ofast -o day_05_2 -DPART2 day_05.cpp


$GDB ./day_05_1 input
$GDB ./day_05_2 input

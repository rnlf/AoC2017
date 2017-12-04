#!/bin/bash -e

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_04_1 day_04.cpp
$CXX -std=c++17 -Ofast -o day_04_2 -DPART2 day_04.cpp


$GDB ./day_04_1 input
$GDB ./day_04_2 input

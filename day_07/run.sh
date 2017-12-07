#!/bin/bash -e

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_07_1 day_07.cpp


$GDB ./day_07_1 input

#!/bin/bash -e

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_08_1 day_08.cpp


$GDB ./day_08_1 input

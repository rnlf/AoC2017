#!/bin/bash -e

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_09_1 day_09.cpp


$GDB ./day_09_1 input

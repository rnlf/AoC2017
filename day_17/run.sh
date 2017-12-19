#!/bin/bash -e

CXX=clang++

#GDB="gdb --args"

INPUT=329

$CXX -std=c++17 -Ofast -o day_17_1 day_17.cpp
$CXX -DPART2 -std=c++17 -Ofast -o day_17_2 day_17.cpp


$GDB ./day_17_1 $INPUT
#$GDB ./day_17_2 input

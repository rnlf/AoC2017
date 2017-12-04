#!/bin/bash

CXX=g++

#GDB="gdb --args"

$CXX -std=c++17 -Ofast -o day_03_1 day_03.cpp
$CXX -std=c++17 -Ofast -o day_03_2 -DPART2 day_03.cpp


$GDB ./day_03_1 265149
$GDB ./day_03_2 265149

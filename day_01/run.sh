#!/bin/bash

CXX=clang++

$CXX -std=c++17 -Ofast -o day_01_1 day_01.cpp
$CXX -std=c++17 -Ofast -o day_01_2 -DPART2 day_01.cpp

./day_01_1 input
./day_01_2 input

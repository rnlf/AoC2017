#!/bin/bash

CXX=g++

$CXX -std=c++17 -Ofast -o day_02_1 day_02.cpp
$CXX -std=c++17 -Ofast -o day_02_2 -DPART2 day_02.cpp

./day_02_1 input
./day_02_2 input

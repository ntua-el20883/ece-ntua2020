#!/bin/bash

program="shops"
g++ -o $program ../shops.cpp
test_dir="Shops"
start=1
end=25

source ../../test.sh


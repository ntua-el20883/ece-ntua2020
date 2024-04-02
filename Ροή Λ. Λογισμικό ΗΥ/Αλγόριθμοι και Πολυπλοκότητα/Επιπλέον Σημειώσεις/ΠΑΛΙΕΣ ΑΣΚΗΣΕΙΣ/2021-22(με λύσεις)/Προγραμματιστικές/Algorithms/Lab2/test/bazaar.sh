#!/bin/bash

program="bazaar"
g++ -o $program ../bazaar.cpp
test_dir="Bazaar"
start=0
end=19

source ../../test.sh

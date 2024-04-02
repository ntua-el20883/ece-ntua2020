#!/bin/bash

program="teleports"
g++ -o $program ../teleports.cpp
test_dir="Teleports"
start=0
end=33

source ../../test.sh


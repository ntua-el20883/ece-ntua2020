#!/bin/bash

program="salaries"
g++ -o $program ../salaries.cpp
test_dir="Salaries"
start=1
end=25

source ../../test.sh

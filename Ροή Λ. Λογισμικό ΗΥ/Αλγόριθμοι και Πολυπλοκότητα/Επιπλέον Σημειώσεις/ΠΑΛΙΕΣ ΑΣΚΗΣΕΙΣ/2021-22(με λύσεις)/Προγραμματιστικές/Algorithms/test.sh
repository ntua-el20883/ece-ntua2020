#!/bin/bash

flag=0
for i in $( eval echo "{$start..$end}" )
	do 
		program_output=$( "./$program" < "$test_dir/input$i.txt" )
		expected_output=$( cat "$test_dir/output$i.txt" )
		if [ $program_output != $expected_output ] 
		then
			flag=1
			echo "Input $i:"
			echo "Expected $expected_output"
			echo "But got $program_output"
			echo ---------
		fi
	done
if [ $flag != 1 ]; then echo Everything good; fi


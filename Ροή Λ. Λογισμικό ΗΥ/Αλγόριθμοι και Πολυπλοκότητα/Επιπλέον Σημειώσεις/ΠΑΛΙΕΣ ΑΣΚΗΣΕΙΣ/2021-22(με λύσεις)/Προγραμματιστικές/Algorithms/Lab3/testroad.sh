#!/bin/bash

flag=0
for i in {1..20}
	do 
		echo "Testcase $i"
		diff -u test/roadtrip/output$i.txt <(./roadtrip < "test/roadtrip/input$i.txt")
	done

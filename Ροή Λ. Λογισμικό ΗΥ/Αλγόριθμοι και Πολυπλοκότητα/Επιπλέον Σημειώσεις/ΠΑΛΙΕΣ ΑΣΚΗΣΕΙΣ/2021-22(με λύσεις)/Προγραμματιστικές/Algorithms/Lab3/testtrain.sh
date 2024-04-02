#!/bin/bash

flag=0
for i in {0..20}
	do 
		echo "Testcase $i"
		diff -u test/traintrips/output$i.txt <(./traintrips < "test/traintrips/input$i.txt")
	done
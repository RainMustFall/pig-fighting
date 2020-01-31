#!/bin/bash

for file in `find -name "*.cpp"`
do
	echo 
	echo
	echo $file
	echo ------------------------
	./cpplint_light.py $file
done

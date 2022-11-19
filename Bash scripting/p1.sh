#!/bin/bash
for i in {1..5}
do 
for((j=1; j <=$((5 - $i));j++))
do 
echo -n " "
done
for((k=1;k<=$i;k++))
do
echo -n "$i "
done
echo
done
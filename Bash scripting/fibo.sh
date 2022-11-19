#!/bin/bash
echo -n "Enter the number (to find the nth Fibonacci number, starting from 0) : "
read number
fibo(){
    num=$1
    if [[ num -le 1 ]] 
    then echo $num
    else echo $(( $(fibo $((num - 1)) ) + $(fibo $((num - 2)) ) )) 
    fi
}
echo -n "$number th Fibonacci number is : "
fibo $number 
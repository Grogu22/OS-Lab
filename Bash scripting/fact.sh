#!/bin/bash
echo -n "Enter the number to find factorial of : "
read number
myfact(){
    if [[ $1 -le 1 ]]
    then echo $1
    else echo $(($1 * $(myfact $(( $1 - 1 )) )))
    fi
}
echo -n "factorial is : "
myfact $number
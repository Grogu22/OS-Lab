#!/bin/bash
pow(){
    num=$1
    for((i=1; i<$2 ;i++))
    do num=$(($num * $1))
    done
    echo $num
}
echo -n "$1 to the power $2 is : "
echo $(pow $1 $2)
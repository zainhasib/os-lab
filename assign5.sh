#! /bin/bash

read -p "Enter the array : " -a array

size=${#array[@]}

for (( i=0;i<$size;i++ ))
do
    t=$(($i+1))
    se=${#array[@]}
    for (( j=$t;j<$se;j++ ))
    do
        if [[ ${array[$i]} == ${array[$j]} ]]
        then
            for (( k=$j;k<$size;k++ ))
            do
                index=$(($k + 1))
                array[$k]=${array[$index]}
            done
            size=$(($size-1))
            j=$(($j-1))
        fi
    done
done

echo ${array[@]}

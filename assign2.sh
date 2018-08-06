#! /bin/bash

read -p "Enter the array : " -a array

max=0
min=10000

echo ${array[2]}

for (( i=0;i<${#array[@]};i++ ))
do 
    if (( ${array[$i]} > $max ))
    then 
        max=${array[$i]}
    fi
    if (( ${array[$i]} < $min ))
    then 
        min=${array[$i]}
    fi
done

echo "Min is $min and Max is $max"
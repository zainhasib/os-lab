#! /bin/bash

read -p "Enter the array : " -a array

num=${#array[@]}
n=$(($num / 2))

for (( i=0;i<$n;i++ ))
do
    res=$(($num - $i - 1))
    temp=${array[$i]}
    array[$i]=${array[$res]}
    array[$res]=$temp
done

echo ${array[@]}
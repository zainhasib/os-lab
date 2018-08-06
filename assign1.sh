#! /bin/bash

read -p "Enter the number of elements : " num

array=()

for (( i=0;i<$num;i++ ))
do
    read -p "Enter element : " a
    array+=($a)
done

echo ${array[@]}
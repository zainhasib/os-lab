#! /bin/bash

num=$1
i=$(($num-1))
flag=0

for (( i ; i>1 ;  i-- ))
do
    r=$(($num % i))
    if [ $r -eq 0 ]
    then
        flag=1
        break
    fi
done

if [[ $flag -eq 1  ]]
then 
    echo "Non-prime"
else 
    echo "Prime"
fi




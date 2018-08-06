#! /bin/bash

file=$1

if [ -f $file ]
then 
    echo "File is present"
    t=`ls -l $file | cut -c2-4`
    echo "The permissions are : " $t

    echo "Removing the write and execute permission"

    p=(`chmod -wx $file`)
else 
    echo "File isn't present"
fi
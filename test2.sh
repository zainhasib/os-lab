#! /bin/bash

file=$1

if [ -f $file ]
then
    line=0
    for word in `cat -nE $file`
    do
        t=(`cat -nE $file`)
        if [[ $word == "$" ]]
        then 
            line=$(($line + 1))
        fi
    done
    
    for l in {$line...1}
    do
        echo  `cat -nE $file | head -$l | tail -1`
    done


else 
    echo "File isn't present"
fi
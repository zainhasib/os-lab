#! /bin//bash

read -p "Enter the array : " -a array

max=${array[0]}
min=${array[0]}

for (( i=0;i<${#array[@]};i++ ))
do 
    if [[ ${array[$i]} > $max ]]
    then 
        max=${array[$i]}
    fi
    if [[ ${array[$i]} < $min ]]
    then 
        min=${array[$i]}
    fi
done

echo "Maximum is : $max"
echo "Minimum is : $min"

maxtwo=0
mintwo=1000

if [ ${#array[@]} -eq 1 ]
then 
    echo "Only one Element"
    echo "Second Maximum : ${array[0]}"
    echo "Second Minimum : ${array[0]}"
else 
    for (( j=0;j<${#array[@]};j++ ))
    do  
        if (( ${array[$j]} > $maxtwo && ${array[$j]} < $max ))
        then 
            maxtwo=${array[$j]}
        fi
        if (( ${array[$j]} < $mintwo && ${array[$j]} > $min ))
        then 
            mintwo=${array[$j]}
        fi
    done
    echo "Second Maximum : $maxtwo"
    echo "Second Minimum : $mintwo"
fi
  
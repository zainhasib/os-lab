#! /bin/bash

x=("$@")
count=$#

date=$1
month=$2
year=$3

num=(`cal $month $year | head -3 | tail -1`)
c=0
start=1

c=${#num[*]}


if [ $c -eq 1 ] 
then 
    start=7
elif [ $c -eq 2 ]
then
    start=6
elif [ $c -eq 3 ]
then
    start=5
elif [ $c -eq 4 ]
then
    start=4
elif [ $c -eq 5 ]
then
    start=3
elif [ $c -eq 6 ]
then
    start=2
elif [ $c -eq 7 ]
then
    start=1
fi


#echo $start
end=$(($start - 1))
flag=0

for x in 3 4 5 6 7
do  
    for y in `cal $month $year | head -$x | tail -1`
    do
        end=$(($end + 1))
        if [ $end -gt 7 ]
        then 
            end=$(($end % 7))
        fi
        if [[ $date == $y ]]
        then
            flag=1
            break 
        fi
    done
    if [ $flag -ne 0 ]
    then 
        break
    fi
done

case $end in 
    1 ) 
        echo "Sunday" ;;
    2 ) 
        echo "Monday" ;;
    3 ) 
        echo "Tuesday" ;;
    4 ) 
        echo "Wednesday" ;;
    5 ) 
        echo "Thursday" ;;
    6 ) 
        echo "Friday" ;;
    7 ) 
        echo "Saturday" ;;
esac







